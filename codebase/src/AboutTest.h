#pragma once


// AboutTest dialog

class AboutTest : public CDialogEx
{
	DECLARE_DYNAMIC(AboutTest)

public:
	AboutTest(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AboutTest();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = CHRMAboutBox };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
