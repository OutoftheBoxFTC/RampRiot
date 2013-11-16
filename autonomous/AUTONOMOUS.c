#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     USonic,         sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     Motor1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Motor4,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Motor3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     Motor5,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motor6,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma platform(Tetrix)
//Include Dependiences
#include "JoystickDriver.c"
#include "\Programs\RampRiot\autonomous\AUTONOMOUS_P1.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//                            Autonomous Setup and Control
// Choose an autonomous file from the incuded files and executes it. Additionally It resets all
// motors to default positions and creates a infinite loop
//
///////////////////////////////////////////////////////////////////////////////////////////////////
int totalPrograms = 2;

void updateTask(int pNum) {
	String desc = "";
	String name = "";
	TaskID rVal = NULL;
	if (pNum == 1) {
		name = "Normal";
		desc = "Runs Robot left to drop I/R blck";
		setHeading(normal);
		rVal = p1;
	} else if (pNum == 2)
	{
		setHeading(opposite);
		name = "Opposite";
		desc = "Runs Robot right to drop I/R blck";
		rVal = p2;
	}
	eraseDisplay();
	nxtDisplayCenteredBigTextLine(1, "P Chooser");
	nxtDisplayString(3, "%d|%d", name, pNum);
	nxtDisplayString(4, desc);

}

task main()
{
	nxtDisplayCenteredBigTextLine(0, Choose The Program);

	int pNum = 1;
	while(nNxtButtonPressed != kEnterButton) {
		if (nNxtButtonPressed == kLeftButton) {
			pNum++;
		} else if(nNxtButtonPressed == kRightButton)
		{
			pNum--;
		}
		if(pNum < 0){
			pNum = totalPrograms;
		}
		else if(pNum > totalPrograms){
			pNum = 0;
		}
		update
	}
	//Wait till start to begin executing
	waitForStart();
	//Reset The servo to the default rotation
	servo[servo2] = 0;
	servo[servo3] = 255;
	servo[servo1] = 75;

	//Start an autonomous program from the incuded files.
	StartTask(updateTask(pNum));
	//Start a paging file to act as a program place holder.
	while (true);
	StopTask(updateTask(pNum));
}
