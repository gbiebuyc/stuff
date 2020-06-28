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

#define FLAG_Z (regs.F>>7&1)
#define FLAG_N (regs.F>>6&1)
#define FLAG_H (regs.F>>5&1)
#define FLAG_C (regs.F>>4&1)

uint8_t *mem;
uint8_t *gamerom;
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
int cycles;
bool isBootROMUnmapped = false;
bool isHalted = false;
bool debug = false;
#include "cpu.h"


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
	gamerom = malloc(8388608); // max 8 MB cartridges
	int readSize = fread(gamerom, 1, 999999, fopen(av[1], "rb"));
	if (readSize>32768)
		exit(printf("Only supports 32K roms for now."));
	// printf("read size: %d\n", readSize);
	while (true) {
		// if (!debug && PC==0x100)
		// 	debug = true;
		if (debug) {
			char flag_str[4];
			flag_str[0] = (regs.F & 0x80) ? 'Z' : '-';
			flag_str[1] = (regs.F & 0x40) ? 'N' : '-';
			flag_str[2] = (regs.F & 0x20) ? 'H' : '-';
			flag_str[3] = (regs.F & 0x10) ? 'C' : '-';
			printf("PC=%-4x AF=%-4x BC=%-4x DE=%-4x HL=%-4x SP=%-4x %.4s Opcode=%-2x\n",
					PC, regs.AF, regs.BC, regs.DE, regs.HL, SP, flag_str, readByte(PC));
			fflush(stdout);
		}
		if (isHalted)
			cycles = 1;
		else {
			uint8_t opcode = fetchByte();
			cycles = cycleTable[opcode];
			if (!instrs[opcode])
				exit(printf("Invalid opcode: %#x\n", opcode));
			instrs[opcode]();
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
					isHalted = false;
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
						// printf("0xffff ie: %x\n", mem[0xffff]);
						// printf("0xff40 lcdc: %x\n", mem[0xff40]);
						// printf("0xff47 palette: %x\n", mem[0xff47]);
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
