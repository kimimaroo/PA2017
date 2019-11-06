#include "cpu/instr.h"

#define make_instr_dec_reg(reg) \
    make_instr_func(concat3(dec, _, reg)) { \
        uint32_t CF = cpu.eflags.CF; \
        cpu.reg = alu_sub(1, cpu.reg); \
        cpu.eflags.CF = CF; \
        return 1; \
    }

static void instr_execute_1op()
{
    operand_read(&opr_src);

    uint32_t CF = cpu.eflags.CF;
    opr_src.val = alu_sub(1, opr_src.val);
    cpu.eflags.CF = CF;

    operand_write(&opr_src);
}

make_instr_impl_1op(dec, rm, v)

make_instr_dec_reg(eax)
make_instr_dec_reg(ecx)
make_instr_dec_reg(edx)
make_instr_dec_reg(ebx)
make_instr_dec_reg(esp)
make_instr_dec_reg(ebp)
make_instr_dec_reg(esi)
make_instr_dec_reg(edi)