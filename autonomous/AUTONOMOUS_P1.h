#include "\Programs\RampRiot\HolomonicAPI.h"
#include "\Programs\RampRiot\utils\sensor.h"
#include "JoystickDriver.c"

//Direction[] directions = new Direction[5];
//int[] waits = new int[5];

typedef enum {//List of directions our robot can go
	normal,
	opposite
} heading;

heading h = normal;

bool breakLoop = false;

void setHeading(heading hd) {
	h = hd;
} // set if we start at right or left

task p1
{
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
	while(HTIRS2readACDir(HTIRS2) != 5) {  // we are not in front of the beacon, and we haven't checked every basket
		playSound(soundBlip);
	  basketNum++; //We checked this basket, move on or store our number, depending on if the basket has a beacon on it
	  move(l, 25);
		nxtDisplayTextLine(1, "%d", HTIRS2readACDir(HTIRS2));
		HTIRS2setDSPMode(HTIRS2, _mode);
		ClearTimer(T1);
	while(T1 < (basketNum != 2 ? 500 : 750))
		{
			if(HTIRS2readACDir(HTIRS2) == 5)
			{
				breakLoop = true;
				PlaySound(soundBeepBeep);
				break;
			}
			//		wait10Msec(80);  // move more to compensate the middle piece
			//	nxtDisplayTextLine(0, "%d", IR);
			nxtDisplayTextLine(3, "%d", basketNum);
		}
		move(none, 0);    // stop and check if we are near
		wait10Msec(5);
		//		qqKillMe = getDirection();
		//	IR = HTIRS2readACDir(HTIRS2);
		move(none, 0);
		wait1Msec(250);   // Spin to adjust for Robot Drift
		move(spin_left, 25);
		wait1Msec(100);
		move(none, 0);
		wait1Msec(250);
		//nxtDisplayTextLine(1, "%d", HTIRS2readACDir(HTIRS2));
		if(breakLoop)
		{
			break;
		}
	}
  nxtDisplayTextLine(7, "BasketNum = %d", basketNum);
	// Procedural movements to drop off our block, and then alert ourselves that we have dropped off the block. //
	move(l, 25); //
	wait10Msec(4);
	move(forward, 30);//Drive forward to deposit block
	wait10Msec(45);//Pause to move.
	move(none, 0);//Stop the robot.
	//servo[servo1] = 190;//Activate the arm to throw the block.
	PlaySound(soundBeepBeep);
	wait10Msec(100);//Pause.
	//servo[servo1] = 0;//Bringing the arm back
	//wait10Msec(100);//Wait for completion

	//Heading back to get out of the way of the baskets. //
	move(reverse, 30); // move back from going forward
	wait10Msec(45); //Pause to move
	move(none, 0);// Stop the robot

	for (int i = 0; i < (basketNum <= 2 ? basketNum : 5 - basketNum); i++)
	{
		move((basketNum <= 2 ? l : r), 25);
		PlaySound(soundBeepBeep);
	}
	move(none,0);
/*	directions[0] = forward;
	directions[1] = none;
	directions[2] = r;
	directions[3] = l;
	directions[4] = none;
	*/
  //move(forward, 35);  Finish LATERRER
  //wait10Msec(125);
  //move((basketNum > 2, r : l), 35)

}
