#include "CRHM_GUI.h"
#include "afxdialogex.h"
#include "TStringList.h"
#include "CRHMmain.h"
//#include "GlobalDll.cpp"
#include "ClassModule.h"
#include "MacroUnit.h"

#pragma once


// CReport dialog

class CReport : public CDialog
{
	DECLARE_DYNAMIC(CReport)

public:
	CReport(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CReport();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = REPORT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnExtractgroup();
	//CStatic reportlabel;
	CListBox listbox1;
	CEdit editbox1;
	afx_msg void OnLbnDblclkList1();
	void ExtractGroupFile(ClassModule *thisModule);
	long Add_NHRU(string S, TStringList *MacroModulesList);
	void AddMacroCode(string S, TStringList * MacroModulesList, TStringList* Memo1, long &MacroPos);
	CStatic static2;
	afx_msg void OnFileSave32791();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	string defaultprojectpath;
};
