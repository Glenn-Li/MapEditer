
// MapEditerDoc.h : CMapEditerDoc 类的接口
//


#pragma once

#include "comlib.h"


class CMapEditerDoc : public CDocument
{
protected: // 仅从序列化创建
	CMapEditerDoc();
	DECLARE_DYNCREATE(CMapEditerDoc)

// 特性
public:
	CString MapFileName;
	int MapLength;
	int MapHeigth;
	CList <MonsterInfo, MonsterInfo&> LMonsterInfo;

// 操作
public:
	int GetMapLength();
	void GetMonstersInfo();
	afx_msg LRESULT OnOpenNewDoc(WPARAM wParam, LPARAM lParam);

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMapEditerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
