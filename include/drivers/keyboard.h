/* keyboard.h: A substitution for old keyboard driver `kbd' */
#ifndef	__KEYBOARD_H_
#define	__KEYBOARD_H_
#include <def.h>
/* Special Scancodes */
#define	BACKSPACE	0x0E
#define	ENTER		0x1C
#define	CTRL		0x1D
#define	LSHIFT		0x2A
#define	RSHIFT		0x36
#define	ALT		0x38
#define	CAPS		0x3A

#ifdef	__cplusplus
extern	"C"{
#endif
extern void init_keyboard(void);
extern uint8_t kbd_read(void);
extern int getchar(void);
#ifdef	__cplusplus
}
#endif
#endif

