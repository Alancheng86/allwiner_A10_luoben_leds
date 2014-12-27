/*
* Platform  for: allwiner  A10
* author  by jiangdou
* time  at: 2012-0801
*
*
*/






#define CPU_AHB_APB0_CFG   (*(volatile unsigned int *)0x01c20054)
#define PLL1_CFG          (*(volatile unsigned int *)0x01c20000)
#define APB1_CLK_DIV_CFG   (*(volatile unsigned int *)0x01c20058)
#define APB1_GATE          (*(volatile unsigned int *)0x01c2006C)
void sdelay(unsigned long loops)
{
  __asm__ volatile("1:\n" "subs %0, %1, #1\n"
  "bne 1b":"=r" (loops):"0"(loops));
}
void clock_init(void)
{
  /*AXI_DIV_1[1:0]  AXI_CLK_DIV_RATIO 00:/1 AXI Clock source is CPU clock
   *AHB_DIV_2[5:4]  AHP_CLK_DIV_RATIO 01:/2 AHB Clock source is AXI CLOCK
   *APB0_DIV_1[9:8] APB0_CLK_RATIO    00:/2 APB0 clock source is AHB2 clock
   *CPU_CLK_SRC_OSC24M[17:16] CPU_CLK_SRC_SEL 01:OSC24M
   */
   CPU_AHB_APB0_CFG = ((0<<0)|(0x1<<4)|(0<<8)|(1<<16));

   /*bit31:PLL1_Enable 1:Enable
    *bit25:EXG_MODE 0x0:Exchange mode
    *bit[17:16]:PLL1_OUT_EXT_DIVP 0x0:P=1
    *bit[12:8]:PLL1_FACTOR_N 0x10:Factor=16,N=16
    *bit[5:4]:PLL1_FACTOR_K 0x0:K=1
    *bit3:SIG_DELT_PAT_IN 0x0
    *bit2:SIG_DELT_PAT_EN 0x0
    *bit[1:0]PLL1_FACTOR_M 0x0:M=1
    *The PLL1 output=(24M*N*K)/(M*P)=(24M*16*1)/(1*1)=384M is for the coreclk
    */
   PLL1_CFG = 0xa1005000;
   sdelay(200);

   CPU_AHB_APB0_CFG = ((0<<0)|(0x1<<4)|(0<<8)|(2<<16));//CPU_CLK_SRC_SEL 10:PLL1

   /*uart clock source is apb1,config apb1 clock*/
   /*bit[25:24]:APB1_CLK_SRC_SEL 00:OSC24M
    *bit[17:16]:CLK_RAT_N 0X0:1 The select clock source is pre-divided by 2^1
    *bit[4:0]:CLK_RAT_M 0x0:1 The pre-devided clock is divided by(m+1)
    */
   APB1_CLK_DIV_CFG = ((0<<5)|(0<<16)|(0<<24));
   /*open the clock for uart0*/
   /*bit16:UART0_APB_GATING 1:pass 0:mask*/
   APB1_GATE = (0x1<<16);
}
