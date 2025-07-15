#include <gtest/gtest.h>
#include <linux/can.h>
#include <memory>
#include <cstring>
#include <chrono>
#include <thread>
#include <iostream>

//#include <linux/socketcan/provider.h>
#include <sockcanpp/can_driver.hpp>

// Using socketcan to pipe to vcan0 interface on Linux for simulation purposes
// Using GTest C++ testing framework
using namespace can::providers::os::socketcan;
using namespace can::protocol::frame;

class CANCommunicationTest : public ::testing::Test {
protected:
    static std::shared_ptr<CANBus> m_cb;
    static std::shared_ptr<sockcanpp::CanDriver> m_testDriver;

    static void SetUpTestSuite() {
        Options *o = new Options();
        o->canInterface = "vcan0";
        o->canProtocol = CAN_RAW;
        m_cb = std::make_shared<CANBus>(nullptr, o);
        m_testDriver = std::make_shared<sockcanpp::CanDriver>("vcan0", CAN_RAW, 0, 0);
    }

    static void TearDownTestSuite() {
        m_cb.reset();
        m_testDriver.reset();
    }

    void SetUp() override {
        while (m_cb->hasMessage()) {
            m_cb->readMessage();
        }
    }
};

std::shared_ptr<CANBus> CANCommunicationTest::m_cb = nullptr;
std::shared_ptr<sockcanpp::CanDriver> CANCommunicationTest::m_testDriver = nullptr;

TEST_F(CANCommunicationTest, Linear_SoC_Depletion_Shutdown){
    std::cout << "[TEST] Starting Linear SoC Battery Depletion Shutdown Trigger Simulation" << std::endl;

    // from 100% to 0%
    for(int soc = 100; soc >= 0; --soc){
      // simulate OrionBMS 2 sending SoC at each % level
      can_frame bms_msg{};
      bms_msg.can_id = 0x400; // arbitrary id 
      bms_msg.can_dlc = 8;
      std::memset(bms_msg.data, 0, 8); // static alloc
      bms_msg.data[0] = static_cast<uint8_t>(soc); // first byte contains SoC
      
      // send to vcan0
      m_testDriver->sendMessage(bms_msg);
      std::this_thread.sleep_for(std::chrono::milliseconds(20));
      
      // dont need to read if there is no message on the bus 
      if(!m_cb->hasMessage){
        continue;
      }
      
      // otherwise there is a message, read it
      frame_res res = m_cb->readMessage();
      ASSERT_TRUE(res.hasValue());
      frame_t rx = res.value();

      std::cout << "[BMS] Send SoC = " << soc << "%, ";
      std::cout << "[CENTRAL ECU] Recieved SoC = " << static_cast<int>(rx.data[0]) << "%" << std::endl;

      // if we go hit 18% SoC 
      if(rx.data[0] <= 18){
        std::cout << "[CENTRAL ECU] LOW BATTERY DETECTED ! SENDING SHUTDOWN SIGNAL TO MOTOR CONTROLLER" << std::endl;
        
        // send shutdown command from ECU to Sevcon Gen4 Motor Controller via SDO according to Canopen DSP402
        // Canopen 6040h `controlword` describes a 16bit field to control state machine of CiA 402 motor Controller.
        // Description of State Machine can be found at DSP402: http://overpof.free.fr/schneider/CAN%20&%20CANopen/CANopen/%A9CiA%20CANCANopen%20CD%20V5.1/standard/dsp402.pdf
        // Sections: 7.2.1 and 10.1.1 Figure 7
        // Description of controlword 6040h: https://www.servotronix.com/html/stepIM_Help/HTML/Documents/6040hcontrolword.htm
        // Also see Sections 10.3.1 Table 6 for more information.
        // we want to transition from state Switched On to state Switch On Disabled

        // So to transition from Switch On (xxxx xxxx x01x 0011) to Switch On Disabled (xxxx xxxx x1xx 0000)
        // we need to send 0x0006 to controlword - as Bit 0 will turn off "switch on" while Bit 1 "enable voltage" and Bit 2 "quick stop" are active
        // See Section 10.1.1.2 State Transition 10

        const uint16_t sevcon_node_id = 500;
        const uint16_t sdo_tx_id = 0x600 + sevcon_node_id;  // 0x7F4
        const uint16_t sdo_rx_id = 0x580 + sevcon_node_id;  // 0x774

        uint8_t payload[8] = {
          0x2B, // commmand specifier (SDO write 2 bytes)
          0x40, // lsb (0x6040)
          0x60, // msb
          0x00, // subindex
          0x06, // value lsb (0x0006)
          0x00, // value msb
          0x00, // padding
          0x00  // padding
        };

        frame_res shutdown_msg = create({
            sdo_tx_id,  // id       
            false,      // rtr 
            false,      // ide 
            false,      // edl 
            8,          // dlc 
            (void*)payload, // data 
            dlc_t(8),       // dlc max
            8               // acc data size 
        }); 
      
        ASSERT_TRUE(shutdown_msg.has_value());

        m_cb->enqueue(shutdown_msg.value());
        m_cb->handleQueue();
        std::cout << "[CENTRAL ECU] Sent SDO shutdown to Sevcon (ID 0x"<< std::hex << sdo_tx_id << ")" << std::endl;
        
        // simulate response to shutdown req 
        can_frame sevcon_reply{};
        sevcon_reply.can_id = sdo_rx_id;
        sevcon_reply.can_dlc = 8;
        sevcon_reply.data[0] = 0x60; // cmd specifier for OK 2 byte write
        sevcon_reply.data[1] = 0x40; // lsb
        sevcon_reply.data[2] = 0x60; // msb
        sevcon_reply.data[3] = 0x00; // subindex 
        std::memset(&sevcon_reply.data[4], 0x00, 4);

        m_testDriver->sendMessage(sevcon_reply);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // check for ack 
        ASSERT_TRUE(m_cb->hasMessage());
        frame_res sevcon_ack = m_cb->readMessage();
        ASSERT_TRUE(sevcon_ack.has_value());

        frame_t ack = sevcon_ack.value();
        std::cout << "[SEVCON] Acknowledged shutdown: ";
        for (int i = 0; i < ack.dlc; ++i){
          printf("%02X ", ack.data[i]);
        }
        std::cout << std::endl;
        break;
      }
    }
    std::cout << "[TEST] Simulation complete!" << std::endl;
}
