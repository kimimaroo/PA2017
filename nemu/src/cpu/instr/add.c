#include "cpu/instr.h"

static void instr_execute_2op() {
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = alu_add(sign_ext(opr_src.val, opr_src.data_size), sign_ext(opr_dest.val, opr_dest.data_size));
    operand_write(&opr_dest);
}

make_instr_impl_2op(add, i, rm, v);

make_instr_func(add_i2eax_v) {
    opr_dest.type = OPR_REG;
    opr_dest.addr = 0;
    opr_dest.data_size = data_size;
      
    opr_src.type = OPR_IMM;
    opr_src.addr = eip + 1;
    opr_src.data_size = data_size;
    opr_src.sreg = SREG_CS;
    
    instr_execute_2op();
    return 1 + data_size / 8;
}