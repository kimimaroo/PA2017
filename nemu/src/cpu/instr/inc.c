#include "cpu/instr.h"

static void instr_execute_1op() {
    operand_read(&opr_src);

    uint32_t CF = cpu.eflags.CF;
    opr_src.val = alu_add(opr_src.val, 1);
    cpu.eflags.CF = CF;

    operand_write(&opr_src);
}

make_instr_impl_1op(inc, rm, v)
