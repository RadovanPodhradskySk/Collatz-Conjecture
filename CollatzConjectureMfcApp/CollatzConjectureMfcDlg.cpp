
// CollatzConjectureMfcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "CollatzConjectureMfcApp.h"
#include "CollatzConjectureMfcDlg.h"
#include "CollatzConjectureMfcWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// could be as resource strings
CString  CCollatzConjectureMfcDlg::m_strDescInitValue = _T("Initial Positive Number");
CString  CCollatzConjectureMfcDlg::m_strDescSeqValue = _T("Generated Sequence");
CString  CCollatzConjectureMfcDlg::m_strDescStatOddCount = _T("Number of Odd Members");
CString  CCollatzConjectureMfcDlg::m_strDescStatEventCount = _T("Number of Even Members");
CString  CCollatzConjectureMfcDlg::m_strDescStatLargestValue = _T("Largest Sequence Value");

CString  CCollatzConjectureMfcDlg::m_strStatusSetInitValue = _T("Set initial value and press Calculate button.");
CString  CCollatzConjectureMfcDlg::m_strStatusWaitCalculateResult = _T("Wait for sequence calculation finish.");
CString  CCollatzConjectureMfcDlg::m_strStatusLastCalculationSpan = _T(" Last calculation take: %H:%M:%S.");
CString  CCollatzConjectureMfcDlg::m_strStatusCalculationStartAt = _T(" Current calculation starts at: %H:%M:%S.");

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCollatzConjectureMfcDlg dialog

CCollatzConjectureMfcDlg::CCollatzConjectureMfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCollatzConjectureMfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSequenceThread = NULL;

}

void CCollatzConjectureMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_INITVALUE, m_strInitValueText);
	//  DDX_Text(pDX, IDC_EDIT_SEQUENCE, m_strSequence);
	DDX_Control(pDX, IDC_EDIT_INITVALUE, m_ebInitValue);
	DDX_Control(pDX, IDC_EDIT_SEQUENCE, m_ebSequence);
	DDX_Control(pDX, IDC_EDIT_LARGESTVALUE, m_ebLargestValue);
	DDX_Control(pDX, IDC_EDIT_ODD_MEMBERS, m_ebOddMembers);
	DDX_Control(pDX, IDC_EDIT_EVEN_MEMBERS, m_ebEvenMembers);
	DDX_Control(pDX, IDC_STATUS_BAR, m_ebStatus);
	DDX_Control(pDX, IDC_LOAD_INIT_VALUE, m_btnLoadInitValue);
	DDX_Control(pDX, IDC_BUTTON_CALC, m_btnCalculate);
	DDX_Control(pDX, IDC_BUTTON_SAVE_SEQUENCE, m_btnSaveSequence);
}

BEGIN_MESSAGE_MAP(CCollatzConjectureMfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CALC, &CCollatzConjectureMfcDlg::OnBnClickedButtonCalc)
	ON_EN_CHANGE(IDC_EDIT_INITVALUE, &CCollatzConjectureMfcDlg::OnEnChangeEditInitvalue)
	ON_EN_KILLFOCUS(IDC_EDIT_INITVALUE, &CCollatzConjectureMfcDlg::OnEnKillfocusEditInitvalue)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CCollatzConjectureMfcDlg::OnBnClickedButtonClean)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SEQUENCE, &CCollatzConjectureMfcDlg::OnBnClickedButtonSaveSequence)
	ON_BN_CLICKED(IDC_LOAD_INIT_VALUE, &CCollatzConjectureMfcDlg::OnBnClickedLoadInitValue)
	ON_MESSAGE(WMU_SEQUENCEFINISH, OnSequenceFinish)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCollatzConjectureMfcDlg message handlers

