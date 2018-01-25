#ifndef	__KBD_H_
#define	__KBD_H_
#define	VK_BACK		0x08
#define VK_TAB		0x09
#define	VK_RETURN	0x0A
#define	VK_SHIFT	0x10
#define	VK_CONTROL	0x11
#define	VK_MENU		0x12
#define	VK_PAUSE	0x13
#define	VK_CAPITAL	0x14
#define	VK_ESCAPE	0x1B
#define	VK_SPACE	0x20
#define	VK_END		0x23
#define	VK_HOME		0x24
#define	VK_LEFT		0x25
#define	VK_UP		0x26
#define	VK_RIGHT	0x27
#define	VK_DOWN		0x28
#define	VK_F1		0x70
#define	VK_F2		0x71
#define	VK_F3		0x72
#define	VK_F4		0x73
#define	VK_F5		0x74
#define	VK_F6		0x75
#define	VK_F7		0x76
#define	VK_F8		0x77
#define	VK_F9		0x78
#define	VK_F10		0x79
#define	VK_F11		0x7A
#define	VK_F12		0x7B
#ifdef	__cplusplus
extern	"C"{
#endif
extern const char press_char[];
extern char _getchar(void);
extern char code2char(unsigned char code);
extern char getScancode();
#ifdef	__cplusplus
}
#endif
#endif
