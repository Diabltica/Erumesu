/*
	Created by LE NINIVEN Thomas 24/04/2022
*/
#include <stdio.h>

// Check OS
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	#include "linux_serial_sender.h"
#endif

#if defined(_WIN32) || defined(_WIN64)
	#include "windows/windows_serial_sender.h"
#endif


#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 6

int main() {
	HANDLE hcom;
	DCB dcb;

	hcom = openComPort(13);

	if(hcom == NULL){
		printf("Error COM port don't open successfully");
		return 0;
	}
	printf("COM port open successfully\n");

	dcb = editComPortBaudrate(hcom, dcb, 115200);

	printConfig(dcb);

	sendData(hcom,"S000000255255000000000255000");
	closeComPort(hcom);
	return 0;
}
