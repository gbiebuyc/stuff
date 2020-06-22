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

uint16_t read16() {
	uint16_t val = *(uint16_t*)(mem+PC);
	PC+=2;
	return val;
}

void set_flags(char Z, char N, char H, char C) {
	if (Z==1) regs.F |= 0x80; else if (Z==0) regs.F &= ~0x80;
	if (N==1) regs.F |= 0x40; else if (N==0) regs.F &= ~0x40;
	if (H==1) regs.F |= 0x20; else if (H==0) regs.F &= ~0x20;
	if (C==1) regs.F |= 0x10; else if (C==0) regs.F &= ~0x10;
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


int main() {
	SDL_Window *window;
	SDL_Surface *surface;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
	}
	window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 144, 0);
	surface = SDL_GetWindowSurface(window);
	memset(mem, 0, sizeof(mem));
	FILE *f = fopen("tetris.gb", "rb");
	if (!f) exit(printf("fopen fail"));
	int x = fread(mem, 1, 2002, f);
	printf("size read: %d\n", x);
	fclose(f);
	memcpy(mem, bootrom, sizeof(bootrom));
	bool debug = false;
	while (true) {
		// if (PC >= 0xc)
		// 	debug = true;
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
		else if (opcode==0x01) { regs.BC = read16(); }
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
			cycles += ((opcode&0x7)==6) ? 16 : 8;
			uint8_t *operand = get_operand(opcode);
			if (opcode >= 0x40 && opcode < 0x80) { // BIT
				int bit = (opcode-0x40)>>3;
				set_flags(!(*operand & (1 << bit)), 0, 1, '-');
			}
			else if (opcode >= 0x10 && opcode < 0x18) { rotate(ROT_LEFT,  operand, true); }
			else if (opcode >= 0x18 && opcode < 0x20) { rotate(ROT_RIGHT, operand, true); }
			else {
				exit(printf("Unknown opcode: 0xcb %#x\n", opcode));
			}
		}
		else if (opcode==0x18) { int8_t i=mem[PC++]; PC+=i; } // JR
		else if (opcode==0x20) { int8_t i=mem[PC++]; if (!FLAG_Z) {PC+=i; cycles+=4;} } // JR NZ
		else if (opcode==0x28) { int8_t i=mem[PC++]; if (FLAG_Z) {PC+=i; cycles+=4;} } // JR Z
		else if (opcode==0x30) { int8_t i=mem[PC++]; if (!FLAG_C) {PC+=i; cycles+=4;} } // JR NC
		else if (opcode==0x38) { int8_t i=mem[PC++]; if (FLAG_C) {PC+=i; cycles+=4;} } // JR C
		else if (opcode==0xc3) { int addr=read16(); PC=addr; } // JP
		else if (opcode==0xc2) { int addr=read16(); if (!FLAG_Z) {PC=addr; cycles+=4;} } // JP NZ
		else if (opcode==0xca) { int addr=read16(); if (FLAG_Z) {PC=addr; cycles+=4;} } // JP Z
		else if (opcode==0xd2) { int addr=read16(); if (!FLAG_C) {PC=addr; cycles+=4;} } // JP NC
		else if (opcode==0xda) { int addr=read16(); if (FLAG_C) {PC=addr; cycles+=4;} } // JP C
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
		else if (opcode==0xcd) { push(PC+2); PC=read16(); } // CALL
		else if (opcode==0xc9) { PC=pop(); } // RET
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
		else if (opcode >= 0xb8 && opcode < 0xc0) { compare(*get_operand(opcode)); } // CP
		else if (opcode==0xfe) { compare(mem[PC++]); }
		else if (opcode==0xea) { mem[read16()] = regs.A; } // LD
		else if (opcode==0xfa) { regs.A = mem[read16()]; }
		else if (opcode==0xf3) { IME = 0; } // DI
		else if (opcode==0xfb) { IME = 1; } // EI
		else {
			printf("Unknown opcode: %#x\n", opcode);
			exit(EXIT_FAILURE);
		}
		scanlineCycles += cycles;
		if (scanlineCycles >= 456) {
			scanlineCycles -= 456;
			mem[0xff44]++;
			if (mem[0xff44] > 153)
				mem[0xff44] = 0;
		}
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
				if (e.type == SDL_KEYDOWN) {
					if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						exit(0);
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
					uint8_t byte0 = tile[v*2];
					uint8_t byte1 = tile[v*2+1];
					int bit0 = (byte0>>(7-u))&1;
					int bit1 = (byte1>>(7-u))&1;
					uint32_t col = (bit0<<1) | bit1;
					uint32_t palette[] = {0xffffff, 0xaaaaaa, 0x555555, 0};
					col = palette[(mem[0xff47]>>col)&3];
					((uint32_t*)surface->pixels)[sy*160 + sx] = col;
				}
			}
			SDL_UpdateWindowSurface(window);
			SDL_Delay(16);
		}
	}
}
