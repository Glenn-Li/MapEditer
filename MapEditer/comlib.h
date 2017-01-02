
#pragma once

#include "stdafx.h"

#define WM_OPENDOC				(WM_USER+100)


/* ��ͼ����������ʾ���� */
/* ��������Ҫ���64 */
#define MAP_SIZE_RATIO	16
#define MONSTER_POS_RATIO	4
/* ���µĿ���������� */
#define GRID_CELL_SIZE	16
#define MONSTER_SIZE	32
#define ID_POS			8

#define DEFAULT_PATH _T("F:\\Game\\����-���ز���\\data\\")

#pragma pack(1)
struct MonsterPropertie
{
	unsigned __int32 Flag;
	unsigned __int16 Id;	// ��Ӧshp�е�����id
	unsigned __int16 Type;	// ��ʱ��Ϊ�����Ͱ�
	__int32 X;
	__int32 Y;
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

#pragma pack(1)
struct MapBinHead
{
	unsigned __int32 Flag;
	unsigned __int32 MonsterCount;
	unsigned __int32 A1;
	unsigned __int32 A2;
};
#pragma pack()

struct MonsterBlock
{
	COLORREF m_PenColor;
	int m_PenWidth;
	COLORREF m_BrushColor;
	COLORREF m_TextColor;
	CRect m_CRect;
	CPoint m_TextPoint;		// Id �ŵ���ʾλ��
};

struct MonsterInfo
{
	struct MonsterPropertie m_Propertie;
	CString m_Name;
	CString m_MapName;
	CString m_ShopName;
	CString m_NpcName;
	CString m_ResName;
};

CString nTos(int n);