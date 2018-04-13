#include <kernel/shell.h>
#include <kernel/syscall.h>
#include <config.h>

void enter_shell(void)
{
	char *cmd=(char*)kmalloc(512);	// Shell buffer
terminal_loop:
	print_at("TravorOS> ",-1,-1,0x0E);
	gets(cmd);
	if(!strcmp(cmd,"help")){
		printf("TravorOS version " VERSION "\n\n");
		printf("Commands:\n");
		printf("about:    Information about this OS\n");
		printf("clear:    Clear the terminal screen\n");
		printf("shutdown: Shutdown the machine\n");
		printf("delay:    Delay 1 second\n");
		printf("reboot:   Reboot this machine\n");
		printf("bsod:     Trigger a Blue Screen of Death\n");
		printf("help:     Display this page\n");
		printf("print:    Call sys_print\n");
		printf("\nThis OS is built for i386\n");
		printf("Report bugs to " BUGREPORT "\n");
		goto terminal_loop;
	}
	if(!strcmp(cmd,"print")){
		sys_puts("Hello world!\n");
		goto terminal_loop;
	}
	if(!strcmp(cmd,"about")){
		printf("TravorOS version " VERSION "\nwritten by Travor Liu\nReport bugs to " BUGREPORT "\n");
		goto terminal_loop;
	}
	if(!strcmp(cmd,"bsod")){
		char *ptr=(char*)0x3000;
		*ptr=1;
		goto terminal_loop;
	}
	if(!strcmp(cmd,"clear")){
		clear_screen(0x07);
		goto terminal_loop;
	}
	if(!strcmp(cmd,"reboot")){
		reboot();
		goto terminal_loop;
	}
	if(!strcmp(cmd,"shutdown")){
		shutdown();
		goto terminal_loop;
	}
	if(!strcmp(cmd,"delay")){
		delay(1000);
		goto terminal_loop;
	}
	if(!strlen(cmd)){
		goto terminal_loop;
	}
	print_at("Unknown Command, type `help' to see available commands\n",-1,-1,0x04);
	goto terminal_loop;
}
