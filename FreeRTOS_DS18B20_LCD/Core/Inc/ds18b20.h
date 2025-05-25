#ifndef __DS18B20_H
#define __DS18B20_H

#include "stm32f4xx_hal.h"

#define DS18B20_PORT GPIOA
#define DS18B20_PIN GPIO_PIN_1

void DS18B20_Init(void);
uint8_t DS18B20_Start(void);
void DS18B20_Write(uint8_t data);
uint8_t DS18B20_Read(void);
float DS18B20_GetTemp(void);

#endif
