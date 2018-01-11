/**
 * @file    hall_sensors.c
 * @author  Curtis Team
 * @brief   Functions to handle hall sensors  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "hall_sensors.h"
#include "exti.h"
#include "system_time.h"
#include "driver_callbacks.h"
#include "common_constants.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief   Value to be add to variables at each edge when forward. 
*/
#define COUNT_ADDER         1 

/**
 * @brief   Value to be add to variables at each edge when backward. 
*/
#define DECOUNT_ADDER       -COUNT_ADDER

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
extern direction_TypeDef Motors_Direction[MOTORS_NUMBER];
    
/* Private variables ---------------------------------------------------------*/
direction_TypeDef Motors_Dir[MOTORS_NUMBER];

/**
 * @brief   Number of the hall detection. Positive is counted on rising edges, negative if not.  
*/
int32_t HallSensor_numberOfPop[HALLSENSORS_NUMBER];

/**
 * @brief   Date of the last dectections of each hall sensor
*/
uint64_t SENSOR_LastPops[HALLSENSOR_MAX_SAVED_POP][HALLSENSORS_NUMBER];

/**
 * @brief   Number of the sector currently seen by each hall sensor
*/
uint16_t HallSensor_sector[HALLSENSORS_NUMBER];

/**
 * @brief   Number of laps count by each hall sensor. Positive is counted on rising edges, negative if not. 
*/
int32_t SENSOR_Lap[HALLSENSORS_NUMBER];

/**
 * @brief   Number of ticks count during this periode
*/
int8_t HallSensor_currentPeriodeTicks[HALLSENSORS_NUMBER];

/**
 * @brief   Number of ticks count during the last periode
*/
int8_t HallSensor_periodeTicks[HALLSENSORS_NUMBER];

/**
 * @brief   Number of systick iteruptions to wait until next hall sensor period
*/
uint32_t SENSOR_RemainingTimeInHallPeriod = HALLSENSOR_TIME_BETWEEN_TWO_UPDATES; 

/**
 * @brief Increment per edge
*/
int8_t adder = COUNT_ADDER;

/* Private function prototypes -----------------------------------------------*/
void SENSOR_Reset (Sensor_Enum hall_identifier);
void HallSensor_newEdge(Sensor_Enum hall_identifier);
void SENSOR_ResetTimeToNextHallPeriod(void);
void HallSensor_countPeridodTicks(void);
void HallSensor_setCountDecount(uint8_t Motor_number, direction_TypeDef Direction);
void HallSensor_count(Sensor_Enum hall_identifier);
void HallSensor_decount(Sensor_Enum hall_identifier);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief       Reset and start specified hall sensor 
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      None
*/
void HallSensor_QuickInit(Sensor_Enum hall_identifier) {
	SENSOR_Reset(hall_identifier);
	HallSensor_count(hall_identifier);
}

/**
 * @brief       Called function on external interrupt (EXTI). Must not be call by user. 
 * @param       hall_identifier : hall sensor on wich edge was detected. 
*/
void HallSensor_Handler(Sensor_Enum hall_identifier) {
	HallSensor_newEdge(hall_identifier);
}

/**
 * @brief       Returns the current sector for hall sensor considered.
 * @param       hall_identifier Number of the hall sensor to consider.
 * @retval      Current sector if current sector is under number of sectors, ERROR_SENSOR_OUT_OF_RANGE if not.
*/
uint16_t HallSensor_getSector(Sensor_Enum hall_identifier){
	if (HallSensor_sector[hall_identifier] >= HALLSENSOR_NUMBER_OF_SECTORS) return ERROR_SENSOR_OUT_OF_RANGE; else {};
	return HallSensor_sector[hall_identifier];
}

/**
 * @brief       Returns the current lap for the hall sensor considered.
 * @param       hall_identifier Number of the hall sensor to consider.
 * @retval      Curent lap.
*/
int32_t HallSensor_getLap(Sensor_Enum hall_identifier) {
	return SENSOR_Lap[hall_identifier];
}

/**
 * @brief       Returns the date (in milliseconds) of the last - n detection of the hall sensor. 
 * @param       n Number of the wanted sample.
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      uint64_t Time of the detection passed as parameter if it is possible to found it, ERROR_VALUE_NOT_FOUND if not.
*/
uint64_t HallSensor_getLastPop(uint8_t n, Sensor_Enum hall_identifier) {
	int position_to_read = HallSensor_numberOfPop[hall_identifier] - n;
	
	if (n > HALLSENSOR_MAX_SAVED_POP) return ERROR_VALUE_NOT_FOUND;  else {}; 

	if (position_to_read < 0) position_to_read = position_to_read + HALLSENSOR_MAX_SAVED_POP; // TODO : verifier ce calcul et le commenter
		
	return SENSOR_LastPops[position_to_read][hall_identifier];
}

/**
 * @brief       Return the number of ticks detected during the last hall sensor period
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      uint8_t Number of ticks during previous period for the hall sensor considered
*/
int8_t HallSensor_getNumberTicksInPeriod(Sensor_Enum hall_identifier) {
	return HallSensor_periodeTicks[hall_identifier];
}


