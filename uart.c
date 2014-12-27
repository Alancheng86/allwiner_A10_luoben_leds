/*
* Platform  for: allwiner  A10
* author  by jiangdou
* time  at: 2012-0801
*
*
*/




#define UART0_LCR   (*(volatile unsigned int *)0x01C2800C) 
#define UART0_DLH   (*(volatile unsigned int *)0x01C28004) 
#define UART0_DLL   (*(volatile unsigned int *)0x01C28000) 
#define UART0_LSR   (*(volatile unsigned int *)0x01C28014) 
#define UART0_THR   (*(volatile unsigned int *)0x01C28000) 
#define UART0_RBR   (*(volatile unsigned int *)0x01C28000) 

void uart_init(void)
{
  /*select dll dlh*/
  /*bit7:Divisor Latch Access Bit
   *0:Select RX Buffer Register(RBR)/TX Holding Register(THR)and Interrupt Enable register(IER)
   *1:Select Divisor Latch LS Register(DLL) and Divisor Latch MS Register(DLM)
   */
  UART0_LCR = 0x80;
  /*set baudrate*/
  UART0_DLH = 0x0;
  /*bit[7:0]:Divisor Latch Low
   *baud rate=(serial clock freq)/(16*divisor)
   *divisor=24M/16/115200=13.02083
   */
  UART0_DLL = 0xd; 
  /*set line control*/
  /*bit3:Parity Enable 0:parity disable 1:parity enable
   *bit2:Number of stop bits 
   *0:1 stop bit;1:1.5 stop bits when DLS(LCR[1:0]is zero,else 2 stop bits)
   *bit[1:0] Data Length Select 00:5bits;01:6bits;10:7bits;11:8bits
   */
  UART0_LCR = ((0<<3)|(0<<2)|0x3);
}

char getc(void)
{
	char c;
	while (!(UART0_LSR & (1<<0)));
	c = UART0_RBR; 
	return c;
}

void putc(char c)
{

	while (!(UART0_LSR & (1<<6)));
	UART0_THR = c; 
	return;
}
void puts(char *str)
{
	int i = 0;
	while (str[i])
	{
		putc(str[i]);
		i++;
	}
}