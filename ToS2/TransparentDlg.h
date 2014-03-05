#pragma once


// CTransparentDlg 對話方塊

class CTransparentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTransparentDlg)

public:
	CTransparentDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CTransparentDlg();

// 對話方塊資料
	enum { IDD = IDD_TRANSPARENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
