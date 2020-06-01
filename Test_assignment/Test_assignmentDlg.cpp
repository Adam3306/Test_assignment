
// Test_assignmentDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Test_assignment.h"
#include "Test_assignmentDlg.h"
#include "afxdialogex.h"

#include <time.h>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// CTestassignmentDlg dialog
CTestassignmentDlg::CTestassignmentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_ASSIGNMENT_DIALOG, pParent)
	, m_bIsRunning(false)
	, m_elapsed_time(0)
	, m_actMainCategory("")
	, m_actSubCategory("")
	, m_actComment("")
	, m_startDate("")
	, m_sDsn(L"ODBC;DRIVER={MICROSOFT ACCESS DRIVER (*.mdb)};DSN='';DBQ=Test.mdb")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CTestassignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_activityTreeCtrl);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CTestassignmentDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START_STOP, &CTestassignmentDlg::OnBnClickedButtonStartStop)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CTestassignmentDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// CTestassignmentDlg message handlers
BOOL CTestassignmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CTestassignmentDlg::OnPaint()
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
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestassignmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CTestassignmentDlg::OnBnClickedButtonStartStop()
{
	insertActivityToDB();
	if (!m_bIsRunning)
	{
		CNewActivity newActivityDialog;
		if (newActivityDialog.DoModal() == IDOK)
		{
			startNewActivity(newActivityDialog);
		}
	}
	else
	{
		endActivity();
		m_elapsed_time = difftime(time(0), m_startTime);
		getCurrentDateAsStr(m_endDate);
		insertActivityToTreeView();
	}
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CTestassignmentDlg::insertActivityToTreeView()
{
	HTREEITEM hItem, hCar;
	hItem = FindItem(m_actMainCategory, NULL);
	if (hItem == NULL)
	{
		hItem = m_activityTreeCtrl.InsertItem(m_actMainCategory, TVI_ROOT);
	}
	else
	{
		// update
	}

	hCar = FindItem(m_actSubCategory, hItem);
	if (hCar == NULL)
	{
		hCar = m_activityTreeCtrl.InsertItem(m_actSubCategory, hItem);
	}
	else
	{
		// update
	}

	m_actComment += CString(" - elapsed time: ") + convertSecToStr(m_elapsed_time);
	m_activityTreeCtrl.InsertItem(m_actComment, hCar);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CTestassignmentDlg::insertActivityToDB()
{
	CString SqlString;
	TRY
	{
		// Open the database
		m_DB.Open(NULL, false, false, m_sDsn);

		SqlString = 
			"INSERT INTO Activities ( Catgory, Subcategory, Start_date, End_date, Comment )\
				VALUES\
			( 'Lol', 'jo', '2020-05-30 17:00:00', '2020-05-30 17:17:00', 'kiraly' )";

		m_DB.ExecuteSQL(SqlString);
		// Close the database
		m_DB.Close();
	}
	CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox(L"Database error: " + e->m_strError);
	}
	END_CATCH;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
CString CTestassignmentDlg::convertSecToStr(int sec)
{
	int hour = sec / 3600;
	sec %= 3600;
	int min = sec / 60;
	sec %= 60;

	char buf[64];
	if (hour > 0)
	{
		sprintf_s(buf, "%d hour %d min %d seconds", hour, min, sec);
	}
	else
	if (min > 0)
	{
		sprintf_s(buf, "%d min %d seconds", min, sec);
	}
	else
	{
		sprintf_s(buf, "%d seconds", min, sec);
	}

	return CString(buf);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CTestassignmentDlg::startNewActivity(CNewActivity& newActivityDialog)
{
	m_bIsRunning = true;
	m_actMainCategory = newActivityDialog.m_actMainCategory;
	m_actSubCategory = newActivityDialog.m_actSubCategory;
	m_actComment = newActivityDialog.m_actComment;
	m_startTime = time(0);
	getCurrentDateAsStr(m_startDate);

	GetDlgItem(IDC_BUTTON_START_STOP)->SetWindowText(L"Stop");
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(SW_SHOW);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CTestassignmentDlg::endActivity()
{
	m_bIsRunning = false;
	GetDlgItem(IDC_BUTTON_START_STOP)->SetWindowText(L"Start");
	GetDlgItem(IDC_BUTTON_CANCEL)->ShowWindow(SW_HIDE);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CTestassignmentDlg::getCurrentDateAsStr(CString& targetStr)
{
	time_t rawtime;
	struct tm * timeinfo = new tm();
	char buffer[80];

	time(&rawtime);
	localtime_s(timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
	targetStr = buffer;

	delete timeinfo;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CTestassignmentDlg::OnBnClickedButtonCancel()
{
	endActivity();
	m_actMainCategory.Delete(0, m_actMainCategory.GetLength());
	m_actSubCategory.Delete(0, m_actSubCategory.GetLength());
	m_actComment.Delete(0, m_actComment.GetLength());
	m_startDate.Delete(0, m_startDate.GetLength());
	m_startTime = 0;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
HTREEITEM CTestassignmentDlg::FindItem(const CString & name, HTREEITEM hRoot)
{
	// check whether the current item is the searched one
	CString text = m_activityTreeCtrl.GetItemText(hRoot);
	if (text.Compare(name) == 0)
		return hRoot;

	// get a handle to the first child item
	HTREEITEM hSub = m_activityTreeCtrl.GetChildItem(hRoot);
	// iterate as long a new item is found
	while (hSub)
	{
		// check the children of the current item
		HTREEITEM hFound = FindItem(name, hSub);
		if (hFound)
			return hFound;

		// get the next sibling of the current item
		hSub = m_activityTreeCtrl.GetNextSiblingItem(hSub);
	}

	// return NULL if nothing was found
	return NULL;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------