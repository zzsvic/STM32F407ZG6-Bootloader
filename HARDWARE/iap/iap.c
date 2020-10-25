#include "sys.h"
#include "iap.h"

iapfunc gotoApp;

u32 iapbuf[512];		// 2KB BUFFER

/******************************************************************************
 * 
 * addr		:应用程序的起始地址
 * appBuffer:应用程序CODE.
 * size		:程序大小(字节)
******************************************************************************/
void iap_write_appbin(u32 addr, u8 *appBuffer, u32 size)
{
	u32 t;
	u16 i = 0;
	u32 temp;
	u32 fwaddr = addr;
	u8 *dfu = appBuffer;
	
	for(t=0; t<size; t+=4)
	{
		temp = (u32)dfu[3] << 24;
		temp |= (u32)dfu[2] << 16;
		temp |= (u32)dfu[1] << 8;
		temp |= (u32)dfu[0];
		dfu += 4;
		iapbuf[i++]=temp;
		if(i==512){
			i = 0;
			flash_write(fwaddr, (u32*)appBuffer, 512);
			addr += 2048;
		}
	}
	if(i)
		flash_write(fwaddr, (u32*)appBuffer, i);
}

/******************************************************************************
 * 跳转到应用程序段
 * addr		:应用程序的起始地址
******************************************************************************/
void iap_load_app(u32 addr)
{
	if(((*(vu32*)addr)&0x2FFE0000)==0x20000000)
	{
		gotoApp = (iapfunc)*(vu32*)(addr+4);
		MSR_MSP(*(vu32*)addr);
		gotoApp();
	}
}
