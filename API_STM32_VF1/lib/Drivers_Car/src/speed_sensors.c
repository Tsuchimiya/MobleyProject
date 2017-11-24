/**
 * @file    speed_sensors.c
 * @author  Curtis Team
 * @brief   Functions to handle speed sensors  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "speed_sensors.h"
#include "hall_sensors.h"
#include "common_constants.h"
#include "system_time.h"
#include "math.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief   Number of samples used to compute speed. It is recommended to keep a value under 5 to keep a good fidelity of the variable. Mus not be negative.  
*/
#define SPEED_SENSOR_SAMPLES_USED 5

/**
 * @brief   Travelled distance between two samples
*/
#define DELTA_DISTANCE 	(float) PI*((float)(((float)CAR_WHEEL_SIZE/(float)HALLSENSOR_NUMBER_OF_SECTORS)))
    
/**
 * @brief   Time corresponding to a hall sensor period : meaning time between two changes of speed 
*/
#define SPEED_SENSOR_TIME_BETWEEN_TWO_UPDATES 1000

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 * @brief   Number of the sample to consider to compute speed
*/
uint8_t SAMPLE_TO_USE;

/**
 * @brief   Last computed speed (expressed in centimeters per second) for each speed sensor
*/
static float speed[HALLSENSORS_NUMBER]; // cm/s

/**
 * @brief   Last computed speed by tick based method (expressed in centimeters per second) for each speed sensor
*/
float speed_tick[HALLSENSORS_NUMBER]; // cm/s

/**
 * @brief   Last computed speed by time based method (expressed in centimeters per second) for each speed sensor
*/
float speed_time[HALLSENSORS_NUMBER]; // cm/s

/* Private function prototypes -----------------------------------------------*/
void SpeedSensor_compute(Sensor_Enum SpeedSensor_identifier);
void SpeedSensor_tickBasedMethod(Sensor_Enum SpeedSensor_identifier);
void SpeedSensor_timeBasedMethod(Sensor_Enum SpeedSensor_identifier);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Initializes specified speed sensor.
 * @param   SpeedSensor_identifier Speed sensor to be considered. 
 * @retval  None
*/
void SpeedSensor_QuickInit(Sensor_Enum SpeedSensor_identifier) {
	speed[SpeedSensor_identifier] = 0.0; 
	
	if (SPEED_SENSOR_SAMPLES_USED <= HALLSENSOR_MAX_SAVED_POP) {
		SAMPLE_TO_USE  = SPEED_SENSOR_SAMPLES_USED - 1;
	}
	else {
		SAMPLE_TO_USE  = HALLSENSOR_MAX_SAVED_POP - 1;
	}
}

/**
 * @brief   Returns the value of speed : unit is given by unit parameter
 * @param   unit A parameter to convert centimeters per second to any expected unit. It is recommended to use defined units such as SPEED_CM_S, SPEED_MM_S, SPEED_M_S, SPEED_KM_H, SPEED_FT_S,...
 * @param   SpeedSensor_identifier Speed sensor to examine
 * @retval float (car speed : unit depends on parameter passed as argument) 
*/
float SpeedSensor_get(float unit, Sensor_Enum SpeedSensor_identifier) {
	SpeedSensor_compute(SpeedSensor_identifier);
	return speed[SpeedSensor_identifier] * unit;
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Computes speed and stores the result in a private variable. 
 * @param   SpeedSensor_identifier Speed sensor to consider.
 * @retval  None
*/
void SpeedSensor_compute(Sensor_Enum SpeedSensor_identifier) {

    float time_based = 0.0;
    float tick_based = 0.0;
    float coeff = 0.0;

    // Update speed variables
    SpeedSensor_tickBasedMethod(SpeedSensor_identifier);
    SpeedSensor_timeBasedMethod(SpeedSensor_identifier);

    // Get values for each method
    time_based = speed_time[SpeedSensor_identifier];
    tick_based = speed_tick[SpeedSensor_identifier];

    // Compute coefficient 
    if (time_based == 0.0) {
        coeff = 0.0;
    }
    else {
        coeff = (fabs(time_based-tick_based) / (CAR_MAX_SPEED));
        if (coeff > 1.0) {coeff = 1.0;}
        else if (coeff < 0.0) {coeff = 0.0;}
        else {}
    }

    // Store value of speed
    if (speed_time[SpeedSensor_identifier] < 0) 
        speed[SpeedSensor_identifier] = coeff*(-tick_based)+(1-coeff)*(time_based);  // N'entre pas dans ce if
    else                                        
        speed[SpeedSensor_identifier]  = (coeff*(tick_based)+(1-coeff)*(time_based));
    
}

/**
 * @brief   Computes speed with tick based method and stores the result in a private variable.
 * @param   SpeedSensor_identifier Number of the speed sensor to consider.
 * @retval  None
*/
void SpeedSensor_tickBasedMethod(Sensor_Enum SpeedSensor_identifier) {
    uint64_t tf = millis();
	uint64_t t0 = HallSensor_getLastPop(SAMPLE_TO_USE, SpeedSensor_identifier);
	
	if (t0 == 0) {
		speed_tick[SpeedSensor_identifier] = 0; // Car hasn't move yet
	} 
	else if (t0 != tf) { 
		speed_tick[SpeedSensor_identifier] = (float) (DELTA_DISTANCE * (SAMPLE_TO_USE + 1) / ((float)(tf - t0)/((float)1000)));
	}
	else {
		speed_tick[SpeedSensor_identifier] = INFINITE; // Car browses instantly the distance
	} 
}

/**
 * @brief Computes speed with a time based method and stores the result in a private variable.
 * @param SpeedSensor_identifier Number of the speed sensor to consider.
 * @retval  None
*/
void SpeedSensor_timeBasedMethod(Sensor_Enum SpeedSensor_identifier) {
    int number_of_ticks = HallSensor_getNumberTicksInPeriod(SpeedSensor_identifier);
    speed_time[SpeedSensor_identifier] = (float) ((number_of_ticks * DELTA_DISTANCE) / SPEED_SENSOR_TIME_BETWEEN_TWO_UPDATES)*1000;
}
