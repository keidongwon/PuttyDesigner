#include "stdafx.h"
#include "PuttyDesigner.h"
#include "PuttyDesignerDoc.h"
#include "PuttyDesignerView.h"
#include "util.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CPuttyDesignerView, CFormView)

BEGIN_MESSAGE_MAP(CPuttyDesignerView, CFormView)
	ON_BN_CLICKED(IDC_RADIO_SELECTALL, &CPuttyDesignerView::OnBnClickedRadioSelectall)
	ON_BN_CLICKED(IDC_RADIO_SELECTONE, &CPuttyDesignerView::OnBnClickedRadioSelectone)
	ON_COMMAND(ID_MANAGE_BACKUP, &CPuttyDesignerView::OnManageBackup)
	ON_COMMAND(ID_MANAGE_RESTORE, &CPuttyDesignerView::OnManageRestore)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, &CPuttyDesignerView::OnBnClickedButtonDefault)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CPuttyDesignerView::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CPuttyDesignerView::OnBnClickedButtonClose)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SESSION, &CPuttyDesignerView::OnNMClickListSession)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SESSION, &CPuttyDesignerView::OnNMDblclkListSession)
	ON_CBN_SELCHANGE(IDC_COMBO_FONTLIST, &CPuttyDesignerView::OnCbnSelchangeComboFontlist)
	ON_CBN_SELCHANGE(IDC_COMBO_CHARSET, &CPuttyDesignerView::OnCbnSelchangeComboCharset)
	ON_CBN_SELCHANGE(IDC_COMBO_FONTSIZE, &CPuttyDesignerView::OnCbnSelchangeComboFontsize)
	ON_EN_CHANGE(IDC_EDIT_FCR_R, &CPuttyDesignerView::OnEnChangeEditFcrR)
	ON_EN_CHANGE(IDC_EDIT_FCR_G, &CPuttyDesignerView::OnEnChangeEditFcrG)
	ON_EN_CHANGE(IDC_EDIT_FCR_B, &CPuttyDesignerView::OnEnChangeEditFcrB)
	ON_EN_CHANGE(IDC_EDIT_FCG_R, &CPuttyDesignerView::OnEnChangeEditFcgR)
	ON_EN_CHANGE(IDC_EDIT_FCG_G, &CPuttyDesignerView::OnEnChangeEditFcgG)
	ON_EN_CHANGE(IDC_EDIT_FCG_B, &CPuttyDesignerView::OnEnChangeEditFcgB)
	ON_EN_CHANGE(IDC_EDIT_FCB_R, &CPuttyDesignerView::OnEnChangeEditFcbR)
	ON_EN_CHANGE(IDC_EDIT_FCB_G, &CPuttyDesignerView::OnEnChangeEditFcbG)
	ON_EN_CHANGE(IDC_EDIT_FCB_B, &CPuttyDesignerView::OnEnChangeEditFcbB)
	ON_EN_CHANGE(IDC_EDIT_FCRB_R, &CPuttyDesignerView::OnEnChangeEditFcrbR)
	ON_EN_CHANGE(IDC_EDIT_FCRB_G, &CPuttyDesignerView::OnEnChangeEditFcrbG)
	ON_EN_CHANGE(IDC_EDIT_FCRB_B, &CPuttyDesignerView::OnEnChangeEditFcrbB)
	ON_EN_CHANGE(IDC_EDIT_FCGB_R, &CPuttyDesignerView::OnEnChangeEditFcgbR)
	ON_EN_CHANGE(IDC_EDIT_FCGB_G, &CPuttyDesignerView::OnEnChangeEditFcgbG)
	ON_EN_CHANGE(IDC_EDIT_FCGB_B, &CPuttyDesignerView::OnEnChangeEditFcgbB)
	ON_EN_CHANGE(IDC_EDIT_FCBB_R, &CPuttyDesignerView::OnEnChangeEditFcbbR)
	ON_EN_CHANGE(IDC_EDIT_FCBB_G, &CPuttyDesignerView::OnEnChangeEditFcbbG)
	ON_EN_CHANGE(IDC_EDIT_FCBB_B, &CPuttyDesignerView::OnEnChangeEditFcbbB)
END_MESSAGE_MAP()

static BOOL CALLBACK EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC /*lptm*/, DWORD dwType, LPARAM lpData)
{
	CPuttyDesignerView* pobj = (CPuttyDesignerView*)lpData;
	pobj->comboFontList.AddString(lplf->lfFaceName);
	return TRUE;
}

CPuttyDesignerView::CPuttyDesignerView()
	: CFormView(CPuttyDesignerView::IDD)
{
	radioSelectAll = FALSE;
	radioSelectOne = TRUE;
	LoadDefault();
}

CPuttyDesignerView::~CPuttyDesignerView()
{
}

