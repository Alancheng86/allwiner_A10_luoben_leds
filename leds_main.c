#include "clock.h"
#include "uart.h"
#include "lib.h"
#define PB_CFG2          (*(volatile unsigned int *)0x01c2082c)
#define PE_DAT          (*(volatile unsigned int *)0x01c208A0)
#define PE_CFG          (*(volatile unsigned int *)0x01c20890)

/*
void delay(void)
{
	puts("delay open for leds on and off\n\r");
	int i,a;
	for (i=1;i<1000;i++)
	  for (a=1;a<1000;a++); 
	

}
*/
static inline void delay(unsigned long loops)
{
	puts("delay open for leds on and off\n\r");
	__asm__ volatile ("1:\n"
			"subs %0, %1, #1\n"
			"bne 1b":"=r" (loops):"0" (loops));
}

void gpio_init()
{
  /*bit[30:28]:PB23_SELECT 010:UART0_RX 
   *bit[26:24]:PB22_SELECT 010:UART0_TX
   */
  PB_CFG2 |= ((0x2<<24)|(0x2<<28));
  /**/
  PE_CFG |= ((0x1<<20)|(0x1<<24)|(0x1<<28));
}
int main(void)
{
	char c;
	clock_init(); /* 初始化时钟 */
	gpio_init();
	uart_init(); /* 初始化UART0 */
	puts("\n\r#####################################\n\r");
	puts("The board:Inet_97F_REV03\n\r");
	puts("The NAND: 256MB\n\r");
	puts("The SRAM:HY x4 512MB\n\r");
	puts("just bootloader linu        date: 2013.10.20;by jiangdou\n\r");
	puts("#####################################\n");

	while (1)
	{
		PE_DAT = 0x80;
		puts("GPIO_PE LED 1\n\r");
		delay(80000000);
		PE_DAT = 0x00;
		delay(80000000);
		PE_DAT = (0x1<<5);
		puts("GPIO_PE LED 2\n\r");
		delay(80000000);
		PE_DAT = (0x5<<5);
		puts("GPIO_PE LED 3\n\r");
		delay(80000000);
		PE_DAT = (0x2<<5);
		puts("GPIO_PE LED 4\n\r");
		delay(80000000);
		PE_DAT = (0x6<<5);
		puts("GPIO_PE LED 5\n\r");
		delay(80000000);
		PE_DAT = (0x3<<5);
		puts("GPIO_PE LED 6\n\r");
		delay(80000000);
		PE_DAT = (0x7<<5);
		puts("GPIO_PE LED 7\n\r");
		delay(80000000);
		PE_DAT = (0x0<<5);
		puts("GPIO_PE LED 8\n\r");
	}
	return 0;
}