
// CollatzConjectureMfcDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "CollatzConjectureThread.h"


#define _CR _T("\n")

// CCollatzConjectureMfcDlg dialog
class CCollatzConjectureMfcDlg : public CDialogEx
{
// Construction
public:
	CCollatzConjectureMfcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COLLATZCONJECTUREMFCAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// dialog class variables
protected:
	std::string m_strInitValue;
	static CString m_strDescInitValue;
	static CString m_strDescSeqValue;
	static CString m_strDescStatOddCount;
	static CString m_strDescStatEventCount;
	static CString m_strDescStatLargestValue;

	static CString m_strStatusSetInitValue;
	static CString m_strStatusWaitCalculateResult;
	static CString m_strStatusLastCalculationSpan;
	static CString m_strStatusCalculationStartAt;

	// Implementation
protected:
	HICON m_hIcon;
	CCollatzConjectureThread* m_pSequenceThread;

	CTime m_SeqStartTime;
	CTime m_SeqSFinishTime;

	void CleanSeqDisplay(bool OnlyOutput);
	void ControlsAccess(bool bEnable);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnSequenceFinish(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCalc();
	afx_msg void OnEnChangeEditInitvalue();
	afx_msg void OnEnKillfocusEditInitvalue();
	CEdit m_ebInitValue;
	CEdit m_ebSequence;
	CEdit m_ebLargestValue;
	CEdit m_ebOddMembers;
	CEdit m_ebEvenMembers;
	afx_msg void OnBnClickedButtonClean();
	afx_msg void OnBnClickedButtonSaveSequence();
	afx_msg void OnBnClickedLoadInitValue();
	afx_msg void OnClose();
	CEdit m_ebStatus;
	CButton m_btnLoadInitValue;
	CButton m_btnCalculate;
	CButton m_btnSaveSequence;
	afx_msg void OnDestroy();
};
