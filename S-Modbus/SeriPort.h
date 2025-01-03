#pragma once
#include <Windows.h>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>

class SeriPort
{
public:
	SeriPort(); //생성자
	~SeriPort(); //소멸자

	// 포트 열기, 닫기
	bool OpenPort(const std::string& protName,
		DWORD baudRate,
		BYTE dataBits = 8,
		BYTE stopBits = ONESTOPBIT,
		BYTE parity = NOPARITY);

	bool ClosePort();
	bool IsOpen() const { return m_hPort != INVALID_HANDLE_VALUE };

	// 데이터 쓰기
	bool WriteData(const BYTE* pData, DWORD size);

	// 스레드
	bool ReadThread();
	void StopReadThread();

	// 큐
	DWORD RecvData(BYTE* outBuf, DWORD bufSize);

private:
	void ThreadF();
	void PushQue(const BYTE* buf, DWORD len);

	HANDLE m_hPort;
	std::thread m_thread;
	std::atomic_bool m_RunThread;

	std::mutex m_mtxQue;
	std::queue<BYTE> m_Queue;

};