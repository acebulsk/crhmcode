// MacroEntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CRHM_GUI.h"
#include "MacroEntryDlg.h"
#include "afxdialogex.h"
#include "GlobalDll.h"


// MacroEntryDlg dialog

IMPLEMENT_DYNAMIC(MacroEntryDlg, CDialogEx)

MacroEntryDlg::MacroEntryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(MacroEntry_DLG, pParent)
{

}

MacroEntryDlg::~MacroEntryDlg()
{
}

void MacroEntryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editbox);
}


BEGIN_MESSAGE_MAP(MacroEntryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MacroEntryDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &MacroEntryDlg::OnBnClickedButton3)
	ON_COMMAND(ID_FILE_CREATEGROUP, &MacroEntryDlg::OnFileCreategroup)
	ON_COMMAND(ID_FILE_SAVEAS32816, &MacroEntryDlg::OnFileSaveas32816)
	ON_COMMAND(ID_FILE_OPEN32814, &MacroEntryDlg::OnFileOpen32814)
	ON_BN_CLICKED(IDC_BUTTON2, &MacroEntryDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// MacroEntryDlg message handlers

void MacroEntryDlg::FormActivate()
{
	CString newline("\r\n");
	CString cstr("");
	editbox.SetWindowText(cstr);	

	for (int ii = 0; ii < Global::MacroModulesList->Count; ++ii)
	{
		CString cstr1(Global::MacroModulesList->Strings[ii].c_str());
		cstr += cstr1 + newline;
	}
	editbox.SetWindowText(cstr);

	ParaList = NULL;
	AKAList = NULL;

	GlobalModule.GrpCnt = 0;
	GlobalModule.StructCnt = 0;


}





void MacroEntryDlg::AddStringsToEditBox(TStringList * tstr)
{
	CString cstr1;
	editbox.GetWindowText(cstr1);
	CString newline("\r\n");

	CString cstr2, cstr;
	for (int i = 0; i < tstr->Count; i++)
	{
		cstr = tstr->Strings[i].c_str();
		if (tstr->Strings[i].length() != 0)
		{
			cstr2 += cstr + newline;
		}
	}

	CString finalcstr;


	//Getting rid of extra new lines in the macro box. Manishankar

	if (cstr1.GetLength() > 0)
	{
		finalcstr = cstr1 + newline + cstr2;
	}
	else
	{
		finalcstr = cstr2;
	}
	
	editbox.SetWindowTextW(finalcstr);
}

void MacroEntryDlg::AddStringsToEditBox(string tstr)
{
	CString cstr1;
	editbox.GetWindowText(cstr1);
	CString newline("\r\n");

	CString cstr2 (tstr.c_str());
	CString finalcstr;


	//Getting rid of extra new lines in the macro box. Manishankar

	if (cstr1.GetLength() > 0)
	{
		finalcstr = cstr1 + newline + cstr2;
	}
	else
	{
		finalcstr = cstr2;
	}

	//finalcstr = cstr1 + newline + cstr2;
	editbox.SetWindowTextW(finalcstr);
}

TStringList * MacroEntryDlg::GetLinesFromEditBox()
{
	TStringList * tstring = new TStringList ();

	CString cstr1;
	editbox.GetWindowText(cstr1);
	string str = CT2A(cstr1);

	int l = str.length();
	string temp = "";

	for (int i = 0; i < l; i++)
	{
		if (str[i] != '\r' && str[i] != '\n') { temp += str[i]; }
		else 
		{  
			if (temp.length() > 0) 
			{ 
				tstring->AddObject(temp, 0); temp = ""; 
			}
		}
	}
	if (temp.length() > 0) { tstring->AddObject(temp, 0); }

	return tstring;
}

TStringList * MacroEntryDlg::GetSelectedLinesFromEditBox()
{
	TStringList * tstring = new TStringList();

	CString cstr1;
	editbox.GetWindowText(cstr1);
	//string str = CT2A(cstr1);

	int start, end;
	CString cstr2;
	editbox.GetSel(start, end);
	cstr2 = cstr1.Mid(start, end - start);
	string str = CT2A(cstr2);


	int l = str.length();
	string temp = "";

	for (int i = 0; i < l; i++)
	{
		if (str[i] != '\r' && str[i] != '\n') { temp += str[i]; }
		else
		{
			if (temp.length() > 0)
			{
				tstring->AddObject(temp, 0); temp = "";
			}
		}
	}
	if (temp.length() > 0) { tstring->AddObject(temp, 0); }

	return tstring;
}


void MacroEntryDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	SaveChangesClick();
	
}


