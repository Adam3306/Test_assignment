
// Test_assignmentDlg.h : header file

#pragma once

#include "odbcinst.h"
#include "afxdb.h"

class CNewActivity;

typedef struct
{
	CString			m_actMainCategory;
	CString			m_actSubCategory;
	CString			m_actComment;
	CString			m_startDate;
	CString			m_endDate;
	time_t			m_startTime;
	int				m_elapsed_time;
} sActivity;

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
	virtual void		DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON				m_hIcon;

	// Generated message map functions
	virtual BOOL		OnInitDialog();
	afx_msg void		OnPaint();
	afx_msg HCURSOR		OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void		OnBnClickedButtonStartStop();
	afx_msg void		OnBnClickedButtonCancel();

private:
	// class methods
	void				startNewActivity(CNewActivity& newActivityDialog);
	void				endActivity();
	void				getCurrentDateAsStr(CString& targetStr);
	void				insertActivityToTreeView();
	void				insertActivityToDB();
	void				loadActivities();
	CString				convertSecToStr(int sec);
	int					getSumWorkingSecondsByCategory();
	int					getSumWorkingSecondsBySubcategory();
	HTREEITEM			FindItem(const CString& name, HTREEITEM hRoot);

	// members
	bool				m_bIsRunning;
	CDatabase			m_DB;
	CString				m_sDsn;
	sActivity			m_activity;
	CTreeCtrl			m_activityTreeCtrl;


	
};
