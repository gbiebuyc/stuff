#!/usr/bin/env python3
import argparse, pygame, random, sys
from pygame.locals import *

class Chip8:
    def __init__(self):
        mem = bytearray(0x1000)
        V = bytearray(16)
        PC = 0x200
        SP = I = DT = ST = 0
        stack = [0]*24
        parser = argparse.ArgumentParser(description='My CHIP-8 interpreter.')
        parser.add_argument('rom')
        parser.add_argument('-s', '--scale', default=6, type=int, choices=range(1, 20))
        args = parser.parse_args()
        self.scale = args.scale
        with open(args.rom, 'rb') as f:
            rom = f.read()
            mem[PC:PC+len(rom)] = rom
        pygame.init()
        self.screen = pygame.display.set_mode((64*self.scale, 32*self.scale))
        self.clear_screen()
        clock = pygame.time.Clock()
        self.keylist = [K_0, K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9, K_a, K_b, K_c, K_d, K_e, K_f]
        font = 0xf0909090f02060202070f010f080f0f010f010f09090f01010f080f010f0f080f090f0f010204040f090f090f0f090f010f0f090f09090e090e090e0f0808080f0e0909090e0f080f080f0f080f08080
        mem[0:16*5] = font.to_bytes(16*5, 'big')
        INSTR_PER_FRAME = 500//60
        nb_instr = 0
        while True:
            PC &= 0xfff
            opcode = mem[PC]<<8 | mem[PC+1]
            PC += 2
            addr = opcode & 0xfff
            byte = opcode & 0xff
            X = opcode>>8 & 0xf
            Y = opcode>>4 & 0xf
            if opcode&0xffff == 0x00E0: self.clear_screen()
            elif opcode&0xffff == 0x00EE: PC = stack[SP]; SP -= 1
            elif opcode&0xf000 == 0x1000: PC = addr
            elif opcode&0xf000 == 0x2000: SP+=1; stack[SP]=PC; PC=addr
            elif opcode&0xf000 == 0x3000: PC += 2 if V[X] == byte else 0
            elif opcode&0xf000 == 0x4000: PC += 2 if V[X] != byte else 0
            elif opcode&0xf00f == 0x5000: PC += 2 if V[X] == V[Y] else 0
            elif opcode&0xf000 == 0x6000: V[X] = byte
            elif opcode&0xf000 == 0x7000: V[X] = V[X]+byte & 0xff
            elif opcode&0xf00f == 0x8000: V[X] = V[Y]
            elif opcode&0xf00f == 0x8001: V[X] |= V[Y]
            elif opcode&0xf00f == 0x8002: V[X] &= V[Y]
            elif opcode&0xf00f == 0x8003: V[X] ^= V[Y]
            elif opcode&0xf00f == 0x8004: n=V[X]+V[Y]; V[15]= 1 if n>255 else 0; V[X]=n&255
            elif opcode&0xf00f == 0x8005: n=V[X]-V[Y]; V[15]= 1 if n>0 else 0; V[X]=n&255
            elif opcode&0xf00f == 0x8006: V[15] = V[X]&1; V[X] >>= 1
            elif opcode&0xf00f == 0x8007: n=V[Y]-V[X]; V[15]= 1 if n>0 else 0; V[X]=n&255
            elif opcode&0xf00f == 0x800E: V[15] = V[X]>>7; V[X] = V[X]<<1 & 255
            elif opcode&0xf00f == 0x9000: PC += 2 if V[X] != V[Y] else 0
            elif opcode&0xf000 == 0xA000: I = addr
            elif opcode&0xf000 == 0xB000: PC = addr + V[0]
            elif opcode&0xf000 == 0xC000: V[X] = byte & random.randint(0, 255)
            elif opcode&0xf000 == 0xD000: V[15] = self.draw(mem[I:I+(opcode&0xf)], V[X], V[Y])
            elif opcode&0xf0ff == 0xE09E: PC += 2 if self.is_pressed(V[X]) else 0
            elif opcode&0xf0ff == 0xE0A1: PC += 2 if not self.is_pressed(V[X]) else 0
            elif opcode&0xf0ff == 0xF007: V[X] = DT
            elif opcode&0xf0ff == 0xF00A: V[X] = self.wait_for_key()
            elif opcode&0xf0ff == 0xF015: DT = V[X]
            elif opcode&0xf0ff == 0xF018: ST = V[X]
            elif opcode&0xf0ff == 0xF01E: I += V[X]; I &= 0xfff
            elif opcode&0xf0ff == 0xF029: I = V[X] * 5
            elif opcode&0xf0ff == 0xF033: mem[I]=V[X]//100; mem[I+1]=V[X]//10%10; mem[I+2]=V[X]%10
            elif opcode&0xf0ff == 0xF055: mem[I:I+X+1] = V[:X+1]
            elif opcode&0xf0ff == 0xF065: V[:X+1] = mem[I:I+X+1]
            nb_instr += 1
            if nb_instr >= INSTR_PER_FRAME:
                nb_instr = 0
                clock.tick(60)
                if DT > 0: DT -= 1
                if ST > 0: ST -= 1
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        pygame.quit(); sys.exit()
                    elif event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_ESCAPE:
                            pygame.quit(); sys.exit()

    def clear_screen(self):
        self.pixels = [0]*2048
        self.screen.fill(0)
        pygame.display.flip()

    def draw(self, bytes, x, y):
        collision = 0
        for j in range(len(bytes)):
            for i in range(8):
                sx, sy = x+i&63, y+j&31
                A = 1 if bytes[j] & 0x80>>i else 0
                B = self.pixels[sx + sy*64]
                C = A ^ B
                if A and not C:
                    collision = 1
                self.pixels[sx + sy*64] = C
                pygame.draw.rect(self.screen, 0xffffff if C else 0,
                    (sx * self.scale, sy * self.scale, self.scale, self.scale))
        pygame.display.flip()
        return collision

    def is_pressed(self, key):
        return pygame.key.get_pressed()[self.keylist[key]]

    def wait_for_key(self):
        while True:
            event = pygame.event.wait()
            if event.type == pygame.QUIT:
                pygame.quit(); sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit(); sys.exit()
                elif event.key in self.keylist:
                    return self.keylist.index(event.key)

if __name__ == "__main__":
    c = Chip8()
