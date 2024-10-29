#ifndef _STUB_HARDWARE_PLATFORM_DEFS_H
#define _STUB_HARDWARE_PLATFORM_DEFS_H

#ifndef _u
#ifdef __ASSEMBLER__
#define _u(x) x
#else
#define _u(x) x##u
#endif
#endif

// import host/hardware_regs package
// #include <hardware/platform_defs.h>

// rp2040/hardware_regs missing in host
// <pico-sdk/src/rp2040/hardware_regs/include/hardware/platform_defs.h>
#define NUM_IRQS _u(32)
#define NUM_USER_IRQS _u(6)
#define NUM_SPIN_LOCKS _u(32)
#define NUM_ALARMS _u(4)

#define FIRST_USER_IRQ (NUM_IRQS - NUM_USER_IRQS)
#define VTABLE_FIRST_IRQ 16

#endif