void CPuttyDesignerView::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_LIST_SESSION, listSession);
	DDX_Check(pDX, IDC_RADIO_SELECTALL, radioSelectAll);
	DDX_Check(pDX, IDC_RADIO_SELECTONE, radioSelectOne);
	DDX_Check(pDX, IDC_CHECK_SCREENSIZE, checkScreenSize);
	DDX_Check(pDX, IDC_CHECK_FONTFACE, checkFontFace);
	DDX_Check(pDX, IDC_CHECK_FONTSIZE, checkFontSize);
	DDX_Check(pDX, IDC_CHECK_FCR, checkFontColorRed);
	DDX_Check(pDX, IDC_CHECK_FCG, checkFontColorGreen);
	DDX_Check(pDX, IDC_CHECK_FCB, checkFontColorBlue);
	DDX_Check(pDX, IDC_CHECK_FCRB, checkFontColorRedBold);
	DDX_Check(pDX, IDC_CHECK_FCGB, checkFontColorGreenBold);
	DDX_Check(pDX, IDC_CHECK_FCBB, checkFontColorBlueBold);
	DDX_Check(pDX, IDC_CHECK_CHARSET, checkCharset);
	DDX_Check(pDX, IDC_CHECK_HANGUL, checkHangul);
	DDX_Control(pDX, IDC_COMBO_FONTLIST, comboFontList);
	DDX_Control(pDX, IDC_COMBO_FONTSIZE, comboFontSize);
	DDX_Control(pDX, IDC_COMBO_CHARSET, comboCharset);
	DDX_Control(pDX, IDC_EDIT_CHARSET, editCharset);
	CFormView::DoDataExchange(pDX);
}

BOOL CPuttyDesignerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CPuttyDesignerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
    MoveWindow(0, 0, 1024, 1000, TRUE);

	//listSession.SetView(LV_VIEW_LIST);
	listSession.SetView(LV_VIEW_DETAILS);
	listSession.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	listSession.InsertColumn(0, _T("Saved Session(s)"), 0, 200, 0);
	listSession.InsertColumn(1, _T("Saved Session(s)"), 0, 0, 0);

	LoadSession();
	LoadControlData();
	SetControlData();

	UpdateData(FALSE);
}

void CPuttyDesignerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPuttyDesignerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

#ifdef _DEBUG
void CPuttyDesignerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPuttyDesignerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPuttyDesignerDoc* CPuttyDesignerView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPuttyDesignerDoc)));
	return (CPuttyDesignerDoc*)m_pDocument;
}
#endif 

void CPuttyDesignerView::OnBnClickedRadioSelectall()
{
	radioSelectAll = TRUE;
	radioSelectOne = FALSE;
	UpdateData(TRUE);
}

void CPuttyDesignerView::OnBnClickedRadioSelectone()
{
	radioSelectAll = FALSE;
	radioSelectOne = TRUE;
	UpdateData(TRUE);
}

void CPuttyDesignerView::OnManageBackup()
{
	CFileDialog dlg(FALSE);
	TCHAR szFilter[] = _T("Registry Files (*.reg)\0*.reg\0\0");
	CString selectedFilePath;
	dlg.m_ofn.lpstrFilter = szFilter;
	dlg.m_ofn.Flags |= OFN_NOCHANGEDIR;
	  
	if (dlg.DoModal() == IDOK) 
	{ 
		selectedFilePath = dlg.GetPathName(); 
		TCHAR path[MAX_PATH] = {0,};
		TCHAR parameter[MAX_PATH] = {0,};
		_stprintf(path, _T("c:\\windows\\system32\\regedt32.exe"));
		_stprintf(parameter, _T("/e \"%s\" \"HKEY_CURRENT_USER\\Software\\SimonTatham\""), selectedFilePath);
		ShellExecute(NULL, _T("open"), path, parameter, NULL, SW_SHOWNORMAL); 
	}
}

void CPuttyDesignerView::OnManageRestore()
{
	CFileDialog dlg(TRUE);
	TCHAR szFilter[] = _T("Registry Files (*.reg)\0*.reg\0\0");
	CString selectedFilePath;
	dlg.m_ofn.lpstrFilter = szFilter;
	dlg.m_ofn.Flags |= OFN_NOCHANGEDIR;
	  
	if (dlg.DoModal() == IDOK) 
	{ 
		selectedFilePath = dlg.GetPathName(); 
		TCHAR path[MAX_PATH] = {0,};
		TCHAR parameter[MAX_PATH] = {0,};
		_stprintf(path, _T("c:\\windows\\system32\\regedt32.exe"));
		_stprintf(parameter, _T("/s \"%s\""), selectedFilePath);
		ShellExecute(NULL, _T("open"), path, parameter, NULL, SW_SHOWNORMAL); 
	}
}

