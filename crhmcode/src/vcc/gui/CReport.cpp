// CReport.cpp : implementation file
//

#include "stdafx.h"
#include "CRHM_GUI.h"
#include "CReport.h"
#include "afxdialogex.h"
#include "MacroEntryDlg.h"
#include "../../core/CRHMmain/CRHMmain.h"


// CReport dialog

IMPLEMENT_DYNAMIC(CReport, CDialog)

CReport::CReport(CWnd* pParent /*=nullptr*/)
	: CDialog(REPORT_DLG, pParent)
{

}

CReport::~CReport()
{
}

void CReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, reportlabel, reportlabel);
	DDX_Control(pDX, IDC_LIST1, listbox1);
	DDX_Control(pDX, IDC_EDIT1, editbox1);
	DDX_Control(pDX, IDC_STATIC2, static2);
}


BEGIN_MESSAGE_MAP(CReport, CDialog)
	ON_COMMAND(ID_EXTRACTGROUP, &CReport::OnExtractgroup)
	ON_LBN_DBLCLK(IDC_LIST1, &CReport::OnLbnDblclkList1)
	ON_COMMAND(ID_FILE_SAVE32791, &CReport::OnFileSave32791)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CReport message handlers


void CReport::OnExtractgroup()
{
	// TODO: Add your command handler code here



	ClassModule *thisMod;

	listbox1.ResetContent();
	editbox1.SetWindowText(_T(""));
	//ListBox1->Clear();
	//Memo1->Lines->Clear();

	static2.SetWindowTextW(_T("Macros Used"));
	//SetWindowText(reportlabel, _T("ExtractGroup"));	
	//Label1->Tag = 4;

	for (
		std::list<std::pair<std::string, ClassModule*>>::iterator modIt = Global::OurModulesList->begin();
		modIt != Global::OurModulesList->end(); 
		modIt++
		) 
	{
		string S = modIt->first;
		std::map<std::string, ClassModule*>::iterator pos = Global::AllModulesList->find(S);
		thisMod = pos->second;
		if (thisMod->isGroup)
		{
			CString cstr(S.c_str());
			listbox1.AddString(cstr);
			//ListBox1->Add(S, (TObject*)thisMod);
		}
	} // for
}


void CReport::OnLbnDblclkList1()
{
	// TODO: Add your control notification handler code here

	//getting the group name.
	CString cstr;
	int index = listbox1.GetCurSel();
	listbox1.GetText(index, cstr);
	CT2A str(cstr);
	string groupname = str;

	//getting the group object and class module.
	ClassModule *thisMod;
	std::map<std::string, ClassModule*>::iterator pos = Global::AllModulesList->find(groupname);
	thisMod = pos->second;

	ExtractGroupFile(thisMod);

}