BOOL MacroEntryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	FormActivate();




	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void MacroEntryDlg::OpenClick()
{	
}

void MacroEntryDlg::DoSave()
{
	TStringList * Lines = new TStringList();
	Lines = GetLinesFromEditBox();
	DWORD dwSel = editbox.GetSel();
	if (dwSel == 0)
	{
		Lines->SaveToFile(macrofile->filepath);
	}
	else
	{
		Lines = GetSelectedLinesFromEditBox();
		Lines->SaveToFile(macrofile->filepath);
	}


	//if (Memo->SelLength == 0)
	//	Memo->Lines->SaveToFile(SaveDialogMcr->FileName);
	//else {
	//	MemoFile->Text = Memo->SelText;
	//	MemoFile->Lines->SaveToFile(SaveDialogMcr->FileName);
	//}
}
//---------------------------------------------------------------------------

void MacroEntryDlg::SaveClick()
{
	if (macrofile->filepath.length() > 0)
		DoSave();
	else SaveAsClick();
}
//---------------------------------------------------------------------------

void MacroEntryDlg::SaveAsClick()
{
	macrofile = new FileDialog();
	bool opened = macrofile->Save("mcr");
	if (opened) { DoSave(); }


	//SaveDialogMcr->Title = "Save As";

	//SaveDialogMcr->DefaultExt = "mcr";
	//SaveDialogMcr->Filter = "Save Macro Files (*.mcr)|*.mcr";
	//if (SaveDialogMcr->Execute()) {
	//	SaveDialogMcr->InitialDir = ExtractFilePath(SaveDialogMcr->FileName);
	//	if (SaveDialogMcr->InitialDir.IsEmpty())
	//		SaveDialogMcr->InitialDir = GetCurrentDir();

	//	DoSave(Sender);
	//}
}


