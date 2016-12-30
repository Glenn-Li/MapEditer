
// MapEditerView.cpp : CMapEditerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MapEditer.h"
#endif

#include "MapEditerDoc.h"
#include "MapEditerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditerView

IMPLEMENT_DYNCREATE(CMapEditerView, CScrollView)

BEGIN_MESSAGE_MAP(CMapEditerView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

#pragma pack(1)
struct MonsterInfo
{
	unsigned __int32 Flag;
	unsigned __int16 Id;	// ��Ӧshp�е�����id
	unsigned __int16 Type;	// ��ʱ��Ϊ�����Ͱ�
	unsigned __int32 X;
	unsigned __int32 Y;
	char unknow0[68]; // ��ֵ
	unsigned __int32 ToMapId;
	unsigned __int32 ToMapX;
	unsigned __int32 ToMapY;
	unsigned __int32 ToShop;
	char unknow1[44]; // ��ֵ
	unsigned __int32 NpcTalkId;
	unsigned __int32 ResNameId;
	char unknow2[56]; // ��ֵ
};
#pragma pack()

#pragma pack(1)
struct MapWrdHead
{
	unsigned __int32 A0;
	unsigned __int32 A1;
	unsigned __int32 A2;
	unsigned __int32 MapLength;
};
#pragma pack()

CList <MonsterInfo, MonsterInfo&> LMonsterInfo;

int GetMapLength()
{
	CString strPathName;
	struct MapWrdHead sMapWrdHead;
	int MapLength = 0;
	int ret = 0;

	strPathName = ".\\data\\LEVEL001.WRD";
	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		AfxMessageBox(strPathName + " �ļ������ڣ�");
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


void GetMonstersInfo()
{
	CString strPathName;
	struct MonsterInfo TmpMonsterInfo;
	char Head[16];
	int ret = 0;

	LMonsterInfo.RemoveAll();

	strPathName = ".\\data\\LEVEL001.BIN";
	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		AfxMessageBox(strPathName + " �ļ������ڣ�");
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

	iar.Close();
	iFile.Close();
}

CString nTos(int n)
{
	static CString str = _T("");
	if (n < 10)
	{
		str = (char)(n % 10 + '0');
		return str;
	}
	else
	{
		str = nTos(n / 10) + (char)(n % 10 + '0');
		return str;
	}
}

// CMapEditerView ����/����

CMapEditerView::CMapEditerView()
{
	// TODO:  �ڴ˴���ӹ������
	MapLength = GetMapLength() * 8;
	MapHeigth = 55 * 8;

}

CMapEditerView::~CMapEditerView()
{
}

BOOL CMapEditerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CMapEditerView ����

void CMapEditerView::OnDraw(CDC* pDC)
{
	CMapEditerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	DrawGrid(pDC);
	
	GetMonstersInfo();

	DisplayMonsterInfo(pDC);
}

void CMapEditerView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO:  �������ͼ�ĺϼƴ�С
	sizeTotal.cx = MapLength;
	sizeTotal.cy = MapHeigth;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CMapEditerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMapEditerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CMapEditerView ���

#ifdef _DEBUG
void CMapEditerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapEditerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMapEditerDoc* CMapEditerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapEditerDoc)));
	return (CMapEditerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapEditerView ��Ϣ�������


void CMapEditerView::DrawGrid(CDC* pDC)
{
	CPen pen;
	//CBrush brush;
	pen.CreatePen(PS_SOLID, 1, RGB(127, 127, 127));
	//brush.CreateSolidBrush(RGB(125, 125, 125));
	pDC->SelectObject(pen);
	//pDC->SelectObject(brush);
	for (int i = 0; i < MapHeigth; i += 8)
	{
		pDC->Rectangle(0, i, MapLength, i + 1);
	}
	for (int j = 0; j < MapLength; j += 8)
	{
		pDC->Rectangle(j, 0, j + 1, MapHeigth);
	}
	DeleteObject(pen);
	//DeleteObject(brush);
}

void CMapEditerView::DisplayMonsterInfo(CDC* pDC)
{
	POSITION pos;
	struct MonsterInfo TmpMonsterInfo;
	CString tmpStr;
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	pDC->SelectObject(pen);

	pos = LMonsterInfo.GetHeadPosition();
	for (int i = 0; i < LMonsterInfo.GetCount(); i++)
	{
		TmpMonsterInfo = LMonsterInfo.GetNext(pos);	
		unsigned __int8 rgb = (unsigned __int8)TmpMonsterInfo.Id;
		CBrush brush;
		brush.CreateSolidBrush(RGB(rgb, rgb, rgb));
		pDC->SelectObject(brush);
		int X = (int)(TmpMonsterInfo.X / 8);
		int Y = (int)(TmpMonsterInfo.Y / 8);

		pDC->Rectangle(X, Y, X+16, Y+16);
		DeleteObject(brush);
	}
	DeleteObject(pen);
}