#ifndef SERIALCLASS_H_INCLUDE
#define SERIALCLASS_H_INCLUDE

#define ARDUINO_WAIT_TIME 2000

#include <Windows.h>

class SerialComm
{
public:
	SerialComm();
	~SerialComm();
	int		ReadData(unsigned char *buffer, unsigned int nbChar);	// ��ȡ����
	int		WriteData(unsigned char *buffer, unsigned int nbChar);	// д����
	void	BlindCommPort(DWORD dwPort);
	void	Open();
	void	Close();
	bool	IsConnected();									// ��鴮���Ƿ�����

private:
	HANDLE	hSerial;		// ���ھ��
	bool	connected;		// ����״̬
	COMSTAT status;			// ����״̬
	DWORD	errors;			// ׷�����һ������
	char	szName[20];		// ���洮������ ����COM1���ַ���
	DCB		dcb;			// ������ ֹͣλ ��
};

#endif	// SERIALCLASS_H_INCLUDED

