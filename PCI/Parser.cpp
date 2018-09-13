#include "Parser.h"
#include "PciDevicesProvider.h"

std::string Parser::getVendorId(std::string info) {
	std::regex regVENID = std::regex(std::string("VEN_.{4}"));
	std::smatch match;
	std::regex_search(info, match, regVENID);

	std::string id = std::string(match[0]).substr(4, 4);

	std::transform(id.begin(), id.end(), id.begin(), ::tolower);

	return id;
}

std::string Parser::getDeviceId(std::string info) {
	std::regex regDEVID = std::regex(std::string("DEV_.{4}"));
	std::smatch match;
	std::regex_search(info, match, regDEVID);

	std::string id = std::string(match[0]).substr(4, 4);

	std::transform(id.begin(), id.end(), id.begin(), ::tolower);

	return id;
}

std::string Parser::getVendorName(std::string vendorId) {
	std::regex regVEN = std::regex(std::string("^" + vendorId + "  "));

	for (int i = 0; i < db.data.size(); i++) {
		std::smatch match;
		if (std::regex_search(db.data.at(i), match, regVEN)) {
			return match.suffix();
		}
	}

	return "";
}

std::string Parser::getDeviceName(std::string deviceId) {
	std::regex regDEV = std::regex(std::string("^\\t" + deviceId + "  "));

	for (int i = 0; i < db.data.size(); i++) {
		std::smatch match;
		if (std::regex_search(db.data.at(i), match, regDEV)) {
			return match.suffix();
		}
	}

	return "";
}

Device Parser::Parse(std::string info) {
	Device device;

	device.deviceId = getDeviceId(info);
	device.vendorId = getVendorId(info);

	device.deviceInfo = getDeviceName(device.deviceId);
	device.vendorInfo = getVendorName(device.vendorId);

	return device;
}

Parser::Parser() {
	db.Initialize();
}


Parser::~Parser() {
}
