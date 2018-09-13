#include <iostream>
#include <locale>
#include <iomanip>
#include "PciDevicesProvider.h"

#pragma comment( lib, "setupapi.lib" )

using namespace std;

int main() {
	PciDevicesProvider provider;
	provider.Initialize();

	vector<Device> Device = provider.GetDevices();

	for (int i = 0; i < Device.size(); i++) {

		cout << setw(5) << left << Device.at(i).vendorId
			 << setw(40) << left << Device.at(i).vendorInfo
			 << setw(5) << left << Device.at(i).deviceId
			 << setw(40) << left << Device.at(i).deviceInfo << endl;
	}
	provider.DestoyInfoList();

	system("pause");
	return EXIT_SUCCESS;
}