#pragma once

#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>

#include "Device.h"
#include "DevicesDatabase.h"

class Parser
{
public:
	DevicesDatabase db;

	std::string getVendorId(std::string info);
	std::string getDeviceId(std::string info);
	std::string getVendorName(std::string vendorId);
	std::string getDeviceName(std::string deviceId);

	Device Parse(std::string info);

	Parser();
	~Parser();
};