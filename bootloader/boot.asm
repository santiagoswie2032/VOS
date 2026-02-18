[org 0x7C00]
bits 16

start:
	mov si, message

print:
	lodsb  				;loads byte from SI into AL
	cmp al, 0
	je done
	mov ah, 0x0E			;BIOS teletype function
	mov bh, 0x00			;page number
	mov bl, 0x07			;text color light gray
	int 0x10			; video interrupt
	jmp print

done:
	jmp $

message db "yoo wassup, im the bootloader ;)", 0

times 510 - ($-$$) db 0
dw 0xAA55
