#include <stdio.h>
#include <string.h>
#include <asm/ioports.h>
#include <cpu/isr.h>
#include <drivers/keyboard.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>
#define	RELEASED(code)	((code) & 0x80)

static char keyboard_buffer[BUFSIZ];
static void (*flush_handler)(const char*)=NULL;

#define	MAX_SCANCODE	58

const char scancode_table[]="??1234567890-=\b\tqwertyuiop[]\n?asdfghjkl;'`?\\zxcvbnm,./??? ?";
const char shift_table[]="..!@#$%^&*()_+\b\tQWERTYUIOP{}\n.ASDFGHJKL:\"~.|ZXCVBNM<>?.*. ?";

struct {
	uint8_t ctrl:1;
	uint8_t shift:1;
	uint8_t alt:1;
	uint8_t caps:1;
	uint8_t interrupt:1;
	uint8_t special:1;
	uint8_t reserved:2;
} __attribute__((packed)) kbd_state;

/* JUST FOR CONVENIENCE */
static char toupper(char c)
{
	if(c>='a' && c<='z'){
		return (c=c+'A'-'a');
	}else{
		return c;
	}
}

static char tolower(char c)
{
	if(c>='A' && c<='Z'){
		return (c=c+'a'-'A');
	}else{
		return c;
	}
}

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

char kbd_parse_code(uint8_t code)
{
	if(kbd_state.caps&&!kbd_state.shift){
		return toupper(scancode_table[code]);
	}else if(!kbd_state.caps&&kbd_state.shift){
		return shift_table[code];
	}else if(kbd_state.caps&&kbd_state.shift){
		return tolower(shift_table[code]);
	}else{
		return scancode_table[code];
	}
}

/* Standard function of reading character from keyboard */
int getchar(void)
{
	while(!kbd_state.interrupt||kbd_state.special==1);
	kbd_state.interrupt=0;
	uint8_t code=inb(0x60);
	char ch=kbd_parse_code(code);
	return ch;
}

static inline void backspace(void)
{
	int len=strlen(keyboard_buffer);
	if(len>0){
		putchar('\b');
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
	kbd_state.special=1;
	uint8_t scancode=inb(0x60);
	char ch;
	if(RELEASED(scancode)){
		scancode&=0x7F;
		// Handlers for released keys
		switch(scancode){
		case LSHIFT:case RSHIFT:
			kbd_state.shift=0;
			break;
		case CTRL:
			kbd_state.ctrl=0;
			break;
		case ALT:
			kbd_state.alt=0;
			break;
		}
		return;
	}
	if(scancode>MAX_SCANCODE){
		return;
	}
	switch(scancode){
	case BACKSPACE:
		backspace();
		kbd_state.special=0;
		break;
	case ENTER:
		putchar('\n');
		kbd_flush();
		kbd_state.special=0;
		break;
	case LSHIFT:case RSHIFT:
		kbd_state.shift=1;
		break;
	case CTRL:
		kbd_state.ctrl=1;
		break;
	case ALT:
		kbd_state.alt=1;
		break;
	case CAPS:
		kbd_state.caps^=1;	// Toggle the bit
		break;
	default:
		kbd_state.special=0;
		ch=kbd_parse_code(scancode);
		putchar(ch);
		append(ch);
	}
}

void kbd_flush_handler(void (*handler)(const char*))
{
	memset(keyboard_buffer,0,BUFSIZ);	// Clear the buffer first
	flush_handler=handler;
}

void init_keyboard(void)
{
	kprint("Initializing keyboard...\n");
	assert(sizeof(kbd_state) == sizeof(char));	// Make sure it's 1 byte
	register_interrupt_handler(IRQ1,keyboard_callback);
}

