#pragma once

#include "Memory.h";
#include "Standarts.h";

class DiskDrive
{
public:
	char* ProductId;
	char* Revision;
	char* BusType;
	char* SerialNumber;

	Standarts standarts;

	Memory memory;
};