#pragma once

#define MEGABYTE 1048576

class Memory {
public:
	ULONGLONG totalDiskSpace;
	ULONGLONG totalFreeSpace;

	void CalcMemory(HANDLE diskHandle) {
		unsigned long int logicalDrivesCount = GetLogicalDrives();

		DISK_GEOMETRY diskGeometry = { 0 };
		DWORD junk = 0;

		if (!DeviceIoControl(
			diskHandle,						// hDevice
			IOCTL_DISK_GET_DRIVE_GEOMETRY,	// dwloControlCode
			NULL,							// lplnBuffer 
			0,								// nlnBufferSize
			&diskGeometry,					// lpOutBuffer
			sizeof(diskGeometry),			// nOutBufferSize
			&junk,							// lpBytesReturned
			(LPOVERLAPPED)NULL				// lpOverlapper
		)) {
			printf("%d", GetLastError());
			CloseHandle(diskHandle);
			exit(-1);
		}

		ULONGLONG DiskSize;

		DiskSize = diskGeometry.Cylinders.QuadPart *
			(ULONG)diskGeometry.TracksPerCylinder *
			(ULONG)diskGeometry.SectorsPerTrack *
			(ULONG)diskGeometry.BytesPerSector;

		this->totalDiskSpace = DiskSize / MEGABYTE;
	}
};