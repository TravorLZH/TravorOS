#include <def.h>
#include <asm/string.h>
#include <asm/ioports.h>
#include <cpu/isr.h>
#include <drivers/keyboard.h>
#include <drivers/screen.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>

#define	BACKSPACE	0x0E
#define	ENTER		0x1C
#define	CTRL		0x1D
#define	LSHIFT		0x2A
#define	RSHIFT		0x36

#define	RELEASED(code)	((code) & 0x80)
#define	TOGGLE(name)	((name)=~(name))

static char keyboard_buffer[BUFSIZ];
static void (*flush_handler)(const char*)=NULL;

#define	MAX_SCANCODE	57

const char scancode_table[]="??1234567890-=\b\tqwertyuiop[]\n?asdfghjkl;'`?\\zxcvbnm,./??? ";

struct {
	char ctrl:1;
	char shift:1;
	char caps:1;
	char interrupt:1;
	char reserved:4;
} __attribute__((packed)) kbd_state;

void kbd_flush(void)
{
	if(flush_handler!=NULL){
		flush_handler(keyboard_buffer);
	}
	memset(keyboard_buffer,0,BUFSIZ);
}

uint8_t kbd_read(void)
{
	while(!kbd_state.interrupt);
	kbd_state.interrupt=0;
	return inb(0x60);
}


int getchar(void)
{
	char ch=scancode_table[kbd_read()];
	print_char(ch,-1,-1,0x07);
	return ch;
}

static inline void backspace(void)
{
	int len=strlen(keyboard_buffer);
	if(len>0){
		keyboard_buffer[len-1]='\0';
	}
}

/* Append character to keyboard buffer */
static inline void append(char c)
{
	int len=strlen(keyboard_buffer);
	keyboard_buffer[len]=c;
	keyboard_buffer[len+1]='\0';
}

static void keyboard_callback(registers_t regs)
{
	kbd_state.interrupt=1;
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
		append(scancode_table[scancode]);
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
	assert(sizeof(kbd_state) == sizeof(char));	// Make sure it's 1 byte
	register_interrupt_handler(IRQ1,keyboard_callback);
}
