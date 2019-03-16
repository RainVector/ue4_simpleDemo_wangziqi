//#include "stdafx.h"
#include "SerialComm.h"
#include <iostream>
#include <tchar.h>
#include <assert.h>

SerialComm::SerialComm():connected(false)
{
	memset(szName, 0, sizeof(unsigned char)*20);
}

SerialComm::~SerialComm()
{
	// Check if we are connected before trying to disconnect
	if (connected)
	{
		// We're no longer connected
		connected = false;
		// Close the serial handler
		CloseHandle(hSerial);
	}
}

void SerialComm::BlindCommPort(DWORD dwPort)
{
	assert(dwPort >= 1 && dwPort <= 1024);

	char p[5];

	strcpy_s(szName, "COM"); 
	_ltoa_s(dwPort, p, 10);
	strcat_s(szName, p);

}

void SerialComm::Close()
{
	// Check if we are connected before trying to disconnect
	if (connected)
	{
		// We're no longer connected
		connected = false;
		// Close the serial handler
		CloseHandle(hSerial);
	}
}

void SerialComm::Open()
{
	hSerial = CreateFileA(
		szName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// check if the connection was successfull
	if (!IsConnected())
	{
		MessageBox(NULL, _T("Serial Port Open Failure!"),_T("Alert"), MB_OK);

		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			// Print Error if neccessary
			printf("Error: Handle was not attached, Reason: %s not available.\n", szName);
			//MessageBox(NULL, _T("Error: Handle was not attached, Reason: %s not available."),_T("Alert"), MB_OK);
		}
		else
		{
			printf("Error\n");
		}
		return;
	}
	else
	{
		// If connected we try to set the comm parameters
		DCB dcbSerialParams = { 0 };

		// Define serial connection parameters for the arduino board
		if (!GetCommState(hSerial, &dcbSerialParams))
		{
			// If impossible, show an error
			printf("failed to get current serial parameters!\n");
			MessageBox(NULL, _T("ALERT: Failed to get current serial parameters!"),_T("Alert"), MB_OK);
		}
		else
		{
			// Define serial connection parameters for the arduino board
			dcbSerialParams.BaudRate = CBR_115200;
			dcbSerialParams.ByteSize = 8;
			dcbSerialParams.StopBits = ONESTOPBIT;
			dcbSerialParams.Parity = NOPARITY;
			// Setting the DTR to Control_Enable ensures that te Arduino is properly
			// reset upon establishing a connection
			dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

			// Set the parameters and check for their proper application
			if (!SetCommState(hSerial, &dcbSerialParams))
			{				
				printf("ALERT: Could not set Serial Port parameters\n");
				MessageBox(NULL, _T("ALERT: Could not set Serial Port parameters"),_T("Alert"), MB_OK);
			}
			else
			{
				// If everything went fine we're connected
				connected = true;
				//SetWindowTextW(NULL, _T("Serial Port is OK"));
				//MessageBox(NULL, _T("Serial Port is OK"),_T("Alert"), MB_OK);
				//printf("Serial Port is OK\n");
				//AfxMessageBox("Serial Port is OK");
				// Flush any reminding characters in the buffers
				PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
				// We wait 2s as the arduino board will be reseting
				Sleep(ARDUINO_WAIT_TIME);
				return;
			}
		}
	}
}

bool SerialComm::IsConnected()
{
	return hSerial != INVALID_HANDLE_VALUE;
}

// 读取串口中nbChar字节的数据，存入buffer中，返回读取到的字节数
int SerialComm::ReadData(unsigned char *buffer, unsigned int nbChar)
{
	// Number of bytes we'll have read
	DWORD bytesRead;
	// Number of bytes we'll really ask to read
	unsigned int toRead;

	// Use the ClearCommError function to get status info on the Serial port
	ClearCommError(hSerial, &errors, &status);

	// Check if there is something to read
	if (status.cbInQue > 0)
	{
		// If there is we check if there is enough data to read the required number
		// of characters, if not we'll read only the available characters to prevent 
		// locking of the application
		if (status.cbInQue > nbChar)
		{
			toRead = nbChar;
		}
		else
		{
			toRead = status.cbInQue;
		}

		// Try to read the require number of chars, and return the number of read bytes on
		if (ReadFile(hSerial, buffer, toRead, &bytesRead, NULL))
		{
			return bytesRead;
		}
	}

	// If nothing has been read, or that an error was detected return 0
	return 0;
}

// 
int SerialComm::WriteData(unsigned char *buffer, unsigned int nbChar)
{
	DWORD bytesSend;

	// Try to write the buffer on the Serial port
	if (!WriteFile(hSerial, buffer, nbChar, &bytesSend, NULL))
	{
		// In case it don't work get comm error and return false
		ClearCommError(hSerial, &errors, &status);

		return -1;
	}
	else
		return bytesSend;
}


