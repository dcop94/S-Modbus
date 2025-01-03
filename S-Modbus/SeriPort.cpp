#include "SeriPort.h"
#include <assert.h>

SeriPort::SeriPort()
	: m_hPort(INVALID_HANDLE_VALUE), m_RunThread(false) {
}

SeriPort::~SeriPort()
{
	ClosePort();
}

bool SeriPort::OpenPort(const std::string& portName,
	DWORD baudRate,
	BYTE dataBits,
	BYTE stopBtis,
	BYTE paity)
{
	// �����ִ��� Ȯ��, �׸��� �ݱ�
	if (IsOpen()) {
		ClosePort();
	}

	// COM��Ʈ 
	std::string fullPortName = portName;
	if (fullPortName.rfind("\\\\.\\", 0) == std::string::npos)
	{
		fullPortName = "\\\\.\\" + portName;
	}

	// 1. ��Ʈ ����
	m_hPort = CreateFileA( // HANDLE CreateFileA
		fullPortName.c_str(), // ����ų� �� ���� �Ǵ� ����̽� �̸�
		GENERIC_READ | GENERIC_WRITE, // ���� �Ǵ� ����̽��� ���� ��û�� ������
		0, // ������ ��û (0�� �ٸ� ���μ����� ���� �Ǵ� ����̽��� �� �� ������ ��)
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (m_hPort == INVALID_HANDLE_VALUE)
	{
		return false;
	}

}
