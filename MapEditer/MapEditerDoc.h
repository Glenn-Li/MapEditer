
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
	CString MapFileFolder;
	CString MapFileName;
	int MapLength = 0;
	int MapHeigth = 0;
	int MonstersCount = 0;
	struct MapBinHead m_MapBinHead;
	CList <MonsterInfo, MonsterInfo&> LMonsterInfo;
	unsigned char MapFileEnd[4*1024];
	int MapFileEndSize = 0;
	int MonstersCounter;

	POSITION PosSelPrev;
	POSITION PosSel;

// 操作
public:
	int GetMapLength();
	int GetMonsterCount();
	void GetMonstersInfo();
	void MonstersAnalysis();
	void CMapEditerDoc::SaveMonstersInfo();
	void CMapEditerDoc::OnOpenNewDoc(CString strFileName);
	void CMapEditerDoc::UpdatePropertiesView(POSITION pos);
	BOOL CMapEditerDoc::GetMonstersRect(CPoint point, POSITION* pos);
	void CMapEditerDoc::CreatMonsterRect(struct MonsterInfo* pMonsterInfo, struct MonsterBlock* pMonsterBlock);

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
