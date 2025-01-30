import can

with can.interface.Bus(interface='socketcan', channel='vcan0', bitrate=500000, fd=True) as bus:

    #msg = can.Message(arbitration_id=0xBBEE, data=[0, 25, 0, 1, 3, 1, 4, 1], is_extended_id=True)
    msg6 = can.Message(arbitration_id=0x74A, dlc=15, data=0x0, is_fd=True)
    #bus.send(msg)
    bus.send(msg6)