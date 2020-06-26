uint8_t readByte(uint16_t addr) {
	return mem[addr];
}

uint16_t readWord(uint16_t addr) {
	return ((uint16_t)readByte(addr+1))<<8 | readByte(addr);
}

void writeByte(uint16_t addr, uint8_t val) {
	mem[addr] = val;
}

void writeWord(uint16_t addr, uint16_t val) {
	writeByte(addr, val);
	writeByte(addr+1, val>>8);
}

uint8_t fetchByte() {
	return readByte(PC++);
}

uint16_t fetchWord() {
	return readWord((PC+=2)-2);
}

void set_flags(char Z, char N, char H, char C) {
	if (Z==1) regs.F |= 0x80; else if (Z==0) regs.F &= ~0x80;
	if (N==1) regs.F |= 0x40; else if (N==0) regs.F &= ~0x40;
	if (H==1) regs.F |= 0x20; else if (H==0) regs.F &= ~0x20;
	if (C==1) regs.F |= 0x10; else if (C==0) regs.F &= ~0x10;
}

void ins00() {}
void ins01() {regs.BC = fetchWord(); }
void ins11() {regs.DE = fetchWord(); }
void ins21() {regs.HL = fetchWord(); }
void ins31() {regs.SP = fetchWord(); }
void ins02() {writeByte(regs.BC, A); }
void ins12() {writeByte(regs.DE, A); }
void ins22() {writeByte(regs.HL++, A); }
void ins32() {writeByte(regs.HL--, A); }
void ins03() {regs.BC++; }
void ins13() {regs.DE++; }
void ins23() {regs.HL++; }
void ins33() {regs.SP++; }
void ins0B() {regs.BC--; }
void ins1B() {regs.DE--; }
void ins2B() {regs.HL--; }
void ins3B() {regs.SP--; }
void setFlagsInc(uint8_t operand) {set_flags(operand==1, 1, ((((int)operand)&0xf)-1)<0, '-'); }
void ins04() {setFlagsInc(regs.B++); }
void ins14() {setFlagsInc(regs.D++); }
void ins24() {setFlagsInc(regs.H++); }
void ins34() {uint8_t val=readByte(regs.HL); setFlagsInc(val); writeByte(regs.HL, val++); }
void ins0C() {setFlagsInc(regs.C++); }
void ins1C() {setFlagsInc(regs.E++); }
void ins2C() {setFlagsInc(regs.L++); }
void ins3C() {setFlagsInc(regs.A++); }
void ins05() {setFlagsInc(regs.B--); }
void ins15() {setFlagsInc(regs.D--); }
void ins25() {setFlagsInc(regs.H--); }
void ins35() {uint8_t val=readByte(regs.HL); setFlagsInc(val); writeByte(regs.HL, val--); }
void ins0D() {setFlagsInc(regs.C--); }
void ins1D() {setFlagsInc(regs.E--); }
void ins2D() {setFlagsInc(regs.L--); }
void ins3D() {setFlagsInc(regs.A--); }
void ins06() {regs.B = fetchByte(); }
void ins16() {regs.D = fetchByte(); }
void ins26() {regs.H = fetchByte(); }
void ins36() {writeByte(regs.HL, fetchByte()); }
void ins0E() {regs.C = fetchByte(); }
void ins1E() {regs.E = fetchByte(); }
void ins2E() {regs.L = fetchByte(); }
void ins3E() {regs.A = fetchByte(); }


void (*instrs[256])(void) = {
	ins00, ins01, ins02, ins03, ins04, ins05, ins06, ins07, ins08, ins09, ins0A, ins0B, ins0C, ins0D, ins0E, ins0F,
	ins10, ins11, ins12, ins13, ins14, ins15, ins16, ins17, ins18, ins19, ins1A, ins1B, ins1C, ins1D, ins1E, ins1F,
	ins20, ins21, ins22, ins23, ins24, ins25, ins26, ins27, ins28, ins29, ins2A, ins2B, ins2C, ins2D, ins2E, ins2F,
	ins30, ins31, ins32, ins33, ins34, ins35, ins36, ins37, ins38, ins39, ins3A, ins3B, ins3C, ins3D, ins3E, ins3F,
	ins40, ins41, ins42, ins43, ins44, ins45, ins46, ins47, ins48, ins49, ins4A, ins4B, ins4C, ins4D, ins4E, ins4F,
	ins50, ins51, ins52, ins53, ins54, ins55, ins56, ins57, ins58, ins59, ins5A, ins5B, ins5C, ins5D, ins5E, ins5F,
	ins60, ins61, ins62, ins63, ins64, ins65, ins66, ins67, ins68, ins69, ins6A, ins6B, ins6C, ins6D, ins6E, ins6F,
	ins70, ins71, ins72, ins73, ins74, ins75, ins76, ins77, ins78, ins79, ins7A, ins7B, ins7C, ins7D, ins7E, ins7F,
	ins80, ins81, ins82, ins83, ins84, ins85, ins86, ins87, ins88, ins89, ins8A, ins8B, ins8C, ins8D, ins8E, ins8F,
	ins90, ins91, ins92, ins93, ins94, ins95, ins96, ins97, ins98, ins99, ins9A, ins9B, ins9C, ins9D, ins9E, ins9F,
	insA0, insA1, insA2, insA3, insA4, insA5, insA6, insA7, insA8, insA9, insAA, insAB, insAC, insAD, insAE, insAF,
	insB0, insB1, insB2, insB3, insB4, insB5, insB6, insB7, insB8, insB9, insBA, insBB, insBC, insBD, insBE, insBF,
	insC0, insC1, insC2, insC3, insC4, insC5, insC6, insC7, insC8, insC9, insCA, insCB, insCC, insCD, insCE, insCF,
	insD0, insD1, insD2, insD3, insD4, insD5, insD6, insD7, insD8, insD9, insDA, insDB, insDC, insDD, insDE, insDF,
	insE0, insE1, insE2, insE3, insE4, insE5, insE6, insE7, insE8, insE9, insEA, insEB, insEC, insED, insEE, insEF,
	insF0, insF1, insF2, insF3, insF4, insF5, insF6, insF7, insF8, insF9, insFA, insFB, insFC, insFD, insFE, insFF,
};
