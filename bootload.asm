BITS 16

jmp	bootloader_start
OEMLabel			db	"TravorOS"
BytesPerSector		dw	512
SectorsPerCluster	db	1
ReservedForBoot		dw	1
NumberOfFats		db	2
RootDirEntries		dw	224
LogicalSectors		dw	2880
MediumByte			db	0F0h
SectorsPerFat		dw	9
SectorsPerTract		dw	18
Sides				dw	2
HiddenSectors		dd	0
LargeSectors		dd	0
DriveNo				dw	0
Signature			db	41	; Drive signature: 41 for floppy
VolumeID			dd	2333ABCDh
VolumeLabel			db	"My First OS"
FileSystem			db	"FAT12"	; File System Type: Don't change
%INCLUDE	"features/io.inc"
bootloader_start:
	mov	[bootDrive],dl
	mov ax, 07C0h		; Set up 4K stack space after this bootloader
	add ax, 288		; (4096 + 512) / 16 bytes per paragraph
	mov ss, ax
	mov sp, 4096
	mov ax, 07C0h		; Set data segment to where we're loaded
	mov ds, ax
	mov	si,hello
	call	os_print_string
;	jmp	$
load_sectors:
	mov	dx,0	; Clear DX
	mov	ah,0x02	; read sectors into memory
	mov	al,0x10	; numbers of sectors to read (16)
	mov	dl,[bootDrive]	; drive number to reset, previously stored on boot
	mov	ch,0	; cylinder number
	mov	dh,0	; head number
	mov	cl,2	; starting sector number
	mov	es,0x1000
	mov	bx,0	; address to load to - Ends up being 0x1000:0000
	int	0x13
	jmp	0x1000:0000

	hello	db	"Hello world",0x0D,0x0A,0
	bootDrive	db	0
	times	510-($-$$)	db	0
	dw	0xAA55
