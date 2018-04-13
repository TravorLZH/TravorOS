/* keyboard.h: A substitution for old keyboard driver `kbd' */
#ifndef	__KEYBOARD_H_
#define	__KEYBOARD_H_
#include <def.h>
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

