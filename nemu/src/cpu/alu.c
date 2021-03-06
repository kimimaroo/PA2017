#include "cpu/cpu.h"
#include <stdio.h>


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
	cpu.eflags.CF = (dest < src)? 1 : 0;
	cpu.eflags.PF = parity_flag_set(dest);
	cpu.eflags.ZF = (dest == 0)? 1 : 0;
	cpu.eflags.SF = sign_flag_set(dest);
	cpu.eflags.OF = (dest_sign == src_sign && cpu.eflags.SF != dest_sign)? 1 : 0;
	return dest;
}

uint32_t alu_adc(uint32_t src, uint32_t dest) {
	int dest_sign = sign_flag_set(dest);
	int src_sign = sign_flag_set(src);
	uint32_t dest_ori = dest;
	dest = src + dest + cpu.eflags.CF;
	if(src == 4294967295){
		cpu.eflags.CF = (dest_ori >=1 || cpu.eflags.CF >= 1)? 1 : 0;
	}
	else{
		cpu.eflags.CF = (dest < src + cpu.eflags.CF)? 1 : 0;
	}
	cpu.eflags.PF = parity_flag_set(dest);
	cpu.eflags.ZF = (dest == 0)? 1 : 0;
	cpu.eflags.SF = sign_flag_set(dest);
	cpu.eflags.OF = (dest_sign == src_sign && cpu.eflags.SF != dest_sign)? 1 : 0;
	return dest;
}

uint32_t alu_sub(uint32_t src, uint32_t dest) {
	int dest_sign = sign_flag_set(dest);
	int src_sign = sign_flag_set(src)? 0 : 1;
	uint32_t dest_ori = dest;
	dest = dest - src;
	cpu.eflags.CF = (dest_ori < src)? 1 : 0;
	cpu.eflags.PF = parity_flag_set(dest);
	cpu.eflags.ZF = (dest == 0)? 1 : 0;
	cpu.eflags.SF = sign_flag_set(dest);
	cpu.eflags.OF = (dest_sign == src_sign && cpu.eflags.SF != dest_sign)? 1 : 0;
	return dest;
}

uint32_t alu_sbb(uint32_t src, uint32_t dest) {
	int dest_sign = sign_flag_set(dest);
	int src_sign = sign_flag_set(src)? 0 : 1;
	uint32_t dest_ori = dest;
	dest = dest - src - cpu.eflags.CF;
	if(src == 4294967295){
		cpu.eflags.CF = (dest_ori == 4294967295 && cpu.eflags.CF == 0)? 0 : 1;
	}
	else{
		cpu.eflags.CF = (dest_ori < src + cpu.eflags.CF)? 1 : 0;
	}
	cpu.eflags.PF = parity_flag_set(dest);
	cpu.eflags.ZF = (dest == 0)? 1 : 0;
	cpu.eflags.SF = sign_flag_set(dest);
	cpu.eflags.OF = (dest_sign == src_sign && cpu.eflags.SF != dest_sign)? 1 : 0;
	return dest;
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
	uint64_t result = 0;
	uint16_t src_8 = src & 0xff;
	uint16_t dest_8 = dest & 0xff;
	uint32_t src_16 = src & 0xffff;
	uint32_t dest_16 = dest & 0xffff;
	uint64_t src_32 = src;
	uint64_t dest_32 = dest;
	switch(data_size){
		case 8:
			result = src_8 * dest_8;  // 乘积结果为16位，虽然result占64位，但前48位都是0
			cpu.eflags.CF = (result == (result & 0xff))? 0 : 1;
			break;
		case 16:
			result = src_16 * dest_16;
			cpu.eflags.CF = (result == (result & 0xffff))? 0 : 1;
			break;
		case 32:
			result = src_32 * dest_32;
			cpu.eflags.CF = (result == (result & 0xffffffff))? 0 : 1;
			break;
	}
	cpu.eflags.OF = cpu.eflags.CF;
	return result;
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
    int64_t result = (int64_t)src * dest;
    int8_t  temp1 = result;       
    int16_t temp2 = result;       
    int32_t temp3 = result;       
    switch (data_size){   
        case 8:
			cpu.eflags.CF = (result == temp1) ? 0 : 1;
			break;
	    case 16:
			cpu.eflags.CF = (result == temp2) ? 0 : 1;
			break;
		case 32:
			cpu.eflags.CF = (result == temp3) ? 0 : 1;
			break;
	}
	cpu.eflags.OF = cpu.eflags.CF;
	return result;
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
	uint32_t result = 0;
	assert(src);
	result = dest / src;
	return result;
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
	uint32_t result = 0;
	assert(src);
	result = dest / src;
	return result;
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
	uint32_t result = 0;
	assert(src);
	result = dest % src;
	return result;
}

int32_t alu_imod(int64_t src, int64_t dest) {
	uint32_t result = 0;
	assert(src);
	result = dest % src;
	return result;
}

uint32_t alu_and(uint32_t src, uint32_t dest) {
	dest = dest & src;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	cpu.eflags.PF = parity_flag_set(dest);
	cpu.eflags.ZF = (dest == 0)? 1 : 0;
	cpu.eflags.SF = sign_flag_set(dest);
	return dest;
}

uint32_t alu_xor(uint32_t src, uint32_t dest) {
	dest = dest ^ src;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	cpu.eflags.PF = parity_flag_set(dest);
	cpu.eflags.ZF = (dest == 0)? 1 : 0;
	cpu.eflags.SF = sign_flag_set(dest);
	return dest;
}

