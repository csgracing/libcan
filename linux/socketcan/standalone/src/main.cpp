#include <core/providers/base.h>
#include <linux/socketcan/provider.h>

using namespace can::providers::os::socketcan;
using namespace can::providers;

int main()
{
    Options *o = new Options();
    o->canInterface = "vcan0";
    o->canProtocol = CAN_RAW;
    CANBus cb = CANBus(NULL, o);

    return 0;
}