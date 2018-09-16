#pragma once

#define MEGABYTE 1048576

class Memory {
public:
	int totalDiskSpace;
	int totalFreeSpace;

	Memory() {
		_ULARGE_INTEGER totalDiskSpace, diskSpace;
		_ULARGE_INTEGER totalFreeSpace, freeSpace;
		
		totalDiskSpace.QuadPart = totalFreeSpace.QuadPart = 0;

		unsigned long int logicalDrivesCount = GetLogicalDrives();

		for (char var = 'A'; var < 'Z'; var++) {
			if ((logicalDrivesCount >> var - 65) & 1) {
				std::string path;
				path = var;
				path.append(":\\");

				if (GetDriveType(path.c_str()) == DRIVE_FIXED) {
					GetDiskFreeSpaceEx(path.c_str(), 0, &diskSpace, &freeSpace);

					totalDiskSpace.QuadPart += diskSpace.QuadPart / MEGABYTE;
					totalFreeSpace.QuadPart += freeSpace.QuadPart / MEGABYTE;
				}
			}
		}

		this->totalDiskSpace = totalDiskSpace.QuadPart;
		this->totalFreeSpace = totalFreeSpace.QuadPart;
	}
};