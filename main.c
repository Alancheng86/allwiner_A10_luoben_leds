/*
* Platform  for: allwiner  A10
* author  by jiangdou
* time  at: 2012-0801
*
*
*/

#include "clock.h"
#include "uart.h"
#include "lib.h"
#define PB_CFG2          (*(volatile unsigned int *)0x01c2082c)
#define PE_6DAT          (*(volatile unsigned int *)0x01c208A0)

void delay(void)
{
	puts("delay open for leds on and off\n\r");
	int i,a;
	for (i=1;i<800;i++)
	  for (a=1;a<1000;a++); 
	

}
void gpio_init()
{
  /*bit[30:28]:PB23_SELECT 010:UART0_RX 
   *bit[26:24]:PB22_SELECT 010:UART0_TX
   */
  PB_CFG2 |= ((0x2<<24)|(0x2<<28));
}
int main(void)
{
	char c;
	clock_init(); /* 初始化时钟 */
	gpio_init();
	uart_init(); /* 初始化UART0 */
	puts("\n\r#####################################3\n\r");
	puts("The board:Inet_97F_REV03\n\r");
	puts("The NAND: 256MB\n\r");
	puts("The SRAM:HY x4 512MB\n\r");
	puts("just bootloader for LED        date: 2013.10.20;by jiangdou\n\r");
	puts("#####################################\n\r");

	while (1)
	{
		PE_6DAT=0x0;
		puts("GPIO_PE6 LED off\n\r");
		delay();
		PE_6DAT=0x40;
		puts("GPIO_PE6 LED on\n\r");
		delay();
	}
	return 0;
}