void CReport::ExtractGroupFile(ClassModule *thisModule) {

	CString newline("\r\n");
	CString cstr("");
	//editbox.SetWindowText(cstr);

	ClassMacro *thisMacro;
	string S, SS;
	//long Variation; varible is unreferenced commenting out for now - jhs507
	MapPar::iterator itPar;
	ClassPar *thisPar;

	if (thisModule->isGroup)
		thisMacro = dynamic_cast<ClassMacro *> (thisModule);
	else
		return;

	editbox1.SetWindowTextW(_T(""));
	
	std::vector<std::string> * stringlist;
	stringlist = new std::vector<std::string>();
	
	
	CRHMmain * test = CRHMmain::getInstance();
	
	S = thisMacro->Name.c_str();
	

	//S = "*** extracted group: '" + S + "' from '" + Main->OpenDialogPrj->FileName + "' ***";
	//S = "*** extracted group: '" + S + "' from '" + "' ***";
	stringlist->push_back("*** extracted group: '" + S + "' from '" + test->OpenProjectPath + "' ***");
	
	stringlist->push_back("######");
	stringlist->push_back("Dimensions:");
	stringlist->push_back("######");
	stringlist->push_back(string("nhru " + Common::longtoStr(Add_NHRU(S, Global::MacroModulesList))));
	stringlist->push_back(string("nlay " + Common::longtoStr(Global::nlay)));
	stringlist->push_back(string("nobs " + Common::longtoStr(1)));
	stringlist->push_back("######");

	stringlist->push_back("Macros:");
	stringlist->push_back("######");

	long MacroPos = stringlist->size();
	stringlist->push_back("######");

	stringlist->push_back("Modules:");
	stringlist->push_back("######");

	list<ModulePtr> ::iterator iterM;
	iterM = ((ClassMacro *)thisModule)->Modules.begin();
	while (iterM != ((ClassMacro *)thisModule)->Modules.end()) {
		std::weak_ptr<ClassModule> MP((*iterM));
		S = (*iterM)->NameRoot.c_str();

		if ((*iterM)->DLLName == "Macro")
		{
			AddMacroCode(S, Global::MacroModulesList, stringlist, MacroPos);
		}
			

		if ((*iterM)->variation > 0) {
			string AA("#0 ");
			AA[1] += (char) (log((*iterM)->variation) / log(2) + 1);
			S = S + AA.c_str();
		}
		else
			S = S + " ";

		S = S + (*iterM)->DLLName + " ";
		S = S + (*iterM)->Version;
		stringlist->push_back(S);
		++iterM;
	} // while

	stringlist->push_back("######");

	//Main->RemoveSharedParams();

	stringlist->push_back("Parameters:");
	stringlist->push_back("######");

	S = thisMacro->Name.c_str();

	for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++) {
		thisPar = (*itPar).second;
		if (S == thisPar->module.c_str()) {
			if (thisPar->param == "HRU_group")
				continue;

			string S = string("Shared " + string(thisPar->param.c_str()));

			if (thisPar->varType != TVar::Txt)
				S += "\t<\t" + FloatToStrF(thisPar->minVal, TFloatFormat::ffGeneral, 4, 0) + "\t" + FloatToStrF(thisPar->maxVal, TFloatFormat::ffGeneral, 4, 0) + "\t>";

			stringlist->push_back(S);

			for (size_t jj = 0;  jj < (size_t) thisPar->lay; jj++) {
				S = "";
				for (int ii = 0; ii < thisPar->dim; ii++) {
					if (thisPar->varType == TVar::Float)
						S = S + FloatToStrF(thisPar->layvalues[jj][ii], TFloatFormat::ffGeneral, 4, 0) + "\t";
					else if (thisPar->varType == TVar::Int)
						S = S + FloatToStrF(thisPar->ilayvalues[jj][ii], TFloatFormat::ffFixed, 8, 0) + "\t";
					else if (thisPar->varType == TVar::Txt)
						if (thisPar->Strings->size() > (size_t) ii)
							S = S + "'" + thisPar->Strings->operator[](ii) + "'\t";
						else
							S = "''\t"; // handle null string

					if (ii % 16 == 15) {
						stringlist->push_back(S);
						S = "";
					}
				} // for dim
				if (S.length() > 0) { stringlist->push_back(S); S = ""; }
			} // for layers
			if (S.length() > 0) stringlist->push_back(S);
		}
	} // for MapPars

	stringlist->push_back("######");

	CString cstrtemp, text;
	for (size_t i = 0; i < stringlist->size(); i++)
	{
		string strtemp = stringlist->operator[](i);
		cstrtemp = strtemp.c_str();
		
		text += newline + cstrtemp;
	}

	editbox1.SetWindowTextW(text);

	//Main->SqueezeParams(Sender);  // converts identical parameters to shared parameters
}

long CReport::Add_NHRU(string S, std::vector<std::string> * MacroModulesList) {

	for (size_t ii = 0; ii < MacroModulesList->size(); ++ii) {
		int found = MacroModulesList->operator[](ii).find(S);
		if (found >= 0) {
			string Trim = Common::trimleft(MacroModulesList->operator[](++ii));
			long len = Trim.length();
			if (len < 11)
				return Global::nhru;
			else {
				string temp = Trim.substr(10, len - 10);
				CString ctemp(temp.c_str());
				long n = StrToInt(ctemp);
				if (n <= 0)
					return Global::nhru;
				else
					return n;
			}
		}
	}
	return 0; //added fall through case if the module is not found - jhs507
}

void CReport::AddMacroCode(string S, std::vector<std::string> * MacroModulesList, std::vector<std::string> * Memo1, long &MacroPos) {

	int endpos=0;

	for (size_t ii = 0; ii < MacroModulesList->size(); ++ii) {
		int found = MacroModulesList->operator[](ii).find(S);
		if (found >= 0) {
			Memo1->push_back("'" + MacroModulesList->operator[](ii) + "'");
			MacroPos++;
			do {
				++ii;
				Memo1->push_back("'" + MacroModulesList->operator[](ii) + "'");
				MacroPos++;

				endpos = MacroModulesList->operator[](ii).find("end");
			} while (!(endpos >= 0 && MacroModulesList->operator[](ii).length() == 3) && ii < MacroModulesList->size() - 1);
			break;
		}
	}
}



void CReport::OnFileSave32791()
{
	// TODO: Add your command handler code here

	//if (!SaveDialog1->FileName.IsEmpty())
	//	Memo1->Lines->SaveToFile(SaveDialog1->FileName);
	//else SaveAs1Click(Sender);

	CString cstr;
	editbox1.GetWindowText(cstr);
	CT2A str(cstr);
	std::vector<std::string> * strings = new std::vector<std::string>();
	string temp = str;	

	int l = temp.length();
	for (int i = 0; i < l; i++)
	{
		if (i < l - 1)
		{
			if (temp[i] == '\r') { temp[i] = ' '; }
		}
	}

	strings->push_back(temp);


	FileDialog * filedialog;
	filedialog = new FileDialog();
	if (filedialog->Save("rpt") == true)
	{
		ofstream file;
		file.open(filedialog->filepath.c_str());

		for (size_t it = 0; it < strings->size(); it++)
		{
			file << strings->operator[](it).c_str() << endl;
		}

		file.close();

		MessageBox(_T("Group Saved"));
	}
}


void CReport::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
	OnExtractgroup();
}
