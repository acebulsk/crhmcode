#pragma once


// MacroEntryDlg dialog
#include "TStringList.h"



class Module {
public:
	Module() : head(0), tail(0), avail(false), isGroup(false), isStruct(false) {};
	int head;
	int tail;
	bool avail;
	bool isGroup;
	bool isStruct;
	long GrpCnt;
	long StructCnt;
};

class FileDialog
{
public:
	string filepath, filename;

	bool Open(string exten)
	{
		CString extension(exten.c_str());
		CString extension2("*.");
		extension2 = extension2 + extension;

		CString filter1("Files(*.");
		CString filter2(") | *.");
		CString filter3("|All Files (*.*)|*.*||");
		CString filter;
		filter = filter1 + extension + filter2 + extension + filter3;

		CFileDialog fileDlg(TRUE, extension, extension2, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filter);

		if (fileDlg.DoModal() == IDOK)
		{
			CString filepath1 = fileDlg.GetPathName();
			CString filename1 = fileDlg.GetFileName();
			filepath = CT2A(filepath1);
			filename = CT2A(filename1);
			return true;
		}
		return false;
	}

	bool Save(string exten)
	{
		CString extension(exten.c_str());
		CString extension2("*.");
		extension2 = extension2 + extension;

		CString filter1("Files(*.");
		CString filter2(") | *.");
		CString filter3("|All Files (*.*)|*.*||");
		CString filter;
		filter = filter1 + extension + filter2 + extension + filter3;

		CFileDialog fileDlg(FALSE, extension, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter);

		if (fileDlg.DoModal() == IDOK)
		{
			CString filepath1 = fileDlg.GetPathName();
			CString filename1 = fileDlg.GetFileName();
			filepath = CT2A(filepath1);
			filename = CT2A(filename1);
			return true;
		}
		return false;
	}
};



class MacroEntryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MacroEntryDlg)

public:
	MacroEntryDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MacroEntryDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = MacroEntry_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit editbox;

	TStringList *ProjectFile; // hold project file
	TStringList *ModuleList;  // list of modules in group
	TStringList *MacroList;   // macros in project file
	TStringList *DefinedList; // macros already defined
	TStringList *ParaList;    // defined parameters
	TStringList *AKAList;     // AKA defines
	

	Module GlobalModule;


	void FormActivate();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	void OpenClick();
	afx_msg void OnBnClickedButton3();
	void CreateGroupClick();
	FileDialog * openfile;
	FileDialog * savefile;
	FileDialog * macrofile;
	void AddGroup(int ii);
	void AddSupport(Module* ThisModule);
	void AddStringsToEditBox(TStringList * str);
	void AddStringsToEditBox(string tstr);
	TStringList * GetLinesFromEditBox();
	TStringList * GetSelectedLinesFromEditBox();
	void SaveChangesClick();
	afx_msg void OnFileCreategroup();
	void DoSave();
	void SaveClick();
	void SaveAsClick();
	afx_msg void OnFileSaveas32816();
	afx_msg void OnFileOpen32814();
	void DoLoad(string filepath);
	afx_msg void OnBnClickedButton2();
};
