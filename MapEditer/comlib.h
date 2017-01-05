
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

//#define DEFAULT_PATH _T("D:\\sgserver\\data-test\\351\\")
#define DEFAULT_PATH _T(".\\data\\")
#define DEFAULT_BIN_FILE _T("LEVEL351.BIN")
//#define DEFAULT_PATH _T("F:\\26-HCSG\\data\\")

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
	CPoint m_TextPoint;		// Id �ŵ���ʾλ��
};

struct MonsterInfo
{
	struct MonsterPropertie m_Propertie;  // ������ڵ�һ���ֶ�
	CString m_Name;
	CString m_MapName;
	CString m_ShopName;
	CString m_NpcName;
	CString m_ResName;
};

#define MONSERT_BASE		_T("����")
#define MONSTER_ID			_T("ID")
#define MONSTER_ID_D		_T("ID")
#define MONSTER_POS_X		_T("X����")
#define MONSTER_POS_X_D		_T("X����")
#define MONSTER_POS_Y		_T("Y����")
#define MONSTER_POS_Y_D		_T("Y����")

#define MONSTER_TRANSFER		_T("����")
#define MONSTER_TRANS_MAP_ID	_T("���͵���ͼID")
#define MONSTER_TRANS_MAP_ID_D	_T("���͵���ͼID")
#define MONSTER_TRANS_MAP_X		_T("����X����")
#define MONSTER_TRANS_MAP_X_D	_T("����X����")
#define MONSTER_TRANS_MAP_Y		_T("����Y����")
#define MONSTER_TRANS_MAP_Y_D	_T("����Y����")

#define MONSTER_TRANS_SHOP_ID	_T("�̵괫��ID")
#define MONSTER_TRANS_SHOP_ID_D	_T("�̵괫��ID")

#define MONSTER_NPC				_T("NPC")
#define MONSTER_NPC_ID			_T("NPC ID")
#define MONSTER_NPC_ID_D		_T("NPC ID")
#define MONSTER_RES_ID			_T("��ԴID")
#define MONSTER_RES_ID_D		_T("��ԴID")

CString nTos(int n);

// ���monster��ʱ�������ʹ��ڽ������ݽ���

extern struct MonsterInfo m_AddMonsterInfo;

void GetAddMonsterInfo(struct MonsterInfo* m_MonsterInfo);
void SetAddMonsterInfo(struct MonsterInfo* m_MonsterInfo);