void CPuttyDesignerView::LoadDefault()
{
	color_fcr_r = 255;
	color_fcr_g = 85;
	color_fcr_b = 85;
	color_fcg_r = 0;
	color_fcg_g = 187;
	color_fcg_b = 0;
	color_fcb_r = 75;
	color_fcb_g = 135;
	color_fcb_b = 215;
	color_fcrb_r = 255;
	color_fcrb_g = 85;
	color_fcrb_b = 85;
	color_fcgb_r = 85;
	color_fcgb_g = 255;
	color_fcgb_b = 85;
	color_fcbb_r = 75;
	color_fcbb_g = 135;
	color_fcbb_b = 215;

	m_colorBlack = RGB(0,0,0);
	m_colorWhite = RGB(255,255,255);

	checkScreenSize = TRUE;
	checkFontFace = TRUE;
	checkFontSize = TRUE;
	checkFontColorRed = TRUE;
	checkFontColorGreen = TRUE;
	checkFontColorBlue = TRUE;
	checkFontColorRedBold = TRUE;
	checkFontColorGreenBold = TRUE;
	checkFontColorBlueBold = TRUE;
	checkCharset = TRUE;
	checkHangul = TRUE;

	m_strCharset = "UTF-8";
	m_strFont = "돋움체";
	m_FontSize = 10;
	m_sizeHeight = 40;
	m_sizeWidth = 120;
}

void CPuttyDesignerView::LoadSession()
{
	HKEY m_hRegKey;
	LSTATUS status = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\SimonTatham\\PuTTY\\Sessions"), 0, KEY_ALL_ACCESS, &m_hRegKey);
	if (status != ERROR_SUCCESS) 
	{
		RegCloseKey(m_hRegKey);
		return;
	}
	DWORD index = 0;
	DWORD dwSubKeyLength = 0;
	TCHAR szSubKey[1024] = {0,};
	DWORD dwReturn = 0;

	while (dwReturn == ERROR_SUCCESS)
	{
		dwSubKeyLength = 1024;
		dwReturn = RegEnumKeyEx(m_hRegKey, index, szSubKey, &dwSubKeyLength, NULL, NULL, NULL, NULL);

		//::OutputDebugString(Unicode_URLDecode(szSubKey));
		listSession.InsertItem(index, Unicode_URLDecode(szSubKey));
		listSession.SetItemText(index, 1, szSubKey);
		ZeroMemory(szSubKey, 1024);
		if(dwReturn == ERROR_NO_MORE_ITEMS)	break;
		index++;
	}
	RegCloseKey(m_hRegKey);
}


void CPuttyDesignerView::OnPaint()
{
	CPaintDC dc(this);

	CBrush cBrush;
	CRect rect1(275,263,800,313);
	CRect rect2(275,396,800,446);
	
	cBrush.CreateSolidBrush(m_colorBlack);

	CBrush* pOldBrush = dc.SelectObject(&cBrush);
	dc.FillRect(&rect1,&cBrush);
	dc.FillRect(&rect2,&cBrush);
	
	dc.SetBkColor(RGB(0,0,0));

	dc.SelectObject(pOldBrush);
	cBrush.DeleteObject();

	CFont m_cFont;
	if ((m_FontSize >= 7) && (m_FontSize <= 20) )
	{
		int size = -MulDiv(m_FontSize, GetDeviceCaps(dc.m_hDC, LOGPIXELSY), 72);
		m_cFont.CreateFont(size,0,0,0,0,0,0,0,1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, m_strFont);
	}
	else
	{
		int size = -MulDiv(10, GetDeviceCaps(dc.m_hDC, LOGPIXELSY), 72);
		m_cFont.CreateFont(size,0,0,0,0,0,0,0,1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, m_strFont);
	}
	CFont* oldFont = dc.SelectObject(&m_cFont);
	dc.SetBkMode(TRANSPARENT);
	
	dc.SetTextColor(m_colorBlack);
	dc.TextOut(510, 143, _T("[1iljILOo0]"));

	dc.SetTextColor(m_colorRed);
	dc.TextOut(285, 270, _T("한글PuTTY"));

	dc.SetTextColor(m_colorGreen);
	dc.TextOut(475, 270, _T("한글PuTTY"));

	dc.SetTextColor(m_colorBlue);
	dc.TextOut(650, 270, _T("한글PuTTY"));

	m_cFont.DeleteObject();

	if ((m_FontSize >= 7) && (m_FontSize <= 20) )
	{
		int size = -MulDiv(m_FontSize, GetDeviceCaps(dc.m_hDC, LOGPIXELSY), 72);
		m_cFont.CreateFont(size,0,0,0,FW_BOLD,0,0,0,1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, m_strFont);
	}
	else
	{
		int size = -MulDiv(10, GetDeviceCaps(dc.m_hDC, LOGPIXELSY), 72);
		m_cFont.CreateFont(size,0,0,0,FW_BOLD,0,0,0,1, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, m_strFont);
	}
	dc.SelectObject(&m_cFont);

	dc.SetTextColor(m_colorRedBold);
	dc.TextOut(285, 405, _T("한글PuTTY"));

	dc.SetTextColor(m_colorGreenBold);
	dc.TextOut(475, 405, _T("한글PuTTY"));

	dc.SetTextColor(m_colorBlueBold);
	dc.TextOut(650, 405, _T("한글PuTTY"));

	dc.SelectObject(oldFont);
	m_cFont.DeleteObject();
}

