#pragma once

#define IS_VALID_HANDLE(h) ((NULL != (h)) && ((h) != INVALID_HANDLE_VALUE))

// CCollatzConjectureThread

class CCollatzConjectureThread : public CWinThread
{
	DECLARE_DYNCREATE(CCollatzConjectureThread)

// protected: constructor inaccesible in case of protected added by class wizard
public:
	CCollatzConjectureThread();           // protected constructor used by dynamic creation
	virtual ~CCollatzConjectureThread();

	std::string* m_pstrInitValue;
	bool m_bExit;
	bool m_bMakeWork;
	bool m_bRunDone;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	inline void CCollatzConjectureThread::SetExitFlag(){ m_bExit = true; };
	inline bool CCollatzConjectureThread::IsRunDone(){ return m_bRunDone; };
	inline bool CCollatzConjectureThread::IsWakedUp(){ return m_bMakeWork; };
	void WakeUp();

protected:
	DECLARE_MESSAGE_MAP()
};


