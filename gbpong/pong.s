.NINTENDOLOGO
.COMPUTEGBCHECKSUM
.COMPUTEGBCOMPLEMENTCHECK

.MEMORYMAP
SLOTSIZE $4000
DEFAULTSLOT 0
SLOT 0 $0000
SLOT 1 $4000
.ENDME
.ROMBANKSIZE $4000
.ROMBANKS 2
.BANK 0 SLOT 0

.ENUM $C000
paddleX DB
ballX DB
ballY DB
speedX DB
speedY DB
.ENDE

.ORG $0040
jp VBlank

.ORG $0100
nop
jp start

.ORG $800
Tiles:
.INCBIN "tiles.bin"

.org $0150
start:
	di				; Disable interrupts
	ld sp, $FFFE	; Init stack pointer
	xor a
	ldh ($26), a	; Sound off

	ld a, $20		; Init variables
	ld (paddleX), a
	ld a, $80
	ld (ballX), a
	ld (ballY), a
	ld a, 2
	ld (speedX), a
	ld (speedY), a

waitvbl:
	ldh a, ($44)
	cp 144
	jr c, waitvbl

	xor a
	ldh ($40),a		; LCD off
	ld b, 3*16		; 3 tiles == 48 bytes
	ld de, Tiles	; src
	ld hl, $8000	; vram
load_sprites:
	ld a, (de)
	ldi (hl), a
	inc de
	dec b
	jr nz, load_sprites

	ld de, 32*32
	ld hl, $9800	; BG tile map
clear_bg_tile_map:
	xor a
	ldi (hl), a
	dec de
	ld a, e
	or d
	jr nz, clear_bg_tile_map

	ld b, 40*4
	ld hl, $fe00	; OAM
clear_sprite_attr:
	xor a
	ldi (hl), a
	dec b
	jr nz, clear_sprite_attr

	xor a
	ldh ($42), a	; SCY
	ldh ($43), a	; SCX
	
	ld hl, $fe00	; OAM
	ld a, (paddleX)
	ld b, 4
draw_paddle:
	ld (hl), 144
	inc hl
	ld (hl), a
	inc hl
	ld (hl), 1
	inc hl
	inc hl
	add 8
	dec b
	jr nz, draw_paddle
	
	ld (hl), $80	; Ball
	inc hl
	ld (hl), $80
	inc hl
	ld (hl), 2
	inc hl
	inc hl
	
	ld a, %11100100	; set palette
	ldh ($47), a
	ldh ($48), a
	ldh ($49), a
	ld a, %10010011	; LCD on
	ldh ($40), a
	
	ld a, %00000001	; enable V-Blank interrupt
	ldh ($ff), a
	ei
loop:
	halt
	nop
	jp loop
	
VBlank:
	ld hl, $ff00	; joypad
	ld a, %00100000	; check direction keys
	ld (hl), a
	ld a, (paddleX)
	bit 1, (hl)		; left
	jr nz, noleftpress
	dec a
	dec a
noleftpress:
	bit 0, (hl)		; right
	jr nz, norightpress
	inc a
	inc a
norightpress:
	ld (paddleX), a	; save new value
	ld a, (paddleX)
	ld hl, $fe01	; OAM sprite 1
	ld (hl), a
	add 8
	ld hl, $fe05	; OAM sprite 2
	ld (hl), a
	add 8
	ld hl, $fe09	; OAM sprite 3
	ld (hl), a
	add 8
	ld hl, $fe0d	; OAM sprite 4
	ld (hl), a
	add 8
	ld hl, ballX
	ld a, (speedX)
	add (hl)
	ld (hl), a
	ld hl, $fe11
	ld (hl), a
	reti
