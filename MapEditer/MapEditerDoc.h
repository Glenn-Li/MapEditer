
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
	int MapLength;
	int MapHeigth;
	CList <MonsterInfo, MonsterInfo&> LMonsterInfo;
	POSITION PosSel;

// ����
public:
	int GetMapLength();
	void GetMonstersInfo();
	void CMapEditerDoc::OnOpenNewDoc(CString strFileName);
	void CMapEditerDoc::UpdatePropertiesView(POSITION pos);
	BOOL CMapEditerDoc::GetMonstersRect(CPoint point, POSITION* pos);

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
