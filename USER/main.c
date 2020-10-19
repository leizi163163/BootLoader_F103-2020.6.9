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
*����ԭ�ͣ�USER_Variable_Init();
*��ڲ�������
*���ڲ�������
*�������ܣ�������ʼ��
*
*******************************************************************************/
void USER_Variable_Init(void)
{
	
}


int main(void)
{
	USER_Variable_Init();												//������ʼ��												//LED��ʾGPIO�˿ڳ�ʼ��
//	USER_SysTick_Init();												//Cortex-M3�ں˶�ʱ����ʼ��
//	USER_SysTick_Start();												//Cortex-M3�ں˶�ʱ����ʼ

	
	USER_USART1_Config(115200);											//����1���ã�921600
//	USER_USART2_Config(921600);											//����2���ã�921600
//	USER_USART3_Config(460800);
	USER_NVIC_Config();													//�ж�����

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
		
		//��ת��Ӧ�ó���
		USER_IAPLoadAPP();				//����Ӧ�ó���ǰ���رմ����жϣ��رմ���
		
		//���û��Ӧ�ó��򣬻�Ӧ�ó�����������´򿪴����жϣ��򿪴���
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

