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

void setFlags(char Z, char N, char H, char C) {
	if (Z==1) regs.F |= 0x80; else if (Z==0) regs.F &= ~0x80;
	if (N==1) regs.F |= 0x40; else if (N==0) regs.F &= ~0x40;
	if (H==1) regs.F |= 0x20; else if (H==0) regs.F &= ~0x20;
	if (C==1) regs.F |= 0x10; else if (C==0) regs.F &= ~0x10;
}

void add(int b) {
	int a = regs.A;
	setFlags(!((a+b)&0xff), 0, (((a&0xf)+(b&0xf))&0x10)==0x10, (a+b)>0xff);
	regs.A += b;
}

void compare(int b) {
	int a = regs.A;
	setFlags(a==b, 1, ((a&0xf)-(b&0xf))<0, b>a);
}

void subtract(int b) {
	compare(b);
	regs.A -= b;
}

void and(uint8_t operand) {
	regs.A &= operand;
	setFlags(!regs.A, 0, 1, 0);
}

void xor(uint8_t operand) {
	regs.A ^= operand;
	setFlags(!regs.A, 0, 0, 0);
}

void or(uint8_t operand) {
	regs.A |= operand;
	setFlags(!regs.A, 0, 0, 0);
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
void setFlagsInc(uint8_t operand) {setFlags(operand==1, 1, ((((int)operand)&0xf)-1)<0, '-'); }
void ins04() {setFlagsInc(regs.B++); }
void ins14() {setFlagsInc(regs.D++); }
void ins24() {setFlagsInc(regs.H++); }
void ins34() {uint8_t val=readByte(regs.HL); setFlagsInc(val); writeByte(regs.HL, val++); }
void ins0C() {setFlagsInc(regs.C++); }
void ins1C() {setFlagsInc(regs.E++); }
void ins2C() {setFlagsInc(regs.L++); }
void ins3C() {setFlagsInc(regs.A++); }
void setFlagsDec(uint8_t operand) {setFlags(operand==1, 1, ((((int)operand)&0xf)-1)<0, '-'); }
void ins05() {setFlagsDec(regs.B--); }
void ins15() {setFlagsDec(regs.D--); }
void ins25() {setFlagsDec(regs.H--); }
void ins35() {uint8_t val=readByte(regs.HL); setFlagsDec(val); writeByte(regs.HL, val--); }
void ins0D() {setFlagsDec(regs.C--); }
void ins1D() {setFlagsDec(regs.E--); }
void ins2D() {setFlagsDec(regs.L--); }
void ins3D() {setFlagsDec(regs.A--); }
void ins06() {regs.B = fetchByte(); }
void ins16() {regs.D = fetchByte(); }
void ins26() {regs.H = fetchByte(); }
void ins36() {writeByte(regs.HL, fetchByte()); }
void ins0E() {regs.C = fetchByte(); }
void ins1E() {regs.E = fetchByte(); }
void ins2E() {regs.L = fetchByte(); }
void ins3E() {regs.A = fetchByte(); }
void ins07() {} // TODO
void ins17() {} // TODO
void ins27() {} // TODO
void ins37() {} // TODO
void ins08() {writeWord(fetchWord(), SP); }
void ins09() { regs.HL+=regs.BC; setFlags('-', 0, 0, 0); }
void ins19() { regs.HL+=regs.DE; setFlags('-', 0, 0, 0); }
void ins29() { regs.HL+=regs.HL; setFlags('-', 0, 0, 0); }
void ins39() { regs.HL+=SP; setFlags('-', 0, 0, 0); }
void ins0A() { regs.A = readByte(regs.BC); }
void ins1A() { regs.A = readByte(regs.DE); }
void ins2A() { regs.A = readByte(regs.HL++); }
void ins3A() { regs.A = readByte(regs.HL--); }
void ins0F() {} // TODO
void ins1F() {} // TODO
void ins2F() {} // TODO
void ins3F() {} // TODO
void ins40() { regs.B = regs.B; }
void ins41() { regs.B = regs.C; }
void ins42() { regs.B = regs.D; }
void ins43() { regs.B = regs.E; }
void ins44() { regs.B = regs.H; }
void ins45() { regs.B = regs.L; }
void ins46() { regs.B = readByte(regs.HL); }
void ins47() { regs.B = regs.A; }
void ins50() { regs.D = regs.B; }
void ins51() { regs.D = regs.C; }
void ins52() { regs.D = regs.D; }
void ins53() { regs.D = regs.E; }
void ins54() { regs.D = regs.H; }
void ins55() { regs.D = regs.L; }
void ins56() { regs.D = readByte(regs.HL); }
void ins57() { regs.D = regs.A; }
void ins60() { regs.H = regs.B; }
void ins61() { regs.H = regs.C; }
void ins62() { regs.H = regs.D; }
void ins63() { regs.H = regs.E; }
void ins64() { regs.H = regs.H; }
void ins65() { regs.H = regs.L; }
void ins66() { regs.H = readByte(regs.HL); }
void ins67() { regs.H = regs.A; }
void ins70() { writeByte(regs.HL, regs.B); }
void ins71() { writeByte(regs.HL, regs.C); }
void ins72() { writeByte(regs.HL, regs.D); }
void ins73() { writeByte(regs.HL, regs.E); }
void ins74() { writeByte(regs.HL, regs.H); }
void ins75() { writeByte(regs.HL, regs.L); }
void ins76() {} // TODO
void ins77() { writeByte(regs.HL, regs.A); }
void ins48() { regs.C = regs.B; }
void ins49() { regs.C = regs.C; }
void ins4A() { regs.C = regs.D; }
void ins4B() { regs.C = regs.E; }
void ins4C() { regs.C = regs.H; }
void ins4D() { regs.C = regs.L; }
void ins4E() { regs.C = readByte(regs.HL); }
void ins4F() { regs.C = regs.A; }
void ins58() { regs.E = regs.B; }
void ins59() { regs.E = regs.C; }
void ins5A() { regs.E = regs.D; }
void ins5B() { regs.E = regs.E; }
void ins5C() { regs.E = regs.H; }
void ins5D() { regs.E = regs.L; }
void ins5E() { regs.E = readByte(regs.HL); }
void ins5F() { regs.E = regs.A; }
void ins68() { regs.L = regs.B; }
void ins69() { regs.L = regs.C; }
void ins6A() { regs.L = regs.D; }
void ins6B() { regs.L = regs.E; }
void ins6C() { regs.L = regs.H; }
void ins6D() { regs.L = regs.L; }
void ins6E() { regs.L = readByte(regs.HL); }
void ins6F() { regs.L = regs.A; }
void ins78() { regs.A = regs.B; }
void ins79() { regs.A = regs.C; }
void ins7A() { regs.A = regs.D; }
void ins7B() { regs.A = regs.E; }
void ins7C() { regs.A = regs.H; }
void ins7D() { regs.A = regs.L; }
void ins7E() { regs.A = readByte(regs.HL); }
void ins7F() { regs.A = regs.A; }
void ins80() { add(regs.B); }
void ins81() { add(regs.C); }
void ins82() { add(regs.D); }
void ins83() { add(regs.E); }
void ins84() { add(regs.H); }
void ins85() { add(regs.L); }
void ins86() { add(readByte(regs.HL)); }
void ins87() { add(regs.A); }
void ins90() { subtract(regs.B); }
void ins91() { subtract(regs.C); }
void ins92() { subtract(regs.D); }
void ins93() { subtract(regs.E); }
void ins94() { subtract(regs.H); }
void ins95() { subtract(regs.L); }
void ins96() { subtract(readByte(regs.HL)); }
void ins97() { subtract(regs.A); }
void insA0() { and(regs.B); }
void insA1() { and(regs.C); }
void insA2() { and(regs.D); }
void insA3() { and(regs.E); }
void insA4() { and(regs.H); }
void insA5() { and(regs.L); }
void insA6() { and(readByte(regs.HL)); }
void insA7() { and(regs.A); }
void insB0() { or(regs.B); }
void insB1() { or(regs.C); }
void insB2() { or(regs.D); }
void insB3() { or(regs.E); }
void insB4() { or(regs.H); }
void insB5() { or(regs.L); }
void insB6() { or(readByte(regs.HL)); }
void insB7() { or(regs.A); }
void ins88() {} // TODO
void ins89() {} // TODO
void ins8A() {} // TODO
void ins8B() {} // TODO
void ins8C() {} // TODO
void ins8D() {} // TODO
void ins8E() {} // TODO
void ins8F() {} // TODO
void ins98() {} // TODO
void ins99() {} // TODO
void ins9A() {} // TODO
void ins9B() {} // TODO
void ins9C() {} // TODO
void ins9D() {} // TODO
void ins9E() {} // TODO
void ins9F() {} // TODO
void insA8() { xor(regs.B); }
void insA9() { xor(regs.C); }
void insAA() { xor(regs.D); }
void insAB() { xor(regs.E); }
void insAC() { xor(regs.H); }
void insAD() { xor(regs.L); }
void insAE() { xor(readByte(regs.HL)); }
void insAF() { xor(regs.A); }
void insB8() { compare(regs.B); }
void insB9() { compare(regs.C); }
void insBA() { compare(regs.D); }
void insBB() { compare(regs.E); }
void insBC() { compare(regs.H); }
void insBD() { compare(regs.L); }
void insBE() { compare(readByte(regs.HL)); }
void insBF() { compare(regs.A); }


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
