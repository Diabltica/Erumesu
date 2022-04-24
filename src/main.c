/*
	Created by LE NINIVEN Thomas 24/04/2022
*/
#include <stdio.h>

// Check OS
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	#include "linux_serial_sender.h"
#endif

#if defined(_WIN32) || defined(_WIN64)
	#include "windows_serial_sender.h"
#endif


#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 6

int main() {
	printf("Hello, World!\n %d",MATRIX_HEIGHT);
	return 0;
}
