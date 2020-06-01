
// Test_assignmentDlg.h : header file
//

#pragma once

#include "odbcinst.h"
#include "afxdb.h"

#include "CNewActivity.h"

// CTestassignmentDlg dialog
class CTestassignmentDlg : public CDialogEx
{
// Construction
public:
	CTestassignmentDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_ASSIGNMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	void startNewActivity(CNewActivity& newActivityDialog);
	void endActivity();
	void getCurrentDateAsStr(CString& targetStr);
	void insertActivityToTreeView();
	void insertActivityToDB();
	CString convertSecToStr(int sec);

	HTREEITEM FindItem(const CString& name, HTREEITEM hRoot);
	// Values
	CString m_actMainCategory;
	CString m_actSubCategory;
	CString m_actComment;
	CString m_startDate;
	CString m_endDate;
	time_t	m_startTime;
	int		m_elapsed_time;

	bool m_bIsRunning;

	CDatabase	m_DB;
	CString		m_sDsn;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStartStop();
	afx_msg void OnBnClickedButtonCancel();
	CTreeCtrl m_activityTreeCtrl;
};
