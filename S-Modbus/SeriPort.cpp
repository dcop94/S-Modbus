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
	// 열려있는지 확인, 그리고 닫기
	if (IsOpen()) {
		ClosePort();
	}

	// COM포트 
	std::string fullPortName = portName;
	if (fullPortName.rfind("\\\\.\\", 0) == std::string::npos)
	{
		fullPortName = "\\\\.\\" + portName;
	}

	// 1. 포트 열기
	m_hPort = CreateFileA( // HANDLE CreateFileA
		fullPortName.c_str(), // 만들거나 열 파일 또는 디바이스 이름
		GENERIC_READ | GENERIC_WRITE, // 파일 또는 디바이스에 대한 요청된 엑세스
		0, // 엑세스 요청 (0은 다른 프로세스가 파일 또는 디바이스를 열 수 없도록 함)
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
