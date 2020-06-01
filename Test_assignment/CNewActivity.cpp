// CNewActivity.cpp : implementation file
//

#include "pch.h"
#include "Test_assignment.h"
#include "CNewActivity.h"
#include "afxdialogex.h"


// CNewActivity dialog

IMPLEMENT_DYNAMIC(CNewActivity, CDialogEx)
// ------------------------------------------------------------------------------------------------------------------------------------------------------
CNewActivity::CNewActivity(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_ACTIVITY_DIALOG, pParent)
{

}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
CNewActivity::~CNewActivity()
{
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CNewActivity::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_mainCatComboBox);
	DDX_Control(pDX, IDC_COMBO2, m_subCatComboBox);
	DDX_Control(pDX, IDC_EDIT1, m_commentEditor);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CNewActivity, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewActivity::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNewActivity::OnCbnSelchangeCombo)
END_MESSAGE_MAP()

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// CNewActivity message handlers
void CNewActivity::OnBnClickedOk()
{
	m_mainCatComboBox.GetLBText(m_mainCatComboBox.GetCurSel(), m_actMainCategory);
	m_subCatComboBox.GetLBText(m_subCatComboBox.GetCurSel(), m_actSubCategory);
	m_commentEditor.GetWindowText(m_actComment);
	if (m_actComment.GetLength() == 0)
	{
		AfxMessageBox(L"Add comment to activity.");
		return;
	}
	CDialogEx::OnOK();
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
BOOL CNewActivity::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_mainCatComboBox.AddString(L"Work");
	m_mainCatComboBox.AddString(L"Learn");
	m_mainCatComboBox.AddString(L"Sport");

	m_subCatComboBox.ResetContent();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CNewActivity::OnCbnSelchangeCombo()
{
	m_mainCatComboBox.GetLBText(m_mainCatComboBox.GetCurSel(), m_actMainCategory);
	
	m_subCatComboBox.ResetContent();

	if (m_actMainCategory.Compare(L"Work") == 0)
	{
		m_subCatComboBox.AddString(L"Work at Sythesis.net company");
		m_subCatComboBox.AddString(L"House work");
	}
	else if (m_actMainCategory.Compare(L"Learn") == 0)
	{
		m_subCatComboBox.AddString(L"Programming");
		m_subCatComboBox.AddString(L"Math");
		m_subCatComboBox.AddString(L"Physics");
		m_subCatComboBox.AddString(L"History");
	}
	else if (m_actMainCategory.Compare(L"Sport") == 0)
	{
		m_subCatComboBox.AddString(L"Running");
		m_subCatComboBox.AddString(L"Swimming");
		m_subCatComboBox.AddString(L"Road cycling");
		m_subCatComboBox.AddString(L"Muay Thai boxing");
	}
	
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
