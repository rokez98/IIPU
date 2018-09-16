#pragma once

#include "DiskDrive.h"

const char* busType[] = { "UNKNOWN", "SCSI", "ATAPI", "ATA", "ONE_TREE_NINE_FOUR", "SSA", "FIBRE", "USB", "RAID", "ISCSI", "SAS", "SATA", "SD", "MMC" };

class StorageInfoProvider {
	DiskDrive drive;
	HANDLE diskHandle;

public:
	StorageInfoProvider() {
		diskHandle = CreateFile(
			"\\\\.\\PhysicalDrive0",		// File name
			GENERIC_READ | GENERIC_WRITE,	// Access
			FILE_SHARE_READ,				// Security attributes
			NULL,
			OPEN_EXISTING,
			NULL,
			NULL
		);
	}

	DiskDrive getHddInfo() {
		STORAGE_PROPERTY_QUERY storagePropertyQuery;
		storagePropertyQuery.QueryType = PropertyStandardQuery;
		storagePropertyQuery.PropertyId = StorageDeviceProperty;

		STORAGE_DEVICE_DESCRIPTOR* deviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)calloc(1024, 1);

		if (!DeviceIoControl(
			diskHandle,						// hDevice
			IOCTL_STORAGE_QUERY_PROPERTY,	// dwloControlCode
			&storagePropertyQuery,			// lplnBuffer 
			sizeof(storagePropertyQuery),	// nlnBufferSize
			deviceDescriptor,				// lpOutBuffer
			1024,							// nOutBufferSize
			NULL,							// lpBytesReturned
			NULL							// lpOverlapper
		)) {
			printf("%d", GetLastError());
			CloseHandle(diskHandle);
			exit(-1);
		}

		drive.ProductId = (char*)(deviceDescriptor)+deviceDescriptor->ProductIdOffset;
		drive.Revision = (char*)(deviceDescriptor)+deviceDescriptor->ProductRevisionOffset;
		drive.BusType = (char*)busType[deviceDescriptor->BusType];
		drive.SerialNumber = (char*)(deviceDescriptor)+deviceDescriptor->SerialNumberOffset;

		drive.standarts.getSupportedInterfaces(diskHandle);

		return drive;
	}
};