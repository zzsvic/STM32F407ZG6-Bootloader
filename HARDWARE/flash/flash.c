#include "flash.h"

u32 flash_read_word(u32 faddr)
{
	return *(vu32*)faddr;
}
/******************************************************************************
 *  获取某个地址所在扇区
 * addr: flash地址
 * return 
 * 		-- 0-11,即addr所在扇区地址
******************************************************************************/
uint16_t flash_Get_FlashSector(u32 addr)
{
	if(addr < ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
	else if (addr < ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
	else if (addr < ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
	else if (addr < ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
	else if (addr < ADDR_FLASH_SECTOR_8)return FLASH_Sector_4;
	else if (addr < ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
	else if (addr < ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
	else if (addr < ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
	else if (addr < ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
	else if (addr < ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
	else if (addr < ADDR_FLASH_SECTOR_11)return FLASH_Sector_10;
	return FLASH_Sector_11;
}

/******************************************************************************
 * 从指定地址开始写入指定长度的数据
 * 特别注意:因为STM32F4的扇区实在太大,没办法本地保存扇区数据,所以本函数
 *          写地址如果非0XFF,那么会先擦除整个扇区且不保存扇区数据.所以
 *          写非0XFF的地址,将导致整个扇区数据丢失.建议写之前确保扇区里
 *          没有重要数据,最好是整个扇区先擦除了,然后慢慢往后写. 
 * addr: flash地址
 * 该函数对OTP区域也有效!可以用来写OTP区!
 * OTP区域地址范围:0X1FFF7800~0X1FFF7A0F
 * waddr:起始地址(此地址必须为4的倍数!!)
 * pBuffer:数据指针
 * size:字(32位)数(就是要写入的32位数据的个数.)
******************************************************************************/
void flash_write(u32 waddr, u32 *pBuffer, u32 size)
{
	FLASH_Status status = FLASH_COMPLETE;
	u32 addrx = 0;
	u32 endaddr = 0;
	
	if (waddr < ADDR_FLASH_BASE||waddr%4)return;		// 非法地址
	FLASH_Unlock();										// 解锁
	FLASH_DataCacheCmd(DISABLE);						// FLASH 擦出期间，必须禁止数据缓存
	
	addrx = waddr;										// 写入起始地址
	endaddr = waddr + size*4;							// 写入结束地址

	if (addrx < 0x1FFF0000)								// 只有主存储区，才需要执行擦除操作
	{
		while(addrx < endaddr){							// 扫清一切障碍.(对非FFFFFFFF的地方，先擦除)
			if (flash_read_word(addrx) != 0xFFFFFFFF){	// 有非FFFFFFFF的地方，要擦除这个扇区
				status = FLASH_EraseSector(flash_Get_FlashSector(addrx), VoltageRange_3);	//VCC = 2.7~3.6之间
				if(status != FLASH_COMPLETE)break; 		// 发生错误
			}else addrx += 4;
		}
	}
	
	if (status == FLASH_COMPLETE){
		while(waddr < endaddr){							// 写数据
			if(FLASH_ProgramWord(waddr, *pBuffer) != FLASH_COMPLETE) // 写入数据
				break;									// 写入异常
			waddr += 4;
			pBuffer++;
		}
	}
	FLASH_DataCacheCmd(ENABLE);							// FLASH 擦除结束，开启数据缓存
	FLASH_Lock();										// 上锁
}

/******************************************************************************
 * 从指定地址开始读出指定长度的数据
 * raddr:起始地址
 * pBuffer:数据指针
 * size:字(4位)数
******************************************************************************/
void flash_read(u32 raddr, u32 *pBuffer, u32 size)
{
	u32 i = 0;
	for( i = 0; i < size; i++){
		pBuffer[i] = flash_read_word(raddr);
		raddr += 4;
	}
}
