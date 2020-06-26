/*
 * DMG Gameboy emulator.
 * Host system is little endian.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#define ROT_LEFT 0
#define ROT_RIGHT 1
#define FLAG_Z (regs.F>>7&1)
#define FLAG_N (regs.F>>6&1)
#define FLAG_H (regs.F>>5&1)
#define FLAG_C (regs.F>>4&1)

uint8_t *mem;
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
uint8_t cycleTable[256] = { // Duration in cycles of each cpu instruction.
	4,12,8,8,4,4,8,4,20,8,8,8,4,4,8,4,
	4,12,8,8,4,4,8,4,12,8,8,8,4,4,8,4,
	8,12,8,8,4,4,8,4,8,8,8,8,4,4,8,4,
	8,12,8,8,12,12,12,4,8,8,8,8,4,4,8,4,
	4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
	4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
	4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
	8,8,8,8,8,8,4,8,4,4,4,4,4,4,8,4,
	4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
	4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
	4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
	4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,
	8,12,12,16,12,16,8,16,8,16,12,4,12,24,8,16,
	8,12,12,0,12,16,8,16,8,16,12,0,12,0,8,16,
	12,12,8,0,0,16,8,16,16,4,16,0,0,0,8,16,
	12,12,8,4,0,16,8,16,12,8,16,4,0,0,8,16
};
uint16_t PC, SP;
union {
	struct { uint16_t AF, BC, DE, HL; };
	struct { uint8_t F, A, C, B, E, D, L, H; };
} regs;
int scanlineCycles;
int frameCycles;
bool IME;
#include "cpu.h"

uint8_t *get_operand(int i) {
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

void rotate(int dir, uint8_t *operand, bool through_carry) {
	int shifted_out = (dir==ROT_LEFT) ? *operand>>7 : *operand&1;
	int shifted_in = through_carry ? FLAG_C : shifted_out;
	*operand = (dir==ROT_LEFT) ? *operand<<1|shifted_in : *operand>>1|shifted_in<<7;
	set_flags(!*operand, 0, 0, shifted_out);
}

void add(int b) {
	int a = regs.A;
	set_flags(!((a+b)&0xff), 0, (((a&0xf)+(b&0xf))&0x10)==0x10, (a+b)>0xff);
	regs.A += b;
}

void compare(int b) {
	int a = regs.A;
	set_flags(a==b, 1, ((a&0xf)-(b&0xf))<0, b>a);
}

void subtract(int b) {
	compare(b);
	regs.A -= b;
}

void increment(uint8_t *operand) {
	set_flags(*operand==0xff, 0, (((*operand&0xf)+1)&0x10)==0x10, '-');
	++*operand;
}

void decrement(uint8_t *operand) {
	set_flags(*operand==1, 1, ((((int)*operand)&0xf)-1)<0, '-');
	--*operand;
}

void push(uint16_t operand) {
	SP -= 2;
	*(uint16_t*)(mem+SP) = operand;
}

uint16_t pop() {
	uint16_t val = *(uint16_t*)(mem+SP);
	SP += 2;
	return val;
}

void and(uint8_t operand) {
	regs.A &= operand;
	set_flags(!regs.A, 0, 1, 0);
}

void xor(uint8_t operand) {
	regs.A ^= operand;
	set_flags(!regs.A, 0, 0, 0);
}

void or(uint8_t operand) {
	regs.A |= operand;
	set_flags(!regs.A, 0, 0, 0);
}

void swap(uint8_t *operand) {
	*operand = ((*operand)>>4) | ((*operand)<<4);
	set_flags(!*operand, 0, 0, 0);
}

void testBit(uint8_t *operand, int bit) {
	set_flags(!(*operand & (1 << bit)), 0, 1, '-');
}

void SLA(uint8_t *operand) {
	set_flags(!(*operand<<1), 0, 0, *operand>>7);
	*operand <<= 1;
}

void SRA(uint8_t *operand) {
	set_flags(!(*operand>>1), 0, 0, (*operand)&1);
	*operand = (*operand>>1) | ((*operand)&0x80);
}

void SRL(uint8_t *operand) {
	set_flags(!(*operand>>1), 0, 0, (*operand)&1);
	*operand >>= 1;
}


int main(int ac, char **av) {
	SDL_Window *window;
	SDL_Surface *surface;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
	}
	window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 144, 0);
	surface = SDL_GetWindowSurface(window);
	mem = malloc(0x10000);
	uint8_t *gamerom = malloc(8388608); // max 8 MB cartridges
	int readSize = fread(gamerom, 1, 999999, fopen(av[1], "rb"));
	if (readSize>32768)
		exit(printf("Only supports 32768 byte roms for now."));
	printf("read size: %d\n", readSize);
	memcpy(mem, gamerom, 32768);
	memcpy(mem, bootrom, sizeof(bootrom));
	bool isBootROMUnmapped = false;
	bool debug = false;
	while (true) {
		// if (PC >= 0xc)
		// 	debug = true;
		if (!isBootROMUnmapped && PC >= 0x100) {
			memcpy(mem, gamerom, 0x100);
			isBootROMUnmapped = true;
		}
		if (debug) {
			char flag_str[4];
			flag_str[0] = (regs.F & 0x80) ? 'Z' : '-';
			flag_str[1] = (regs.F & 0x40) ? 'N' : '-';
			flag_str[2] = (regs.F & 0x20) ? 'H' : '-';
			flag_str[3] = (regs.F & 0x10) ? 'C' : '-';
			printf("PC=%-4x AF=%-4x BC=%-4x DE=%-4x HL=%-4x SP=%-4x %.4s Opcode=%-2x\n",
					PC, regs.AF, regs.BC, regs.DE, regs.HL, SP, flag_str, mem[PC]);
			fflush(stdout);
		}
		uint8_t opcode = mem[PC++];
		int cycles = cycleTable[opcode];
		if (opcode==0) {} // NOP
		else if (opcode==0x01) { regs.BC = fetchWord(); }
		else if (opcode==0x11) { regs.DE = fetchWord(); }
		else if (opcode==0x21) { regs.HL = fetchWord(); }
		else if (opcode==0x31) { SP = fetchWord(); }
		else if (opcode==0x03) { regs.BC++; } // INC
		else if (opcode==0x13) { regs.DE++; }
		else if (opcode==0x23) { regs.HL++; }
		else if (opcode==0x33) { SP++; }
		else if (opcode==0x0b) { regs.BC--; } // DEC
		else if (opcode==0x1b) { regs.DE--; }
		else if (opcode==0x2b) { regs.HL--; }
		else if (opcode==0x3b) { SP--; }
		else if (opcode==0x07) { rotate(ROT_LEFT,  &regs.A, false); }
		else if (opcode==0x0f) { rotate(ROT_RIGHT, &regs.A, false); }
		else if (opcode==0x17) { rotate(ROT_LEFT,  &regs.A, true); }
		else if (opcode==0x1f) { rotate(ROT_RIGHT, &regs.A, true); }
		else if (opcode==0xcb) {
			opcode = mem[PC++];
			cycles += ((opcode&0x7)==6) ? 16 : 8;
			uint8_t *operand = get_operand(opcode);
			int bit = (opcode>>3)&7;
			if (opcode >= 0x40 && opcode < 0x80) { testBit(operand, bit); }
			else if (opcode >= 0x10 && opcode < 0x18) { rotate(ROT_LEFT,  operand, true); }
			else if (opcode >= 0x18 && opcode < 0x20) { rotate(ROT_RIGHT, operand, true); }
			else if (opcode >= 0x20 && opcode < 0x28) { SLA(operand); }
			else if (opcode >= 0x28 && opcode < 0x30) { SRA(operand); }
			else if (opcode >= 0x30 && opcode < 0x38) { swap(operand); }
			else if (opcode >= 0x38 && opcode < 0x40) { SRL(operand); }
			else if (opcode >= 0x80 && opcode < 0xc0) { *operand &= ~(1<<bit); } // RES
			else if (opcode >= 0xc0) { *operand |= (1<<bit); } // SET
			else {
				exit(printf("Unknown opcode: 0xcb %#x at PC=%#x\n", opcode, PC-2));
			}
		}
		else if (opcode==0x18) { int8_t i=mem[PC++]; PC+=i; } // JR
		else if (opcode==0x20) { int8_t i=mem[PC++]; if (!FLAG_Z) {PC+=i; cycles+=4;} } // JR NZ
		else if (opcode==0x28) { int8_t i=mem[PC++]; if (FLAG_Z) {PC+=i; cycles+=4;} } // JR Z
		else if (opcode==0x30) { int8_t i=mem[PC++]; if (!FLAG_C) {PC+=i; cycles+=4;} } // JR NC
		else if (opcode==0x38) { int8_t i=mem[PC++]; if (FLAG_C) {PC+=i; cycles+=4;} } // JR C
		else if (opcode==0xc3) { int addr=fetchWord(); PC=addr; } // JP
		else if (opcode==0xc2) { int addr=fetchWord(); if (!FLAG_Z) {PC=addr; cycles+=4;} } // JP NZ
		else if (opcode==0xca) { int addr=fetchWord(); if (FLAG_Z) {PC=addr; cycles+=4;} } // JP Z
		else if (opcode==0xd2) { int addr=fetchWord(); if (!FLAG_C) {PC=addr; cycles+=4;} } // JP NC
		else if (opcode==0xda) { int addr=fetchWord(); if (FLAG_C) {PC=addr; cycles+=4;} } // JP C
		else if (opcode==0xe9) { PC = regs.HL; } // JP HL
		else if (opcode < 0x40 && (opcode&0x7)==4) { increment(get_operand(opcode>>3)); }
		else if (opcode < 0x40 && (opcode&0x7)==5) { decrement(get_operand(opcode>>3)); }
		else if (opcode < 0x40 && (opcode&0x7)==6) { *get_operand(opcode>>3) = mem[PC++]; }
		else if (opcode >= 0x40 && opcode < 0x80) { *get_operand((opcode-0x40)>>3) = *get_operand(opcode); }
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
		else if (opcode==0xcd) { int addr=fetchWord(); push(PC); PC=addr; } // CALL
		else if (opcode==0xc4) { int addr=fetchWord(); if (!FLAG_Z) {push(PC); PC=addr; cycles+=12;} } // CALL NZ
		else if (opcode==0xcc) { int addr=fetchWord(); if (FLAG_Z) {push(PC); PC=addr; cycles+=12;} } // CALL Z
		else if (opcode==0xd4) { int addr=fetchWord(); if (!FLAG_C) {push(PC); PC=addr; cycles+=12;} } // CALL NC
		else if (opcode==0xdc) { int addr=fetchWord(); if (FLAG_C) {push(PC); PC=addr; cycles+=12;} } // CALL C
		else if (opcode==0xc9) { PC=pop(); } // RET
		else if (opcode==0xc0) { if (!FLAG_Z) PC=pop(); } // RET NZ
		else if (opcode==0xc8) { if (FLAG_Z) PC=pop(); } // RET Z
		else if (opcode==0xd0) { if (!FLAG_C) PC=pop(); } // RET NC
		else if (opcode==0xd8) { if (FLAG_C) PC=pop(); } // RET C
		else if (opcode==0xd9) { PC=pop(); IME=1; } // RETI
		else if (opcode==0xc5) { push(regs.BC); } // PUSH
		else if (opcode==0xd5) { push(regs.DE); }
		else if (opcode==0xe5) { push(regs.HL); }
		else if (opcode==0xf5) { push(regs.AF); }
		else if (opcode==0xc1) { regs.BC=pop(); } // POP
		else if (opcode==0xd1) { regs.DE=pop(); }
		else if (opcode==0xe1) { regs.HL=pop(); }
		else if (opcode==0xf1) { regs.AF=pop(); }
		else if (opcode >= 0x80 && opcode < 0x88) { add(*get_operand(opcode)); } // ADD
		else if (opcode==0xc6) { add(mem[PC++]); }
		else if (opcode >= 0x90 && opcode < 0x98) { subtract(*get_operand(opcode)); } // SUB
		else if (opcode==0xd6) { subtract(mem[PC++]); }
		else if (opcode >= 0xa0 && opcode < 0xa8) { and(*get_operand(opcode)); } // AND
		else if (opcode==0xe6) { and(mem[PC++]); }
		else if (opcode >= 0xa8 && opcode < 0xb0) { xor(*get_operand(opcode)); } // XOR
		else if (opcode==0xee) { xor(mem[PC++]); }
		else if (opcode >= 0xb0 && opcode < 0xb8) { or(*get_operand(opcode)); } // OR
		else if (opcode==0xf6) { or(mem[PC++]); }
		else if (opcode >= 0xb8 && opcode < 0xc0) { compare(*get_operand(opcode)); } // CP
		else if (opcode==0xfe) { compare(mem[PC++]); }
		else if (opcode==0xea) { mem[fetchWord()] = regs.A; } // LD
		else if (opcode==0xfa) { regs.A = mem[fetchWord()]; }
		else if (opcode==0xf3) { IME = 0; } // DI
		else if (opcode==0xfb) { IME = 1; } // EI
		else if (opcode==0x2f) { regs.A = ~regs.A; set_flags('-', 1, 1, '-'); } // CPL
		else if (opcode>0xc0 && (opcode&0x7)==7) { push(PC); PC=opcode-0xc7; } // RST
		else if (opcode==0x09) { regs.HL+=regs.BC; set_flags('-', 0, 0, 0); } // ADD
		else if (opcode==0x19) { regs.HL+=regs.DE; set_flags('-', 0, 0, 0); }
		else if (opcode==0x29) { regs.HL+=regs.HL; set_flags('-', 0, 0, 0); }
		else if (opcode==0x39) { regs.HL+=SP; set_flags('-', 0, 0, 0); }
		else {
			printf("Unknown opcode: %#x at PC=%#x\n", opcode, PC-1);
			// exit(EXIT_FAILURE);
		}

		mem[0xff00] |= 0xcf; // Joypad

		scanlineCycles += cycles;
		if (scanlineCycles >= 456) {
			scanlineCycles -= 456;
			mem[0xff44]++;
			if (mem[0xff44] > 153)
				mem[0xff44] = 0;
		}
		if (mem[0xff44]==144)
			mem[0xff0f] |= 1; // V-Blank interrupt
		int lcd_mode;
		if (mem[0xff44] >= 144)
			lcd_mode = 1;
		else if (scanlineCycles >= 252)
			lcd_mode = 0;
		else if (scanlineCycles >= 80)
			lcd_mode = 3;
		else
			lcd_mode = 2;
		mem[0xff41] &= ~3;
		mem[0xff41] |= lcd_mode;

		// Interrupts
		if (IME && mem[0xff0f] && mem[0xffff]) {
			for (int i=0; i<5; i++) {
				int mask = 1<<i;
				if ((mem[0xff0f]&mask) && (mem[0xffff]&mask)) {
					push(PC);
					PC = "@HPX`"[i];
					mem[0xff0f] &= ~mask;
					IME = 0;
					break;
				}
			}
		}

		frameCycles += cycles;
		if (frameCycles >= 70224) {
			frameCycles -= 70224;
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT)
					exit(0);
				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						printf("0xffff ie: %x\n", mem[0xffff]);
						printf("0xff40 lcdc: %x\n", mem[0xff40]);
						printf("0xff47 palette: %x\n", mem[0xff47]);
						exit(0);
					}
				}
			}
			uint8_t *BGTileMap = mem+0x9800;
			uint8_t *TileData = mem+0x8000;
			for (int sy=0; sy<144; sy++) {
				for (int sx=0; sx<160; sx++) {
					int x = (sx+mem[0xff43])&0xff;
					int y = (sy+mem[0xff42])&0xff;
					int tileX = x>>3;
					int tileY = y>>3;
					int u = x&7;
					int v = y&7;
					int tileIndex = BGTileMap[tileY*32 + tileX];
					uint8_t *tile = TileData + tileIndex*16;
					uint16_t line = ((uint16_t*)tile)[v];
					line >>= (7-u);
					uint32_t color = (line>>7&2) | (line&1);
					uint32_t palette[] = {0xffffff, 0xaaaaaa, 0x555555, 0x000000};
					color = palette[(mem[0xff47]>>(color<<1))&3];
					((uint32_t*)surface->pixels)[sy*160 + sx] = color;
				}
			}
			if (isBootROMUnmapped) { // Skip display of boot animation
				SDL_UpdateWindowSurface(window);
				// SDL_Delay(16);
				SDL_Delay(5);
			}
		}
	}
}
