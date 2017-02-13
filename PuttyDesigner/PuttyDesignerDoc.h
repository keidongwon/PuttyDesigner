#pragma once

class CPuttyDesignerDoc : public CDocument
{
protected:
	CPuttyDesignerDoc();
	DECLARE_DYNCREATE(CPuttyDesignerDoc)

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

public:
	virtual ~CPuttyDesignerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};