void CPuttyDesignerView::OnBnClickedButtonDefault()
{
	LoadDefault();
	SetControlData();
}

void CPuttyDesignerView::OnBnClickedButtonApply()
{
	if ( (radioSelectAll == TRUE) && (radioSelectOne == FALSE) )
	{
		if (MessageBox(_T("모든 세션에 현재 설정을 저장합니다."), _T("설정 저장"), MB_YESNO) != IDYES) return;
		UpdateData(TRUE);
		if (SaveSession())
		{
			MessageBox(_T("적용 되었습니다"));
			return;
		}
	}
	else if ( (radioSelectAll == FALSE) && (radioSelectOne == TRUE) )
	{
		if (selectSession.GetLength() == 0)
		{
			MessageBox(_T("세션을 선택해 주세요"));
			return;
		}
		CString strMsg;
		strMsg.Format(_T("[%s] 세션에 현재 설정을 저정합니다."), selectSession);
		if (MessageBox(strMsg, _T("설정 저장"), MB_YESNO) != IDYES) return;
		UpdateData(TRUE);
		if (SaveSession(selectSession))
		{
			MessageBox(_T("적용 되었습니다"));
			return;
		}
	}

	MessageBox(_T("적용할 수 없습니다"));
}

void CPuttyDesignerView::OnBnClickedButtonClose()
{
    PostQuitMessage(WM_CLOSE);
}

void CPuttyDesignerView::OnNMClickListSession(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;

	int row = listSession.GetNextItem(-1, LVNI_FOCUSED);	
	selectSession = listSession.GetItemText(row, 1);
}

void CPuttyDesignerView::OnNMDblclkListSession(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;

	int row = listSession.GetNextItem(-1, LVNI_FOCUSED);	
	selectSession = listSession.GetItemText(row, 1);
	LoadSession(selectSession);
}

void CPuttyDesignerView::LoadControlData()
{
	TCHAR text[1024] = {0,};
	int i = 0;
	for (i=7; i<21; i++)
	{
		_stprintf(text, _T("%d"), i);
		comboFontSize.AddString(text);
		ZeroMemory(text, 1024);
	}

	EnumFonts (::GetDC(NULL), 0,(FONTENUMPROC) EnumFontProc,(LPARAM)this);

	comboCharset.AddString(_T("UTF-8"));
	comboCharset.AddString(_T("CP949"));
	comboCharset.AddString(_T("(edit)"));
	SetDlgItemText(IDC_EDIT_CHARSET, _T("UTF-8"));

	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_HEIGHT), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_WIDTH), EM_LIMITTEXT, 3, 0);

	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCR_R), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCR_G), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCR_B), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCG_R), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCG_G), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCG_B), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCB_R), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCB_G), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCB_B), EM_LIMITTEXT, 3, 0);

	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCRB_R), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCRB_G), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCRB_B), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCGB_R), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCGB_G), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCGB_B), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCBB_R), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCBB_G), EM_LIMITTEXT, 3, 0);
	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_FCBB_B), EM_LIMITTEXT, 3, 0);

	::SendMessage(::GetDlgItem(m_hWnd, IDC_EDIT_CHARSET), EM_LIMITTEXT, 20, 0);
}

