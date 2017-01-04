
// MapEditerView.h : CMapEditerView ��Ľӿ�
//

#pragma once


class CMapEditerView : public CScrollView
{
protected: // �������л�����
	CMapEditerView();
	DECLARE_DYNCREATE(CMapEditerView)

// ����
public:
	CMapEditerDoc* GetDocument() const;
// 	int MapLength;
// 	int MapHeigth;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	BOOL m_startRect = FALSE;
	CPoint m_ptPrev = 0;       // the last mouse pt in the stroke in progress
	CPoint m_ptPrev1 = 0;
	CPoint m_LastPt = 0;

	POSITION m_MonsterSel;
	int m_nColor;
	int m_nMonster_X;
	int m_nMonster_Y;

// ʵ��
public:
	virtual ~CMapEditerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MapEditerView.cpp �еĵ��԰汾
inline CMapEditerDoc* CMapEditerView::GetDocument() const
   { return reinterpret_cast<CMapEditerDoc*>(m_pDocument); }
#endif

