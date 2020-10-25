#ifndef __FLASH_H__
#define __FLASH_H__
#include "sys.h"
#include "stm32f4xx_flash.h"

#define ADDR_FLASH_BASE		0x08000000				// STM32 FALSH 的起始地址

#define ADDR_FLASH_SECTOR_0		((u32)0x08000000)	// 扇区0起始地址， 	16Kbytes
#define ADDR_FLASH_SECTOR_1		((u32)0x08004000)	// 扇区1起始地址， 	16Kbytes
#define ADDR_FLASH_SECTOR_2		((u32)0x08008000)	// 扇区2起始地址， 	16Kbytes
#define ADDR_FLASH_SECTOR_3		((u32)0x0800C000)	// 扇区3起始地址， 	16Kbytes
#define ADDR_FLASH_SECTOR_4		((u32)0x08010000)	// 扇区4起始地址， 	64Kbytes
#define ADDR_FLASH_SECTOR_5		((u32)0x08020000)	// 扇区5起始地址， 	128Kbytes
#define ADDR_FLASH_SECTOR_6		((u32)0x08040000)	// 扇区6起始地址， 	128Kbytes
#define ADDR_FLASH_SECTOR_7		((u32)0x08060000)	// 扇区7起始地址， 	128Kbytes
#define ADDR_FLASH_SECTOR_8		((u32)0x08080000)	// 扇区8起始地址， 	128Kbytes
#define ADDR_FLASH_SECTOR_9		((u32)0x080A0000)	// 扇区9起始地址， 	128Kbytes
#define ADDR_FLASH_SECTOR_10	((u32)0x080C0000)	// 扇区10起始地址， 128Kbytes
#define ADDR_FLASH_SECTOR_11	((u32)0x080E0000)	// 扇区11起始地址， 128Kbytes

u32 flash_read_word(u32 faddr);
void flash_write(u32 waddr, u32 *pBuffer, u32 size);
void flash_read(u32 raddr, u32 *pBuffer, u32 size);
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite);
#endif
