
#pragma once

#include "stdafx.h"

#define WM_OPENDOC				(WM_USER+100)


/* 地图各种缩放显示比例 */
/* 以下兩項相乘要等於64 */
#define MAP_SIZE_RATIO	16
#define MONSTER_POS_RATIO	4
/* 以下的看的舒服就行 */
#define GRID_CELL_SIZE	16
#define MONSTER_SIZE	32
#define ID_POS			8

#define DEFAULT_PATH _T("F:\\Game\\三国-本地测试\\data\\")

#pragma pack(1)
struct MonsterPropertie
{
	unsigned __int32 Flag;
	unsigned __int16 Id;	// 对应shp中的造型id
	unsigned __int16 Type;	// 暂时认为是类型吧
	__int32 X;
	__int32 Y;
	char unknow0[68]; // 空值
	unsigned __int32 ToMapId;
	unsigned __int32 ToMapX;
	unsigned __int32 ToMapY;
	unsigned __int32 ToShop;
	char unknow1[44]; // 空值
	unsigned __int32 NpcTalkId;
	unsigned __int32 ResNameId;
	char unknow2[56]; // 空值
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
	CPoint m_TextPoint;		// Id 号的显示位置
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