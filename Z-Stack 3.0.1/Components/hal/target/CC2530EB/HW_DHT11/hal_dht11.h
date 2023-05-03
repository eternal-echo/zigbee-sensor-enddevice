/**
 * Copyright (c) 2020~2022 iotlucker.com, All Rights Reserved.
 *
 * @Official Store: https://shop233815998.taobao.com
 * @Official Website & Online document: http://www.iotlucker.com
 * @WeChat Official Accounts: shanxuefang_iot
 * @Support: 1915912696@qq.com
 */
#ifndef HAL_DHT11_H
#define HAL_DHT11_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief   DHT11 GPIO. */
#define HAL_DHT11_PORT  0 //!< Port0.
#define HAL_DHT11_PIN   6 //!< Pin6.
   
/** @brief   DHT11 Data. */
typedef struct  {
    unsigned char ok;   //!< Is ok?
    unsigned char temp; //!< Temperature, 0~50.
    unsigned char humi; //!< Humidity, 20~95.
} halDHT11Data_t;

/**
 * @fn      halDHT11Init
 * 
 * @brief	Init. DHT11.
 */
void halDHT11Init(void);   
   
/**
 * @fn      halDHT11GetData
 * 
 * @brief	Get data from DHT11.
 *
 * @return  T&H value if ok is 1.
 */
halDHT11Data_t  halDHT11GetData(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef HAL_DHT11_H */
