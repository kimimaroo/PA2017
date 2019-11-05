#include "cpu/instr.h"

#define make_impl_pop(reg) \
    make_instr_func(concat3(pop, _, reg)) {\
        OPERAND m; \
        m.type = OPR_MEM; \
        m.data_size = 32; \
        m.addr = cpu.esp; \
        m.sreg = SREG_SS; \
        operand_read(&m); \
        cpu.reg = m.val; \
        cpu.esp += 4; \
        return 1; \
    } 

make_impl_pop(eax)
make_impl_pop(ecx)
make_impl_pop(edx)
make_impl_pop(ebx)
make_impl_pop(esp)
make_impl_pop(ebp)
make_impl_pop(esi)
make_impl_pop(edi)
