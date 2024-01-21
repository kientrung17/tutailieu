/* 
 * LD2410C.c
 *
 * Created on: Jun 6, 2024
 * 	Author : KienTrung
 */
 
 #include "LD2410C.h" 
 
	void Enable_config(UART_HandleTypeDef *huart)
 {
	uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x04,0x00,0xFF,0x00,0x01,0x00,0x04,0x03,0x02,0x01};
	uint8_t Upward[20];
		while(1)
		{
			HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			HAL_UART_Receive(huart, Upward, 18, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
 }
  void End_config(UART_HandleTypeDef *huart)
 {
	 uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x02,0x00,0xFE,0x00,0x04,0x03,0x02,0x01};
	 uint8_t Upward[14];
		while(1)
		{
			HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
 }
 /* configuration range 2~8
		configuration range 0~65535 seconds
 */
	 void Max_distance_gate(UART_HandleTypeDef *huart,uint8_t mov,uint8_t rest,uint8_t duration)
	 {
		 uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x14,0x00,0x60,0x00,0x00,0x00,mov,0x00,0x00
		 ,0x00,0x01,0x00,rest,0x00,0x00,0x00,0x02,0x00,duration,0x00,0x00,0x00,0x04,0x03,0x02,0x01};
		 uint8_t Upward[20];
		while(1)
		{
			HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
	 }
	 void Read_parameter(UART_HandleTypeDef *huart, Ld2410Typedef *ld2410)
 {
	 uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x61,0x00,0x04,0x03,0x02,0x01};
	 uint8_t Upward[38];
	 HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
		while(1)
		{
			HAL_UART_Receive(huart, Upward, 38, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
		ld2410->gate.config_motion = Upward[12];
		ld2410->gate.config_rest = Upward[13];
		ld2410->gate.duration = (Upward[34] << 8)|Upward[33];
		
 }
	 void Enable_EngineeringMode(UART_HandleTypeDef *huart)
	{
		 uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x02,0x00,0x62,0x00,0x04,0x03,0x02,0x01};
		 uint8_t Upward[14];
		 HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
		while(1)
		{
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
	}
	 void Close_EngineeringMode(UART_HandleTypeDef *huart)
	{
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x02,0x00,0x63,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[14];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
	}
	void Range_gate_sensivity_config(UART_HandleTypeDef *huart,uint8_t door,uint8_t mov_sens,uint8_t static_sens)
	{
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x14,0x00,0x64,0x00,0x00,0x00,door,0x00,
					0x00,0x00,0x01,0x00,mov_sens,0x00,0x00,0x00,0x02,0x00,static_sens,0x00,
					0x00,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[14];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
	}
	
	void Get_version(UART_HandleTypeDef *huart,uint8_t *version)
	{
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x02,0x00,0xA0,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[20];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 20, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
		version[0] = Upward[11];
		version[1] = Upward[10];
		version[2] = Upward[15];
		version[3] = Upward[14];
		version[4] = Upward[13];
		version[5] = Upward[12];
	}
	/* support baudrate 9600,19200,38400,57600,115200,230400,256000,460800
			The factory default value is 0x0004, which is 57600
	*/
		void Baudrate_setting(UART_HandleTypeDef *huart,uint32_t baudrate)
	{
		uint8_t value;
		switch(baudrate)
		{
			case 9600:
				value = 0x01;
				break;
			case 19200:
				value = 0x02;
				break;
			case 38400:
				value = 0x03;
				break;
			case 57600:
				value = 0x04;
				break;
			case 115200:
				value = 0x05;
				break;
			case 230400:
				value = 0x06;
				break;
			case 256000:
				value = 0x07;
				break;
			case 460800:
				value = 0x08;
				break;
			default:
				value = 0x04;
			  break;
		}
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x04,0x00,0xA1,0x00,(uint8_t) value,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[14];
		
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
	}
		void factory_reset(UART_HandleTypeDef *huart)
	{
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x02,0x00,0xA2,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[14];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
	}
		void restart_module(UART_HandleTypeDef *huart)
	{
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x02,0x00,0xA3,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[14];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
	}
	void distance_resolution(UART_HandleTypeDef *huart,uint8_t distance)
	{
		uint8_t value;
		switch (distance)
    {
    	case 75:
				value = 0x00;
    		break;
    	case 20:
				value = 0x01;
    		break;
    	default :
				value = 0x00;
    		break;
    }
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x04,0x00,0xAA,0x00,value,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[14];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
		
	}
	 uint8_t query_distance_resolution(UART_HandleTypeDef *huart)
	{
		uint8_t dis_resolution;
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x02,0x00,0xAB,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[16];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 16, HAL_MAX_DELAY);
			if(Upward[10] == 0x01) {
				dis_resolution = 20;
				break;
			}
			else { dis_resolution = 75;
				break;
			}
		}
		return dis_resolution;
	}
	void Get_MacAddress(UART_HandleTypeDef *huart,uint8_t *address)
	{
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x04,0x00,0xA5,0x00,0x01,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[20];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 20, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
		for(int i=0;i<=5;i++)
		{
			address[i] = Upward[i+10];
		}
	}
	/* default is enabled */
	void Bluetooth_setting(UART_HandleTypeDef *huart)
	{
		uint8_t Downward[] = {0xFD,0xFC,0xFB,0xFA,0x04,0x00,0xA4,0x00,0x01,0x00,0x04,0x03,0x02,0x01};
		uint8_t Upward[14];
		HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
			while(1)
		{
			HAL_UART_Receive(huart, Upward, 14, HAL_MAX_DELAY);
			if(Upward[8] == 0x00) break;
		}
	}
	void read_sensor(UART_HandleTypeDef *huart,Ld2410Typedef *ld2410)
	{
		uint8_t Upward[23];
		uint8_t head;
		while(1)
		{
		HAL_UART_Receive(huart, &head, 1, HAL_MAX_DELAY);
			if(head == 0xFD)
			{
				End_config(huart);
				break;
			}
			if(head== 0xF4)
			{
				Upward[0] = head;
				HAL_UART_Receive(huart, &Upward[1], 22,HAL_MAX_DELAY);
				break;
			}
		}
		ld2410->state = Upward[8];
		ld2410->mov_distance = Upward[9];
		ld2410->mov_energy = Upward[11];
		ld2410->sta_distance = Upward[12];
		ld2410->sta_energy = Upward[14];
		ld2410->detection = Upward[15];
	}
