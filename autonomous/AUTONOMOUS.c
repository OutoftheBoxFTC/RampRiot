#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S3,     USonic,         sensorSONAR)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S4,     HTMC,           sensorI2CCustom)
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
#include "drivers/hitechnic-compass.h"
#include "\Programs\RampRiot\autonomous\AUTONOMOUS_P1.h"
#include "\Programs\RampRiot\utils\compassStorage.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
//
//                            Autonomous Setup and Control
// Choose an autonomous file from the incuded files and executes it. Additionally It resets all
// motors to default positions and creates a infinite loop
//
///////////////////////////////////////////////////////////////////////////////////////////////////
int totalPrograms = 2;
bool hasSelected = false; // Haven't selected Mode yet
int pNum = 1; // Program we are on

typedef enum {//List of directions our robot can go
	START,
	STOP,
	NOA,  // None of the Above
} TaskChoice;

void updateTask(int pNum, TaskChoice choice) {
	string desc1 = "";// 4 parts
	string desc2 = "";
	string desc3 = "";
	string desc4 = "";
	string name = ""; // Name of the task we are starting

	if (pNum == 1) {  // Starting Position is normal, so it runs left when chosen
		name = "Normal"; // Setting Name
		desc1 = "Moves Robot left"; //Setting description on multiple lines to bypass line length
		desc2 = "To deposit the";
		desc3 = "I/R block";
		setHeading(normal);
		if (choice == START)// If variable = start, we execute task
		{
			StartTask(p1);
		} else if (choice == STOP) // If we want to start the program
		{
			StopTask(p1);
		}
	} else if (pNum == 2)
	{
		name = "Opposite"; // Setting Name
		desc1 = "Moves Robot right";//Setting description on multiple lines to bypass line length
		desc2 = "To deposit the";
		desc3 = "I/R block";
		setHeading(opposite); //If our robot needs to move Right, sets the directions
		if (choice == START)
		{
			StartTask(p1);
		} else if (choice == STOP)
		{
			StopTask(p1);
		}
	}
	nxtDisplayCenteredBigTextLine(0, "PChooser");
	nxtDisplayString(3, "%s|%d", name, pNum); // displays the task you are starting
	nxtDisplayString(5, desc1); // Multi line to bypass line char limit
	nxtDisplayString(6, desc2);
	nxtDisplayString(7, desc3);
	nxtDisplayString(8, desc4);


	// Following code  Didn't work because of the 20 Character Limit on Strings Dc>:

	/*	if(strlen(desc) > 16) {
	for (int dex = 0; dex < strlen(desc); dex++) {
	if(dex < strlen(desc)) {
	if (dex < 16) {
	desc1 = desc1 + StringGetChar(desc, dex);
	} else if (dex < 20)
	{
	desc2 = desc2 + StringGetChar(desc, dex);
	else if(dex < 32){

	}
	} else if(dex < 48)
	{
	desc3 = desc3 + StringGetChar(desc, dex);
	} else
	{
	desc4 = desc4 + StringGetChar(desc, dex);
	}
	}
	}
	} else
	{
	desc1 = desc;
	} */


}

void initializeRobot() {
	disableDiagnosticsDisplay(); // Display Joystick Diagnostics gets disabled so we have room to display text
	eraseDisplay(); // clears screen

	int total = 0;
	int count = 0;

	while (count < 5) {
		// Get the true heading and relative heading from the sensor and
		// display them on the screen.
		while(nNxtButtonPressed != kEnterButton) {
			eraseDisplay();
			nxtDisplayCenteredBigTextLine(0, "Reading");
			nxtDisplayTextLine(2, "Target Avg: %4d", total / count);
			nxtDisplayTextLine(3, "Abs:   %4d", HTMCreadHeading(HTMC));
			nxtDisplayCenteredTextLine(6, "Press enter");
			nxtDisplayCenteredTextLine(7, "to set target");
			wait1Msec(100);
		}

		// Reset the target no more than once a second
		// This also helps with debouncing the [enter] button.
		eraseDisplay();
		nxtDisplayTextLine(1, "Changing");
		nxtDisplayTextLine(2, "target");
		wait1Msec(500);
		// Set the current heading as the value for the offset to be used as the
		// new zero-point for the relative heading returned by
		// HTMCreadRelativeHeading()
		count++;
		total += HTMCreadHeading(HTMC);
		PlaySound(soundBlip);
		while(bSoundActive) break;
	}
	write(total / count);

	while(nNxtButtonPressed != kEnterButton && !hasSelected)
	{ //kEnterButton is the orange button
		if (nNxtButtonPressed == kLeftButton) {
			pNum++; // scrolls to the next option
			PlaySound(soundBlip);
			eraseDisplay();
		} else if(nNxtButtonPressed == kRightButton)
		{
			pNum--; // Scrolls backwards
			PlaySound(soundBlip);
			eraseDisplay();
		}
		if(pNum <= 0) {
			pNum = totalPrograms; // Sets up the number of options
		}
		else if(pNum > totalPrograms){
			pNum = 1;
		}
		updateTask(pNum, NOA); // runs above function
		if (nNxtButtonPressed != kEnterButton) {
			wait10Msec(30); // Prevents quick key pressing
		}
	}
	hasSelected = true;//prevents an infinite loop of program selection
	nxtDisplayCenteredBigTextLine(3, "Waiting ");
}

task main()
{
	initializeRobot();
	//Wait till start to begin executing
	waitForStart();
	//Start an autonomous program from the incuded files.
	updateTask(pNum, START);
	//Start a paging file to act as a program place holder.
	while (true);
}
