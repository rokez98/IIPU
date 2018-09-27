#pragma once

#include <Windows.h>
#include <iostream>
#include "BatteryInfo.h"
#include "ChargeLevelStatus.h"
#include "BatterySaverStatus.h"
#include "BatteryLifePercent.h"

class BatteryInfoProvider {
	BatteryInfo battery;

public:
	BatteryInfo getBatteryInfo() {
		SYSTEM_POWER_STATUS batteryState;

		if ( !GetSystemPowerStatus(&batteryState)) {
			std::cout << GetLastError() << std::endl;
			exit(-1);
		}

		battery.ACStatus = (ACLineStatus) batteryState.ACLineStatus;
		battery.ChargeLevel = (ChargeLevelStatus) batteryState.BatteryFlag;
		battery.BatteryLifePercent = BatteryLifePercent(batteryState.BatteryLifePercent);
		battery.BatterySaver = (BatterySaverStatus) batteryState.SystemStatusFlag;

		return battery;
	}
};