void MacroEntryDlg::CreateGroupClick()
{
	string Txt, S, MacroName, GrpName;
	int Indx;

	//FileDialog filedialog;
	openfile = new FileDialog();
	bool opened = openfile->Open("prj");

	if (opened == false) { return; }


	MacroName = openfile->filename;
	Indx = MacroName.rfind("\\");

	if (Indx != -1) // handle directories
		MacroName = MacroName.substr(Indx + 1, MacroName.length());

	Indx = MacroName.rfind(".");
	if (Indx != -1) { // handle extensions
		string AA;
		Common::GroupEnding(AA, ++GlobalModule.GrpCnt);
		MacroName = MacroName.substr(0, Indx) + "_Grp" + AA.substr(1, 2);
	}

	if (!isalpha(MacroName[0])) { // must be a proper variable name
		MessageBox(_T("Alpha characters are upper-/lowercase characters from A through Z. Project file name must begin with an alpha character."), MB_OK);
		return;
	}
	GrpName = MacroName;
	if (GlobalModule.GrpCnt > 1)
		GlobalModule.GrpCnt = 1;


	ProjectFile = new TStringList; // hold project file
	ModuleList = new TStringList;  // list of modules in group
	MacroList = new TStringList;   // macros in project file
	DefinedList = new TStringList; // macros already defined

	if (!ParaList) 
	{
		ParaList = new TStringList; // macros already defined
		ParaList->Add("Parameters for created Group Macro");
		ParaList->Add("#####");
	}

	if (!AKAList) { AKAList = new TStringList; } // macros already defined

	ProjectFile->LoadFromFile(openfile->filepath); // load project

	int ThisEnd = 0;
	Module *ThisModule;

	TStringList * Lines = new TStringList();
	Lines = GetLinesFromEditBox();

	while (ThisEnd < Lines->Count)
	{
		if (Lines->Strings[ThisEnd].length() == 0)
			continue;
		while (ThisEnd < Lines->Count && (Txt = Common::trimleft(Lines->Strings[ThisEnd]),
			Txt[0] == '/'))
			++ThisEnd;
		if (Indx = Txt.find(" "))
			Txt = Txt.substr(0, Indx);
		ThisModule = new Module;
		ThisModule->head = ThisEnd;
		do
			S = Common::trim(Lines->Strings[++ThisEnd]);
		while (S[0] == '/');
		if (S.find("declgroup"))
		{
			++ThisModule->GrpCnt;
			ThisModule->isGroup = true;
		}
		if (S.find("declstruct"))
		{
			++ThisModule->StructCnt;
			ThisModule->isStruct = true;
		}
		while (ThisEnd < Lines->Count && !(S = Common::trim(Lines->Strings[ThisEnd]),
			S.substr(0, 3) == "end" && (S.length() == 3 || S[3] == ' ' || S[3] == '/')))
			++ThisEnd;
		ThisModule->tail = ThisEnd++;
		DefinedList->AddObject(Txt, (TObject*)ThisModule);
	}

	for (int ii = 0; ii < ProjectFile->Count; ++ii)
	{
		Txt = ProjectFile->Strings[ii];
		if (Txt == "Dimensions:")
		{
			CString cstr1(ProjectFile->Strings[ii + 2].substr(4, 10).c_str());
			Global::nhru = StrToInt(cstr1);

			CString cstr2(ProjectFile->Strings[ii + 3].substr(4, 10).c_str());
			Global::nlay = StrToInt(cstr2);
		}
		if (Txt == "Parameters:")
		{
			++ii;
			++ii;
			while (ProjectFile->Strings[ii][0] != '#')
			{
				if (ProjectFile->Strings[ii][0] == '\'' || ProjectFile->Strings[ii][0] == '-' || iswdigit(ProjectFile->Strings[ii][0]))
					ParaList->Add(ProjectFile->Strings[ii]);
				else
				{
					Indx = ProjectFile->Strings[ii].find(" ");
					S = ProjectFile->Strings[ii].substr(Indx + 1, ProjectFile->Strings[ii].length() - Indx-1);
					ParaList->Add(GrpName + " " + S);
				}
				++ii;
			}
			continue;
		}
		if (Txt == "Macros:")
		{
			++ii;
			++ii;
			ThisModule = NULL;
			while (ProjectFile->Strings[ii][0] != '#')
			{

				while (ii < ProjectFile->Count && (S = Common::trimleft(ProjectFile->Strings[ii]), S[0] == '/'))
					++ii;
				S = S.substr(0, S.length() - 2);
				if (!ThisModule)
				{
					if (Indx = S.find(" "))
						S = S.substr(0, Indx);
					ThisModule = new Module;
					ThisModule->head = MacroList->Count;
					MacroList->Add(S);
				}
				else
				{
					if (S.find("declgroup"))
					{
						++ThisModule->GrpCnt;
						ThisModule->isGroup = true;
					}
					if (S.find("declstruct"))
					{
						++ThisModule->StructCnt;
						ThisModule->isStruct = true;
					}
					MacroList->Add(S);
					if (S.substr(0, 3) == "end" && (S.length() == 3 || S[3] == ' ' || S[3] == '/'))
					{
						ThisModule->tail = MacroList->Count;
						MacroList->Objects[ThisModule->head] = (TObject*)(ThisModule);
						ThisModule = NULL;
					}
				}
				++ii;
			}
			continue;
		}
	}
	for (int ii = 0; ii < ProjectFile->Count; ++ii)
	{
		Txt = ProjectFile->Strings[ii];
		if (Txt == "AKAs:")
		{
			++ii;
			++ii;
			while (ProjectFile->Strings[ii][0] != '#')
			{
				string S = Common::trim(ProjectFile->Strings[ii]);
				int Indx = S.find(" ");
				string type = S.substr(0, Indx);
				S = S.substr(Indx + 1, S.length() - Indx-1);
				Indx = S.find(" ");
				string module = S.substr(0, Indx);
				S = S.substr(Indx + 1, S.length() - Indx-1);
				Indx = S.find(" ");
				string name = S.substr(0, Indx);
				S = S.substr(Indx + 1, S.length() - Indx-1);
				string alias;
				Indx = S.find(" ");
				if (Indx == -1)
				{
					alias = S;
					ParaList->Add(type + " " + GrpName + " " + name + " " + alias);
				}
				else
				{
					alias = S.substr(0, Indx);
					string source = S.substr(Indx + 1, S.length() - Indx-1);
					if (MacroList->IndexOf(source) > -1)
						AKAList->Add(type + " " + GrpName + " " + name + " " + alias + " " + source);
					else
						AKAList->Add(type + " " + GrpName + " " + name + " " + alias + " " + GrpName);
				}
				++ii;
			}
		}
		if (Txt == "Modules:")
		{
			++ii;
			++ii;
			while (DefinedList->IndexOf(S) > -1)
			{
				++S[S.length()-1];
			}
			ModuleList->Add(GrpName);
			ModuleList->Add("declgroup " + to_string(Global::nhru));
			while (ProjectFile->Strings[ii][0] != '#')
			{
				S = Common::trim(ProjectFile->Strings[ii]);
				if (S.find("+") > -1)
				{
					++ii;
					continue;
				}
				if (S.find(" "))
					S = S.substr(0, S.find(" "));
				ModuleList->Add(S);
				++ii;
			}
			ModuleList->Add("command");
			ModuleList->Add("end");
			break;
		}
	}
	ProjectFile->Clear();
	int EndList = ModuleList->Count - 2;
	for (int ii = 2; ii < EndList; ++ii)
	{
		AddGroup(ii);
	}
	
	//Memo->Lines->AddStrings(ModuleList);
	AddStringsToEditBox(ModuleList);

	delete ProjectFile;
	delete ModuleList;
	for (int ii = 0; ii < MacroList->Count; ++ii)
		delete (Module*)MacroList->Objects[ii];
	delete MacroList;
	for (int ii = 0; ii < DefinedList->Count; ++ii)
		delete (Module*)DefinedList->Objects[ii];
	delete DefinedList;
}

