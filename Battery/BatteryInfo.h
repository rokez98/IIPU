#pragma once

#include "ACLineStatus.h"
#include "ChargeLevelStatus.h"
#include "BatterySaverStatus.h"
#include "BatteryLifePercent.h"

class BatteryInfo
{
public:
	ACLineStatus ACStatus;
	ChargeLevelStatus ChargeLevel;
	BatteryLifePercent BatteryLifePercent;
	BatterySaverStatus  BatterySaver;
};