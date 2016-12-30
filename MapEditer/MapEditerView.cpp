
// MapEditerView.cpp : CMapEditerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MapEditer.h"
#endif

#include "MapEditerDoc.h"
#include "MapEditerView.h"
#include "comlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditerView

IMPLEMENT_DYNCREATE(CMapEditerView, CScrollView)

BEGIN_MESSAGE_MAP(CMapEditerView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMapEditerView ����/����

CMapEditerView::CMapEditerView()
{
	// TODO:  �ڴ˴���ӹ������
	//MapLength = GetMapLength() * 16;
	//MapHeigth = 55 * 16;

}

CMapEditerView::~CMapEditerView()
{
}

BOOL CMapEditerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CMapEditerView ����

void CMapEditerView::OnDraw(CDC* pDC)
{
	CMapEditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	CSize sizeTotal;
	sizeTotal.cx = pDoc->MapLength;
	sizeTotal.cy = pDoc->MapHeigth;
	SetScrollSizes(MM_TEXT, sizeTotal);

	DrawGrid(pDC, pDoc);

	DisplayMonsterInfo(pDC, pDoc);
}

void CMapEditerView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 200;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CMapEditerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMapEditerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CMapEditerView ���

#ifdef _DEBUG
void CMapEditerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapEditerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMapEditerDoc* CMapEditerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditerDoc)));
	return (CMapEditerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditerView ��Ϣ�������

void CMapEditerView::DrawGrid(CDC* pDC, CMapEditerDoc* pDoc)
{
	CPen pen;

	int MapHeigth = pDoc->MapHeigth;
	int MapLength = pDoc->MapLength;

	//CBrush brush;
	pen.CreatePen(PS_SOLID, 1, RGB(127, 127, 127));
	//brush.CreateSolidBrush(RGB(125, 125, 125));
	pDC->SelectObject(pen);
	//pDC->SelectObject(brush);
	for (int i = 0; i < MapHeigth; i += 16)
	{
		pDC->Rectangle(0, i, MapLength, i + 1);
	}
	for (int j = 0; j < MapLength; j += 16)
	{
		pDC->Rectangle(j, 0, j + 1, MapHeigth);
	}
	DeleteObject(pen);
	//DeleteObject(brush);
}

void CMapEditerView::DisplayMonsterInfo(CDC* pDC, CMapEditerDoc* pDoc)
{
	POSITION pos;
	struct MonsterInfo TmpMonsterInfo;
	CString tmpStr;
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	pDC->SelectObject(pen);

	pos = pDoc->LMonsterInfo.GetHeadPosition();
	for (int i = 0; i < pDoc->LMonsterInfo.GetCount(); i++)
	{
		TmpMonsterInfo = pDoc->LMonsterInfo.GetNext(pos);
		unsigned __int8 rgb = (unsigned __int8)TmpMonsterInfo.Id;
		CBrush brush;
		brush.CreateSolidBrush(RGB(rgb, rgb, rgb));
		pDC->SelectObject(brush);
		int X = (int)(TmpMonsterInfo.X / 4);
		int Y = (int)(TmpMonsterInfo.Y / 4);
		pDC->Rectangle(X, Y, X+32, Y+32);
		DeleteObject(brush);

		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->TextOutW(X+8, Y+8, nTos(TmpMonsterInfo.Id));
	}
	DeleteObject(pen);
}

BOOL CMapEditerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CBrush brush(RGB(0, 0, 0));
	CBrush* pOldOne= pDC->SelectObject(&brush);
	CRect rc;
	pDC->GetClipBox(&rc);
	pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
	pDC->SelectObject(pOldOne);
	return TRUE;

	//return CScrollView::OnEraseBkgnd(pDC);
}
