/**
 * @file 	common_constants.h
 * @author 	Curtis Team
 * @brief 	Constants used by all the layers
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _COMMON_CONSTANTS_H
#define _COMMON_CONSTANTS_H

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>

/* Exported types ------------------------------------------------------------*/
/**
 * @brief    Direction of the car
*/
typedef enum {
    /** * @brief    Neither forward neither backward */
    NEUTRAL,
    /** * @brief    Forward */
    FORWARD,  
    /** * @brief    Backward */
    BACKWARD
} direction_TypeDef;

/**
 * @brief    Side of turning 
*/
typedef enum {
  /** * @brief    Left */
  LEFT = 1,
  /** * @brief    Neither left neither right */
  NONE = 0,
  /** * @brief    Right */
  RIGHT = -1
} side_TypeDef;

/* Exported constants --------------------------------------------------------*/
/**
 * @brief    Number of microseconds per second
*/
#define US_PER_S                (1.0e+06)

/**
 * @brief    Pi constant
*/
#define PI                      3.141592653589793238


/**
 * @brief    Car wheel diameter (expressed in cm)
*/
#define CAR_WHEEL_SIZE          19

/**
 * @brief    Car maximum forward speed (expressed in cm/s)
*/
#define CAR_MAX_SPEED 		    138.889	                // cm/s  => 138.889 cm/s = 5 km/h

/**
 * @brief    Car maximum backward speed (expressed in cm/s)
*/
#define CAR_MIN_SPEED			-CAR_MAX_SPEED			// cm/s

/**
 * @brief   Value given if car browses instantly the distance between two samples
*/
#define INFINITE                999999.99

/**
 * @brief   Used to get position value in the adequate unit 
*/
#define POSITION_MM		        10                      // millimeters

/**
 * @brief   Used to get position value in the adequate unit 
*/
#define POSITION_CM		        1                       // centimeters

/**
 * @brief   Used to get position value in the adequate unit 
*/
#define POSITION_M 		        0.01                    // meters

/**
 * @brief   Used to get position value in the adequate unit 
*/
#define	POSITION_KM		        0.00001                 // kilometers

/**
 * @brief   Used to get position value in the adequate unit 
*/
#define POSITION_IN		        0.393701                // inches

/**
 * @brief   Used to get position value in the adequate unit 
*/
#define POSITION_FT		        0.0328084               // feet

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_MM_S		        10                      // millimeters per second

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_CM_S 		        1                       // centimeters per second

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_M_S		        0.01                    // meters per second

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_KM_S		        0.00001                 // kilometers per second

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_KM_H		        0.036                   // kilometers per hour

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_FT_S		        0.0328084               // feet per second

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_MI_H		        0.02236936		        // miles per hour

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_MI_S		        0.0000062137            // miles per second

/**
 * @brief   Used to get speed value in the adequate unit
 */
#define SPEED_KNOT		        0.01943845  	        // knots

/**
 * @brief   Convert float to percentage coefficient 
 */
#define PERCENTAGE              100


/**
* @brief    Number of ultrasonic sensors
*/
#define US_NUM             6

// Ultrasonic ID
/**
* @brief    US_FR : id of front right ultrasonic sensor
*/
#define US_FR                       0x00

/**
* @brief    US_FM : id of front middle ultrasonic sensor
*/
#define US_FM                       0x01

/**
* @brief    US_FL : id of front left ultrasonic sensor
*/
#define US_FL                       0x02

/**
* @brief    US_BR : id of back right ultrasonic sensor
*/
#define US_BR                       0x03

/**
* @brief    US_BM : id of back middle ultrasonic sensor
*/
#define US_BM                       0x04
    
/**
* @brief    US_BL : id of back left ultrasonic sensor
*/
#define US_BL                       0x05

// Wheel position sensors 
/**
* @brief    WP_R : id of Right wheel position sensor
*/
#define WP_R                        0x00

/**
* @brief    WP_L : id of Left wheel position sensor
*/
#define WP_L                        0x01

// Steering stop sensor
/**
* @brief    SS_R : id of Right wheel position sensor
*/
#define SS_R                        0x00

/**
* @brief    SS_L : id of Left wheel position sensor
*/
#define SS_L                        0x01

/**
 * @brief coef to convert counter value in cm
 */
#define DISTANCE_COEF								0.02621

/* Position of US in array*/
#define REAR_LEFT						0
#define REAR_CENTER					1
#define REAR_RIGHT					2
#define FRONT_LEFT					3
#define FRONT_CENTER				4
#define FRONT_RIGHT					5

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif // _COMMON_CONSTANTS_H
