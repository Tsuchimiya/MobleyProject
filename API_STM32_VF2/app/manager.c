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
int16_t motor_prop_old = 0;
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
		
		motor_prop_old = 0;
		pDataITF_PI->enable_motors_control = ENABLE;
}
/*************************
Fonction privée
**************************/
void Tournervolant(int degree_I)
{	
	degree_I = degree_I + 142;
	
	if(Direction_get() >= degree_I+4)
	{
		//-0°
		FrontMotor_turn(RIGHT);
	}
	else if(Direction_get() <= degree_I-4)
	{
		//+0°
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
int Bat_level;
float distance_US[6];

//SCADE
inC_US_handler inC;
outC_US_handler outC;
kcg_float64 toto;

void Manager_Callback(void) {
	int surveillance=0;	
	
    Manager_remainingTimeInCommandPeriod --;
    pDataITF_PI->enable_motors_control = ENABLE; //Modif SumSum
    if (Manager_remainingTimeInCommandPeriod == 0) {
			
			// Batterie pas faible (Batterie>8.1V)
			if (surveillance==0) {
			// ACTUATORS    
					// Rear motors
					if(motor_prop_old != pDataITF_PI->motor_prop && !(outC.Emergency_stop))
					{
						RearMotors_setSpeed(pDataITF_PI->motor_prop);
						motor_prop_old = pDataITF_PI->motor_prop;
					}
					else if(outC.Emergency_stop)
					{
						pDataITF_PI->motor_prop = 0;
					}
			
					// Front motors
					if (pDataITF_PI->motor_dir >= -20. && pDataITF_PI->motor_dir <= 20. ){
							Tournervolant(pDataITF_PI->motor_dir);
					}
					else if (pDataITF_PI->motor_dir < -20.){
						Tournervolant(-20);
					}
					else if (pDataITF_PI->motor_dir > 20.){
						Tournervolant(20);
					}
					else{
							Tournervolant(0);// do nothing
					}
				}
			// Batterie faible (Batterie<=8.1V)
			else if (surveillance==1) {
				// Arret moteurs
				RearMotors_setSpeed(0);
				Tournervolant(0);
			}
					
			// SENSORS   
					// wheel speed    
					pDataITF_STM->wheel_speed_R = SpeedSensor_get(SPEED_CM_S, SENSOR_R);
					pDataITF_STM->wheel_speed_L = SpeedSensor_get(SPEED_CM_S, SENSOR_L);
					
					// travelled distance
					pDataITF_STM->travelled_distance_R = PositionSensor_get(POSITION_CM, SENSOR_R);
					pDataITF_STM->travelled_distance_L = PositionSensor_get(POSITION_CM, SENSOR_L);
					
					
					//motors current
					Manager_remainingTimeInCommandPeriod = MANAGER_TIME_BETWEEN_TWO_UPDATES;  
			
//					//US_Sensor in front
//						//Gauche
//						distance_US[0] = US_CalcDistance(0);
//						//Milieux
//						distance_US[1] = US_CalcDistance(1);
//						//Droite
//						distance_US[2] = US_CalcDistance(2);
//					
//					if(distance_US[0] < 10 || distance_US[1] < 20 || distance_US[2] < 10)
//					{
//						surveillance=1;
//					}
//					else if(Bat_level > 51)
//					{
//						surveillance = 0;
//					}		
						
						//SCADE
						inC.Left_Sensor = US_CalcDistance(0);
						inC.Middle_Sensor = US_CalcDistance(1);
						inC.Right_Sensor = US_CalcDistance(2);
						//US_handler(&inC,&outC);
						pDataITF_STM->US_sensors_emergency = outC.Emergency_stop;
						pDataITF_STM->US_sensors_emergency = 0;
		}
		
		// Get battery level
		Bat_level=Battery_get();
		
		// Arret moteurs si Batterie <= 8.1V (51% de 16V)
		if (Bat_level<=51) {
			surveillance=1;
		}		
}
