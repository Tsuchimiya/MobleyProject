#include <stdint.h>
#include <stm32f10x.h>

#include "system_time.h"
#include "manager.h"

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

int main(void) {
	
	Manager_Init();	
	while (1){	
		//Mashalah (D)121 => 145 => (G)168
		//pDataITF_PI->motor_prop = 25;
		Tournervolant(0);
	}
}
