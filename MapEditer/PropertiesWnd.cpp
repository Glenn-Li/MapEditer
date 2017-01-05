
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MapEditer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

CMapEditerDoc* CPropertiesWnd::GetDocument()
{
	CMainFrame *frm = (CMainFrame*)::AfxGetMainWnd();
	ASSERT(frm);
	CDocument *pDoc = frm->GetActiveDocument();
	ASSERT(pDoc);
	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CMapEditerDoc)));

	return (CMapEditerDoc*)pDoc;
}


void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建组合: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;      // 未能创建
	}

	//m_wndObjectCombo.AddString(_T("应用程序"));
	m_wndObjectCombo.AddString(_T("Monster属性"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* pCmdUI)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	CMapEditerDoc *pDoc = GetDocument();
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());

	/* 此处会不停的刷新，从这里读取当前选中的monster，把属性更新显示，不好，存在问题 */
	if (!pDoc->PosSel)
		return;

	MonsterInfo m_MonsterInfo = pDoc->LMonsterInfo.GetNext(pDoc->PosSel);

	UpdatePropList(&m_MonsterInfo);

	pDoc->PosSel = NULL;
}

void CPropertiesWnd::OnProperties1()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* pCmdUI)
{
	// TODO:  在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO:  在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();
	CMFCPropertyGridProperty* pProp;

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	pGroupBase = new CMFCPropertyGridProperty(MONSERT_BASE);

	pGroupBase->AddSubItem(new CMFCPropertyGridProperty(MONSTER_ID, (_variant_t)250l, MONSTER_ID_D));
	pGroupBase->AddSubItem(new CMFCPropertyGridProperty(MONSTER_POS_X, (_variant_t)0l, MONSTER_POS_X_D));
	pGroupBase->AddSubItem(new CMFCPropertyGridProperty(MONSTER_POS_Y, (_variant_t)0l, MONSTER_POS_Y_D));

// 	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("边框"), _T("对话框外框"), _T("其中之一: “无”、“细”、“可调整大小”或“对话框外框”"));
// 	pProp->AddOption(_T("无"));
// 	pProp->AddOption(_T("细"));
// 	pProp->AddOption(_T("可调整大小"));
// 	pProp->AddOption(_T("对话框外框"));
// 	pProp->AllowEdit(FALSE);
// 
// 	pGroup1->AddSubItem(pProp);
// 	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("标题"), (_variant_t) _T("关于"), _T("指定窗口标题栏中显示的文本")));

	m_wndPropList.AddProperty(pGroupBase);

	pGroupToMap = new CMFCPropertyGridProperty(MONSTER_TRANSFER, 0, FALSE);

	pProp = new CMFCPropertyGridProperty(MONSTER_TRANS_MAP_ID, (_variant_t)1l, MONSTER_TRANS_MAP_ID_D);
	//pProp->EnableSpinControl(TRUE, 50, 300);
	pGroupToMap->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(MONSTER_TRANS_MAP_X, (_variant_t)0l, MONSTER_TRANS_MAP_X_D);
	pProp->EnableSpinControl(TRUE, 0, 55);
	pGroupToMap->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(MONSTER_TRANS_MAP_Y, (_variant_t)0l, MONSTER_TRANS_MAP_Y_D);
	pProp->EnableSpinControl(TRUE, 0, 1000);
	pGroupToMap->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(MONSTER_TRANS_SHOP_ID, (_variant_t)0l, MONSTER_TRANS_SHOP_ID_D);
	//pProp->EnableSpinControl(TRUE, 50, 200);
	pGroupToMap->AddSubItem(pProp);

	m_wndPropList.AddProperty(pGroupToMap);


	pGroupNPC = new CMFCPropertyGridProperty(MONSTER_NPC, 0, FALSE);

	pProp = new CMFCPropertyGridProperty(MONSTER_NPC_ID, (_variant_t)1l, MONSTER_NPC_ID_D);
	//pProp->EnableSpinControl(TRUE, 50, 300);
	pGroupNPC->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(MONSTER_RES_ID, (_variant_t)0l, MONSTER_RES_ID_D);
	pProp->EnableSpinControl(TRUE, 0, 55);
	pGroupNPC->AddSubItem(pProp);

	m_wndPropList.AddProperty(pGroupNPC);

	/*
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("传送"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	lstrcpy(lf.lfFaceName, _T("宋体, Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("字体"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("指定窗口的默认字体")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("使用系统字体"), (_variant_t) true, _T("指定窗口使用“MS Shell Dlg”字体")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("杂项"));
	pProp = new CMFCPropertyGridProperty(_T("(名称)"), _T("应用程序"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("窗口颜色"), RGB(210, 192, 254), NULL, _T("指定默认的窗口颜色"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("图标文件(*.ico)|*.ico|所有文件(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("图标"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("指定窗口图标")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("文件夹"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("层次结构"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("第一个子级"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("第二个子级"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 1"), (_variant_t) _T("值 1"), _T("此为说明")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 2"), (_variant_t) _T("值 2"), _T("此为说明")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 3"), (_variant_t) _T("值 3"), _T("此为说明")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);

	*/
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

LRESULT CPropertiesWnd::OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam)
{
	TRACE(_T("PropertyChanged\n"));
	CMFCPropertyGridProperty* pProperty = (CMFCPropertyGridProperty*) lparam;
	CMapEditerDoc *pDoc = GetDocument();

	if (!pDoc->PosSelPrev)
		return 0;

	POSITION tmpPos = pDoc->PosSelPrev;
	MonsterInfo m_MonsterInfo = pDoc->LMonsterInfo.GetNext(tmpPos);
	struct MonsterPropertie* pMonsterPropertie = &m_MonsterInfo.m_Propertie;

	CString strName = pProperty->GetName();

	if (strName == MONSTER_ID)
	{
		pMonsterPropertie->Id = pProperty->GetValue().iVal;
	}
	else if (strName == MONSTER_POS_X)
	{
		pMonsterPropertie->X = pProperty->GetValue().iVal;
	}
	else if (strName == MONSTER_POS_Y)
	{
		pMonsterPropertie->Y = pProperty->GetValue().iVal;
	}
	else if (strName == MONSTER_TRANS_MAP_ID)
	{
		pMonsterPropertie->ToMapId = pProperty->GetValue().iVal;
	}
	else if (strName == MONSTER_TRANS_MAP_X)
	{
		pMonsterPropertie->ToMapX = pProperty->GetValue().iVal;
	}
	else if (strName == MONSTER_TRANS_MAP_Y)
	{
		pMonsterPropertie->ToMapY = pProperty->GetValue().iVal;
	}
	else if (strName == MONSTER_TRANS_SHOP_ID)
	{
		pMonsterPropertie->ToShop = pProperty->GetValue().iVal;
	}
	else if (strName == MONSTER_NPC_ID)
	{
		pMonsterPropertie->NpcTalkId = pProperty->GetValue().iVal;
	}
	else if (strName == MONSTER_RES_ID)
	{
		pMonsterPropertie->ResNameId = pProperty->GetValue().iVal;
	}

	pDoc->LMonsterInfo.SetAt(pDoc->PosSelPrev, m_MonsterInfo);

	pDoc->OnUpdateViews();
	return 0;
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}


