#include "cpu/instr.h"

make_instr_func(jmp_near) {
        OPERAND rel;
        rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

	int offset = sign_ext(rel.val, data_size);
	print_asm_1("jmp", "",  1 + data_size / 8, &rel);

	cpu.eip += offset;

        return 1 + data_size / 8;
}

make_instr_func(jmp_short_) {
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = 8;
    rel.addr = eip + 1;

    operand_read(&rel);

    int offset = sign_ext(rel.val, 8);
    print_asm_1("jmp", "", 1 + 1, &rel);

    cpu.eip += offset;

    return 1 + 1;
}

make_instr_func(jmp_rm_v) {
    int len = 0;
    decode_data_size_v
    decode_operand_rm

    operand_read(&opr_src);
    cpu.eip = opr_src.val;
    return 0;
}