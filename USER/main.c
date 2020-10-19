/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"


/*******************************************************************************
*
*函数原型：USER_Variable_Init();
*入口参数：无
*出口参数：无
*函数功能：变量初始化
*
*******************************************************************************/
void USER_Variable_Init(void)
{
	
}


int main(void)
{
	USER_Variable_Init();												//变量初始化												//LED显示GPIO端口初始化
//	USER_SysTick_Init();												//Cortex-M3内核定时器初始化
//	USER_SysTick_Start();												//Cortex-M3内核定时器开始

	
	USER_USART1_Config(115200);											//串口1配置，921600
//	USER_USART2_Config(921600);											//串口2配置，921600
//	USER_USART3_Config(460800);
	USER_NVIC_Config();													//中断配置

	USER_Delay1ms(600);
	
	USER_Buffer_To_App();
	
	if(EnterBootFlag == 1)
	{
		EnterBootFlag = 0;
		PC_EnterBootFunction();
	}
	else
	{
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);

		USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
		USART_Cmd(USART1, DISABLE);
		
		//跳转到应用程序
		USER_IAPLoadAPP();				//进入应用程序前，关闭串口中断，关闭串口
		
		//如果没有应用程序，或应用程序出错，则重新打开串口中断，打开串口
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
		USART_Cmd(USART1, ENABLE);
	}
	
	for( ; ;)
	{	
		if(ReceiveOverFlag == 1)
		{
			ReceiveOverFlag = 0;
			PC_DataProcess();
		}
		
		if(CrcErrFlag == 1)
		{
			CrcErrFlag = 0;
			PC_ReTransFrameFunction();
		}
	}	
}