BOOL CCollatzConjectureMfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// create sequence thread
	m_pSequenceThread = new CCollatzConjectureThread();

	m_pSequenceThread->CreateThread(CREATE_SUSPENDED);
	m_pSequenceThread->m_bAutoDelete = false; // Let me delete it.
	// get init value string pointer
	m_pSequenceThread->m_pstrInitValue = &m_strInitValue;

	m_ebStatus.SetWindowTextW(m_strStatusSetInitValue);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCollatzConjectureMfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCollatzConjectureMfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCollatzConjectureMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CCollatzConjectureMfcDlg::OnBnClickedButtonCalc()
{
	// TODO: Add your control notification handler code here
	// all necessary data define in dlg.cpp amd call wrapper functions here
	//m_ebSequence.SetWindowTextW(_T(""));
	CleanSeqDisplay(true);
	ControlsAccess(false);
	m_SeqStartTime = CTime::GetCurrentTime();
	m_ebStatus.SetWindowTextW(m_strStatusWaitCalculateResult + m_SeqStartTime.Format(m_strStatusCalculationStartAt));

	// process math to take Collatz Conjecture sequence in thread, it post OnSequenceFinish on finish
	if (m_pSequenceThread != NULL)
	{
		m_pSequenceThread->WakeUp();
		m_pSequenceThread->ResumeThread();
	}

	// MOVED TO THREAD RUN() and OnSequenceFinish message handler
	// process math to take Collatz Conjecture sequence, get it's results and display it in dialog controls
	//if (CCW_CalcSequence(&m_strInitValue) == true)
	//{
	//	std::string sText = "";
	//	
	//	CCW_GetSequence(&sText);
	//	CString strText(sText.c_str());
	//	m_ebSequence.SetWindowTextW(strText);

	//	sText.clear();
	//	CCW_GetLargest(&sText);
	//	strText = sText.c_str();
	//	m_ebLargestValue.SetWindowTextW(strText);

	//	sText.clear();
	//	CCW_GetOddCount(&sText);
	//	strText = sText.c_str();
	//	m_ebOddMembers.SetWindowTextW(strText);

	//	sText.clear();
	//	CCW_GetEvenCount(&sText);
	//	strText = sText.c_str();
	//	m_ebEvenMembers.SetWindowTextW(strText);
	//}
}


// initial number changed handler
void CCollatzConjectureMfcDlg::OnEnChangeEditInitvalue()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	//CCollatzConjectureMfcApp* pApp = (CCollatzConjectureMfcApp*)AfxGetApp();
}


void CCollatzConjectureMfcDlg::OnEnKillfocusEditInitvalue()
{
	// TODO: Add your control notification handler code here
	CString strText; 
	//CCollatzConjectureMfcApp* pApp = (CCollatzConjectureMfcApp*)AfxGetApp();

	m_ebInitValue.GetWindowTextW(strText);

	USES_CONVERSION;
	m_strInitValue = W2A(strText);
	
	//pApp->m_u2lInputNumber = _tcstoui64(strText, NULL, 10);
}


