
#ifndef DEF_ld2420_h
#define DEF_ld2420_h
#include "main.h"
#include "stm32f1xx_hal.h"

uint8_t read_sensor(UART_HandleTypeDef *huart);
uint8_t read_range(UART_HandleTypeDef *huart);
#endif
