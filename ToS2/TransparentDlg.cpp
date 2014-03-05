// TransparentDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ToS2.h"
#include "TransparentDlg.h"
#include "afxdialogex.h"


// CTransparentDlg 對話方塊

IMPLEMENT_DYNAMIC(CTransparentDlg, CDialogEx)

CTransparentDlg::CTransparentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTransparentDlg::IDD, pParent)
{

}

CTransparentDlg::~CTransparentDlg()
{
}

void CTransparentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTransparentDlg, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CTransparentDlg 訊息處理常式


void CTransparentDlg::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	// CDialogEx::OnClose();
}
