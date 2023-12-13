#include "ld2420.h"

uint8_t read_sensor(UART_HandleTypeDef *huart)
{
	uint8_t data;
	uint8_t bien;
	while(1)
	{
	HAL_UART_Receive(huart, &data, 1,10);
		if(data == 0x46)
		{
			bien =0;
			break;
		}
		else if(data == 0x4E)
		{
			bien =1;
			break;
		}
	}
	return bien;
}