void CPropertiesWnd::UpdatePropList(struct MonsterInfo *pMonsterInfo)
{
/*	CMFCPropertyGridProperty* pProp;*/
	struct MonsterPropertie* pMonsterPropertie = &pMonsterInfo->m_Propertie;

	pGroupBase->GetSubItem(0)->SetValue((_variant_t)(long)pMonsterPropertie->Id);
	pGroupBase->GetSubItem(1)->SetValue((_variant_t)(long)pMonsterPropertie->X);
	pGroupBase->GetSubItem(2)->SetValue((_variant_t)(long)pMonsterPropertie->Y);


	pGroupToMap->GetSubItem(0)->SetValue((_variant_t)(long)pMonsterPropertie->ToMapId);
	pGroupToMap->GetSubItem(1)->SetValue((_variant_t)(long)pMonsterPropertie->ToMapX);
	pGroupToMap->GetSubItem(2)->SetValue((_variant_t)(long)pMonsterPropertie->ToMapY);
	pGroupToMap->GetSubItem(3)->SetValue((_variant_t)(long)pMonsterPropertie->ToShop);

	pGroupNPC->GetSubItem(0)->SetValue((_variant_t)(long)pMonsterPropertie->NpcTalkId);
	pGroupNPC->GetSubItem(1)->SetValue((_variant_t)(long)pMonsterPropertie->ResNameId);
}
