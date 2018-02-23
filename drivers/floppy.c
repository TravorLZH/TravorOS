/* floppy.c: A stub for my floppy driver */
#include <drivers/floppy.h>
#include <cpu/isr.h>

static void floppy_handler(registers_t reg){
  printf("Floppy IRQ received!\n");
}

void init_floppy(void){
  register_interrupt_handler(IRQ6,floppy_handler);
}
