/* 
 * LD2410C.h
 *
 * Created on: Jun 6, 2024
 * 	Author : KienTrung
 */
 
 #ifndef INC_LD2410C_H_
 #define INC_LD2410C_H_
 
 #include "main.h"
 #include "stm32f1xx_hal.h"
 typedef struct {
	uint8_t config_motion;
	uint8_t config_rest;
	uint16_t duration;
 } dist_gate;
 typedef struct {
	uint8_t state;
	uint8_t mov_distance;
	uint8_t mov_energy;
	uint8_t sta_distance;
	uint8_t sta_energy;
	uint8_t detection;
	dist_gate gate;
 }Ld2410Typedef;
 void Enable_config(UART_HandleTypeDef *huart);
 void End_config(UART_HandleTypeDef *huart);
 /* configuration range 2~8
		configuration range 0~65535 seconds
  */
 void Max_distance_gate(UART_HandleTypeDef *huart,uint8_t mov,uint8_t rest,uint8_t duration);
 void Read_parameter(UART_HandleTypeDef *huart,Ld2410Typedef *ld2410); 
 void Enable_EngineeringMode(UART_HandleTypeDef *huart);
 void Close_EngineeringMode(UART_HandleTypeDef *huart);
 void Range_gate_sensivity_config(UART_HandleTypeDef *huart,uint8_t door,uint8_t mov_sens,uint8_t static_sens);
 void Get_version(UART_HandleTypeDef *huart,uint8_t *version);
 void Baudrate_setting(UART_HandleTypeDef *huart,uint32_t baudrate);
 /* support baudrate 9600,19200,38400,57600,115200,230400,256000,460800
			The factory default value is 0x0004, which is 57600
	*/
 void factory_reset(UART_HandleTypeDef *huart);
 void restart_module(UART_HandleTypeDef *huart);
 void distance_resolution(UART_HandleTypeDef *huart,uint8_t distance);/* Distance resolution has only 2 values: 75cm and 20cm */
 uint8_t query_distance_resolution(UART_HandleTypeDef *huart);
 void Get_MacAddress(UART_HandleTypeDef *huart,uint8_t *address);
 void Bluetooth_setting(UART_HandleTypeDef *huart); /* default is enabled */
 void read_sensor(UART_HandleTypeDef *huart,Ld2410Typedef *ld2410);
 #endif // INC_LD2410C_H_
