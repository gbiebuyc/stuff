/*
 * DMG Gameboy emulator.
 * Host system is little endian.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

unsigned char mem[0xffff];
unsigned char bootrom[] = {
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
uint16_t PC = 0;
uint16_t SP;
uint16_t AF, BC, DE, HL;
#define FLAGS (*(unsigned char*)&AF)

unsigned char *get_reg(int i) {
	i &= 0x7;
	if (i==0) return ((unsigned char*)&BC)+1;
	if (i==1) return ((unsigned char*)&BC);
	if (i==2) return ((unsigned char*)&DE)+1;
	if (i==3) return ((unsigned char*)&DE);
	if (i==4) return ((unsigned char*)&HL)+1;
	if (i==5) return ((unsigned char*)&HL);
	if (i==6) return mem + HL;
	if (i==7) return ((unsigned char*)&AF)+1;
}


int main() {
	memcpy(mem, bootrom, sizeof(bootrom));
	while (true) {
		printf("AF=%-4x BC=%-4x DE=%-4x HL=%-4x SP=%-4x PC=%-4x\n", AF, BC, DE, HL, SP, PC);
		fflush(stdout);
		unsigned char opcode = mem[PC++];
		if (opcode==0x31)      { memcpy(&SP, mem+PC, sizeof(SP)); PC += 2; }
		else if (opcode==0xaf) { AF &= 0x00ff;                             }
		else if (opcode==0x21) { memcpy(&HL, mem+PC, sizeof(HL)); PC += 2; }
		else if (opcode==0x32) { mem[HL--] = AF>>8;                        }
		else if (opcode==0xcb) {
			opcode = mem[PC++];
			unsigned char hi_nibble = opcode >> 4;
			unsigned char lo_nibble = opcode & 0xf;
			if (hi_nibble >= 0x4 && hi_nibble < 0x8) {
				unsigned char bit = (hi_nibble-4)<<1 + lo_nibble>>3;
				FLAGS = (*get_reg(lo_nibble) & (1 << bit)) ? 0 : 0x80;
			}

		}
		else {
			printf("Unknown opcode: %x\n", opcode);
			exit(EXIT_FAILURE);
		}
	}
}
