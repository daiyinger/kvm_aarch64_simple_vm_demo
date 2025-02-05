#include <misc.h>
#include <register.h>

uintptr_t read_current_el(void)
{
	uintptr_t el;

	asm volatile("mrs %0, CurrentEL"
		     :"=r"(el)::);

	return el>>2;
}
char *serial_test_str = "Hello Serial! I'm in guest! \r\n";
unsigned int *UART_DR = (unsigned int *)0x3F201000; //0x7e201000;

void delay(int i)
{
	while(i--);
}

int main(void)
{
	int i;
	printf("Hello World, Guest is in EL%lld\n", read_current_el());
	printf("UART_DR:%x\n", *UART_DR);
	for(i = 0; i < strlen(serial_test_str); i++)
	{
		*UART_DR = serial_test_str[i];
		delay(10000);
	}
	return 0;
}
