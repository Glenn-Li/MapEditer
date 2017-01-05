
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

//#define DEFAULT_PATH _T("D:\\sgserver\\data-test\\351\\")
#define DEFAULT_PATH _T(".\\data\\")
#define DEFAULT_BIN_FILE _T("LEVEL351.BIN")
//#define DEFAULT_PATH _T("F:\\26-HCSG\\data\\")

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
	unsigned __int32 MapWigth;
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
	struct MonsterPropertie m_Propertie;  // 必须放在第一个字段
	CString m_Name;
	CString m_MapName;
	CString m_ShopName;
	CString m_NpcName;
	CString m_ResName;
};

#define MONSERT_BASE		_T("基本")
#define MONSTER_ID			_T("ID")
#define MONSTER_ID_D		_T("ID")
#define MONSTER_POS_X		_T("X坐标")
#define MONSTER_POS_X_D		_T("X坐标")
#define MONSTER_POS_Y		_T("Y坐标")
#define MONSTER_POS_Y_D		_T("Y坐标")

#define MONSTER_TRANSFER		_T("传送")
#define MONSTER_TRANS_MAP_ID	_T("传送到地图ID")
#define MONSTER_TRANS_MAP_ID_D	_T("传送到地图ID")
#define MONSTER_TRANS_MAP_X		_T("传送X坐标")
#define MONSTER_TRANS_MAP_X_D	_T("传送X坐标")
#define MONSTER_TRANS_MAP_Y		_T("传送Y坐标")
#define MONSTER_TRANS_MAP_Y_D	_T("传送Y坐标")

#define MONSTER_TRANS_SHOP_ID	_T("商店传送ID")
#define MONSTER_TRANS_SHOP_ID_D	_T("商店传送ID")

#define MONSTER_NPC				_T("NPC")
#define MONSTER_NPC_ID			_T("NPC ID")
#define MONSTER_NPC_ID_D		_T("NPC ID")
#define MONSTER_RES_ID			_T("资源ID")
#define MONSTER_RES_ID_D		_T("资源ID")

CString nTos(int n);

// 添加monster的时候用来和窗口进行数据交互

extern struct MonsterInfo m_AddMonsterInfo;

void GetAddMonsterInfo(struct MonsterInfo* m_MonsterInfo);
void SetAddMonsterInfo(struct MonsterInfo* m_MonsterInfo);