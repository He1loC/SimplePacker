
// SimplePackerDlg.h : header file
//

#pragma once


// CSimplePackerDlg dialog
class CSimplePackerDlg : public CDialogEx
{
// Construction
public:
	CSimplePackerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIMPLEPACKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strFileName;
	afx_msg void OnBnClickedButtonPack();
	afx_msg void OnBnClickedButtonUnpack();
};
