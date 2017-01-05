#pragma once
#include "afxwin.h"

#include "comlib.h"

// CDlgAddMonster 对话框

class CDlgAddMonster : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddMonster)

public:
	CDlgAddMonster(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddMonster();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADD_MONSTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_CEditID;
	CEdit m_CEditX;
	CEdit m_CEditY;
	virtual BOOL OnInitDialog();
};
