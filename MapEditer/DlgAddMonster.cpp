// DlgAddMonster.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MapEditer.h"
#include "DlgAddMonster.h"
#include "afxdialogex.h"


// CDlgAddMonster �Ի���

IMPLEMENT_DYNAMIC(CDlgAddMonster, CDialogEx)

CDlgAddMonster::CDlgAddMonster(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAddMonster::IDD, pParent)
{

}

CDlgAddMonster::~CDlgAddMonster()
{
}

void CDlgAddMonster::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_CEditID);
	DDX_Control(pDX, IDC_EDIT_X, m_CEditX);
	DDX_Control(pDX, IDC_EDIT_Y, m_CEditY);
}


BEGIN_MESSAGE_MAP(CDlgAddMonster, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgAddMonster::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgAddMonster ��Ϣ�������


void CDlgAddMonster::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	struct MonsterInfo m_MonsterInfo = {0};
	//CString strValue = _T("");
// 
// 	m_CEditID.GetWindowText(strValue);
// 	m_MonsterInfo.m_Propertie.Id = _ttoi(strValue);
// 
// 	m_CEditX.GetWindowText(strValue);
// 	m_MonsterInfo.m_Propertie.X = _ttoi(strValue);
// 
// 	m_CEditY.GetWindowText(strValue);
// 	m_MonsterInfo.m_Propertie.Y = _ttoi(strValue);

	//SetAddMonsterInfo(&m_MonsterInfo);

	CDialogEx::OnOK();
}


BOOL CDlgAddMonster::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	struct MonsterInfo m_MonsterInfo;
	GetAddMonsterInfo(&m_MonsterInfo);
	if (m_MonsterInfo.m_Propertie.Id != 0)
	{
		m_CEditID.SetWindowTextW(nTos(m_MonsterInfo.m_Propertie.Id));
	}
	else
	{
		m_CEditID.SetWindowTextW(_T("0"));
	}

	if (m_MonsterInfo.m_Propertie.X != 0)
	{
		m_CEditID.SetWindowTextW(nTos(m_MonsterInfo.m_Propertie.X));
	}
	else
	{
		m_CEditX.SetWindowTextW(_T("0"));
	}

	if (m_MonsterInfo.m_Propertie.Y != 0)
	{
		m_CEditID.SetWindowTextW(nTos(m_MonsterInfo.m_Propertie.Y));
	}
	else
	{
		m_CEditY.SetWindowTextW(_T("0"));
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
