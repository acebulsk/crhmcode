#pragma once


// mainForm dialog

class mainForm : public CDialogEx
{
	DECLARE_DYNAMIC(mainForm)

public:
	mainForm(CWnd* pParent = nullptr);   // standard constructor
	virtual ~mainForm();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = MAIN_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
