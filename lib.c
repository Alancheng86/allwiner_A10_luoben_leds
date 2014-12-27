
/*
* Platform  for: allwiner  A10
* author  by jiangdou
* time  at: 2012-0801
*
*
*/



int putchar(int c)
{
	if (c == '\n')
	putc('\r');
	putc(c);
	return 0;
}