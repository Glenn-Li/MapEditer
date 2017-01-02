
// MapEditerView.cpp : CMapEditerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MONSTER_ADD, OnMonsterAdd)
	ON_COMMAND(ID_MONSTER_DEL, OnMonsterDel)
	ON_COMMAND(ID_MONSTER_CHECK, OnMonsterCheck)
END_MESSAGE_MAP()

// CMapEditerView 构造/析构

CMapEditerView::CMapEditerView()
{
	// TODO:  在此处添加构造代码
	//MapLength = GetMapLength() * 16;
	//MapHeigth = 55 * 16;

	m_MonsterSel = NULL;

}

CMapEditerView::~CMapEditerView()
{
}

BOOL CMapEditerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CMapEditerView 绘制

void CMapEditerView::OnDraw(CDC* pDC)
{
	CMapEditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CSize sizeTotal;
	sizeTotal.cx = pDoc->MapLength;
	sizeTotal.cy = pDoc->MapHeigth;
	SetScrollSizes(MM_TEXT, sizeTotal);

	// 双缓存技术解决闪屏，部分更新带了的画笔不一致问题

//	CPoint ptCenter;

//	CRect rect, ellipseRect;

//	GetClientRect(&rect);

//	ptCenter = rect.CenterPoint();

	CDC dcMem; //用于缓冲作图的内存DC

	CBitmap bmp; //内存中承载临时图象的位图

	dcMem.CreateCompatibleDC(pDC); //依附窗口DC创建兼容内存DC

	bmp.CreateCompatibleBitmap(pDC, pDoc->MapLength, pDoc->MapHeigth); //创建兼容位图, 传入pDC才能画出彩色图

	dcMem.SelectObject(&bmp); //将位图选择进内存DC

//	dcMem.FillSolidRect(rect, pDC->GetBkColor()); //按原来背景填充客户区，不然会是黑色

	DrawGrid(&dcMem, pDoc);

	DisplayMonsterInfo(&dcMem, pDoc);

	pDC->BitBlt(0, 0, pDoc->MapLength, pDoc->MapHeigth, &dcMem, 0, 0, SRCCOPY);//将内存DC上的图象拷贝到前台

	dcMem.DeleteDC(); //删除DC

	bmp.DeleteObject(); //删除位图
}

void CMapEditerView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  计算此视图的合计大小
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

// CMapEditerView 诊断

#ifdef _DEBUG
void CMapEditerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapEditerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMapEditerDoc* CMapEditerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditerDoc)));
	return (CMapEditerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditerView 消息处理程序

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
	for (int i = 0; i < MapHeigth; i += GRID_CELL_SIZE)
	{
		pDC->Rectangle(0, i, MapLength, i + 1);
	}
	for (int j = 0; j < MapLength; j += GRID_CELL_SIZE)
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

	pos = pDoc->LMonsterInfo.GetHeadPosition();
	for (int i = 0; i < pDoc->LMonsterInfo.GetCount(); i++)
	{
		TmpMonsterInfo = pDoc->LMonsterInfo.GetNext(pos);

		struct MonsterBlock m_MonsterBlock;
		pDoc->CreatMonsterRect(&TmpMonsterInfo, &m_MonsterBlock);

		CPen pen;
		pen.CreatePen(PS_SOLID, m_MonsterBlock.m_PenWidth, m_MonsterBlock.m_PenColor);
		pDC->SelectObject(pen);

		CBrush brush;
		brush.CreateSolidBrush(m_MonsterBlock.m_BrushColor);
		pDC->SelectObject(brush);

		pDC->Rectangle(m_MonsterBlock.m_CRect);

		pDC->SetTextColor(m_MonsterBlock.m_TextColor);
		pDC->TextOutW(m_MonsterBlock.m_TextPoint.x, m_MonsterBlock.m_TextPoint.y, nTos(TmpMonsterInfo.m_Propertie.Id));

		DeleteObject(brush);
		DeleteObject(pen);
	}
}

BOOL CMapEditerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	// 把背景刷黑，放到内存缓冲处理，否则会导致闪屏
// 	CBrush brush(RGB(0, 0, 0));
// 	CBrush* pOldOne= pDC->SelectObject(&brush);
// 	CRect rc;
// 	pDC->GetClipBox(&rc);
// 	pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
// 	pDC->SelectObject(pOldOne);
	
	return TRUE;

	//return CScrollView::OnEraseBkgnd(pDC);
}


void CMapEditerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CMapEditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

// 	int X = point.x * MONSTER_POS_RATIO;
// 	int Y = point.y * MONSTER_POS_RATIO;

	POSITION pos;
	CRect rectReflash;
	struct MonsterPropertie* pMonsterPropertie;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);
	m_LastPt = point;

	if (pDoc->GetMonstersRect(point, &pos, &pMonsterPropertie))
	{
		pDoc->UpdatePropertiesView(pos);

		rectReflash.left = pMonsterPropertie->X;
		rectReflash.top = pMonsterPropertie->Y;
		rectReflash.right = pMonsterPropertie->X + MONSTER_SIZE;
		rectReflash.bottom = pMonsterPropertie->Y + MONSTER_SIZE;

		dc.LPtoDP(&rectReflash);		//注意：LPtoDP

		//InvalidateRect(rectReflash);

		Invalidate();
	}

	if (GetCapture() != this)
		return;

	ReleaseCapture();
	m_MonsterSel = NULL;

	CScrollView::OnLButtonUp(nFlags, point);
}


void CMapEditerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CMapEditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	m_ptPrev = point;
	m_ptPrev1 = point;

	SetCapture();

	POSITION pos, posPrev;
	struct MonsterPropertie* pMonsterPropertie;

	if (pDoc->GetMonstersRect(point, &pos, &pMonsterPropertie))
	{
		posPrev = pos;
		struct MonsterInfo m_MonsterInfo = pDoc->LMonsterInfo.GetNext(pos);
		//struct MonsterPropertie* pMonsterPropertie = &m_MonsterInfo.m_Propertie;
		struct MonsterBlock m_MonsterBlock;
		pDoc->CreatMonsterRect(&m_MonsterInfo, &m_MonsterBlock);

		if (m_MonsterBlock.m_CRect.PtInRect(point))
		{
			m_MonsterSel = posPrev;
			m_nMonster_X = pMonsterPropertie->X;
			m_nMonster_Y = pMonsterPropertie->Y;
		}
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMapEditerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (GetCapture() != this)
		return;

	CMapEditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	CRect rectReflash;

	if (m_MonsterSel)
	{
		int offset_x = point.x - m_ptPrev.x;
		int offset_y = point.y - m_ptPrev.y;

		// Update MonsterInfo
		POSITION tmpPos = m_MonsterSel;
		struct MonsterInfo m_MonsterInfo = pDoc->LMonsterInfo.GetNext(tmpPos);
		struct MonsterPropertie* pMonsterPropertie = &m_MonsterInfo.m_Propertie;

		//TRACE("X,Y = %d,%d\n", m_MonsterInfo.X, m_MonsterInfo.Y);
		pMonsterPropertie->X = m_nMonster_X + offset_x * MONSTER_POS_RATIO;
		pMonsterPropertie->Y = m_nMonster_Y + offset_y * MONSTER_POS_RATIO;
		//TRACE("X,Y = %d,%d\n", m_MonsterInfo.X, m_MonsterInfo.Y);
		pDoc->LMonsterInfo.SetAt(m_MonsterSel, m_MonsterInfo);



		rectReflash.left = min(m_ptPrev1.x - MONSTER_SIZE, point.x);
		rectReflash.top = min(m_ptPrev1.y - MONSTER_SIZE, point.y);
		rectReflash.right = max(m_ptPrev1.x + MONSTER_SIZE, point.x);
		rectReflash.bottom = max(m_ptPrev1.y + MONSTER_SIZE, point.y);

		dc.LPtoDP(&rectReflash);		//注意：LPtoDP

		//InvalidateRect(rectReflash);
		Invalidate();
		m_ptPrev1 = point;
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CMapEditerView::OnMonsterAdd()
{
	//AfxMessageBox(_T("ADD"));
	POSITION pos, posPrev;
	int i;
	CMapEditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	struct MonsterInfo TmpMonsterInfo;
	struct MonsterPropertie* TmpMonsterPropertie = &TmpMonsterInfo.m_Propertie;

	memset(TmpMonsterPropertie, 0, sizeof(struct MonsterPropertie));

	if (pDoc->PosSelPrev)
	{
		posPrev = pDoc->PosSelPrev;
		struct MonsterInfo m_MonsterInfo = pDoc->LMonsterInfo.GetNext(posPrev);
		struct MonsterPropertie* pMonsterPropertie = &m_MonsterInfo.m_Propertie;
		TmpMonsterPropertie->Id = pMonsterPropertie->Id;
		TmpMonsterPropertie->X = pMonsterPropertie->X;// +MONSTER_SIZE * MONSTER_POS_RATIO / 2;
		TmpMonsterPropertie->Y = pMonsterPropertie->Y;// +MONSTER_SIZE * MONSTER_POS_RATIO / 2;
	}
	else
	{
		TmpMonsterPropertie->Id = 894;
		TmpMonsterPropertie->X = 256;
		TmpMonsterPropertie->Y = 256;
	}

	pos = pDoc->LMonsterInfo.GetHeadPosition();
	for (i = 0; i < pDoc->LMonsterInfo.GetCount(); i++)
	{
		posPrev = pos;
		struct MonsterInfo m_MonsterInfo = pDoc->LMonsterInfo.GetNext(pos);
		struct MonsterPropertie* pMonsterPropertie = &m_MonsterInfo.m_Propertie;
		// 先比较Y坐标
		if (pMonsterPropertie->Y > TmpMonsterPropertie->Y)
		{
			pDoc->LMonsterInfo.InsertBefore(posPrev, TmpMonsterInfo);
			pDoc->m_MapBinHead.MonsterCount--;
			break;
		}
		else if (pMonsterPropertie->Y == TmpMonsterPropertie->Y)  // 如果Y坐标相等就再比较X坐标
		{
			if (pMonsterPropertie->X >= TmpMonsterPropertie->X)
			{
				pDoc->LMonsterInfo.InsertBefore(posPrev, TmpMonsterInfo);
				pDoc->m_MapBinHead.MonsterCount--;
				break;
			}
		}
	}

	// 说明没有找到比这个坐标更小的坐标了，就插到最后
	if (i >= pDoc->LMonsterInfo.GetCount())
	{
		pDoc->LMonsterInfo.AddTail(TmpMonsterInfo);
		pDoc->m_MapBinHead.MonsterCount--;
	}

	CRect rectReflash;

	rectReflash.left = TmpMonsterPropertie->X / MONSTER_POS_RATIO;
	rectReflash.top = TmpMonsterPropertie->Y / MONSTER_POS_RATIO;
	rectReflash.right = TmpMonsterPropertie->X / MONSTER_POS_RATIO + MONSTER_SIZE;
	rectReflash.bottom = TmpMonsterPropertie->Y / MONSTER_POS_RATIO + MONSTER_SIZE;

	//InvalidateRect(rectReflash);
	Invalidate();
}

void CMapEditerView::OnMonsterDel()
{
	//AfxMessageBox(_T("Del"));
	POSITION pos, posPrev;
	CRect rectReflash;
	int i;
	CMapEditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	struct MonsterInfo m_MonsterInfo;
	struct MonsterPropertie* pMonsterPropertie = NULL;

	if (pDoc->GetMonstersRect(m_LastPt, &pos, &pMonsterPropertie))
	{
		posPrev = pos;
		m_MonsterInfo = pDoc->LMonsterInfo.GetNext(pos);
		
		rectReflash.left = pMonsterPropertie->X / MONSTER_POS_RATIO;
		rectReflash.top = pMonsterPropertie->Y / MONSTER_POS_RATIO;
		rectReflash.right = pMonsterPropertie->X / MONSTER_POS_RATIO + MONSTER_SIZE * 2;
		rectReflash.bottom = pMonsterPropertie->Y / MONSTER_POS_RATIO + MONSTER_SIZE * 2;

		// 删除这个节点

		pDoc->LMonsterInfo.RemoveAt(posPrev);
		pDoc->m_MapBinHead.MonsterCount--;
	}

	//InvalidateRect(rectReflash);
	Invalidate();
}

void CMapEditerView::OnMonsterCheck()
{
	AfxMessageBox(_T("check"));
}