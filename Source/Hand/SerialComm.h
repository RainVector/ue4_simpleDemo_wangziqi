#ifndef SERIALCLASS_H_INCLUDE
#define SERIALCLASS_H_INCLUDE

#define ARDUINO_WAIT_TIME 2000

#include <Windows.h>

class SerialComm
{
public:
	SerialComm();
	~SerialComm();
	int		ReadData(unsigned char *buffer, unsigned int nbChar);	// 读取数据
	int		WriteData(unsigned char *buffer, unsigned int nbChar);	// 写数据
	void	BlindCommPort(DWORD dwPort);
	void	Open();
	void	Close();
	bool	IsConnected();									// 检查串口是否连接

private:
	HANDLE	hSerial;		// 串口句柄
	bool	connected;		// 连接状态
	COMSTAT status;			// 串口状态
	DWORD	errors;			// 追踪最后一个错误
	char	szName[20];		// 保存串口名称 类似COM1的字符串
	DCB		dcb;			// 波特率 停止位 等
};

#endif	// SERIALCLASS_H_INCLUDED

