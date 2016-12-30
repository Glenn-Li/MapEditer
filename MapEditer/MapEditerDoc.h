
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
	CString MapFileName;
	int MapLength;
	int MapHeigth;
	CList <MonsterInfo, MonsterInfo&> LMonsterInfo;

// ����
public:
	int GetMapLength();
	void GetMonstersInfo();
	afx_msg LRESULT OnOpenNewDoc(WPARAM wParam, LPARAM lParam);

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
