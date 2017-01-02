
// MapEditerDoc.cpp : CMapEditerDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MapEditer.h"
#endif

#include "comlib.h"
#include "MapEditerDoc.h"

#include <propkey.h>

#include <stdio.h>
#include <stdlib.h>
#include <share.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMapEditerDoc

IMPLEMENT_DYNCREATE(CMapEditerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapEditerDoc, CDocument)
	//ON_MESSAGE(WM_OPENDOC, OnOpenNewDoc)
END_MESSAGE_MAP()


// CMapEditerDoc 构造/析构

CMapEditerDoc::CMapEditerDoc()
{
	// TODO:  在此添加一次性构造代码
	//MapFileFolder = ".\\data\\";
	MapFileFolder = "F:\\Game\\三国-本地测试\\data\\";
	MapFileName = "LEVEL517.BIN";
	PosSel = NULL;

	memset(m_MonsterInfoSel, 0, sizeof(m_MonsterInfoSel));
}

CMapEditerDoc::~CMapEditerDoc()
{
}

BOOL CMapEditerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	MapLength = GetMapLength() * MAP_SIZE_RATIO;
	MapHeigth = 55 * MAP_SIZE_RATIO;

	GetMonstersInfo();

	return TRUE;
}

// CMapEditerDoc 序列化

void CMapEditerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		struct MonsterInfo TmpMonsterInfo;
		// 写入头
		ar.Write((void*)&m_MapBinHead, sizeof(m_MapBinHead));

		// 写入主体
		POSITION pos;
		pos = LMonsterInfo.GetHeadPosition();
		for (int i = 0; i < LMonsterInfo.GetCount(); i++)
		{
			TmpMonsterInfo = LMonsterInfo.GetNext(pos);
			struct MonsterPropertie* pMonsterPropertie = &TmpMonsterInfo.m_Propertie;

			ar.Write((void *)pMonsterPropertie, sizeof(struct MonsterPropertie));
		}	

		// 写入末尾数据
		ar.Write(MapFileEnd, MapFileEndSize);
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMapEditerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CMapEditerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CMapEditerDoc 诊断

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
	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		AfxMessageBox(_T("WRD文件不存在！"));
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

int CMapEditerDoc::GetMonsterCount()
{
	CString strPathName;
	int MapLength = 0;
	int ret = 0;

	strPathName = MapFileFolder + MapFileName;
	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		AfxMessageBox(_T("WRD文件不存在！"));
		return 0;
	}

	CFile iFile(strPathName, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);
	CArchive iar(&iFile, CArchive::load);

	ret = sizeof(m_MapBinHead);
	ret = iar.Read(&m_MapBinHead, sizeof(m_MapBinHead));
	if (ret > 0)
		MonstersCount = m_MapBinHead.MonsterCount;

	iar.Close();
	iFile.Close();

	return MonstersCount;
}

void CMapEditerDoc::MonstersAnalysis()
{
// 	POSITION pos, posPrev;
// 	// 排序
// 	pos = LMonsterInfo.GetHeadPosition();
// 	posPrev = pos;
// 	for (size_t i = 0; i < LMonsterInfo.GetCount(); i++)
// 	{
// 
// 		for (size_t j = i; i < LMonsterInfo.GetCount(); j++)
// 		{
// 			// 先比较Y坐标
// 			if ()
// 		}
// 	}
}


void CMapEditerDoc::GetMonstersInfo()
{
	CString strPathName;
	struct MonsterInfo TmpMonsterInfo;
	struct MonsterPropertie* TmpMonsterPropertie = &TmpMonsterInfo.m_Propertie;
	int ret = 0;

	LMonsterInfo.RemoveAll();

	//检查文件是否存在
	strPathName = MapFileFolder + MapFileName;
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		AfxMessageBox(MapFileName + " 文件不存在！");
		return;
	}

	CFile iFile(strPathName, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);
	CArchive iar(&iFile, CArchive::load);

	ret = sizeof(struct MonsterPropertie);
	MonstersCounter = 0;
	memset(&m_MapBinHead, 0, sizeof(m_MapBinHead));
	memset(MapFileEnd, 0, sizeof(MapFileEnd));
	// 读取头
	ret = iar.Read(&m_MapBinHead, sizeof(m_MapBinHead));

	// 读取怪物分布信息
	for (; ret > 0;)
	{
		ret = iar.Read(TmpMonsterPropertie, sizeof(struct MonsterPropertie));
		TRACE("ID-%u(%u, %u)\n", TmpMonsterPropertie->Id, TmpMonsterPropertie->X, TmpMonsterPropertie->Y);
		if (ret <= 0) break;

		if (TmpMonsterPropertie->Flag == 0)
		{
			// 按升序插入
			if (LMonsterInfo.GetCount() == 0)
			{
				LMonsterInfo.AddTail(TmpMonsterInfo);
			}
			else
			{
				POSITION pos, posPrev;
				int i;
				pos = LMonsterInfo.GetHeadPosition();
				for (i = 0; i < LMonsterInfo.GetCount(); i++)
				{
					posPrev = pos;
					struct MonsterInfo m_MonsterInfo = LMonsterInfo.GetNext(pos);
					struct MonsterPropertie* pMonsterPropertie = &m_MonsterInfo.m_Propertie;

					// 先比较Y坐标
					if (pMonsterPropertie->Y > TmpMonsterPropertie->Y)
					{
						LMonsterInfo.InsertBefore(posPrev,TmpMonsterInfo);
						break;
					}
					else if (pMonsterPropertie->Y == TmpMonsterPropertie->Y)  // 如果Y坐标相等就再比较X坐标
					{
						if (pMonsterPropertie->X >= TmpMonsterPropertie->X)
						{
							LMonsterInfo.InsertBefore(posPrev, TmpMonsterInfo);
							break;
						}
					}
				}

				// 说明没有找到比这个坐标更小的坐标了，就插到最后
				if (i >= LMonsterInfo.GetCount())
				{
					LMonsterInfo.AddTail(TmpMonsterInfo);
				}
			}
			
			MonstersCounter++;
			//TRACE("X-%d,Y-%d\n", TmpMonsterInfo.X, TmpMonsterInfo.Y);
		}
		else
		{
			// 说明读取到的是尾部信息
			memcpy_s(MapFileEnd, sizeof(MapFileEnd), (void *)TmpMonsterPropertie, sizeof(struct MonsterPropertie));
			MapFileEndSize = sizeof(struct MonsterPropertie);
			break;
		}
	}
	// 读取剩余的尾部数据
	for (; ret > 0;)
	{
		unsigned char cTmp;
		ret = iar.Read(&cTmp, 1);
		if (ret <= 0) break;
		
		MapFileEnd[MapFileEndSize++] = cTmp;
	}

	iar.Close();
	iFile.Close();

	// 填充名称，排序
	MonstersAnalysis();
}

