#pragma once


// CHRMAboutBoxDlg dialog

class CHRMAboutBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHRMAboutBoxDlg)

public:
	CHRMAboutBoxDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CHRMAboutBoxDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = CHRMAboutBox };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
