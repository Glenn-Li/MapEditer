#pragma once
#include "afxwin.h"

#include "comlib.h"

// CDlgAddMonster �Ի���

class CDlgAddMonster : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddMonster)

public:
	CDlgAddMonster(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddMonster();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADD_MONSTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_CEditID;
	CEdit m_CEditX;
	CEdit m_CEditY;
	virtual BOOL OnInitDialog();
};
