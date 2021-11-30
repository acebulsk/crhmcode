#include "CExport.h"

IMPLEMENT_DYNAMIC(CExport, CDialog)

CExport::CExport(CWnd* pParent /*=nullptr*/)
	: CDialog(EXPORT_DLG, pParent)
{

}

CExport::~CExport()
{

}

void CExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EXPORT_CHOICES_LIST_BOX, choicesListBox);
	DDX_Control(pDX, ID_EXPORT_SELECTED_LIST_BOX, selectedListBox);
	DDX_Control(pDX, ID_EXPORT_PREVIEW_MORE, previewMoreButton);
	DDX_Control(pDX, ID_EXPORT_FORMAT_BTN, formatToggle);
	DDX_Control(pDX, ID_EXPORT_PREVIEW_EDIT_BOX, previewEditBox);
}


BEGIN_MESSAGE_MAP(CExport, CDialog)
	ON_LBN_SELCHANGE(ID_EXPORT_CHOICES_LIST_BOX, &CExport::OnChoicesSelectionChange)
END_MESSAGE_MAP()


BOOL CExport::OnInitDialog()
{
	CDialog::OnInitDialog();

	choicesListBox.ResetContent();
	selectedListBox.ResetContent();

	std::list<std::pair<std::string, ClassVar*>>* sel_variables = CRHMmain::getInstance()->getSelectedVariables();

	for (
		std::list<std::pair<std::string, ClassVar*>>::iterator it = sel_variables->begin();
		it != sel_variables->end();
		it++
		)
	{
		CString text = CString(it->first.c_str());
		choicesListBox.AddString(text);
	}

	return true;
}

void CExport::OnChoicesSelectionChange()
{
	int selectedCount = choicesListBox.GetSelCount();
	int * selectedIndicies = new int[selectedCount];
	choicesListBox.GetSelItems(selectedCount, selectedIndicies);

	for (int i = 0; i < selectedCount; i++)
	{
		CString selectedText;
		choicesListBox.GetText(selectedIndicies[i], selectedText);
		CT2CA pszConvertedAnsiString(selectedText); //Intermediary to convert CString to std::string
		std::string selectedString(pszConvertedAnsiString);

		int found = selectedListBox.FindString(-1, selectedText);
		if (found == LB_ERR)
		{
			selectedListBox.AddString(selectedText);
		}

	}

	delete[] selectedIndicies;
}