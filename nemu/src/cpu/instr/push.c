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

static void instr_execute_1op() {
    operand_read(&opr_src);

    cpu.esp -= 4;
    OPERAND m;
    m.type = OPR_MEM;
    m.addr = cpu.esp;
    m.val = sign_ext(opr_src.val, opr_src.data_size);
    m.data_size = 32;
    m.sreg = SREG_SS;
    operand_write(&m);
}

make_impl_push(eax)
make_impl_push(ecx)
make_impl_push(edx)
make_impl_push(ebx)
make_impl_push(esp)
make_impl_push(ebp)
make_impl_push(esi)
make_impl_push(edi)

make_instr_impl_1op(push, rm, v)