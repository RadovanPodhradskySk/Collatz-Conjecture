// CollatzConjectureThread.cpp : implementation file
//

#include "stdafx.h"
#include "CollatzConjectureMfcApp.h"
#include "CollatzConjectureThread.h"
#include "CollatzConjectureMfcWrapper.h"
#include "TraceWrapper.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

// CCollatzConjectureThread

IMPLEMENT_DYNCREATE(CCollatzConjectureThread, CWinThread)

CCollatzConjectureThread::CCollatzConjectureThread()
{
	m_pstrInitValue = NULL;
	m_bExit = false;
	m_bMakeWork = false;
	m_bRunDone = false;
}

CCollatzConjectureThread::~CCollatzConjectureThread()
{
}

BOOL CCollatzConjectureThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CCollatzConjectureThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

void CCollatzConjectureThread::WakeUp()
{
	m_bMakeWork = true;
}

BEGIN_MESSAGE_MAP(CCollatzConjectureThread, CWinThread)
END_MESSAGE_MAP()


// CCollatzConjectureThread message handlers


int CCollatzConjectureThread::Run()
{
	TRACE(("CCollatzConjectureThread: Run() called\n"));
	
	while (!m_bExit)
	{
		bool bSeqResult = false;

		if (m_bMakeWork)
		{

			TRACE(("CCollatzConjectureThread: Run() calculation start\n"));	
			if (m_pstrInitValue != NULL)
			{
				bSeqResult = CCW_CalcSequence(m_pstrInitValue);
			}
			TRACE(("CCollatzConjectureThread: Run() calculation finish\n"));

			if (!m_bExit && bSeqResult)
			{
				CWinApp* pApp = AfxGetApp();
				HWND hMainWnd = pApp->m_pMainWnd->m_hWnd;
				// check validity of handle
				if (IS_VALID_HANDLE(hMainWnd))
				{
					PostMessage(hMainWnd, WMU_SEQUENCEFINISH, (WPARAM)NULL, (LPARAM)(bSeqResult) ? static_cast<DWORD_PTR>(1) : static_cast<DWORD_PTR>(0));
				}
			}

			m_bMakeWork = false;
		}

		// threading sleep 1ms
		if (!m_bExit && bSeqResult)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	m_bRunDone = true;

	return (0);
}


//{