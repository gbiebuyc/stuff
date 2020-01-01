bits 16
org 0x7c00

%define GREEN 0x2020
%define BLACK 0x0020

    xor ax, ax
    mov ds, ax

    mov ss, ax      ; stack
    mov sp, 0x9c00

    mov ah, 0       ; text mode 80x25
    mov al, 3
    int 0x10

    mov ax, 0xb800  ; text video memory
    mov es, ax

    mov ah, 1
    mov ch, 0x20    ; hide cursor
    int 0x10

    mov ax, BLACK   ; fill screen in black
    xor di, di
    mov cx, 2000
    cld             ; clear direction flag
    rep stosw

    mov si, sprite  ; draw sprite
    mov di, 164     ; at row 2, col 3

    mov ax, GREEN   ; row 1
    mov cx, 8
    rep stosw
    add di, 144

    mov cx, 8       ; row 2
    rep stosw
    add di, 144

loop:
    mov cx, 8       ; row 3-8
    rep movsw
    add di, 144
    cmp si, endsprite
    jne loop

    add di, 160     ; print msg
    mov si, msg
    mov ah, 0x0b0
str_loop:
    lodsb
    stosw
    or al, al
    jnz str_loop

    cli
    hlt

sprite:
    dw GREEN, BLACK, BLACK, GREEN, GREEN, BLACK, BLACK, GREEN
    dw GREEN, BLACK, BLACK, GREEN, GREEN, BLACK, BLACK, GREEN
    dw GREEN, GREEN, GREEN, BLACK, BLACK, GREEN, GREEN, GREEN
    dw GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN
    dw GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN
    dw GREEN, GREEN, BLACK, GREEN, GREEN, BLACK, GREEN, GREEN
endsprite:
msg:
    db 'Hello world :)', 0

times 510-($-$$) db 0
dw 0xaa55
