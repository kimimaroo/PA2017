#include "cpu/instr.h"

make_instr_func(leave) {
    cpu.esp = cpu.ebp;

    OPERAND m;
    m.type = OPR_MEM;
    m.data_size = data_size;
    m.addr = cpu.esp;
    m.sreg = SREG_SS;
    operand_read(&m);

    cpu.ebp = m.val;
    cpu.esp += data_size / 8;

    return 1;
}