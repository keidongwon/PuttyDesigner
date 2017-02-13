#pragma once

class CPuttyDesignerView : public CFormView
{
protected:
	CPuttyDesignerView();
	DECLARE_DYNCREATE(CPuttyDesignerView)

public:
	enum{ IDD = IDD_PUTTYDESIGNER_FORM };

public:
	CPuttyDesignerDoc* GetDocument() const;

public:
	CListCtrl listSession;
	CComboBox comboFontList;
	CComboBox comboFontSize;
	CComboBox comboCharset;
	CEdit editHeight;
	CEdit editWidth;
	CEdit editCharset;

	BOOL radioSelectAll;
	BOOL radioSelectOne;

	BOOL checkScreenSize;
	BOOL checkFontFace;
	BOOL checkFontSize;
	BOOL checkFontColorRed;
	BOOL checkFontColorGreen;
	BOOL checkFontColorBlue;
	BOOL checkFontColorRedBold;
	BOOL checkFontColorGreenBold;
	BOOL checkFontColorBlueBold;
	BOOL checkCharset;
	BOOL checkHangul;

	COLORREF m_colorBlack;
	COLORREF m_colorWhite;

	COLORREF m_colorRed;
	COLORREF m_colorGreen;
	COLORREF m_colorBlue;
	COLORREF m_colorRedBold;
	COLORREF m_colorGreenBold;
	COLORREF m_colorBlueBold;
	CFont m_cFont;

	int color_fcr_r;
	int color_fcr_g;
	int color_fcr_b;
	int color_fcg_r;
	int color_fcg_g;
	int color_fcg_b;
	int color_fcb_r;
	int color_fcb_g;
	int color_fcb_b;
	int color_fcrb_r;
	int color_fcrb_g;
	int color_fcrb_b;
	int color_fcgb_r;
	int color_fcgb_g;
	int color_fcgb_b;
	int color_fcbb_r;
	int color_fcbb_g;
	int color_fcbb_b;

	CString m_strFont;
	CString m_strCharset;
	int m_FontSize;
	DWORD m_sizeHeight;
	DWORD m_sizeWidth;

	void LoadSession();
	void LoadSession(CString session);
	BOOL SaveSession();
	BOOL SaveSession(CString session);
	void LoadDefault();
	void LoadControlData();
	void SetControlData();
	void TokenColor(CString strValue, int &r, int &g, int &b);

private:
	CString selectSession;

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

public:
	virtual ~CPuttyDesignerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioSelectall();
	afx_msg void OnBnClickedRadioSelectone();
	afx_msg void OnManageBackup();
	afx_msg void OnManageRestore();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonDefault();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnNMClickListSession(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListSession(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboFontlist();
	afx_msg void OnCbnSelchangeComboCharset();
	afx_msg void OnCbnSelchangeComboFontsize();
	afx_msg void OnEnChangeEditFcrR();
	afx_msg void OnEnChangeEditFcrG();
	afx_msg void OnEnChangeEditFcrB();
	afx_msg void OnEnChangeEditFcgR();
	afx_msg void OnEnChangeEditFcgG();
	afx_msg void OnEnChangeEditFcgB();
	afx_msg void OnEnChangeEditFcbR();
	afx_msg void OnEnChangeEditFcbG();
	afx_msg void OnEnChangeEditFcbB();
	afx_msg void OnEnChangeEditFcrbR();
	afx_msg void OnEnChangeEditFcrbG();
	afx_msg void OnEnChangeEditFcrbB();
	afx_msg void OnEnChangeEditFcgbR();
	afx_msg void OnEnChangeEditFcgbG();
	afx_msg void OnEnChangeEditFcgbB();
	afx_msg void OnEnChangeEditFcbbR();
	afx_msg void OnEnChangeEditFcbbG();
	afx_msg void OnEnChangeEditFcbbB();
};

#ifndef _DEBUG  // PuttyDesignerView.cpp의 디버그 버전
inline CPuttyDesignerDoc* CPuttyDesignerView::GetDocument() const
   { return reinterpret_cast<CPuttyDesignerDoc*>(m_pDocument); }
#endif