void CPuttyDesignerView::SetControlData()
{
	m_colorRed = RGB(color_fcr_r, color_fcr_g, color_fcr_b);
	m_colorGreen = RGB(color_fcg_r, color_fcg_g, color_fcg_b);
	m_colorBlue = RGB(color_fcb_r, color_fcb_g, color_fcb_b);

	m_colorRedBold = RGB(color_fcrb_r, color_fcrb_g, color_fcrb_b);
	m_colorGreenBold = RGB(color_fcgb_r, color_fcgb_g, color_fcgb_b);
	m_colorBlueBold = RGB(color_fcbb_r, color_fcbb_g, color_fcbb_b);

	SetDlgItemInt(IDC_EDIT_HEIGHT, m_sizeHeight, TRUE);
	SetDlgItemInt(IDC_EDIT_WIDTH, m_sizeWidth, TRUE);

	SetDlgItemInt(IDC_EDIT_FCR_R, color_fcr_r, TRUE);
	SetDlgItemInt(IDC_EDIT_FCR_G, color_fcr_g, TRUE);
	SetDlgItemInt(IDC_EDIT_FCR_B, color_fcr_b, TRUE);

	SetDlgItemInt(IDC_EDIT_FCG_R, color_fcg_r, TRUE);
	SetDlgItemInt(IDC_EDIT_FCG_G, color_fcg_g, TRUE);
	SetDlgItemInt(IDC_EDIT_FCG_B, color_fcg_b, TRUE);

	SetDlgItemInt(IDC_EDIT_FCB_R, color_fcb_r, TRUE);
	SetDlgItemInt(IDC_EDIT_FCB_G, color_fcb_g, TRUE);
	SetDlgItemInt(IDC_EDIT_FCB_B, color_fcb_b, TRUE);

	SetDlgItemInt(IDC_EDIT_FCRB_R, color_fcrb_r, TRUE);
	SetDlgItemInt(IDC_EDIT_FCRB_G, color_fcrb_g, TRUE);
	SetDlgItemInt(IDC_EDIT_FCRB_B, color_fcrb_b, TRUE);

	SetDlgItemInt(IDC_EDIT_FCGB_R, color_fcgb_r, TRUE);
	SetDlgItemInt(IDC_EDIT_FCGB_G, color_fcgb_g, TRUE);
	SetDlgItemInt(IDC_EDIT_FCGB_B, color_fcgb_b, TRUE);

	SetDlgItemInt(IDC_EDIT_FCBB_R, color_fcbb_r, TRUE);
	SetDlgItemInt(IDC_EDIT_FCBB_G, color_fcbb_g, TRUE);
	SetDlgItemInt(IDC_EDIT_FCBB_B, color_fcbb_b, TRUE);

	TCHAR text[1024] = {0,};
	int i = 0;
	BOOL bInputDirect = TRUE;
	for (i=0; i<comboCharset.GetCount(); i++)
	{
		ZeroMemory(text, 1024);
		comboCharset.GetLBText(i, text);
		if (_tcscmp(text, m_strCharset.GetBuffer()) == 0)
		{
			bInputDirect = FALSE;
			comboCharset.SetCurSel(i);
			editCharset.EnableWindow(FALSE);
			m_strCharset.ReleaseBuffer();
			m_strCharset = text;
			break;
		}
		m_strCharset.ReleaseBuffer();
	}
	if (bInputDirect == TRUE)
	{
		for (i=0; i<comboCharset.GetCount(); i++)
		{
			ZeroMemory(text, 1024);
			comboCharset.GetLBText(i, text);
			if (_tcscmp(text, _T("(edit)")) == 0)
			{
				editCharset.EnableWindow(TRUE);
				comboCharset.SetCurSel(i);
				break;
			}
		}
	}
	SetDlgItemText(IDC_EDIT_CHARSET, m_strCharset);

	for (i=0; i<comboFontSize.GetCount(); i++)
	{
		ZeroMemory(text, 1024);
		comboFontSize.GetLBText(i, text);
		TCHAR szFontSize[8] = {0,};
		_itot(m_FontSize, szFontSize, 10);
		if (_tcscmp(text, szFontSize) == 0)
		{
			comboFontSize.SetCurSel(i);
			break;
		}
	}

	for (i=0; i<comboFontList.GetCount(); i++)
	{
		ZeroMemory(text, 1024);
		comboFontList.GetLBText(i, text);
		if (_tcscmp(text, m_strFont.GetBuffer()) == 0)
		{
			comboFontList.SetCurSel(i);
			break;
		}
		m_strFont.ReleaseBuffer();
	}

	UpdateData(FALSE);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}

void CPuttyDesignerView::OnCbnSelchangeComboFontlist()
{
	TCHAR text[1024] = {0,};
	ZeroMemory(text, 1024);
	int index = comboFontList.GetCurSel();
	comboFontList.GetLBText(index, text);
	m_strFont = text;
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}

void CPuttyDesignerView::OnCbnSelchangeComboCharset()
{
	TCHAR text[1024] = {0,};
	ZeroMemory(text, 1024);
	int index = comboCharset.GetCurSel();
	comboCharset.GetLBText(index, text);
	if (_tcscmp(text, _T("(edit)")) == 0)
	{
		editCharset.EnableWindow(TRUE);
	}
	else
	{
		editCharset.EnableWindow(FALSE);
	}
	SetDlgItemText(IDC_EDIT_CHARSET, text);
	m_strCharset = text;
}


void CPuttyDesignerView::OnCbnSelchangeComboFontsize()
{
	TCHAR text[1024] = {0,};
	ZeroMemory(text, 1024);
	int index = comboFontSize.GetCurSel();
	comboFontSize.GetLBText(index, text);
	m_FontSize = _ttoi(text);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}

void CPuttyDesignerView::TokenColor(CString strValue, int &r, int &g, int &b)
{
	if (strValue.GetLength() == 0) return;

	int pos = 0;
	CString tok;
	int i = 0, color = 0;

	do
	{
		tok = (strValue.Tokenize(_T(","), pos)).Trim();
		color = _ttoi(tok.GetBuffer());
		switch (i)
		{
		case 0:
			r = color;
			break;
		case 1:
			g = color;
			break;
		case 2:
			b = color;
			break;
		}
		i++;
		tok.ReleaseBuffer();
	}
	while (tok != _T(""));
}

