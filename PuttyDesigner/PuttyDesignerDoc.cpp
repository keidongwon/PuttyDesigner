#include "stdafx.h"
#include "PuttyDesigner.h"

#include "PuttyDesignerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CPuttyDesignerDoc, CDocument)

BEGIN_MESSAGE_MAP(CPuttyDesignerDoc, CDocument)
END_MESSAGE_MAP()


CPuttyDesignerDoc::CPuttyDesignerDoc()
{
}

CPuttyDesignerDoc::~CPuttyDesignerDoc()
{
}

BOOL CPuttyDesignerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CPuttyDesignerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CPuttyDesignerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPuttyDesignerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
