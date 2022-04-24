/*
	Created by LE NINIVEN Thomas 24/04/2022
*/

#ifndef ERUMESU_WINDOWS_SERIAL_SENDER_H
#define ERUMESU_WINDOWS_SERIAL_SENDER_H
#include <windows.h>

HANDLE openComPort(int portNumber);
void closeComPort(HANDLE hComm);
void printConfig(DCB dcb);
DCB editComPortBaudrate(HANDLE hCom, DCB dcb, int baudrate);

#endif//ERUMESU_WINDOWS_SERIAL_SENDER_H