void MacroEntryDlg::AddGroup(int ii)
{
	int Indx;
	if (DefinedList->IndexOf(ModuleList->Strings[ii]) == -1)
	{
		if (Indx = MacroList->IndexOf(ModuleList->Strings[ii]), Indx > -1)
		{
			Module* ThisModule = (Module*)MacroList->Objects[Indx];
			AddSupport(ThisModule);
			for (int jj = ThisModule->head; jj < ThisModule->tail; ++jj)
			{
				//Memo->Lines->Add(MacroList->Strings[jj]);
				AddStringsToEditBox(MacroList->Strings[jj]);
			}

			ThisModule->avail = true;
		}
	}
}

void MacroEntryDlg::AddSupport(Module* ThisModule)
{
	int Indx;
	for (int ii = ThisModule->head + 2; ii < ThisModule->tail - 2; ++ii)
	{
		if (DefinedList->IndexOf(MacroList->Strings[ii]) > -1)
		{			
			return;
		}
		if (Indx = MacroList->IndexOf(MacroList->Strings[ii]), Indx > -1 && MacroList->Objects[Indx])
		{
			Module* ThisModule = (Module*)MacroList->Objects[Indx];
			if (ThisModule->avail)
				continue;
			if (ThisModule->isGroup || ThisModule->isStruct)
			{
				AddSupport(ThisModule);
				ThisModule->avail = true;
			}
			for (int jj = Indx; jj < ThisModule->tail; ++jj)
			{
				//Memo->Lines->Add(MacroList->Strings[jj]);
				AddStringsToEditBox(MacroList->Strings[jj]);
			}
			ThisModule->avail = true;
		}
	}
}


