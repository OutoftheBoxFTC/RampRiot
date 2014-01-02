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
	servo[servo1] = 120;
	servo[servo2] = 120;
	servo[servo3] = 120;

	tHTIRS2DSPMode _mode = DSP_600;
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
	int basketNum = 0; //check which basket we are at
	eraseDisplay();
	disableDiagnosticsDisplay();
	//int qqKillMe = getDirection(); Onw of the many functions I ave used to identify the IR seeker problem.
	//int IR = HTIRS2readACDir(HTIRS2);
//	nxtDisplayTextLine(5, "%d", IR);
	wait1Msec(1000);
	while(HTIRS2readACDir(HTIRS2) != 5){  // we are not in front of the beacon, and we haven't checked every basket
		//	move(l, 25);
		nxtDisplayTextLine(1, "%d", HTIRS2readACDir(HTIRS2));
		if(HTIRS2setDSPMode(HTIRS2, _mode))
		{
//			nxtDisplayTextLine(5, "%d", IR);
		}
		else
		{
			nxtDisplayTextLine(5, "NOPE");
		}
		if(basketNum != 2)
		{
			wait10Msec(50);  // move a little
		}
		else
		{
			wait10Msec(75);  // move more to compensate the middle piece
			//	nxtDisplayTextLine(0, "%d", IR);
			nxtDisplayTextLine(3, "%d", basketNum);
		}
		if(basketNum == 0)
		{
			nxtDisplayTextLine(2, "FIRST TIME");
			wait10Msec(100);
		}
		else
		{
			nxtDisplayTextLine(2, "NOT FIRST TIME");
		}
		move(none, 0);    // stop and check if we are near
		wait10Msec(5);
		basketNum++; //We checked this basket, move on or store our number, depending on if the basket has a beacon on it
		//		qqKillMe = getDirection();
	//	IR = HTIRS2readACDir(HTIRS2);
		nxtDisplayTextLine(1, "%d", HTIRS2readACDir(HTIRS2));
	}


	nxtDisplayTextLine(0, "OMG WE WIN LIFE!!!!!!!1111!!!!!");
	// Procedural movements to drop off our block, and then alert ourselves that we have dropped off the block. //
	//move(l, 25); //
	//wait10Msec(4);
/*	move(forward, 30);//Drive forward to deposit block
	wait10Msec(45);//Pause to move.
	move(none, 0);//Stop the robot.
	servo[servo1] = 190;//Activate the arm to throw the block.
	wait10Msec(100);//Pause.
	servo[servo1] = 0;//Bringing the arm back
	wait10Msec(100);//Wait for completion


	//Heading back to get out of the way of the baskets. //
	move(reverse, 30); // move back from going forward
	wait10Msec(45); //Pause to move
	move(none, 0);// Stop the robot

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
	}

	else  // basket is 3 / 4
	{
		move(l, 35);  //reverse above procedure to minimize time spent, insted of going twice as far right, go left instead
		wait1Msec(500 * (5 - basketNum)); //if basket 4, go 1/2 second to the left, because 4 is outside like 1 and 5-4 = 1, else go 5-3 = 2* 1/2, or 1 second to the left
		move(none,0); // stop to prevent wheel slips
		wait1Msec(20); //wait a little
		move(forward, 35);
		wait1Msec(500);
		move(r, 35);  //reverse above procedure to minimize time spent, insted of going twice as far right, go left instead
		wait1Msec(500);
		move(none, 0);
	}
*/
}
