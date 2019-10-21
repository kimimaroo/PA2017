#include "cpu/cpu.h"

int parity_flag_set(uint32_t dest) {
	int binarynum[32];
	uint32_t tmp = dest;
	for(int i = 0; i < 32; i++){
		if(tmp == 0) break;
		binarynum[i] = tmp % 2;
		tmp = tmp / 2;
	}
	int sum = 1;
	for(int i = 0; i < 8; i++) sum += binarynum[i];
	return (sum % 2);
}

uint32_t alu_add(uint32_t src, uint32_t dest) {
	dest = src + dest;
	if(dest < src){
		cpu.eflags.CF = 1;
	}
	else{
		cpu.eflags.CF = 0;
	}
	cpu.eflags.PF = parity_flag_set(dest);
	cpu.eflags.AF = 1;
	cpu.eflags.ZF = 1;
	cpu.eflags.SF = 1;
	cpu.eflags.OF = 1;
	return dest;
}

uint32_t alu_adc(uint32_t src, uint32_t dest) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}


uint32_t alu_sub(uint32_t src, uint32_t dest) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_sbb(uint32_t src, uint32_t dest) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

int32_t alu_imod(int64_t src, int64_t dest) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_and(uint32_t src, uint32_t dest) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_xor(uint32_t src, uint32_t dest) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_or(uint32_t src, uint32_t dest) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	assert(0);
	return 0;
}
