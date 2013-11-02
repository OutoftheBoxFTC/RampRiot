#include "\Programs\RampRiot\HolomonicAPI.h"
#include "\Programs\RampRiot\utils\sensor.h"
#include "JoystickDriver.c"

task p1()
{
	// Wait for the beginning

	bool blockDeposited = true;
	while(blockDeposited == true)
	{
		while(getDirectionFromIR() != 5){
			move(left, 35);
		}
		control(0,0,0,0);
		//wait10Msec(10);
		//while(getDirectionFromIR() == 5){
		//wait10Msec(500);
		//move(left, 20);
		//wait1Msec(10);
		//}
		move(left, 35);
		wait10Msec(25);
		move(none, 0);
		servo[servo1] = 190;
		wait10Msec(100);
		servo[servo1] = 75;
		wait10Msec(100);
		blockDeposited = false;
	}
	/*while(SensorValue[USonic] > 100){
	move(forward, 50);
	wait1Msec(10);
	}
	move(left,75);
	wait1Msec(100);
	move(reverse, 75);
	wait1Msec(50);
	} */
}
