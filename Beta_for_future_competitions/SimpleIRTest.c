#pragma config(Sensor, S3,     HTIRS2,         sensorI2CCustom)

#include "drivers/hitechnic-irseeker-v2.h"

task main()
{
	tHTIRS2DSPMode _mode = DSP_600;
	while(true)
	{
		if (HTIRS2setDSPMode(HTIRS2, _mode))
		{
      nxtDisplayTextLine(0, "YAY");
		}
		else
		{
      nxtDisplayTextLine(0, "NOOOOEEEEEESSSSSSSs");
		}
		 nxtDisplayTextLine(1, "%d", HTIRS2readACDir(HTIRS2));
	}


}
