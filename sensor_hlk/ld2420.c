#include "ld2420.h"

uint8_t read_sensor(UART_HandleTypeDef *huart)
{
	uint8_t data[2];
	uint8_t bien;
	HAL_UART_Receive(huart, data, 2,10);
		if(data == 0x4E)
		{
			bien =1;
		}
	else bien = 0;
	return bien;
}
