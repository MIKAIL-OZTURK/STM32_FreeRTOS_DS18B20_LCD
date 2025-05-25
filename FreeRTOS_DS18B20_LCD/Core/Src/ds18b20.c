#include "ds18b20.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

void delay_us(uint16_t us) {
    uint32_t start = DWT->CYCCNT;
    uint32_t delayTicks = us * (HAL_RCC_GetHCLKFreq() / 1000000);
    while ((DWT->CYCCNT - start) < delayTicks);
}

void DS18B20_Init(void) {
    // DWT Delay aktif et (1us çözünürlük)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void Set_Pin_Output(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

void Set_Pin_Input(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS18B20_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
}

uint8_t DS18B20_Start(void) {
    uint8_t response = 0;
    Set_Pin_Output();
    HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
    delay_us(480);
    Set_Pin_Input();
    delay_us(80);

    if (!(HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN))) response = 1;
    else response = 0;

    delay_us(400);
    return response;
}

void DS18B20_Write(uint8_t data) {
    Set_Pin_Output();
    for (int i = 0; i < 8; i++) {
        if ((data & (1 << i)) != 0) {
            HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
            delay_us(1);
            HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
            delay_us(60);
        } else {
            HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
            delay_us(60);
            HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_SET);
        }
    }
}

uint8_t DS18B20_Read(void) {
    uint8_t value = 0;
    Set_Pin_Input();
    for (int i = 0; i < 8; i++) {
        Set_Pin_Output();
        HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);
        delay_us(1);
        Set_Pin_Input();
        if (HAL_GPIO_ReadPin(DS18B20_PORT, DS18B20_PIN)) {
            value |= 1 << i;
        }
        delay_us(60);
    }
    return value;
}

float DS18B20_GetTemp(void) {
    uint8_t temp_l, temp_h;
    int16_t temp;
    float temperature = 0;

    DS18B20_Start();
    DS18B20_Write(0xCC); // Skip ROM
    DS18B20_Write(0x44); // Convert T
    osDelay(750);        // Bekle

    DS18B20_Start();
    DS18B20_Write(0xCC); // Skip ROM
    DS18B20_Write(0xBE); // Read Scratchpad

    temp_l = DS18B20_Read();
    temp_h = DS18B20_Read();

    temp = (temp_h << 8) | temp_l;
    temperature = (float) temp / 16.0;

    return temperature;
}