void CPuttyDesignerView::LoadSession(CString session)
{
	if (session.GetLength() == 0) return;

	TCHAR szSubKey[512] = {0,};
	_stprintf(szSubKey, _T("Software\\SimonTatham\\PuTTY\\Sessions\\%s"), session.GetBuffer());
	session.ReleaseBuffer();

	HKEY m_hRegKey;
	LSTATUS status = RegOpenKeyEx(HKEY_CURRENT_USER, szSubKey, 0, KEY_ALL_ACCESS, &m_hRegKey);
	if (status != ERROR_SUCCESS) 
	{
		RegCloseKey(m_hRegKey);
		return;
	}
	BYTE szValue[ 128 ] = { 0, };
	DWORD lType = REG_SZ; 
	DWORD lRetValue = 128;

	ZeroMemory(szValue, 128); lRetValue = 128;
	RegQueryValueEx(m_hRegKey, _T("Font"), NULL, &lType, (BYTE*)szValue, &lRetValue);
	m_strFont.Format(_T("%s"), szValue);

	ZeroMemory(szValue, 128); lRetValue = 128;
	RegQueryValueEx(m_hRegKey, _T("LineCodePage"), NULL, &lType, (BYTE*)szValue, &lRetValue);
	m_strCharset.Format(_T("%s"), szValue);

	CString strColor;

	ZeroMemory(szValue, 128); lRetValue = 128;
	status = RegQueryValueEx(m_hRegKey, _T("Colour8"), NULL, &lType, (BYTE*)szValue, &lRetValue);
	strColor.Format(_T("%s"), szValue);
	TokenColor(strColor, color_fcr_r, color_fcr_g, color_fcr_b);

	ZeroMemory(szValue, 128); lRetValue = 128;
	RegQueryValueEx(m_hRegKey, _T("Colour10"), NULL, &lType, (BYTE*)szValue, &lRetValue);
	strColor.Format(_T("%s"), szValue);
	TokenColor(strColor, color_fcg_r, color_fcg_g, color_fcg_b);

	ZeroMemory(szValue, 128); lRetValue = 128;
	RegQueryValueEx(m_hRegKey, _T("Colour14"), NULL, &lType, (BYTE*)szValue, &lRetValue);
	strColor.Format(_T("%s"), szValue);
	TokenColor(strColor, color_fcb_r, color_fcb_g, color_fcb_b);

	ZeroMemory(szValue, 128); lRetValue = 128;
	RegQueryValueEx(m_hRegKey, _T("Colour9"), NULL, &lType, (BYTE*)szValue, &lRetValue);
	strColor.Format(_T("%s"), szValue);
	TokenColor(strColor, color_fcrb_r, color_fcrb_g, color_fcrb_b);

	ZeroMemory(szValue, 128); lRetValue = 128;
	RegQueryValueEx(m_hRegKey, _T("Colour11"), NULL, &lType, (BYTE*)szValue, &lRetValue);
	strColor.Format(_T("%s"), szValue);
	TokenColor(strColor, color_fcgb_r, color_fcgb_g, color_fcgb_b);

	ZeroMemory(szValue, 128); lRetValue = 128;
	RegQueryValueEx(m_hRegKey, _T("Colour15"), NULL, &lType, (BYTE*)szValue, &lRetValue);
	strColor.Format(_T("%s"), szValue);
	TokenColor(strColor, color_fcbb_r, color_fcbb_g, color_fcbb_b);

	lType = REG_DWORD;
	DWORD dwValue;
	lRetValue = 4;
	RegQueryValueEx(m_hRegKey, _T("FontHeight"), NULL, &lType, (BYTE*)(&dwValue), &lRetValue);
	m_FontSize = (int)dwValue;
	CString tempString;
	lRetValue = 4;
	RegQueryValueEx(m_hRegKey, _T("TermHeight"), NULL, &lType, (BYTE*)(&dwValue), &lRetValue);
	m_sizeHeight = dwValue;
	lRetValue = 4;
	RegQueryValueEx(m_hRegKey, _T("TermWidth"), NULL, &lType, (BYTE*)(&dwValue), &lRetValue);
	m_sizeWidth = dwValue;

	RegCloseKey(m_hRegKey);

	SetControlData();
}

BOOL CPuttyDesignerView::SaveSession()
{
	HKEY m_hRegKeyAll;
	LSTATUS status = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\SimonTatham\\PuTTY\\Sessions"), 0, KEY_ALL_ACCESS, &m_hRegKeyAll);
	if (status != ERROR_SUCCESS) 
	{
		RegCloseKey(m_hRegKeyAll);
		return FALSE;
	}
	DWORD index = 0;
	DWORD dwSubKeyLength = 0;
	TCHAR szSubKey[1024] = {0,};
	DWORD dwReturn = 0;

	while (dwReturn == ERROR_SUCCESS)
	{
		dwSubKeyLength = 1024;
		dwReturn = RegEnumKeyEx(m_hRegKeyAll, index, szSubKey, &dwSubKeyLength, NULL, NULL, NULL, NULL);
		SaveSession(szSubKey);
		ZeroMemory(szSubKey, 1024);
		if(dwReturn == ERROR_NO_MORE_ITEMS)	break;
		index++;
	}
	RegCloseKey(m_hRegKeyAll);
	
	return TRUE;
}

