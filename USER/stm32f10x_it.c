/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	SysTickCount++;
	if(SysTickCount >= 100)
	{
		SysTickCount = 0;
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/


/*******************************************************************************
*
*函数原型：
*入口参数：无
*出口参数：无
*函数功能：DMA1通道4中断服务，
*
*******************************************************************************/
void DMA1_Channel4_IRQHandler(void)
{	
	
}


/*******************************************************************************
*
*函数原型：
*入口参数：无
*出口参数：无
*函数功能：DMA1通道5中断服务，
*
*******************************************************************************/
void DMA1_Channel5_IRQHandler(void)
{	
	
}

/*******************************************************************************
*
*函数原型：
*入口参数：无
*出口参数：无
*函数功能：串口1中断服务，
*
*******************************************************************************/

void USART1_IRQHandler(void)
{
	uint16_t crc_temp = 0;
	uint16_t buf_len1 = 0;
	
	//串口接收中断
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET) 
	{     
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		USART1_ReceiveBuff[USART1_ReceiveDataCount++] = USART1->DR & (uint16_t)0x01FF;
	}	
	
	//串口空闲检测中断
	if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET) 
	{     
		USART_IdleClear = USART1 ->SR;								//序列清空闲标志位
		USART_IdleClear = USART1->DR;								//序列清空闲标志位
																	//读出值没有用
		
		
		if(!strncmp((const char *)USART1_ReceiveBuff,String_ResetDeviceCommand,strlen(String_ResetDeviceCommand)))
		{
			SoftReset();
			USART1_ReceiveDataCount = 0;
			return;
		}
		
		if((USART1_ReceiveBuff[0] == 0xFF) && (USART1_ReceiveBuff[1] == 0xFF))
		{
			buf_len1 = USART1_ReceiveBuff[6] * 256 + USART1_ReceiveBuff[7];
			if(USART1_ReceiveDataCount == buf_len1 + 2 + 6 + 2)
			{
				crc_temp = (USART1_ReceiveBuff[USART1_ReceiveDataCount - 2] << 8) | USART1_ReceiveBuff[USART1_ReceiveDataCount - 1];
				CRC_Value = USER_CRC16_X25(USART1_ReceiveBuff + 2,USART1_ReceiveDataCount - 2 - 2);
				if(CRC_Value == crc_temp)
				{
					if(USART1_ReceiveBuff[8] == PC_ENTER_BOOT_RQ)				//进入Boot指令
					{
						EnterBootFlag = 1;										//进入Boot标志
					}
					else
					{
						ReceiveOverFlag = 1;						
					}
				}
				else
				{
					//校验失败
					CrcErrFlag = 1;
				}
			}
		}
			
		USART1_ReceiveDataCount = 0;
		
	}	
}

/*******************************************************************************
*
*函数原型：
*入口参数：无
*出口参数：无
*函数功能：串口2中断服务，与辅STM32通信，接收的3个字节为本块地砖感应点数据
*
*******************************************************************************/
void USART2_IRQHandler(void)
{

}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
