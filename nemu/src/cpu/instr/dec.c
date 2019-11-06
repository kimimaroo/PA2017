#include "cpu/instr.h"

#define make_instr_dec_reg(reg) \
    make_instr_func(concat3(dec, _, reg)) { \
        uint32_t CF = cpu.eflags.CF; \
        cpu.reg = alu_sub(1, cpu.reg); \
        cpu.eflags.CF = CF; \
        return 1; \
    }


make_instr_dec_reg(eax)
make_instr_dec_reg(ecx)
make_instr_dec_reg(edx)
make_instr_dec_reg(ebx)
make_instr_dec_reg(esp)
make_instr_dec_reg(ebp)
make_instr_dec_reg(esi)
make_instr_dec_reg(edi)