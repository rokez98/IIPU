#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <WinIoCtl.h>
#include <ntddscsi.h>
#include <conio.h>

#include "BatteryInfo.h"
#include "BatteryInfoProvider.h"
#include "BatteryLifePercent.h"

using namespace std;


std::ostream& operator<<(std::ostream& lhs, ACLineStatus e) {
	switch (e) {
	case Online: lhs << "Online"; break;
	case Offline: lhs << "Offline"; break;
	case UnknownStatus: lhs << "Unknown"; break;
	}
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, ChargeLevelStatus e) {
	switch (e) {
	case High: lhs << "High"; break;
	case Low: lhs << "Low"; break;
	case Critical: lhs << "Critical"; break;
	case Charging: lhs << "Charging"; break;
	case NoSystemBattery: lhs << "No System Battery"; break;
	case UnknownChargeLevelStatus: lhs << "Unknown"; break;
	}
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, BatterySaverStatus e) {
	switch (e) {
	case Off: lhs << "Off"; break;
	case On: lhs << "On"; break;
	}
	return lhs;
}

std::ostream& operator<<(std::ostream& lhs, BatteryLifePercent e) {
	auto value = e.getValue();
	switch (value) {
	case UnknownChargeLevelStatus: lhs << "No system battery"; break;
	default: lhs << value << "%"; break;
	}
	return lhs;
}

void ShowInfo(BatteryInfo battery) {
	cout << "AC line status:          " << battery.ACStatus << endl;
	cout << "Battery charge level:    " << battery.ChargeLevel << endl;
	cout << "Battery life percent:    " << battery.BatteryLifePercent << endl;
	cout << "Battery saver status:    " << battery.BatterySaver << endl;
}

int main() {
	BatteryInfoProvider provider;

	while (true) {
		auto battery = provider.getBatteryInfo();
		ShowInfo(battery);

		Sleep(100);

		system("cls");
	}

	system("pause");
	return 0;
}