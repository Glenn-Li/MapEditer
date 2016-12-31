
// MapEditerDoc.cpp : CMapEditerDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MapEditer.h"
#endif

#include "comlib.h"
#include "MapEditerDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMapEditerDoc

IMPLEMENT_DYNCREATE(CMapEditerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEditerDoc, CDocument)
	//ON_MESSAGE(WM_OPENDOC, OnOpenNewDoc)
END_MESSAGE_MAP()


// CMapEditerDoc ����/����

CMapEditerDoc::CMapEditerDoc()
{
	// TODO:  �ڴ����һ���Թ������
	MapFileFolder = ".\\data\\";
	MapFileName = "LEVEL001.BIN";
	PosSel = NULL;
}

CMapEditerDoc::~CMapEditerDoc()
{
}

BOOL CMapEditerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	MapLength = GetMapLength() * 16;
	MapHeigth = 55 * 16;

	GetMonstersInfo();

	return TRUE;
}

// CMapEditerDoc ���л�

void CMapEditerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMapEditerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMapEditerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMapEditerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMapEditerDoc ���

#ifdef _DEBUG
void CMapEditerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapEditerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

int CMapEditerDoc::GetMapLength()
{
	CString strPathName;
	struct MapWrdHead sMapWrdHead;
	int MapLength = 0;
	int ret = 0;

	strPathName = MapFileFolder + MapFileName;
	strPathName.Replace(_T(".BIN"), _T(".WRD"));
	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		AfxMessageBox(_T("WRD�ļ������ڣ�"));
		return 0;
	}

	CFile iFile(strPathName, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);
	CArchive iar(&iFile, CArchive::load);

	ret = sizeof(sMapWrdHead);
	ret = iar.Read(&sMapWrdHead, sizeof(sMapWrdHead));
	if (ret > 0)
		MapLength = sMapWrdHead.MapLength;

	iar.Close();
	iFile.Close();

	return MapLength;
}


void CMapEditerDoc::GetMonstersInfo()
{
	CString strPathName;
	struct MonsterInfo TmpMonsterInfo;
	char Head[16];
	int ret = 0;

	LMonsterInfo.RemoveAll();

	//����ļ��Ƿ����
	strPathName = MapFileFolder + MapFileName;
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		AfxMessageBox(MapFileName + " �ļ������ڣ�");
		return;
	}

	CFile iFile(strPathName, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);
	CArchive iar(&iFile, CArchive::load);

	ret = sizeof(TmpMonsterInfo);
	ret = iar.Read(Head, sizeof(Head));
	for (; ret > 0;)
	{
		ret = iar.Read(&TmpMonsterInfo, sizeof(TmpMonsterInfo));
		if (ret <= 0) break;

		if (TmpMonsterInfo.Flag == 0)
		{
			LMonsterInfo.AddTail(TmpMonsterInfo);
			//TRACE("X-%d,Y-%d\n", TmpMonsterInfo.X, TmpMonsterInfo.Y);
		}
	}

//	LMonsterInfo.sort();

	iar.Close();
	iFile.Close();
}

// CMapEditerDoc ����

void CMapEditerDoc::OnOpenNewDoc(CString strFileName)
{
	MapFileName = strFileName;

	MapLength = GetMapLength() * MAP_SIZE_RATIO;
	MapHeigth = 55 * MAP_SIZE_RATIO;

	GetMonstersInfo();

	UpdateAllViews(NULL);
}

void CMapEditerDoc::UpdatePropertiesView(POSITION pos)
{
	PosSel = pos;
}

BOOL CMapEditerDoc::GetMonstersRect(CPoint point, POSITION* pos)
{
	struct MonsterInfo TmpMonsterInfo;

	*pos = LMonsterInfo.GetHeadPosition();

	for (int i = 0; i < LMonsterInfo.GetCount(); i++)
	{
		TmpMonsterInfo = LMonsterInfo.GetNext(*pos);

		int X = (int)(TmpMonsterInfo.X / GRID_CELL_SIZE);
		int Y = (int)(TmpMonsterInfo.Y / GRID_CELL_SIZE);

		if (point.x >= X && point.x <= X + MONSTER_SIZE
			&& point.y >= Y && point.y <= Y + MONSTER_SIZE)
		{
			return TRUE;
		}
	}

	return FALSE;
}
