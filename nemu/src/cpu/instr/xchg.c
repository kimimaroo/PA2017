#include "cpu/instr.h"

#define make_instr_impl_xchg_reg(reg) \
    make_instr_func(concat3(xchg, _, reg)) {\
        uint32_t temp = cpu.reg; \
        cpu.reg = cpu.eax; \
        cpu.eax = temp; \
        return 1; \
    }

static void instr_execute_2op()
{
    operand_read(&opr_src);
    operand_read(&opr_dest);
    uint32_t temp = opr_src.val;
    opr_src.val = opr_dest.val;
    opr_dest.val = temp;
    operand_write(&opr_src);
    operand_write(&opr_dest);
}

make_instr_impl_2op(xchg, r, rm, b)
make_instr_impl_2op(xchg, r, rm, v)
make_instr_impl_xchg_reg(ecx)
make_instr_impl_xchg_reg(edx)
make_instr_impl_xchg_reg(ebx)
make_instr_impl_xchg_reg(esp)
make_instr_impl_xchg_reg(ebp)
make_instr_impl_xchg_reg(esi)
make_instr_impl_xchg_reg(edi)