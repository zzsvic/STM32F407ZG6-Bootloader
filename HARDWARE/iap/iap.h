#ifndef __IAP_H__
#define __IAP_H__
#include "sys.h"
#include "flash.h"
typedef void (*iapfunc)(void);					// 定义一个函数类型的参数
#define FLASH_APP1_ADDR			0x08010000

void iap_write_appbin(u32 addr, u8* buf, u32 size);
void iap_load_app(u32 addr);

#endif

