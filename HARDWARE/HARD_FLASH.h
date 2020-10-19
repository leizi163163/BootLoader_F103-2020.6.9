#ifndef __HARD_FLASH_H
#define __HARD_FLASH_H

#include "stm32f10x.h"

typedef  void (*pFunction)(void);


#define ApplicationAddress    		0x08004000


/* STM32��������Ʒÿҳ��С2KByte���С�С������Ʒÿҳ��С1KByte */
#if defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_CL) || defined (STM32F10X_XL)
	#define FLASH_PAGE_SIZE    ((uint16_t)0x800)	//2048
  
	//������оƬ��ǰ16KΪBoot�������240KΪAPPӦ��������240KΪ���������������16KΪ�����洢����

	#define FLASH_USER_APP_START_ADDR				((uint32_t)0x08004000)			//APP��ʼFLASH��--����
	#define FLASH_USER_APP_END_ADDR					((uint32_t)0x08040000)			//APP����FLASH��--������
	#define FLASH_USER_BUFFER_START_ADDR			((uint32_t)0x08040000)			//����ʱ�Ļ��濪ʼFLASH��--����
	#define FLASH_USER_BUFFER_END_ADDR				((uint32_t)0x0807C000)			//����ʱ�Ļ������FLASH��--������
#else
	#define FLASH_PAGE_SIZE    ((uint16_t)0x400)	//1024
  
	//������оƬ��ǰ16KΪBoot�������55KΪAPPӦ��������55KΪ���������������2KΪ�����洢����

	#define FLASH_USER_APP_START_ADDR				((uint32_t)0x08004000)			//APP��ʼFLASH��--����
	#define FLASH_USER_APP_END_ADDR					((uint32_t)0x08011C00)			//APP����FLASH��--������
	#define FLASH_USER_BUFFER_START_ADDR			((uint32_t)0x08011C00)			//����ʱ�Ļ��濪ʼFLASH��--����
	#define FLASH_USER_BUFFER_END_ADDR				((uint32_t)0x0801F800)			//����ʱ�Ļ������FLASH��--������

#endif





																			
#define BIN_COMPLETE_FLAG_ADDR    	FLASH_USER_BUFFER_START_ADDR
#define BIN_FILE_LEN_ADDR    		(FLASH_USER_BUFFER_START_ADDR + 4)

#define BIN_COMPLETE_FLAG    		0x55AAAA55





uint8_t FLASH_ReadByte(uint32_t address);
uint16_t FLASH_ReadHalfWord(uint32_t address);
uint32_t FLASH_ReadWord(uint32_t address);

void STMFLASH_Erase(uint32_t start_address,uint32_t end_address);
void STMFLASH_Write(uint32_t address,uint8_t *pBuffer,uint16_t pBuffer_Num);		//��ָ����ַ��ʼд��ָ�����ȵ�����	

void USER_IAPLoadAPP(void);

#endif

















