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
uint8_t read_range(UART_HandleTypeDef *huart)
{
	uint8_t data[20];
	uint8_t bien=read_sensor(huart);
	uint8_t range;
	if(bien == 1)
	{
		HAL_UART_Receive(huart, data, 11,10);
		if(data[10] == 0x0D) int range = data[9] - '0';
		else 
		{
		int range = (data[9] - '0') * 10 + (data[10] - '0');
		return range;
		}
	}
	else return 1;
}
