
// MapEditerView.h : CMapEditerView 类的接口
//

#pragma once


class CMapEditerView : public CScrollView
{
protected: // 仅从序列化创建
	CMapEditerView();
	DECLARE_DYNCREATE(CMapEditerView)

// 特性
public:
	CMapEditerDoc* GetDocument() const;
// 	int MapLength;
// 	int MapHeigth;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	BOOL m_startRect = FALSE;
	CPoint m_ptPrev = 0;       // the last mouse pt in the stroke in progress
	CPoint m_ptPrev1 = 0;
	CPoint m_LastPt = 0;

	POSITION m_MonsterSel;
	int m_nColor;
	int m_nMonster_X;
	int m_nMonster_Y;

// 实现
public:
	virtual ~CMapEditerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	void DrawGrid(CDC* pDC, CMapEditerDoc* pDoc);
	void CMapEditerView::DrawSelRect(CDC* pDC, CMapEditerDoc* pDoc);
	void CMapEditerView::DisplayMonsterInfo(CDC* pDC, CMapEditerDoc* pDoc);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMonsterAdd();
	afx_msg void OnMonsterDel();
	afx_msg void OnMonsterCheck();

	void CMapEditerView::DoAlign(int nType);
	afx_msg void OnLeftAlign();
	afx_msg void OnTopAlign();
	afx_msg void OnRightAlign();
	afx_msg void OnBottomAlign();
	afx_msg void OnCenterAlign();
};

#ifndef _DEBUG  // MapEditerView.cpp 中的调试版本
inline CMapEditerDoc* CMapEditerView::GetDocument() const
   { return reinterpret_cast<CMapEditerDoc*>(m_pDocument); }
#endif

