#include "cpu/instr.h"

#define make_instr_inc_reg(reg) \
    make_instr_func(concat3(inc, _, reg)) {\
        uint32_t CF = cpu.eflags.CF; \
        cpu.reg = alu_add(cpu.reg, 1); \
        cpu.eflags.CF = CF; \
        return 1; \
    }

static void instr_execute_1op()
{
    operand_read(&opr_src);

    uint32_t CF = cpu.eflags.CF;
    opr_src.val = alu_add(opr_src.val, 1);
    cpu.eflags.CF = CF;

    operand_write(&opr_src);
}

make_instr_impl_1op(inc, rm, v)

make_instr_inc_reg(eax)
make_instr_inc_reg(ecx)
make_instr_inc_reg(edx)
make_instr_inc_reg(ebx)
make_instr_inc_reg(esp)
make_instr_inc_reg(ebp)
make_instr_inc_reg(esi)
make_instr_inc_reg(edi)