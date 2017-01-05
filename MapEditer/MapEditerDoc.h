
// MapEditerDoc.h : CMapEditerDoc ��Ľӿ�
//


#pragma once

#include "comlib.h"


class CMapEditerDoc : public CDocument
{
protected: // �������л�����
	CMapEditerDoc();
	DECLARE_DYNCREATE(CMapEditerDoc)

// ����
public:
	CString MapFileFolder;
	CString MapFileName;
	int MapLength = 0;
	int MapHeigth = 0;
	struct MapBinHead m_MapBinHead;
	CList <MonsterInfo, MonsterInfo&> LMonsterInfo;
	unsigned char MapFileEnd[4*1024];
	int MapFileEndSize = 0;
	int MonstersCounter;

	POSITION PosSelPrev;
	POSITION PosSel;

	POSITION m_MonsterInfoSel[128]; // ѡ�еĹ���id

// ����
public:
	int GetMapSize();
	int GetMonsterCount();
	void GetMonstersInfo();
	void MonstersAnalysis();
	void CMapEditerDoc::SaveMonstersInfo();
	void CMapEditerDoc::OnOpenNewDoc(CString strFileName);
	void OnUpdateFileView(CString strDir);
	void CMapEditerDoc::UpdatePropertiesView(POSITION pos);
	BOOL CMapEditerDoc::GetMonstersRect(CPoint point, POSITION* pos, struct MonsterPropertie** pMonsterPropertie, int nFlag);
	void CMapEditerDoc::CreatMonsterRect(struct MonsterInfo* pMonsterInfo, struct MonsterBlock* pMonsterBlock);
	BOOL MonsterInfoCompare(struct MonsterInfo* pSrc, struct MonsterInfo* pSrc1);
	void MarkMonstersInRect(CPoint m_ptPrev, CPoint m_ptLast);
	void OnAlignSelectMonsters(int nType);
	void OnUpdateViews();

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMapEditerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
