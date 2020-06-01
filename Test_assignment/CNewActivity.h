#pragma once


// CNewActivity dialog

class CNewActivity : public CDialogEx
{
	DECLARE_DYNAMIC(CNewActivity)

public:
	CNewActivity(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewActivity();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_ACTIVITY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	// UI controls
	CComboBox m_mainCatComboBox;
	CComboBox m_subCatComboBox;
	CEdit m_commentEditor;

	// Values
	CString m_actMainCategory;
	CString m_actSubCategory;
	CString m_actComment;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo();
};
