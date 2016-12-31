
#pragma once

#include "stdafx.h"

#define WM_OPENDOC				(WM_USER+100)


/* ��ͼ����������ʾ���� */
#define MAP_SIZE_RATIO	16
#define GRID_CELL_SIZE	4
#define MONSTER_SIZE	32
#define ID_POS			8

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

CString nTos(int n);