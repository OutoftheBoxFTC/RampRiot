#include "\Programs\RampRiot\HolomonicAPI.h"
#include "\Programs\RampRiot\utils\sensor.h"
#include "JoystickDriver.c"

typedef enum {//List of directions our robot can go
	normal,
	opposite
} heading;

heading h = normal;

void setHeading(heading hd) {
	h = hd;
}
task p1
{
	Direction l;
	Direction r;

	if(h == normal)
	{
		r = right;
		l = left;
	} else
	{
		r = left;
		l = right;
	}
	bool blockDeposited = true;
	while(blockDeposited)
	{
		while(getDirectionFromIR() != 5){
			move(l, 25);
		}
		move(l, 25);
		wait10Msec(4);
		move(forward, 30);
		wait10Msec(45);
		move(none, 0);
		servo[servo1] = 190;
		wait10Msec(100);
		servo[servo1] = 0;
		wait10Msec(100);
		blockDeposited = false;

		//Heading back
		move(reverse, 30);
		wait10Msec(45);
		move(r, 30);
		wait10Msec(100);
		move(none, 0);
	}
}
