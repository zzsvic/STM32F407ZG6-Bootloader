#include "stm32f4xx.h"

#include "usart.h"
#include "delay.h"

#include "flash.h"

const u8 TEXT_Buffer[]={"STM32 FLASH TEST"};
#define TEXT_LENTH sizeof(TEXT_Buffer)	 		  	//数组长度	
#define SIZE TEXT_LENTH/4+((TEXT_LENTH%4)?1:0)
#define FLASH_SAVE_ADDR  0X0800C004
int main(void)
{
	u8 datatemp[SIZE];
	u8 oldcnt = 0;
	u8 applen = 0;
	u8 clearflag = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	uart_init(115200);
	delay_init(168);

	printf("********************************************************************************\n");
	printf("STM32 IAP v1.0 Build(2020-10-25 17:03:47)\n");
	printf("board: STM32F407ZGT6\n");
	printf("SRAM: 192KBytes\n");
	printf("ROM: 1024Kbytes\n");

	printf("********************************************************************************\n");
	while (1){
		if (USART_RX_CNT){
			if(oldcnt == USART_RX_CNT){
				applen = USART_RX_CNT;
				oldcnt = 0;
				USART_RX_CNT = 0;
				printf("用户程序接收完成!\n ");
				printf("代码长度：%dBytes\n",applen);
			}else oldcnt = USART_RX_CNT;
		}
	}
}

