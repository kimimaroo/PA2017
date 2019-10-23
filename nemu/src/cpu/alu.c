#include "cpu/cpu.h"
#include <stdio.h>

// int carry_flag_set(uint64_t dest_64) {
// 	int binarynum[33];
// 	uint64_t tmp = dest_64;
// 	for(int i = 0; i < 33; i++){
// 		if(tmp == 0){
// 			binarynum[i] = 0;
// 		}
// 		else{
// 			binarynum[i] = tmp % 2;
// 			tmp = tmp / 2;
// 		}
// 	}
// 	return binarynum[32];
// }

int parity_flag_set(uint32_t dest) {
	int binarynum[32];
	uint32_t tmp = dest;
	for(int i = 0; i < 32; i++){
		if(tmp == 0){
			binarynum[i] = 0;
		}
		else{
			binarynum[i] = tmp % 2;
			tmp = tmp / 2;
		}
	}
	int sum = 1;
	for(int i = 0; i < 8; i++){
		sum += binarynum[i];
	}
	return (sum % 2);
}

int sign_flag_set(uint32_t dest) {
	int binarynum[32];
	uint32_t tmp = dest;
	for(int i = 0; i < 32; i++){
		if(tmp == 0){
			binarynum[i] = 0;
		}
		else{
			binarynum[i] = tmp % 2;
			tmp = tmp / 2;
		}
	}
	return binarynum[31];
}

uint32_t alu_add(uint32_t src, uint32_t dest) {
	int dest_sign = sign_flag_set(dest);
	int src_sign = sign_flag_set(src);
	dest = src + dest;
	if(dest < src){
		cpu.eflags.CF = 1;
	}
	else{
		cpu.eflags.CF = 0;
	}
	cpu.eflags.PF = parity_flag_set(dest);
	if(dest == 0){
		cpu.eflags.ZF = 1;
	}
	else{
		cpu.eflags.ZF = 0;
	}
	cpu.eflags.SF = sign_flag_set(dest);
	if(dest_sign == src_sign && cpu.eflags.SF != dest_sign){
		cpu.eflags.OF = 1;
	}
	else{
		cpu.eflags.OF = 0;
	}
	return dest;
}

uint32_t alu_adc(uint32_t src, uint32_t dest) {
	int dest_sign = sign_flag_set(dest);
	int src_sign = sign_flag_set(src);
	uint32_t dest_ori = dest;
	dest = src + dest + cpu.eflags.CF;
	if(src==4294967295)	{
		if(dest_ori + cpu.eflags.CF >= 1){
			cpu.eflags.CF = 1;
		}
		else{
			cpu.eflags.CF = 0;
		}
	}
	else{
		if(dest < src + cpu.eflags.CF){
			cpu.eflags.CF = 1;
		}
	else{
			cpu.eflags.CF = 0;
		}
	}
	cpu.eflags.CF = (dest_64 == dest)? 0 : 1;
	printf("%d\n", cpu.eflags.CF);
	cpu.eflags.PF = parity_flag_set(dest);
	if(dest == 0){
		cpu.eflags.ZF = 1;
	}
	else{
		cpu.eflags.ZF = 0;
	}
	cpu.eflags.SF = sign_flag_set(dest);
	if(dest_sign == src_sign && cpu.eflags.SF != dest_sign){
		cpu.eflags.OF = 1;
	}
	else{
		cpu.eflags.OF = 0;
	}
	return dest;
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
