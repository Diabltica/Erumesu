/*
	Created by LE NINIVEN Thomas 24/04/2022
*/
#include <stdio.h>
#include <errno.h>

// Check OS
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	#include "linux_serial_sender.h"
#endif

#if defined(_WIN32) || defined(_WIN64)
	#include "windows/windows_serial_sender.h"
#endif


#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 6
#define PORT_NUMBER 3

int main() {
	HANDLE hcom;
	DCB dcb;

	hcom = openComPort(PORT_NUMBER);

	if(hcom == INVALID_HANDLE_VALUE){
        DWORD dLastError = GetLastError();
        switch (dLastError) {
            case 5: printf("Error COM port %d access denied, port busy\n", PORT_NUMBER);
                    break;
            default: printf("COM port %d not found\n", PORT_NUMBER);
        }
		return 0;
	}
	printf("COM port %d opened successfully\n", PORT_NUMBER);

	dcb = editComPortBaudrate(hcom, dcb, 115200);

	printConfig(dcb);

	sendData(hcom,"S000000255255000000000255000");
	closeComPort(hcom);
	return 0;
}
