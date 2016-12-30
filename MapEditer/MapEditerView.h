
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

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

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

public:
	int MapLength;
	int MapHeigth;

private:
	void DrawGrid(CDC* pDC);
	void CMapEditerView::DisplayMonsterInfo(CDC* pDC);
};

#ifndef _DEBUG  // MapEditerView.cpp 中的调试版本
inline CMapEditerDoc* CMapEditerView::GetDocument() const
   { return reinterpret_cast<CMapEditerDoc*>(m_pDocument); }
#endif

