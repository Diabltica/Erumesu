/*
	Created by LE NINIVEN Thomas 24/04/2022
*/
#include "display_manager.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
// Check OS
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	#include "linux_serial_sender.h"
#endif

#if defined(_WIN32) || defined(_WIN64)
	#include "windows/windows_serial_sender.h"
#endif



#define PORT_NUMBER 13

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
     // Data protocol
     // S <LED_NUMBER> R <8bits> G <8bits> B <8bits> R <8bits> G <8bits> B <8bits>
	int colorMatrix[3][48] = {{255,0,0,51,65,127,666},
	                          {0,255,0,51,65,127,666},
	                          {0,0,255,51,65,127,666}};
	int size = 0;
	do{
		size++;
	}while(colorMatrix[0][size] != 666);
	char msg [576] = "S00";

	char buffer [20] = "";
	for (int i = 0; i < size; ++i) {
		int R = colorMatrix[0][i];
		int G = colorMatrix[1][i];
		int B = colorMatrix[2][i];
		sprintf(buffer,"R%.3dG%.3dB%.3d",R,G,B);
		strcat(msg, buffer);
	}
	sendData(hcom,msg);
	closeComPort(hcom);

	return 0;
}
