/*
	Created by LE NINIVEN Thomas 24/04/2022
*/

#ifndef ERUMESU_WINDOWS_SERIAL_SENDER_H
#define ERUMESU_WINDOWS_SERIAL_SENDER_H
#include <windows.h>

HANDLE openComPort(int portNumber);
void closeComPort(HANDLE hComm);
void printConfig(DCB dcb);
//BAUDRATE AVAILABLE
/* 110
 * 300
 * 600
 * 1200
 * 2400
 * 4800
 * 9600
 * 14400
 * 19200
 * 38400
 * 57600
 * 115200
 * 128000
 * 25600
 */
DCB editComPortBaudrate(HANDLE hCom, DCB dcb, int baudrate);
void sendData(HANDLE hcom, char *data);

#endif//ERUMESU_WINDOWS_SERIAL_SENDER_H