BOOL CPuttyDesignerView::SaveSession(CString session)
{
	if (session.GetLength() == 0) return FALSE;

	TCHAR szSubKey[512] = {0,};
	_stprintf(szSubKey, _T("Software\\SimonTatham\\PuTTY\\Sessions\\%s"), session.GetBuffer());
	session.ReleaseBuffer();

	HKEY m_hRegKey;
	LSTATUS status = RegOpenKeyEx(HKEY_CURRENT_USER, szSubKey, 0, KEY_ALL_ACCESS, &m_hRegKey);
	if (status != ERROR_SUCCESS) 
	{
		RegCloseKey(m_hRegKey);
		return FALSE;
	}

	if (checkFontFace == TRUE)
	{
		RegSetValueEx(m_hRegKey, _T("Font"), NULL, REG_SZ, (BYTE*)m_strFont.GetBuffer(), sizeof(TCHAR)*m_strFont.GetLength());
		m_strFont.ReleaseBuffer();
	}

	if (checkCharset == TRUE)
	{
		GetDlgItemText(IDC_EDIT_CHARSET, m_strCharset);
		RegSetValueEx(m_hRegKey, _T("LineCodePage"), NULL, REG_SZ, (BYTE*)m_strCharset.GetBuffer(), sizeof(TCHAR)*m_strCharset.GetLength());
		m_strCharset.ReleaseBuffer();
	}

	CString strColor;
	
	if (checkFontColorRed == TRUE) 
	{
		strColor.Format(_T("%d,%d,%d"), color_fcr_r, color_fcr_g, color_fcr_b);
		status = RegSetValueEx(m_hRegKey, _T("Colour8"), NULL, REG_SZ, (BYTE*)strColor.GetBuffer(), sizeof(TCHAR)*strColor.GetLength());
		strColor.ReleaseBuffer();
	}

	if (checkFontColorGreen == TRUE) 
	{
		strColor.Format(_T("%d,%d,%d"), color_fcg_r, color_fcg_g, color_fcg_b);
		RegSetValueEx(m_hRegKey, _T("Colour10"), NULL, REG_SZ, (BYTE*)strColor.GetBuffer(), sizeof(TCHAR)*strColor.GetLength());
		strColor.ReleaseBuffer();
	}

	if (checkFontColorBlue == TRUE) 
	{
		strColor.Format(_T("%d,%d,%d"), color_fcb_r, color_fcb_g, color_fcb_b);
		RegSetValueEx(m_hRegKey, _T("Colour14"), NULL, REG_SZ, (BYTE*)strColor.GetBuffer(), sizeof(TCHAR)*strColor.GetLength());
		strColor.ReleaseBuffer();
	}

	if (checkFontColorRedBold == TRUE) 
	{
		strColor.Format(_T("%d,%d,%d"), color_fcrb_r, color_fcrb_g, color_fcrb_b);
		RegSetValueEx(m_hRegKey, _T("Colour9"), NULL, REG_SZ, (BYTE*)strColor.GetBuffer(), sizeof(TCHAR)*strColor.GetLength());
		strColor.ReleaseBuffer();
	}

	if (checkFontColorGreenBold == TRUE) 
	{
		strColor.Format(_T("%d,%d,%d"), color_fcgb_r, color_fcgb_g, color_fcgb_b);
		RegSetValueEx(m_hRegKey, _T("Colour11"), NULL, REG_SZ, (BYTE*)strColor.GetBuffer(), sizeof(TCHAR)*strColor.GetLength());
		strColor.ReleaseBuffer();
	}

	if (checkFontColorBlueBold == TRUE) 
	{
		strColor.Format(_T("%d,%d,%d"), color_fcbb_r, color_fcbb_g, color_fcbb_b);
		RegSetValueEx(m_hRegKey, _T("Colour15"), NULL, REG_SZ, (BYTE*)strColor.GetBuffer(), sizeof(TCHAR)*strColor.GetLength());
		strColor.ReleaseBuffer();
	}

	if (checkFontSize == TRUE) 
	{
		RegSetValueEx(m_hRegKey, _T("FontHeight"), NULL, REG_DWORD, (BYTE*)(&m_FontSize), sizeof(DWORD));
	}	

	if (checkScreenSize == TRUE)
	{
		m_sizeHeight = GetDlgItemInt(IDC_EDIT_HEIGHT);
		m_sizeWidth = GetDlgItemInt(IDC_EDIT_WIDTH);
		RegSetValueEx(m_hRegKey, _T("TermHeight"), NULL, REG_DWORD, (BYTE*)(&m_sizeHeight), sizeof(DWORD));
		RegSetValueEx(m_hRegKey, _T("TermWidth"), NULL, REG_DWORD, (BYTE*)(&m_sizeWidth), sizeof(DWORD));
	}

	if (checkHangul == TRUE) 
	{
		DWORD dwValue = 129;
		RegSetValueEx(m_hRegKey, _T("FontCharSet"), NULL, REG_DWORD, (BYTE*)(&dwValue), sizeof(DWORD));
	}

	RegCloseKey(m_hRegKey);
	return TRUE;
}

