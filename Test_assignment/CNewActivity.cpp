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

	// TODO: add subcategories depending on main category!
	m_subCatComboBox.AddString(L"Synthesis homework");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
void CNewActivity::OnCbnSelchangeCombo()
{
	
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------
