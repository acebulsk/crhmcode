#pragma once

#include "stdafx.h"
#include "afxdialogex.h"
#include <string>
#include <list>

#include "CRHM_GUI.h"
#include "../../core/CRHMmain/CRHMmain.h"
#include "../../core/ClassCRHM/ClassVar.h"

// CExport dialog

class CExport : public CDialog
{
	DECLARE_DYNAMIC(CExport)

public:
	CExport(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CExport();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = EXPORT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CListBox choicesListBox;
	CListBox selectedListBox;
	CButton previewMoreButton;
	CButton formatToggle;
	CEdit previewEditBox;

	BOOL OnInitDialog();
};