// Red
void CPuttyDesignerView::OnEnChangeEditFcrR()
{
	color_fcr_r = GetDlgItemInt(IDC_EDIT_FCR_R);
	m_colorRed = RGB(color_fcr_r, color_fcr_g, color_fcr_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcrG()
{
	color_fcr_g = GetDlgItemInt(IDC_EDIT_FCR_G);
	m_colorRed = RGB(color_fcr_r, color_fcr_g, color_fcr_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcrB()
{
	color_fcr_b = GetDlgItemInt(IDC_EDIT_FCR_B);
	m_colorRed = RGB(color_fcr_r, color_fcr_g, color_fcr_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
// Green
void CPuttyDesignerView::OnEnChangeEditFcgR()
{
	color_fcg_r = GetDlgItemInt(IDC_EDIT_FCG_R);
	m_colorGreen = RGB(color_fcg_r, color_fcg_g, color_fcg_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcgG()
{
	color_fcg_g = GetDlgItemInt(IDC_EDIT_FCG_G);
	m_colorGreen = RGB(color_fcg_r, color_fcg_g, color_fcg_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcgB()
{
	color_fcg_b = GetDlgItemInt(IDC_EDIT_FCG_B);
	m_colorGreen = RGB(color_fcg_r, color_fcg_g, color_fcg_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
// Blue
void CPuttyDesignerView::OnEnChangeEditFcbR()
{
	color_fcb_r = GetDlgItemInt(IDC_EDIT_FCB_R);
	m_colorBlue = RGB(color_fcb_r, color_fcb_g, color_fcb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcbG()
{
	color_fcb_g = GetDlgItemInt(IDC_EDIT_FCB_G);
	m_colorBlue = RGB(color_fcb_r, color_fcb_g, color_fcb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcbB()
{
	color_fcb_b = GetDlgItemInt(IDC_EDIT_FCB_B);
	m_colorBlue = RGB(color_fcb_r, color_fcb_g, color_fcb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}

// Red Bold
void CPuttyDesignerView::OnEnChangeEditFcrbR()
{
	color_fcrb_r = GetDlgItemInt(IDC_EDIT_FCRB_R);
	m_colorRedBold = RGB(color_fcrb_r, color_fcrb_g, color_fcrb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcrbG()
{
	color_fcrb_g = GetDlgItemInt(IDC_EDIT_FCRB_G);
	m_colorRedBold = RGB(color_fcrb_r, color_fcrb_g, color_fcrb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcrbB()
{
	color_fcrb_b = GetDlgItemInt(IDC_EDIT_FCRB_B);
	m_colorRedBold = RGB(color_fcrb_r, color_fcrb_g, color_fcrb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
// Green Bold
void CPuttyDesignerView::OnEnChangeEditFcgbR()
{
	color_fcgb_r = GetDlgItemInt(IDC_EDIT_FCGB_R);
	m_colorGreenBold = RGB(color_fcgb_r, color_fcgb_g, color_fcgb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcgbG()
{
	color_fcgb_g = GetDlgItemInt(IDC_EDIT_FCGB_G);
	m_colorGreenBold = RGB(color_fcgb_r, color_fcgb_g, color_fcgb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcgbB()
{
	color_fcgb_b = GetDlgItemInt(IDC_EDIT_FCGB_B);
	m_colorGreenBold = RGB(color_fcgb_r, color_fcgb_g, color_fcgb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
// Blue Bold
void CPuttyDesignerView::OnEnChangeEditFcbbR()
{
	color_fcbb_r = GetDlgItemInt(IDC_EDIT_FCBB_R);
	m_colorBlueBold = RGB(color_fcbb_r, color_fcbb_g, color_fcbb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcbbG()
{
	color_fcbb_g = GetDlgItemInt(IDC_EDIT_FCBB_G);
	m_colorBlueBold = RGB(color_fcbb_r, color_fcbb_g, color_fcbb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
void CPuttyDesignerView::OnEnChangeEditFcbbB()
{
	color_fcbb_b = GetDlgItemInt(IDC_EDIT_FCBB_B);
	m_colorBlueBold = RGB(color_fcbb_r, color_fcbb_g, color_fcbb_b);
	::InvalidateRect(this->m_hWnd,NULL,TRUE);
}
