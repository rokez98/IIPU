#pragma once

class BatteryLifePercent {
	int _code = 0;
public:
	BatteryLifePercent() {}

	BatteryLifePercent(int code) {
		this->_code = code;
	}

	int getValue() {
		return _code;
	}
};
