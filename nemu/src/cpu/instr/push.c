#include "cpu/instr.h"

#define make_impl_push(reg) \
    make_instr_func(concat3(push, _, reg)) {\
        OPERAND m; \
        m.type = OPR_MEM; \
        m.data_size = 32; \
        m.val = cpu.reg; \
        cpu.esp -= 4; \
        m.addr = cpu.esp; \
        m.sreg = SREG_SS; \
        operand_write(&m); \
        return 1; \
    }

make_impl_push(ebp)