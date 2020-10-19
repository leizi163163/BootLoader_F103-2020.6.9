#include "stm32f10x.h"

 
pFunction Jump_To_Application;
uint32_t JumpAddress;


uint8_t FLASH_ReadByte(uint32_t address)
{
	return (uint8_t)(*(__IO uint32_t *)address);
}

uint16_t FLASH_ReadHalfWord(uint32_t address)
{
	return (uint16_t)(*(__IO uint32_t *)address);
}

uint32_t FLASH_ReadWord(uint32_t address)
{
	return (uint32_t)(*(__IO uint32_t *)address);
}

void STMFLASH_Erase(uint32_t start_address,uint32_t end_address)
{
	uint32_t i;
	
	/* 解锁 */
	FLASH_Unlock();
	/* 清空所有标志位 */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		
	//擦除FLASH
	for (i = start_address; i < end_address; i += FLASH_PAGE_SIZE)
	{
		if (FLASH_ErasePage(i) != FLASH_COMPLETE)
		{ 
			SoftReset();
		}
	}	
	/*擦除完毕*/	
	FLASH_Lock();  //读FLASH不需要FLASH处于解锁状态。
}
void STMFLASH_Write(uint32_t address,uint8_t *pBuffer,uint16_t pBuffer_Num)	
{
	uint32_t temp;
	
	FLASH_Unlock(); //解锁FLASH后才能向FLASH中写数据。
	
	/*开始写入*/
	while(pBuffer_Num > 0)
	{
		if(pBuffer_Num < 4)
		{
			switch(pBuffer_Num)
			{
				case 1:
//					temp = (0xFF << 24) | (0xFF << 16) | (0xFF << 8) | pBuffer[0];			//编译数据溢出
					temp = 0xFFFFFF00 + pBuffer[0];
					break;
				case 2:
					temp = 0xFFFF0000 + (pBuffer[1] << 8) | pBuffer[0];
					break;
				case 3:
					temp = 0xFF000000 +  (pBuffer[2] << 16) | (pBuffer[1] << 8) | pBuffer[0];
					break;
				default:
					break;
			}
		}
		else
		{
			temp = (pBuffer[3] << 24) | (pBuffer[2] << 16) | (pBuffer[1] << 8) | pBuffer[0];
		}
		FLASH_ProgramWord(address,temp);
		pBuffer += 4;
		address += 4;
		pBuffer_Num -= 4;
	}
	
	FLASH_Lock();  //读FLASH不需要FLASH处于解锁状态。
}


void USER_IAPLoadAPP(void)
{
	if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)  
	{   
		JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);  
		Jump_To_Application = (pFunction) JumpAddress;    
		__set_MSP(*(__IO uint32_t*) ApplicationAddress);  
		Jump_To_Application();  
	}  
	else  
	{  
//		USART_Send_String(USART2,"NO Program\r\n",12);  
	} 
}






