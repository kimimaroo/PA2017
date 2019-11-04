#include "cpu/instr.h"

static void push_ret_addr(uint8_t len)
{
    cpu.esp -= data_size / 8;
    OPERAND m;
    m.type = OPR_MEM;
    m.data_size = data_size; 
    m.addr = cpu.esp;
    m.sreg = SREG_SS;
    m.val = (data_size == 32) ? cpu.eip : (cpu.eip & 0x0000ffff);
    m.val += len;
    operand_write(&m);
}

make_instr_func(call_Av) 
{
    push_ret_addr(1 + data_size / 8);

    OPERAND imm;
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + 1;
    imm.sreg = SREG_CS;
    operand_read(&imm);

    cpu.eip += 1 + data_size / 8 + imm.val;
    return 0;
}