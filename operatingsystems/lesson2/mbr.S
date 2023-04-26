#define SECT_SIZE 512

.code16

.globl _start

_start:
    lea (msg), %si      //R[si]=&msg;

again:
    movb (%si), %al     //R[al]=*R[si];
    incw %si            //R[si]++
    orb %al, %al        //if(!R[al])
    jz done
    movb $0x0e, %ah
    movb $0x00, %bh
    int $0x10
    jmp again

done:
    jmp done

msg:
    .asciz "This is a baby step towards operating system!\r\n"

.org SECT_SIZE - 2
.byte 0x55,0xAA
