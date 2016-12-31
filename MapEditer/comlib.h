
#pragma once

#include "stdafx.h"

#define WM_OPENDOC				(WM_USER+100)


/* 地图各种缩放显示比例 */
#define MAP_SIZE_RATIO	16
#define GRID_CELL_SIZE	4
#define MONSTER_SIZE	32
#define ID_POS			8

#pragma pack(1)
struct MonsterInfo
{
	unsigned __int32 Flag;
	unsigned __int16 Id;	// 对应shp中的造型id
	unsigned __int16 Type;	// 暂时认为是类型吧
	unsigned __int32 X;
	unsigned __int32 Y;
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

CString nTos(int n);