void MacroEntryDlg::SaveChangesClick()
{	
	TStringList * Lines = new TStringList();
	Lines = GetLinesFromEditBox();


	Global::MacroModulesList->Clear();

	for (int ii = 0; ii < Lines->Count; ++ii)
	{
		string S;
		if (Lines->Strings[ii].length() == 0)
			S = " ";
		else
			S = Common::trimright(Lines->Strings[ii]);
		//Lines->Strings[ii] = S;
		Global::MacroModulesList->Add(S);
	}
	//Memo->SelStart = 0;
	//Memo->SetFocus();
	if (ParaList)
	{
		ParaList->Add("#####");
		FileDialog *saveparameter = new FileDialog();
		bool opened = saveparameter->Save("par");

		if (opened == true)
		{
			ParaList->SaveToFile(saveparameter->filepath);
			delete ParaList;
			ParaList = NULL;
		}

		
		//SaveDialogPar->Filter = "Parameter Files (*.par)|*.par";
		//SaveDialogPar->DefaultExt = "par";
		//SaveDialogPar->Title = "Save Original Parameters As (Load this parameter file after Building the new project to keep the parameters from the cloned projects)";
		//SaveDialogPar->InitialDir = GetCurrentDir();
		//SaveDialogPar->FileName = "CreateGroup.par";
		//if (SaveDialogPar->Execute())
		//{
		//	ParaList->SaveToFile(SaveDialogPar->FileName);
		//	delete ParaList;
		//	ParaList = NULL;
		//}
	}
	if (AKAList && AKAList->Count)
	{
		string filepath = "CreateGroup.aka";
		AKAList->SaveToFile(filepath);
		delete AKAList;
		AKAList = NULL;
	}
	//ModalResult = mrOk;
	this->OnOK();
}

void MacroEntryDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CreateGroupClick();
	GetLinesFromEditBox();
}




void MacroEntryDlg::OnFileCreategroup()
{
	// TODO: Add your command handler code here

	CreateGroupClick();
}


void MacroEntryDlg::OnFileSaveas32816()
{
	// TODO: Add your command handler code here

	SaveAsClick();

}


void MacroEntryDlg::OnFileOpen32814()
{
	// TODO: Add your command handler code here

	openfile = new FileDialog();
	bool opened = openfile->Open("mcr");
	
	if (!opened) { return; }
	
	DoLoad(openfile->filepath);

	/*
	OpenDialogMcr->Filter = "Macro Files (*.mcr)|*.mcr";
	OpenDialogMcr->DefaultExt = "mcr";
	OpenDialogMcr->Title = "Open Macro File";
	if (OpenDialogMcr->Execute()) {

		OpenDialogMcr->InitialDir = ExtractFilePath(OpenDialogMcr->FileName);
		if (OpenDialogMcr->InitialDir.IsEmpty())
			OpenDialogMcr->InitialDir = GetCurrentDir();

		SaveDialogMcr->InitialDir = OpenDialogMcr->InitialDir;

		DoLoad(Sender);
	}
	*/

}

void MacroEntryDlg::DoLoad(string filepath)
{
	TStringList * slist = new TStringList();
	slist->LoadFromFile(filepath);


	editbox.SetWindowText(_T(""));
	AddStringsToEditBox(slist);

	/*
	MemoFile->Clear();
	MemoFile->Lines->LoadFromFile(OpenDialogMcr->FileName);
	MemoFile->SelectAll();
	Memo->SelText = MemoFile->Text;
	*/
}


void MacroEntryDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	editbox.SetWindowText(_T(""));


	GlobalModule.GrpCnt = 0;
	GlobalModule.StructCnt = 0;

	if (ParaList) {
		delete ParaList;
		ParaList = NULL;
	}

	if (AKAList) {
		delete AKAList;
		AKAList = NULL;
	}


	Global::MacroModulesList->Clear();
	int c = Global::AllModulesList->size();
	Global::AllModulesList->erase(Global::AllModulesList->rbegin()->first);

	//ModalResult = mrCancel;
	this->OnCancel();
}