void HallSensor_TimeCallback(void) {
    int i; 
    
    SENSOR_RemainingTimeInHallPeriod --; 
    
    for (i=0;i<HALLSENSORS_NUMBER;i++) 
    {
        if (Motors_Dir[i] != Motors_Direction[i]) {
            Motors_Dir[i] = Motors_Direction[i];
            HallSensor_setCountDecount(i, Motors_Dir[i]);
        }
        else {}
    }
    
	if (SENSOR_RemainingTimeInHallPeriod == 0) {
		HallSensor_countPeridodTicks();
		SENSOR_ResetTimeToNextHallPeriod();
	}
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief       Reset all the variables used to describe a hall_sensor.
 * @param       hall_identifier Number of the hall sensor to consider.
 * @retval      None
*/
void SENSOR_Reset (Sensor_Enum hall_identifier) {
    int i = 0;
	HallSensor_numberOfPop[hall_identifier] = 0;
	HallSensor_sector[hall_identifier] = 0;
	SENSOR_Lap[hall_identifier] = 0;
	for (i = 0; i < HALLSENSOR_MAX_SAVED_POP; i++)	{
		SENSOR_LastPops[i][hall_identifier] = 0;
	}
	HallSensor_periodeTicks[hall_identifier] = 0;
	HallSensor_currentPeriodeTicks[hall_identifier] = 0;
    SENSOR_ResetTimeToNextHallPeriod();
}

/**
 * @brief       Updates the hall sensor definied variables according to hall sensor specified. 
 * @param       hall_identifier Number of the hall sensor to consider.
 * @retval      None
*/
void HallSensor_newEdge(Sensor_Enum hall_identifier) {
	SENSOR_LastPops[HallSensor_numberOfPop[hall_identifier]][hall_identifier] = millis();
	
	HallSensor_numberOfPop[hall_identifier] ++;
	if (HallSensor_numberOfPop[hall_identifier] >= HALLSENSOR_MAX_SAVED_POP) HallSensor_numberOfPop[hall_identifier] = 0; else {} 
	
	HallSensor_sector[hall_identifier] = HallSensor_sector[hall_identifier] + adder;
	
	if (HallSensor_sector[hall_identifier] == (uint16_t)(-1)) {
		HallSensor_sector[hall_identifier] = HALLSENSOR_NUMBER_OF_SECTORS - 1; 
		SENSOR_Lap[hall_identifier] --;
	}
	
	else if (HallSensor_sector[hall_identifier] >= HALLSENSOR_NUMBER_OF_SECTORS) {
		HallSensor_sector[hall_identifier] = 0; 
		SENSOR_Lap[hall_identifier] ++;
	}
	else {}
	HallSensor_currentPeriodeTicks[hall_identifier] = HallSensor_currentPeriodeTicks[hall_identifier] + adder;
}

/**
 * @brief       Reinit private variable indicating time remainng before the next hall sensor period.
 * @retval      None
*/
void SENSOR_ResetTimeToNextHallPeriod(void) {
    SENSOR_RemainingTimeInHallPeriod = HALLSENSOR_TIME_BETWEEN_TWO_UPDATES; 
}

/**
 * @brief       Update local variable HallSensor_periodeTicks[] with the number of ticks counted during completed period.
 * @retval      None
*/
void HallSensor_countPeridodTicks(void) {
	int i = 0; 
	for (i=0; i<HALLSENSORS_NUMBER; i++) {
		HallSensor_periodeTicks[i] = HallSensor_currentPeriodeTicks[i];
		HallSensor_currentPeriodeTicks[i] = 0;
	}
}

/**
 * @brief       Sets hall sensor associated to MotorIdentifier as counter or decounter according to specified Direction.
 * @param       MotorIdentifier Identifier of the motor whose associated HallSensor must be set as counter or decounter
 * @param       Direction Direction of the motor.
 * @retval      None
*/
void HallSensor_setCountDecount(uint8_t MotorIdentifier, direction_TypeDef Direction){
    Sensor_Enum hall_identifier; 
            if (MotorIdentifier == FRONT_MOTOR_IDENTIFIER)  return;
    else     if (MotorIdentifier == REAR_MOTOR_L_IDENTIFIER) hall_identifier = SENSOR_L; 
    else     if (MotorIdentifier == REAR_MOTOR_R_IDENTIFIER) hall_identifier = SENSOR_R; 
    else return;

    if (Direction != BACKWARD) HallSensor_count(hall_identifier);
    else HallSensor_decount(hall_identifier);
}

/**
 * @brief       Parameterizes hall sensor as counter
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      None
*/
void HallSensor_count(Sensor_Enum hall_identifier) {
	GPIO_TypeDef *GPIO;
	uint16_t pin;
	
	if (hall_identifier == SENSOR_L) {
		GPIO = SENSOR_L_GPIO;
		pin = SENSOR_L_PIN;
	}
	else if (hall_identifier == SENSOR_R) {
		GPIO = SENSOR_R_GPIO;
		pin = SENSOR_R_PIN;
	}
	else {return;}	
	
	EXTI_QuickInit(GPIO, pin, HALLSENSOR_TRIGG_FW, HALLSENSOR_PRIO);
    
    adder = COUNT_ADDER;
}

/**
 * @brief       Parameterizes hall sensor as decounter
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      None
*/
void HallSensor_decount(Sensor_Enum hall_identifier) {
	GPIO_TypeDef *GPIO;
	uint16_t pin;
	
	if (hall_identifier == SENSOR_L) {
		GPIO = SENSOR_L_GPIO;
		pin = SENSOR_L_PIN;
	}
	else if (hall_identifier == SENSOR_R) {
		GPIO = SENSOR_R_GPIO;
		pin = SENSOR_R_PIN;
	}
	else {return;}	
	
	EXTI_QuickInit(GPIO, pin, HALLSENSOR_TRIGG_BW, HALLSENSOR_PRIO);
    
    adder = DECOUNT_ADDER;
}
