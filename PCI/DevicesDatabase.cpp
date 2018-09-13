#include "DevicesDatabase.h"

void DevicesDatabase::Initialize() {
	std::ifstream devInfoFile("pci.ids.txt");
	if (!devInfoFile.is_open()) {
		std::cerr << GetLastError();
	}

	std::string buffer;
	while (std::getline(devInfoFile, buffer)) {
		data.push_back(buffer);
	}
	devInfoFile.close();
}