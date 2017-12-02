mov     [bootDrive], dl ; DL contains the drive number used to boot.

mov ah,0x00 ; reset disk
int 0x13

            ; Load the next 16 sectors as boot code.
mov dx,0    ; Clear DX
mov ah,0x02 ; read sectors into memory
mov al,0x10 ; number of sectors to read (16)
mov dl,[bootDrive]  ; drive number to reset, previously stored on boot
mov ch,0    ; cylinder number
mov dh,0    ; head number
mov cl,2    ; starting sector number
mov es, 0x1000
mov bx,0    ; address to load to - Ends up being 0x1000:0000
int 0x13    ; call the interrupt routine
jmp 0x1000:0000
