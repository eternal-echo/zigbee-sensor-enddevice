/**
 * Copyright (c) 2020~2022 iotlucker.com, All Rights Reserved.
 *
 * @Official Store: https://shop233815998.taobao.com
 * @Official Website & Online document: http://www.iotlucker.com
 * @WeChat Official Accounts: shanxuefang_iot
 * @Support: 1915912696@qq.com
 */
#ifndef HW_LIGHT_H
#define HW_LIGHT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_delay.h"
#include "cc2530_ioctl.h"
  
/** @brief Lighting type:
 *      On/Off Lighting,
 *      Dimmable Lighting
 */
#define HW_LIGHT_TYPE_ONOFF             0
#define HW_LIGHT_TYPE_DIMMABLE          1
  
/** @brief Lighting GPIO
 */
#define HW_LIGHT_GPIO_P04               0
#define HW_LIGHT_GPIO_P14               1

void hwLight_Init(uint8 type, uint8 gpio);

void hwLight_SetOn(uint8 gpio);
void hwLight_SetOff(uint8 gpio);
void hwLight_SetLevel(uint8 gpio, uint8 level);
  

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HW_LIGHT_H */