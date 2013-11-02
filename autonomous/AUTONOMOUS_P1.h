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

		move(none, 0);
		move(left, 30);
		wait10Msec(5);
		move(forward, 30);
		wait10Msec(45);
		move(none, 0);
		servo[servo1] = 190;
		wait10Msec(100);
		servo[servo1] = 75;
		wait10Msec(100);
		blockDeposited = false;

		//Heading back
		move(reverse, 30);
		wait10Msec(45);
		move(right, 30);
		wait10Msec(100);
		move(none, 0);
	}
}
