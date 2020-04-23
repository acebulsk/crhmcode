#pragma once


// EntryFormDlg dialog



class Module {
public:
	Module() : head(0), tail(0), avail(false), isGroup(false), isStruct(false) {};
	int head;
	int tail;
	bool avail;
	bool isGroup;
	bool isStruct;
	static long GrpCnt;
	static long StructCnt;
};

class EntryFormDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EntryFormDlg)

public:
	EntryFormDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EntryFormDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = EntryForm_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void FormActivate();

};
