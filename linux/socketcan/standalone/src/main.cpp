#include <core/providers/base.h>
#include <linux/socketcan/provider.h>

using namespace can::providers::os::socketcan;
using namespace can::providers;

int main()
{
    base::options_t a;
    CANBus cb = CANBus(a);
}