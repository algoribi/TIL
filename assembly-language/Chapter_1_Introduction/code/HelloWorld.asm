%include "io64.inc"

section .text
global CMAIN
CMAIN:
    ;write your code here
    
    ;메모를 남길 수 있는 기능 = 주석
    
    ; 10진수(DEC) {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    
    ; 2진수(BIN) {0, 1}
    ; 0b0 0b1 0b10 0b11 0b100 ...
    
    ; 16진수(HEX) {0 ~ 9, A ~ F }
    ; 0x0 0x1 0x2 0x3 0x4 0x5 0x6 0x7 0x8 0x9 0xA 0xB 0xC 0xD 
    ; 0xE 0xF 0x10 ...
    
    ; 프로그래머에게 있어서 16진수를 쓰는 것이 유리 : 2진수와의 전환이 빠르기 때문
    
    
    PRINT_STRING msg
    
    xor rax, rax
    ret
    
section .data
    msg db 'Hello World', 0x00