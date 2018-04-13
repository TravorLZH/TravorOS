#include <stddef.h>
#include <asm/string.h>
#include <asm/ioports.h>
#include <cpu/isr.h>
#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>

#define	BACKSPACE	0x0E
#define	ENTER		0x1C

static char keyboard_buffer[BUFSIZ];
static void (*flush_handler)(const char*)=NULL;

#define	MAX_SCANCODE	57

const char scancode="??1234567890-=??qwertyuiop[]??asdfghjkl;'`?\\zxcvbnm,./??? ";

void kbd_flush(void)
{
	flush_handler(keyboard_buffer);
	memset(keyboard_buffer,0,BUFSIZ);
}

static inline void backspace(void)
{
	int len=strlen(keyboard_buffer);
	if(len>0){
		buf[len-1]='\0';
	}
}

/* Append character to keyboard buffer */
static inline void append(char c)
{
	int len=strlen(keyboard_buffer);
	s[len]=c;
	s[len+1]='\0';
}

static void keyboard_callback(registers_t regs)
{
	uint8_t scancode=inb(0x60);
	if(scancode>MAX_SCANCODE){
		return;
	}
	switch(scancode){
	case BACKSPACE:
		backspace();
		break;
	case ENTER:
		kbd_flush();
		break;
	default:
		append(scancode[code]);
	}
}

void kbd_flush_handler(void (*handler)(const char*),char override)
{
	if(!override&&flush_handler!=NULL){
		return;
	}
	flush_handler=handler;
}

void init_keyboard(void)
{
	kprint("Initializing keyboard...\n");
	kbd_setbuf(keyboard_buffer);
	register_interrupt_handler(IRQ1,keyboard_callback);
}
