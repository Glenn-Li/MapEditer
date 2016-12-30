
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

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

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

public:
	int MapLength;
	int MapHeigth;

private:
	void DrawGrid(CDC* pDC);
	void CMapEditerView::DisplayMonsterInfo(CDC* pDC);
};

#ifndef _DEBUG  // MapEditerView.cpp �еĵ��԰汾
inline CMapEditerDoc* CMapEditerView::GetDocument() const
   { return reinterpret_cast<CMapEditerDoc*>(m_pDocument); }
#endif

