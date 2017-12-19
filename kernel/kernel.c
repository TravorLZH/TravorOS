
int main(void){
	__asm__("mov $65,%al");
	__asm__("mov $0x0F,%ah");
	__asm__("mov $0xb8000,%edx");
	__asm__("mov %ax,(%edx)");
	return 0;
}
