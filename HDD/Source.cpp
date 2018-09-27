#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <WinIoCtl.h>
#include <ntddscsi.h>
#include <conio.h>

#include "DiskDrive.h"
#include "StorageInfoProvider.h"

using namespace std;


void ShowInfo(DiskDrive drive) {
	cout << "Model:         " << drive.ProductId << endl;
	cout << "Version        " << drive.Revision << endl;
	cout << "Bus type:      " << drive.BusType << endl;
	cout << "Serial number: " << drive.SerialNumber << endl;

	cout << "Total space[Mb]:  " << drive.memory.totalDiskSpace << endl;

	cout << "ATA Support:   ";
	for (int i = 8; i >= 4; i--) {
		if (drive.standarts.ata.support[i] == 1)
			cout << "ATA" << i << " | ";
	}
	cout << endl;

	cout << "DMA Support:   ";
	for (int i = 0; i < 8; i++) {
		if (drive.standarts.dma.support[i] == 1)
			cout << "DMA" << i << " | ";
	}
	cout << endl;

	cout << "PIO Support:   ";
	for (int i = 0; i < 2; i++) {
		if (drive.standarts.pio.support[i] == 1)
			cout << "PIO" << i + 3 << " | ";
	}
	cout << endl;
}

int main() {
	StorageInfoProvider provider;
	DiskDrive hdd = provider.getHddInfo();

	ShowInfo(hdd);

	system("pause");
	return 0;
}