void CMapEditerDoc::SaveMonstersInfo()
{
	
}

// CMapEditerDoc 命令

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
	PosSelPrev = pos;
}

BOOL CMapEditerDoc::GetMonstersRect(CPoint point, POSITION* pos, struct MonsterPropertie** pMonsterPropertie)
{
// 	struct MonsterInfo TmpMonsterInfo;
// 	struct MonsterPropertie* pTmpMonsterPropertie = &TmpMonsterInfo.m_Propertie;

	POSITION tmpPos, PosPrev;
	tmpPos = LMonsterInfo.GetHeadPosition();

	for (int i = 0; i < LMonsterInfo.GetCount(); i++)
	{
		PosPrev = tmpPos;
		*pMonsterPropertie = &LMonsterInfo.GetNext(tmpPos).m_Propertie;

		int X = (int)((*pMonsterPropertie)->X / MONSTER_POS_RATIO);
		int Y = (int)((*pMonsterPropertie)->Y / MONSTER_POS_RATIO);

		if (point.x >= X && point.x <= X + MONSTER_SIZE
			&& point.y >= Y && point.y <= Y + MONSTER_SIZE)
		{
			*pos = PosPrev;
			m_MonsterInfoSel[0] = PosPrev;
			return TRUE;
		}
	}

	m_MonsterInfoSel[0] = NULL;
	*pMonsterPropertie = NULL;
	return FALSE;
}

BOOL CMapEditerDoc::MonsterInfoCompare(struct MonsterInfo* pSrc, struct MonsterInfo* pSrc1)
{
	if (pSrc->m_Propertie.Id == pSrc1->m_Propertie.Id
		&& pSrc->m_Propertie.X == pSrc1->m_Propertie.X
		&& pSrc->m_Propertie.Y == pSrc1->m_Propertie.Y)
	{
		return TRUE;
	}

	return FALSE;
}

void CMapEditerDoc::CreatMonsterRect(struct MonsterInfo* pMonsterInfo, struct MonsterBlock* pMonsterBlock)
{
	struct MonsterInfo TmpMonsterInfo;
	struct MonsterPropertie* pMonsterPropertie = &pMonsterInfo->m_Propertie;
	pMonsterBlock->m_TextColor = RGB(0, 0, 0);
	pMonsterBlock->m_PenColor = RGB(255, 0, 255);
	pMonsterBlock->m_PenWidth = 1;

	POSITION tmpPos = m_MonsterInfoSel[0];
	if (LMonsterInfo.GetCount() > 0 && tmpPos != NULL)
	{
		TmpMonsterInfo = LMonsterInfo.GetNext(tmpPos);
		if (MonsterInfoCompare(&TmpMonsterInfo, pMonsterInfo))
		{
			pMonsterBlock->m_PenColor = RGB(0, 255, 0);
			pMonsterBlock->m_PenWidth = 2;
		}
	}
		

	unsigned __int8 rgb = (unsigned __int8)pMonsterPropertie->Id;
	pMonsterBlock->m_BrushColor = RGB(rgb, rgb, rgb);

	int X = (int)(pMonsterPropertie->X / MONSTER_POS_RATIO);
	int Y = (int)(pMonsterPropertie->Y / MONSTER_POS_RATIO);

	pMonsterBlock->m_CRect = CRect(X, Y, X + MONSTER_SIZE, Y + MONSTER_SIZE);
	pMonsterBlock->m_TextPoint.x = X + ID_POS;
	pMonsterBlock->m_TextPoint.y = Y;
}
