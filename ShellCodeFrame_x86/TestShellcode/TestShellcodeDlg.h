
// TestShellcodeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTestShellcodeDlg �Ի���
class CTestShellcodeDlg : public CDialog
{
// ����
public:
	CTestShellcodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTSHELLCODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_reditShellcode;
	CEdit m_editProcessId;
	afx_msg void OnBnClickedButtonInject();
	afx_msg void OnBnClickedButtonShell();
	CEdit m_txtApiName;
	CEdit m_txtHashValue;
	afx_msg void OnBnClickedButtonCalchash();
	afx_msg void OnBnClickedButtonInjectDll();
	CEdit m_txtDllPath;
	afx_msg void OnBnClickedButtonLoadDll();
};
