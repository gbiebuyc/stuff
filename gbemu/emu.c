/*
 * DMG Gameboy emulator.
 * Host system is little endian.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

uint8_t mem[0xffff];
uint8_t bootrom[] = {
  0x31, 0xfe, 0xff, 0xaf, 0x21, 0xff, 0x9f, 0x32, 0xcb, 0x7c, 0x20, 0xfb,
  0x21, 0x26, 0xff, 0x0e, 0x11, 0x3e, 0x80, 0x32, 0xe2, 0x0c, 0x3e, 0xf3,
  0xe2, 0x32, 0x3e, 0x77, 0x77, 0x3e, 0xfc, 0xe0, 0x47, 0x11, 0x04, 0x01,
  0x21, 0x10, 0x80, 0x1a, 0xcd, 0x95, 0x00, 0xcd, 0x96, 0x00, 0x13, 0x7b,
  0xfe, 0x34, 0x20, 0xf3, 0x11, 0xd8, 0x00, 0x06, 0x08, 0x1a, 0x13, 0x22,
  0x23, 0x05, 0x20, 0xf9, 0x3e, 0x19, 0xea, 0x10, 0x99, 0x21, 0x2f, 0x99,
  0x0e, 0x0c, 0x3d, 0x28, 0x08, 0x32, 0x0d, 0x20, 0xf9, 0x2e, 0x0f, 0x18,
  0xf3, 0x67, 0x3e, 0x64, 0x57, 0xe0, 0x42, 0x3e, 0x91, 0xe0, 0x40, 0x04,
  0x1e, 0x02, 0x0e, 0x0c, 0xf0, 0x44, 0xfe, 0x90, 0x20, 0xfa, 0x0d, 0x20,
  0xf7, 0x1d, 0x20, 0xf2, 0x0e, 0x13, 0x24, 0x7c, 0x1e, 0x83, 0xfe, 0x62,
  0x28, 0x06, 0x1e, 0xc1, 0xfe, 0x64, 0x20, 0x06, 0x7b, 0xe2, 0x0c, 0x3e,
  0x87, 0xe2, 0xf0, 0x42, 0x90, 0xe0, 0x42, 0x15, 0x20, 0xd2, 0x05, 0x20,
  0x4f, 0x16, 0x20, 0x18, 0xcb, 0x4f, 0x06, 0x04, 0xc5, 0xcb, 0x11, 0x17,
  0xc1, 0xcb, 0x11, 0x17, 0x05, 0x20, 0xf5, 0x22, 0x23, 0x22, 0x23, 0xc9,
  0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83,
  0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
  0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63,
  0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e,
  0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c, 0x21, 0x04, 0x01, 0x11,
  0xa8, 0x00, 0x1a, 0x13, 0xbe, 0x20, 0xfe, 0x23, 0x7d, 0xfe, 0x34, 0x20,
  0xf5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xfb, 0x86, 0x20, 0xfe,
  0x3e, 0x01, 0xe0, 0x50
};
uint16_t PC, SP;
union {
	struct { uint16_t AF, BC, DE, HL; };
	struct { uint8_t F, A, C, B, E, D, L, H; };
} regs;
#define ROT_LEFT 0
#define ROT_RIGHT 1

uint8_t *get_param(int i) {
	i &= 0x7;
	if (i==0) return &regs.B;
	if (i==1) return &regs.C;
	if (i==2) return &regs.D;
	if (i==3) return &regs.E;
	if (i==4) return &regs.H;
	if (i==5) return &regs.L;
	if (i==6) return mem + regs.HL;
	if (i==7) return &regs.A;
}

uint16_t read16() {
	uint16_t val = *(uint16_t*)(mem+PC);
	PC+=2;
	return val;
}

void rotate(int dir, uint8_t *param, bool through_carry) {
	int shifted_out = (dir==ROT_LEFT) ? *param>>7 : *param&1;
	int shifted_in = through_carry ? regs.F>>4&1 : shifted_out;
	*param = (dir==ROT_LEFT) ? *param<<1|shifted_in : *param>>1|shifted_in<<7;
	regs.F = ((*param==0) ? 0x80 : 0) | (shifted_out<<4);
}

void set_flag(char flag, int val) {
	for (int i=0; i<4; i++) {
		if (flag=="ZNHC"[i]) {
			regs.F = val ? (regs.F|0x80>>i) : (regs.F&~(0x80>>i));
			return;
		}
	}
}


int main() {
	memcpy(mem, bootrom, sizeof(bootrom));
	while (true) {
		char flag_str[4];
		flag_str[0] = (regs.F & 0x80) ? 'Z' : '-';
		flag_str[1] = (regs.F & 0x40) ? 'N' : '-';
		flag_str[2] = (regs.F & 0x20) ? 'H' : '-';
		flag_str[3] = (regs.F & 0x10) ? 'C' : '-';
		printf("AF=%-4x BC=%-4x DE=%-4x HL=%-4x SP=%-4x PC=%-4x %.4s Opcode=%-2x\n",
				regs.AF, regs.BC, regs.DE, regs.HL, SP, PC, flag_str, mem[PC]);
		fflush(stdout);
		uint8_t opcode = mem[PC++];
		if (opcode==0x01)      { regs.BC = read16(); }
		else if (opcode==0x11) { regs.DE = read16(); }
		else if (opcode==0x21) { regs.HL = read16(); }
		else if (opcode==0x31) { SP = read16(); }
		else if (opcode==0x03) { regs.BC++; } // INC
		else if (opcode==0x13) { regs.DE++; }
		else if (opcode==0x23) { regs.HL++; }
		else if (opcode==0x33) { SP++; }
		else if (opcode==0x0b) { regs.BC--; } // DEC
		else if (opcode==0x1b) { regs.DE--; }
		else if (opcode==0x2b) { regs.HL--; }
		else if (opcode==0x3b) { SP--; }
		else if (opcode==0xaf) { regs.A = 0; }
		else if (opcode==0x32) { mem[regs.HL--] = regs.A; }
		else if (opcode==0x07) { rotate(ROT_LEFT,  &regs.A, false); }
		else if (opcode==0x0f) { rotate(ROT_RIGHT, &regs.A, false); }
		else if (opcode==0x17) { rotate(ROT_LEFT,  &regs.A, true); }
		else if (opcode==0x1f) { rotate(ROT_RIGHT, &regs.A, true); }
		else if (opcode==0xcb) {
			opcode = mem[PC++];
			uint8_t *param = get_param(opcode);
			if (opcode >= 0x40 && opcode < 0x80) {
				int bit = (opcode-0x40)>>3;
				set_flag('Z', !(*param & (1 << bit)));
				set_flag('N', 0);
				set_flag('H', 1);
			}
			else if (opcode >= 0x10 && opcode < 0x18) { rotate(ROT_LEFT,  param, true); }
			else if (opcode >= 0x18 && opcode < 0x20) { rotate(ROT_RIGHT, param, true); }
			else {
				exit(printf("Unknown opcode: 0xcb %#x\n", opcode));
			}

		}
		else if (opcode==0x20) {
			int offset = ((int8_t*)mem)[PC++];
			if (!(regs.F & 0x80))
				PC += offset;
		}
		else if (opcode < 0x40 && (opcode&0x7)==4) { *get_param(opcode>>3) += 1; }
		else if (opcode < 0x40 && (opcode&0x7)==5) { *get_param(opcode>>3) -= 1; }
		else if (opcode < 0x40 && (opcode&0x7)==6) { *get_param(opcode>>3) = mem[PC++]; }
		else if (opcode >= 0x40 && opcode < 0x80) { *get_param((opcode-0x40)>>3) = *get_param(opcode); }
		else if (opcode==0xe0) { mem[0xff00+mem[PC++]] = regs.A; }
		else if (opcode==0xf0) { regs.A = mem[0xff00+mem[PC++]]; }
		else if (opcode==0xe2) { mem[0xff00+regs.C] = regs.A; }
		else if (opcode==0xf2) { regs.A = mem[0xff00+regs.C]; }
		else if (opcode==0x02) { mem[regs.BC] = regs.A; }
		else if (opcode==0x12) { mem[regs.DE] = regs.A; }
		else if (opcode==0x22) { mem[regs.HL++] = regs.A; }
		else if (opcode==0x32) { mem[regs.HL--] = regs.A; }
		else if (opcode==0x0a) { regs.A = mem[regs.BC]; }
		else if (opcode==0x1a) { regs.A = mem[regs.DE]; }
		else if (opcode==0x2a) { regs.A = mem[regs.HL++]; }
		else if (opcode==0x3a) { regs.A = mem[regs.HL--]; }
		else if (opcode==0xcd) { SP-=2; mem[SP]=PC+2; PC=read16(); } // CALL
		else if (opcode==0xc9) { PC=mem[SP]; SP+=2; } // RET
		else if (opcode==0xc5) { SP-=2; mem[SP]=regs.BC; } // PUSH
		else if (opcode==0xd5) { SP-=2; mem[SP]=regs.DE; }
		else if (opcode==0xe5) { SP-=2; mem[SP]=regs.HL; }
		else if (opcode==0xf5) { SP-=2; mem[SP]=regs.AF; }
		else if (opcode==0xc1) { regs.BC=mem[SP]; SP+=2; } // POP
		else if (opcode==0xd1) { regs.DE=mem[SP]; SP+=2; }
		else if (opcode==0xe1) { regs.HL=mem[SP]; SP+=2; }
		else if (opcode==0xf1) { regs.AF=mem[SP]; SP+=2; }
		//else if (opcode >= 0xb8 && opcode < 0xc0) 
		else {
			printf("Unknown opcode: %#x\n", opcode);
			exit(EXIT_FAILURE);
		}
	}
}
