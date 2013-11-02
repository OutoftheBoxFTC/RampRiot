#include "\Programs\RampRiot\HolomonicAPI.h"
#include "\Programs\RampRiot\utils\sensor.h"

task p1()
{
	while(true) {
		control(0,0,0,0);
		waitForStart();

		int power = 35;
		int spinPowerIncrement = 10;
		bool blockDeposited = true;
		while(blockDeposited == true)
		{
			while(getDirectionFromIR() != 5){
				move(reverse, power);
			}
			nxtDisplayTextLine(0, "%d IR Light", getPowerFromAcIR());
			nxtDisplayTextLine(2, "%d Direction", (getDirectionFromIR()));

			if(getDirectionFromIR() == 5)
			{
				move(forward, power);
			} else if(getDirectionFromIR() < 5 && getDirectionFromIR() != 0)
			{
				move(spin_right, getSpinPowerFromIR(spinPowerIncrement));
			} else if(getDirectionFromIR() > 5)
			{
				move(spin_left, getSpinPowerFromIR(spinPowerIncrement));
			} else
			{
				move(none, 0);
			}

			if(getPowerFromAcIR() > 150){
				wait10Msec(500);
				while(getDirectionFromIR() == 5){
					wait10Msec(500);
					move(reverse, power);
				}
				move(none, 0);
				servo[servo1] = 190;
				wait1Msec(1000);
				servo[servo1] = 75;
				blockDeposited = false;
			}
		}
	}
}
