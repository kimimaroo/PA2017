#include "cpu/instr.h"

static void pop_ret_addr()
{
    OPERAND m;
    m.type = OPR_MEM;
    m.data_size = data_size;
    m.addr = cpu.esp;
    m.sreg = SREG_SS;
    operand_read(&m);
    
    cpu.eip = m.val;
    if (data_size == 16) cpu.eip &= 0x0000ffff;
}

make_instr_func(ret_near) {
    pop_ret_addr();
    cpu.esp += data_size / 8;
    return 0;
}

make_instr_func(ret_i_near) {
    OPERAND imm;
    imm.type = OPR_IMM;
    imm.data_size = 16;
    imm.addr = cpu.eip + 1;
    imm.sreg = SREG_CS;
    operand_read(&imm);

    pop_ret_addr();

    cpu.esp += imm.val;
    return 0;
}