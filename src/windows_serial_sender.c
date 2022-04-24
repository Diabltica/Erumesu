/*
	Created by LE NINIVEN Thomas 24/04/2022
*/


#include "windows_serial_sender.h"
#include <stdio.h>
#include <windows.h>

HANDLE openComPort(int portNumber)
{
	HANDLE hCom;
	char portName[] = "\\\\.\\COM";
	sprintf(portName, "%s%d", portName, portNumber);

	hCom = CreateFileA(portName,
	                   GENERIC_READ | GENERIC_WRITE,//Read/Write
	                   0,                           // No Sharing
	                   NULL,                        // No Security
	                   OPEN_EXISTING,               // Open existing port only
	                   0,                           // Non Overlapped I/O
	                   NULL);                       // Null for Comm Devices

	if (hCom == INVALID_HANDLE_VALUE) {
		return NULL;
	} else {
		return hCom;
	}
}

void closeComPort(HANDLE hCom)
{
	CloseHandle(hCom);//Closing the Serial Port
}

DCB editComPortBaudrate(HANDLE hCom, DCB dcb, int baudrate)
{
	//  Initialize the DCB structure.
	SecureZeroMemory(&dcb, sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);

	GetCommState(hCom, &dcb);

	dcb.BaudRate = baudrate;//set new baudrate

	SetCommState(hCom, &dcb);
	return dcb;
}

void printConfig(DCB dcb)
{
	printf("BaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d\n",
	       dcb.BaudRate, dcb.ByteSize, dcb.Parity, dcb.StopBits);
}

void sendData(HANDLE hcom, char *data)
{
	LPCVOID lpbuffer = data;
	DWORD dNoOFBytestoWrite = strlen(data);
	WriteFile(hcom,
	          lpbuffer,
	          dNoOFBytestoWrite,
	          &dNoOFBytestoWrite,
	          NULL);
}