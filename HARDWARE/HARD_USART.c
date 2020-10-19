
#include "stm32f10x.h"

uint16_t USART_IdleClear;

uint8_t USART1_ReceiveBuff[DATA_FRAME_SIZE];
uint16_t USART1_ReceiveDataCount = 0;

uint8_t ReceiveOverFlag = 0;
uint8_t EnterBootFlag = 0;
uint8_t CrcErrFlag = 0;

char const String_ResetDeviceCommand[] = "Reset Device Command!";


/************************************************************************************************/

/*******************************************************************************
*
*函数原型：USER_USART1_Config(uint32_t baud_rate);
*入口参数：baud_rate，波特率
*出口参数：无
*函数功能：串口1初始化
*
*******************************************************************************/

void USER_USART1_Config(uint32_t baud_rate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = baud_rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART1, ENABLE);
	
//	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	
	USART_GetFlagStatus(USART1, USART_FLAG_TC);						//解决第一字节丢失现象

}


/*******************************************************************************
*
*函数原型：USER_USART2_Config(uint32_t baud_rate);
*入口参数：baud_rate，波特率
*出口参数：无
*函数功能：串口2初始化
*
*******************************************************************************/
void USER_USART2_Config(uint32_t baud_rate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = baud_rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2,&USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
	USART_GetFlagStatus(USART2, USART_FLAG_TC);					//解决第一字节丢失现象
	
}

void USER_USART3_Config(uint32_t baud_rate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = baud_rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART3,&USART_InitStructure);

//	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

//	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART3, ENABLE);
	
//	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
//	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
	
	USART_GetFlagStatus(USART3, USART_FLAG_TC);						//解决第一字节丢失现象

}

 

/*******************************************************************************
*
*函数原型：USART_Send_String(USART_TypeDef* USARTx,uint8_t *usart_string,uint8_t usart_string_count);
*入口参数：USARTx,串口编号，USART1,	USART2,	USART3, UART4 or UART5	;
*		   usart_string,要发送的数据的首地址
*		   usart_string_count，要发送的数据个数
*出口参数：无
*函数功能：串口数据发送
*
*******************************************************************************/
void USART_Send_String(USART_TypeDef* USARTx,uint8_t *usart_string,uint8_t usart_string_count)
{
	uint8_t i;
	for(i = 0; i < usart_string_count; i++)
	{
//		USART_SendData(USARTx,*usart_string++);
		USARTx->DR = (*usart_string & (uint16_t)0x01FF);
		usart_string++;		
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
		USART_ClearFlag(USARTx,USART_FLAG_TC);
	}
		
}


//#define	USER_Debug
//#define	Usart1Debug
//#define	Usart6Debug


#ifdef	USER_Debug

uint8_t DebugTemp[1024];
uint16_t Debug_i;
uint8_t new_line[2] = "\r\n";

void log_title(char *title)
{	
	//120MHz运行时,计数器加1,时间为8.33ns;	因此计数器增加120,即为1us;
	
//	uint8_t temp = 0;
//	temp = sprintf((char *)DebugTemp,"%05d | ",DWT_CYCCNT / 72000);
//	USART_Send_String(USART3,DebugTemp,temp);


	while(*(uint8_t *)title != 0)
	{
		USART3->DR = (*(uint8_t *)title & (uint16_t)0x01FF);
		title++;		
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
		USART_ClearFlag(USART3,USART_FLAG_TC);
	}
	USART_Send_String(USART3,new_line,2);


}

void log_hex(char *title,uint8_t *hex,uint16_t len)
{	
	//120MHz运行时,计数器加1,时间为8.33ns;	因此计数器增加120,即为1us;
	
//	uint8_t temp = 0;
//	
//	temp = sprintf((char *)DebugTemp,"%05d | ",DWT_CYCCNT / 72000);
//	USART_Send_String(USART3,DebugTemp,temp);
	
	
	while(*(uint8_t *)title != 0)
	{
		USART3->DR = (*(uint8_t *)title & (uint16_t)0x01FF);
		title++;		
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
		USART_ClearFlag(USART3,USART_FLAG_TC);
	}
	
	for(Debug_i = 0; Debug_i < len; Debug_i++)
	{
		sprintf((char *)(DebugTemp + Debug_i * 2),"%02X",hex[Debug_i]);
	}
	USART_Send_String(USART3,DebugTemp,len * 2);
	USART_Send_String(USART3,new_line,2);

	

}

#else
void log_title(char *title)
{

}

void log_hex(char *title,uint8_t *hex,uint16_t len)
{

}
#endif