void CCollatzConjectureMfcDlg::OnBnClickedButtonClean()
{
	// TODO: Add your control notification handler code here
	// add yes/no dialog box
	CString strText = _T("Clear displayed sequence values?");
	if (AfxMessageBox(strText, MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		CleanSeqDisplay(false);
	}
}

void CCollatzConjectureMfcDlg::CleanSeqDisplay(bool OnlyOutput)
{
	if (!OnlyOutput) { m_ebInitValue.SetWindowTextW(_T("")); }

	m_ebSequence.SetWindowTextW(_T(""));
	m_ebLargestValue.SetWindowTextW(_T(""));
	m_ebOddMembers.SetWindowTextW(_T(""));
	m_ebEvenMembers.SetWindowTextW(_T(""));
}

void CCollatzConjectureMfcDlg::ControlsAccess(bool bEnable)
{
	m_btnLoadInitValue.EnableWindow(bEnable);
	m_btnCalculate.EnableWindow(bEnable);
	m_btnSaveSequence.EnableWindow(bEnable);
}


void CCollatzConjectureMfcDlg::OnBnClickedButtonSaveSequence()
{
	// TODO: Add your control notification handler code here

    // save as dialog and save sequence output to stdiofile
	const TCHAR szFilter[] = _T("TXT Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("csv"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();
		CString strLine = _T("");

		try
		{
			CStdioFile InitValueFile(strFilePath, CFile::modeCreate | CFile::modeWrite, NULL);
			
			// save sequence params, result and stats to file
			std::string sText = "";

			// init value
			USES_CONVERSION;
			InitValueFile.WriteString(m_strDescInitValue + _CR);
			strLine = m_strInitValue.c_str();
			strLine += _CR; strLine += _CR;
			InitValueFile.WriteString(strLine);

			// sequence
			InitValueFile.WriteString(m_strDescSeqValue + _CR);
			CCW_GetSequence(&sText);
			strLine = sText.c_str();
			strLine += _CR; strLine += _CR;
			InitValueFile.WriteString(strLine);

			// largest
			InitValueFile.WriteString(m_strDescStatLargestValue + _CR);
			sText.clear();
			CCW_GetLargest(&sText);
			strLine = sText.c_str();
			strLine += _CR; strLine += _CR;
			InitValueFile.WriteString(strLine);

			// odd count
			InitValueFile.WriteString(m_strDescStatOddCount + _CR);
			sText.clear();
			CCW_GetOddCount(&sText);
			strLine = sText.c_str();
			strLine += _CR; strLine += _CR;
			InitValueFile.WriteString(strLine);

			// even count
			InitValueFile.WriteString(m_strDescStatEventCount + _CR);
			sText.clear();
			CCW_GetEvenCount(&sText);
			strLine = sText.c_str();
			strLine += _CR; strLine += _CR;
			InitValueFile.WriteString(strLine);

			InitValueFile.Close();

		}
		catch (CFileException* pe)
		{
			TRACE(_T("File could not be opened, cause = %d\n"),
				pe->m_cause);
			pe->Delete();
		}
	}
}


void CCollatzConjectureMfcDlg::OnBnClickedLoadInitValue()
{
	// TODO: Add your control notification handler code here

	const TCHAR szFilter[] = _T("TXT Files (*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("csv"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();
		CString strInitValue = _T("");
		CString strLine = _T("");

		try
		{
			CStdioFile InitValueFile(strFilePath, CFile::modeRead, NULL);
			while (InitValueFile.ReadString(strLine))
			{
				strInitValue += strLine;
			}

			m_ebInitValue.SetWindowTextW(strInitValue);
			USES_CONVERSION;
			m_strInitValue = W2A(strInitValue);

			InitValueFile.Close();
		}
		catch (CFileException* pe)
		{
			TRACE(_T("File could not be opened, cause = %d\n"),
				pe->m_cause);
			pe->Delete();
		}
	}
}


// user message handler psted on sequence calculation done from worker thread CollatzConjectureThread
afx_msg LRESULT CCollatzConjectureMfcDlg::OnSequenceFinish(WPARAM wparam, LPARAM lparam)
{
	// LPCTSTR lpszMessage = (LPCTSTR)lparam;

	// add text to view
	//if (::IsWindow(m_wndView.m_hWnd))
	//{
	//	m_wndView.AddMessage(lpszMessage);
	//}
	m_SeqSFinishTime = CTime::GetCurrentTime();
	CTimeSpan CalcSpan = m_SeqSFinishTime - m_SeqStartTime;
	CString strCalcSpan = CalcSpan.Format(m_strStatusLastCalculationSpan);

	if (m_pSequenceThread != NULL)
	{
		m_pSequenceThread->SuspendThread();

	}

	bool bSequenceResult = static_cast<DWORD_PTR>(lparam) == 0 ? false : true;
	
	if (bSequenceResult)
	{
		std::string sText = "";

		CCW_GetSequence(&sText);
		CString strText(sText.c_str());
		m_ebSequence.SetWindowTextW(strText);

		sText.clear();
		CCW_GetLargest(&sText);
		strText = sText.c_str();
		m_ebLargestValue.SetWindowTextW(strText);

		sText.clear();
		CCW_GetOddCount(&sText);
		strText = sText.c_str();
		m_ebOddMembers.SetWindowTextW(strText);

		sText.clear();
		CCW_GetEvenCount(&sText);
		strText = sText.c_str();
		m_ebEvenMembers.SetWindowTextW(strText);
	}

	m_ebStatus.SetWindowTextW(m_strStatusSetInitValue + strCalcSpan);
	ControlsAccess(true);

	return 0L;
}


void CCollatzConjectureMfcDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnClose();
}


void CCollatzConjectureMfcDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// set thread exit flag befor cancel calculation
	if (m_pSequenceThread != NULL)
	{
		if (m_pSequenceThread->IsWakedUp())
		{
			m_pSequenceThread->SetExitFlag();
		}
	}

	// if calcularion run, force it to finish loop
	CCW_CancelCalculation();
	//bool bCalcCancel = CCW_IsCalcCancel();

	// let calc exit loop
	for (int nCnt = 0; CCW_IsCalcRun() == true && nCnt < 100; nCnt++)
	{
		Sleep(10);
	} 

	if (m_pSequenceThread != NULL)
	{
		if(m_pSequenceThread->IsWakedUp())
		{ 
			Sleep(30);
		}
	}

	delete(m_pSequenceThread);
	m_pSequenceThread = NULL;
}

