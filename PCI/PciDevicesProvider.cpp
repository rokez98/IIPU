#include "PciDevicesProvider.h"
#include "Parser.h"


bool PciDevicesProvider::Initialize() {
	DevInfoSet = SetupDiGetClassDevs(
		NULL,								// Class GUID
		"PCI",								// Enumerator
		NULL,								// hwndParent
		DIGCF_ALLCLASSES | DIGCF_PRESENT);	// Flags

	if (DevInfoSet == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	else return TRUE;
}

std::vector<Device> PciDevicesProvider::GetDevices() {
	DevInfoData.cbSize = sizeof(DevInfoData);

	std::vector<Device> devicesList;

	int count = 0;
	while (SetupDiEnumDeviceInfo(DevInfoSet, count, &DevInfoData)) {
		SetupDiGetDeviceRegistryProperty(
			DevInfoSet,					// Device Info Set
			&DevInfoData,				// Device Info Data
			SPDRP_HARDWAREID,			// Propetry	
			NULL,						// Property Reg Data Type
			(BYTE*)pbuffer,				// Property Buffer
			512,						// Property Buffer Size 
			NULL);						// Required Size

		Device device = parser.Parse(std::string(pbuffer));
		devicesList.push_back(device);

		count++;
	}

	return devicesList;
}

void PciDevicesProvider::DestoyInfoList() {
	SetupDiDestroyDeviceInfoList(DevInfoSet);
}