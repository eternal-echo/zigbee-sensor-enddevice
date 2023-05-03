/**
 * Copyright (c) 2020~2022 iotlucker.com, All Rights Reserved.
 *
 * @Official Store: https://shop233815998.taobao.com
 * @Official Website & Online document: http://www.iotlucker.com
 * @WeChat Official Accounts: shanxuefang_iot
 * @Support: 1915912696@qq.com
 */
#include "hw_light.h"

#define HW_LIGHT_ON     1
#define HW_LIGHT_OFF    0

static void initTimer3PWM(uint8 lowLevelDuty);
static void timer3PWMStart(void);
static void timer3PWMStop(void);

static uint8 lightP14Type_g = 0xFF;

void hwLight_Init(uint8 type, uint8 gpio)
{
  switch(type)
  {
  case HW_LIGHT_TYPE_ONOFF:
    if (gpio == HW_LIGHT_GPIO_P04)
    {
      CC2530_IOCTL(0, 4, CC2530_OUTPUT);
    }
    else if(gpio == HW_LIGHT_GPIO_P14)
    {
      lightP14Type_g = HW_LIGHT_TYPE_ONOFF;
      CC2530_IOCTL(1, 4, CC2530_OUTPUT);
    }
    break;
    
  case HW_LIGHT_TYPE_DIMMABLE:
    if(gpio == HW_LIGHT_GPIO_P14)
    {
      lightP14Type_g = HW_LIGHT_TYPE_DIMMABLE;
      P1SEL |= (1 << 4);
      initTimer3PWM(100);
      timer3PWMStart();
    }
    break;
  }
}

void hwLight_SetOn(uint8 gpio)
{
    if(gpio == HW_LIGHT_GPIO_P04)
    {
        P0_4 = HW_LIGHT_ON;
    }
    else if(gpio == HW_LIGHT_GPIO_P14)
    {
      if(lightP14Type_g == HW_LIGHT_TYPE_ONOFF)
      {
        P1_4 = HW_LIGHT_ON;
      }
      else
      {
        hwLight_SetLevel(gpio, 100);
      }
    }
}

void hwLight_SetOff(uint8 gpio)
{
    if(gpio == HW_LIGHT_GPIO_P04)
    {
        P0_4 = HW_LIGHT_OFF;
    }
    else if(gpio == HW_LIGHT_GPIO_P14)
    {
      if(lightP14Type_g == HW_LIGHT_TYPE_ONOFF)
      {
        P1_4 = HW_LIGHT_OFF;
      }
      else
      {
        hwLight_SetLevel(gpio, 0);
      }
    }
}

void hwLight_SetLevel(uint8 gpio, uint8 level)
{
    uint8 lowLevel;
    
    if(gpio == HW_LIGHT_GPIO_P14 && lightP14Type_g != 0xFF)
    {
      if(level > 100)
        level = 100;

      lowLevel = 100 - level;
      
      timer3PWMStop();
      initTimer3PWM(lowLevel);
      timer3PWMStart();
    }
}

static void initTimer3PWM(uint8 lowLevelDuty)
{ 
    if(lowLevelDuty > 100)
      lowLevelDuty = 100;
  
    PERCFG &= ~(1<<5);  // Timer 3 I/O location: Alternative 1 location
    
    T3CTL = 0xE0;  // Tick frequency/128
                   // Free running, repeatedly count from 0x00 to 0xFF
    
    T3CCTL1 = 0x2C;  // Set output on compare, clear on 0xFF
                     // Compare mode

    T3CC1 = (uint8)((0x00FF * lowLevelDuty) / 100);  // low-level duty
}

static void timer3PWMStart(void)
{
    T3CTL |= (1 << 4);
}

static void timer3PWMStop(void)
{
    T3CTL &= ~(1 << 4);
}
