/*
 * can.h
 *
 *  Created on: 19 sept. 2017
 *      Author: senaneuc
 */

#ifndef CAN_H_
#define CAN_H_


#define CANx                       CAN1
#define GPIO_CAN                   GPIO_CAN1
#define GPIO_Remapping_CAN         GPIO_Remapping_CAN1
#define GPIO_CAN                   GPIO_CAN1

#define ERROR_ID									 -1 // 2047 max
#define ERROR_DLC									 -2 // 18 bit max
#define ERROR											 -3 //



/* STM32 INFORMATION DATA's ID */

#define ID_POSITION_OTHER						0x010

#define ID_DISTANCE									0x020

#define ID_SPEED										0x030

#define ID_FRONT_US									0x100
#define ID_REAR_US									0x110

#define ID_MOTOR_CURRENT  					0x050



/* Raspberry Pi INFORMATION DATA's ID */

#define ID_MOTOR_PROP								0x003
#define ID_MOTOR_DIR								0x001
#define ID_MOTOR_ENABLE							0x002
#define ID_BATTERY									0x07


#include "stm32f10x.h"

extern uint8_t CAN_ENABLE;
//extern uint16_t counterCanMes;
//extern uint16_t timeRcv[120];

typedef union data_paquet data_paquet;
union data_paquet
{
    char stringMessage[8];
    int8_t byteMessage[8];
    int16_t intMessage[4];
		float floatMessage[2];
};





void CAN_QuickInit(void);

int  CAN_Send(int id,char *data);
void CAN_IT_Config(void);
void CAN_Rx_Callback(uint8_t size, int id, char * data) __attribute((weak));

void CAN_Send_Distance(void);
void CAN_Send_Speed(void);
void CAN_Send_Front_US(void);
void CAN_Send_Rear_US(void);
void CAN_Send_Wheel_Position(void);
void  CAN_Send_Current(void);
void CAN_Send_Battery (void);
#endif /* CAN_H_ */
