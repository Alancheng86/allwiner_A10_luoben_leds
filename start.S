/*
* Platform  for: allwiner  A10
* author  by jiangdou
* time  at: 2012-0801
*
*
*/




.global _start
_start:
	ldr r0,=0x1c20890	
	ldr r1,=0x1000000
	str r1,[r0]
	
	ldr r0,=0x1c208a0
	ldr r1,=0x40
	str r1,[r0]
	ldr sp, =0x00007f00 //条用C程序之前设置好堆栈
	b main