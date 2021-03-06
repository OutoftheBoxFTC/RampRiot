#pragma fileExtension("rtm")
#pragma platform("NXT")
#pragma config(Sensor, S4,     HTSMUX,          sensorLowSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//   Our multiplexer
//#pragma config(Sensor, S4,     HTSMUX,          sensorI2CCustom) old code, doesn't work with the UltraSensor sensor, unlike the above lowSpeed

#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-compass.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-ultrasound.h"
#include "drivers/lego-touch.h"

//driver setup


const tMUXSensor touch = msensor_S4_1;
const tMUXSensor compass = msensor_S4_2;
const tMUXSensor LEGOUS = msensor_S4_3;
const tMUXSensor ir = msensor_S4_4;

//the sensors on out multiplexer  ^


task main()
{
	int targetForCompass, irValue, dist = 0;
	bool touchState;
	while(true)
	{
		touchState = TSreadState(touch);
		targetForCompass = HTMCsetTarget(compass);
		irValue = HTIRS2readACDir(ir);
		dist = USreadDist(LEGOUS);

		if (TSreadState(touch))
		{
			nxtDisplayTextLine(0, "touch : 1");
		}
		else
		{
			nxtDisplayTextLine(0, "touch : 0");
		}

		nxtDisplayTextLine(1, "compass : %4d", targetForCompass);
		nxtDisplayTextLine(2, "ultrasonic : %3d", SensorValue[LEGOUS]);
		nxtDisplayTextLine(3, "ir : %4d", irValue);
		nxtDisplayTextLine(4, "Dist:  %3d cm", dist);
		// display the variables
		// Q has a bowtie like a boss
	}

}
