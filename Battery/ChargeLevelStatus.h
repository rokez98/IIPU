#pragma once

enum ChargeLevelStatus {
	High = 1,
	Low = 2,
	Critical = 4,
	Charging = 8,
	NoSystemBattery = 128,
	UnknownChargeLevelStatus = 255
};