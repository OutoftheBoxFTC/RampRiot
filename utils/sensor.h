#include "drivers/hitechnic-irseeker-v2.h"

int getDirectionFromIR()
{
	int _dirEnh, _strEnh;
	if(!HTIRS2readEnhanced(HTIRS2, _dirEnh, _strEnh)) {
		return 0;
	}
	return _dirEnh;
}

int getStrengthFromIR()
{
	int _dirEnh, _strEnh;
	if(!HTIRS2readEnhanced(HTIRS2, _dirEnh, _strEnh)) {
		return 0;
	}
	return _strEnh;
}

int getSpinPowerFromIR(int increment)
{
	int direction = getDirectionFromIR();
	int power;
	if(direction == 5)
	{
		power = 0;
	} else if(direction > 5)
	{
		power = direction - 5;
	} else if(direction < 5 && direction != 0)
	{
		power = 5 - direction;
	} else
	{
		power = 0;
	}
	return power * increment;
}

int getPowerFromAcIR()
{
	int c1, c2, c3, c4, c5;
	HTIRS2readAllACStrength(HTIRS2, c1, c2, c3, c4, c5);
	int returnVal;

	if(getDirectionFromIR() == 1)
	{
		returnVal = c1;
	}
	else if(getDirectionFromIR() == 2)
	{
		returnVal = c1 + c2;
	} else if(getDirectionFromIR() == 3)
	{
		returnVal = c2;
	} else if(getDirectionFromIR() == 4)
	{
		returnVal = c2 + c3;
	} else if(getDirectionFromIR() == 5)
	{
		returnVal = c3;
	} else if(getDirectionFromIR() == 6)
	{
		returnVal = c3 + c4;
	} else if(getDirectionFromIR() == 7)
	{
		returnVal = c4;
	} else if(getDirectionFromIR() == 8)
	{
		returnVal = c4 + c5;
	} else if(getDirectionFromIR() == 9)
	{
		returnVal = c5;
	} else
	{
		returnVal = 0;
	}

	if(returnVal <= 10) {
		returnVal = 0;
	}
	return returnVal;
}
