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
} // set if we start at right or left
task p1
{
	Direction l;
	Direction r;

	if(h == normal)
	{
		r = right;
		l = left; //assign normal direction
	} else
	{
		r = left;
		l = right; // flip directions for starting on the opposite sides
	}
	bool blockDeposited = false; // haven't dropped off our block yet
	int basketNum = 0; //check which basket we are at

	while(!blockDeposited) // while we haven't dropped block off
	{
		while(getDirectionFromIR() != 5){  // we are not in front of the beacon
			move(l, 25);
			if(basketNum != 2)
			{
				wait1Msec(500);  // move a little
			}
			else
			{
        wait1Msec(750);  // move more to compensate the middle piece
			}
			move(none, 0);    // stop and check if we are near
			wait1Msec(500);
			basketNum++; //We checked this basket, move on or store our number, deoending on if the basket has a beacon on it
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
		blockDeposited = true;
		// Procedural movements to drop off our block, and then alert ourselves that we have dropped off the block.

		//Heading back to get out of the way.
		move(reverse, 30);
		wait10Msec(45);
		move(r, 30);
		wait10Msec(100);
		move(none, 0);
	}
	if(basketNum < 3) // basket is 1 or 2
	{
		move(r, 35);
		wait1Msec(500 * basketNum); //if basket1, go 1/2 second to the right, else go 2* 1/2, or 1 second to the right
		move(none,0); // stop to prevent wheel slips
		wait1Msec(20);
		move(forward, 35);
		wait1Msec(500);

		move(none,0); // stop to prevent wheel slips
		wait1Msec(20);

		move(l, 35);
		wait1Msec(500);
		move(none, 0);
		while(true);
	}

	else  // basket is 3 / 4
	{
		move(l, 35);  //reverse above procedure to minimize time spent, insted of going twice as far right, go left instead
		wait1Msec(500 * (5 - basketNum)); //if basket4, go 1/2 second to the left, because 4 is outside like 1 and 5-4 = 1, else go 5-3 = 2* 1/2, or 1 second to the left
		move(none,0); // stop to prevent wheel slips
		wait1Msec(20);
		move(forward, 35);
		wait1Msec(500);
		move(r, 35);  //reverse above procedure to minimize time spent, insted of going twice as far right, go left instead
		wait1Msec(500);
		move(none, 0);
		while(true);
	}

}
