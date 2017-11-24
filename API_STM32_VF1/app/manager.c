/**
 * @file    nucleo_functionnalities_manager.c
 * @author  Curtis Team
 * @brief   for the updates of the data structures and of the car commands
 */


/* Includes ------------------------------------------------------------------*/
#include "manager.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief   Manager refresh time (in ms)
*/
#define MANAGER_TIME_BETWEEN_TWO_UPDATES 10 //ms

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/
/**
 * @brief   Speed of the motors
*/
float motor_speed = 0.0;
uint16_t speedD;
uint16_t speedG;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/


/**
 * @brief   Counter to determine command refreshing time
*/
uint32_t Manager_remainingTimeInCommandPeriod = MANAGER_TIME_BETWEEN_TWO_UPDATES;



/** 
* @brief  Initializes all the sensors / actuators
* @retval none  
*/

void Manager_Init(void) {
    
    FrontMotor_QuickInit();
    RearMotors_QuickInit();
    
    RearMotors_Enable();
    
    PositionSensor_QuickInit(SENSOR_L);
    PositionSensor_QuickInit(SENSOR_R);
    
    SpeedSensor_QuickInit(SENSOR_L);
    SpeedSensor_QuickInit(SENSOR_R);
		
    Mirroring_Init();
    //Mirroring_Start();
	
	  US_QuickInit();
		US_StartAcq();
			
	  Direction_QuickInit();
	
		CAN_QuickInit();
    System_Time_QuickInit();
}
/*************************
Fonction privée
**************************/
void Tournervolant(int degree_I)
{	
	degree_I = degree_I + 145;
	
	if(Direction_get() >= degree_I+5)
	{
		FrontMotor_turn(RIGHT);
	}
	else if(Direction_get() <= degree_I-5)
	{
		FrontMotor_turn(LEFT);
	}
	else
	{
		FrontMotor_turn(NONE);
	}
}

/**
 * @brief   Callback associated to the nucleo functionnalities manager whose aim is to set the adequate command and update the sensors' data
 * @retval	None
*/
void Manager_Callback(void) {
    Manager_remainingTimeInCommandPeriod --;
    pDataITF_PI->enable_motors_control = ENABLE; //Modif SumSum
    if (Manager_remainingTimeInCommandPeriod == 0) {
    // ACTUATORS    
        // Rear motors
        if (pDataITF_PI->enable_motors_control == ENABLE) {
          speed_cmd = pDataITF_PI->motor_prop;  
          RearMotors_setSpeed(speed_cmd);
        }
        else{
            motor_speed = (float)(pDataITF_PI->motor_prop/100.0);
            Motor_setSpeed(REAR_MOTOR_R, motor_speed);
            Motor_setSpeed(REAR_MOTOR_L, motor_speed);
        }
    
        // Front motors
        if (pDataITF_PI->motor_dir >= -20. && pDataITF_PI->motor_dir <= 20. ){
            Tournervolant(pDataITF_PI->motor_dir);
        }
        else{
            Tournervolant(0);// do nothing
        }
        
    // SENSORS   
        // wheel speed    
        pDataITF_STM->wheel_speed_R = SpeedSensor_get(SPEED_CM_S, SENSOR_R);
        pDataITF_STM->wheel_speed_L = SpeedSensor_get(SPEED_CM_S, SENSOR_L);
        
        // travelled distance
        pDataITF_STM->travelled_distance_R = PositionSensor_get(POSITION_CM, SENSOR_R);
        pDataITF_STM->travelled_distance_L = PositionSensor_get(POSITION_CM, SENSOR_L);
        
        
        //motors current
       // pDataITF_STM->motor_current_R = ;
       // pDataITF_STM->motor_current_L = ;
        Manager_remainingTimeInCommandPeriod = MANAGER_TIME_BETWEEN_TWO_UPDATES;  
    }
}
