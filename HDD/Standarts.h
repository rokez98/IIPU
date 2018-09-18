#pragma once

class Interface {
public:
	int support[16];

	void setSupported(unsigned short supported) {
		int i = 16;

		while (i--) {
			support[i] = supported & 32768 ? 1 : 0;
			supported <<= 1;
		}
	}
};

class ATA : public Interface { };

class DMA : public Interface { };

class PIO : public Interface { };

class Standarts {
public:
	ATA ata;
	DMA dma;
	PIO pio;

	void getSupportedInterfaces(HANDLE diskHandle) {
		UCHAR identifyDataBuffer[512 + sizeof(ATA_PASS_THROUGH_EX)] = { 0 };

		ATA_PASS_THROUGH_EX &PTE = *(ATA_PASS_THROUGH_EX *)identifyDataBuffer;
		PTE.Length = sizeof(PTE);
		PTE.TimeOutValue = 10;
		PTE.DataTransferLength = 512;
		PTE.DataBufferOffset = sizeof(ATA_PASS_THROUGH_EX);
		PTE.AtaFlags = ATA_FLAGS_DATA_IN;

		IDEREGS *ideRegs = (IDEREGS *)PTE.CurrentTaskFile;
		ideRegs->bCommandReg = 0xEC;
		DeviceIoControl(
			diskHandle,
			IOCTL_ATA_PASS_THROUGH,
			&PTE,
			sizeof(identifyDataBuffer),
			&PTE,
			sizeof(identifyDataBuffer),
			NULL,
			NULL
		);

		WORD *data = (WORD *)(identifyDataBuffer + sizeof(ATA_PASS_THROUGH_EX));

		ata.setSupported(data[80]);
		dma.setSupported(data[63]);
		pio.setSupported(data[63]);
	}
};

