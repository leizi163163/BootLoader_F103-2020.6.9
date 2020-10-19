#ifndef __HARD_FLASH_H
#define __HARD_FLASH_H

#include "stm32f10x.h"

typedef  void (*pFunction)(void);


#define ApplicationAddress    		0x08004000


/* STM32大容量产品每页大小2KByte，中、小容量产品每页大小1KByte */
#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
	#define FLASH_PAGE_SIZE    ((uint16_t)0x800)	//2048
  
	//大容量芯片，前16K为Boot区，随后240K为APP应用区，再240K为升级缓存区，最后16K为常量存储区域

	#define FLASH_USER_APP_START_ADDR				((uint32_t)0x08004000)			//APP开始FLASH区--包含
	#define FLASH_USER_APP_END_ADDR					((uint32_t)0x08040000)			//APP结束FLASH区--不包含
	#define FLASH_USER_BUFFER_START_ADDR			((uint32_t)0x08040000)			//升级时的缓存开始FLASH区--包含
	#define FLASH_USER_BUFFER_END_ADDR				((uint32_t)0x0807C000)			//升级时的缓存结束FLASH区--不包含
#else
	#define FLASH_PAGE_SIZE    ((uint16_t)0x400)	//1024
  
	//中容量芯片，前16K为Boot区，随后55K为APP应用区，再55K为升级缓存区，最后2K为常量存储区域

	#define FLASH_USER_APP_START_ADDR				((uint32_t)0x08004000)			//APP开始FLASH区--包含
	#define FLASH_USER_APP_END_ADDR					((uint32_t)0x08011C00)			//APP结束FLASH区--不包含
	#define FLASH_USER_BUFFER_START_ADDR			((uint32_t)0x08011C00)			//升级时的缓存开始FLASH区--包含
	#define FLASH_USER_BUFFER_END_ADDR				((uint32_t)0x0801F800)			//升级时的缓存结束FLASH区--不包含

#endif





																			
#define BIN_COMPLETE_FLAG_ADDR    	FLASH_USER_BUFFER_START_ADDR
#define BIN_FILE_LEN_ADDR    		(FLASH_USER_BUFFER_START_ADDR + 4)

#define BIN_COMPLETE_FLAG    		0x55AAAA55





uint8_t FLASH_ReadByte(uint32_t address);
uint16_t FLASH_ReadHalfWord(uint32_t address);
uint32_t FLASH_ReadWord(uint32_t address);

void STMFLASH_Erase(uint32_t start_address,uint32_t end_address);
void STMFLASH_Write(uint32_t address,uint8_t *pBuffer,uint16_t pBuffer_Num);		//从指定地址开始写入指定长度的数据	

void USER_IAPLoadAPP(void);

#endif

