uint32_t alu_or(uint32_t src, uint32_t dest) {
	dest = dest | src;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	cpu.eflags.PF = parity_flag_set(dest);
	cpu.eflags.ZF = (dest == 0)? 1 : 0;
	cpu.eflags.SF = sign_flag_set(dest);
	return dest;
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
	// assert(data_size == 8 || data_size == 16 || data_size == 32);
	uint32_t result = dest;
	uint8_t dest_8 = dest & 0xff;
	uint16_t dest_16 = dest & 0xffff;
	uint8_t result_8 = dest_8 << src;
	uint16_t result_16 = dest_16 << src;
	switch(data_size){
		case 8:  // 只对dest的低8位进行操作操作
			result = (dest & 0xffffff00) | result_8;
			cpu.eflags.CF = (uint8_t)(dest_8 << (src - 1)) >= 128;
			cpu.eflags.PF = parity_flag_set(result_8);
			cpu.eflags.ZF = (result_8 == 0)? 1 : 0;
			cpu.eflags.SF = result_8 >= 128;
			break;
		case 16:
			result = (dest & 0xffff0000) | result_16;
			cpu.eflags.CF = (uint16_t)(dest_16 << (src - 1)) >= 32768;
			cpu.eflags.PF = parity_flag_set(result_16);
			cpu.eflags.ZF = (result_16 == 0)? 1 : 0;
			cpu.eflags.SF = result_16 >= 32768;
			break;
		case 32:
			result = dest << src;
			cpu.eflags.CF = (dest << (src - 1)) >= 2147483648;
			cpu.eflags.PF = parity_flag_set(result);
			cpu.eflags.ZF = (result == 0)? 1 : 0;
			cpu.eflags.SF = result >= 2147483648;
			break;
	}
	return result;
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t result = dest;
	uint8_t dest_8 = dest & 0xff;
	uint16_t dest_16 = dest & 0xffff;
	uint8_t result_8 = dest_8 >> src;
	uint16_t result_16 = dest_16 >> src;
	switch(data_size){
		case 8:  // 只对dest的低8位进行操作操作
			result = (dest & 0xffffff00) | result_8;
			cpu.eflags.CF = (dest_8 >> (src - 1)) %2;
			cpu.eflags.PF = parity_flag_set(result_8);
			cpu.eflags.ZF = (result_8 == 0)? 1 : 0;
			cpu.eflags.SF = result_8 >= 128;
			break;
		case 16:
			result = (dest & 0xffff0000) | result_16;
			cpu.eflags.CF = (dest_16 >> (src - 1)) % 2;
			cpu.eflags.PF = parity_flag_set(result_16);
			cpu.eflags.ZF = (result_16 == 0)? 1 : 0;
			cpu.eflags.SF = result_16 >= 32768;
			break;
		case 32:
			result = dest >> src;
			cpu.eflags.CF = (dest >> (src - 1)) % 2;
			cpu.eflags.PF = parity_flag_set(result);
			cpu.eflags.ZF = (result == 0)? 1 : 0;
			cpu.eflags.SF = result >= 2147483648;
			break;
	}
	return result;
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t result = dest;
	int8_t dest_8 = dest & 0xff;
	int16_t dest_16 = dest & 0xffff;
	int32_t dest_32 = dest;
	uint8_t result_8 = dest_8 >> src;
	uint16_t result_16 = dest_16 >> src;
	switch(data_size){
		case 8:  // 只对dest的低8位进行操作操作
			result = (dest & 0xffffff00) | result_8;
			cpu.eflags.CF = (dest_8 >> (src - 1)) %2;
			cpu.eflags.PF = parity_flag_set(result_8);
			cpu.eflags.ZF = (result_8 == 0)? 1 : 0;
			cpu.eflags.SF = result_8 >= 128;
			break;
		case 16:
			result = (dest & 0xffff0000) | result_16;
			cpu.eflags.CF = (dest_16 >> (src - 1)) % 2;
			cpu.eflags.PF = parity_flag_set(result_16);
			cpu.eflags.ZF = (result_16 == 0)? 1 : 0;
			cpu.eflags.SF = result_16 >= 32768;
			break;
		case 32:
			result = dest_32 >> src;
			cpu.eflags.CF = (dest_32 >> (src - 1)) % 2;
			cpu.eflags.PF = parity_flag_set(result);
			cpu.eflags.ZF = (result == 0)? 1 : 0;
			cpu.eflags.SF = result >= 2147483648;
			break;
	}
	return result;
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
	uint32_t result = dest;
	uint8_t dest_8 = dest & 0xff;
	uint16_t dest_16 = dest & 0xffff;
	uint8_t result_8 = dest_8 << src;
	uint16_t result_16 = dest_16 << src;
	switch(data_size){
		case 8:  // 只对dest的低8位进行操作操作
			result = (dest & 0xffffff00) | result_8;
			cpu.eflags.CF = (uint8_t)(dest_8 << (src - 1)) >= 128;
			cpu.eflags.PF = parity_flag_set(result_8);
			cpu.eflags.ZF = (result_8 == 0)? 1 : 0;
			cpu.eflags.SF = result_8 >= 128;
			break;
		case 16:
			result = (dest & 0xffff0000) | result_16;
			cpu.eflags.CF = (uint16_t)(dest_16 << (src - 1)) >= 32768;
			cpu.eflags.PF = parity_flag_set(result_16);
			cpu.eflags.ZF = (result_16 == 0)? 1 : 0;
			cpu.eflags.SF = result_16 >= 32768;
			break;
		case 32:
			result = dest << src;
			cpu.eflags.CF = (dest << (src - 1)) >= 2147483648;
			cpu.eflags.PF = parity_flag_set(result);
			cpu.eflags.ZF = (result == 0)? 1 : 0;
			cpu.eflags.SF = result >= 2147483648;
			break;
	}
	return result;
}
