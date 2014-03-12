
// ToS2Dlg.h : 標頭檔
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define SERVER_PORT			7052

#define COLUMN	6
#define ROW		5

#define SINGLE_MOVE_DIRECTION	8
#define SINGLE_MOVE_MAX_STEP	6
#define SINGLE_MOVE_MAX_SHORT_STEP	3
#define SINGLE_MOVE_MAX_SMOOTH_STEP	250
#define SINGLE_MOVE_MAX_2S_SMOOTH_STEP	105
#define SINGLE_MOVE_MAX_SEARCH	13
#define SINGLE_MOVE_MAX_2S_SEARCH	5

#define MULTI_MOVE_DIRECTION	18
#define MULTI_MOVE_MAX_STEP		7
#define MULTI_MOVE_MAX_SHORT_STEP	3
#define MULTI_MOVE_MAX_SMOOTH_STEP	240
#define MULTI_MOVE_MAX_2S_SMOOTH_STEP	90
#define MULTI_MOVE_MAX_SEARCH	7
#define MULTI_MOVE_MAX_2S_SEARCH	2

#define SINGLE_MOVE_MAX_PATH_COUNT	70000
#define MULTI_MOVE_MAX_PATH_COUNT	100000

#define MAX_SHORT_PATH_COUNT	8000
#define MAX_KEEP_COUNT		30
#define MAX_REAL_KEEP_COUNT	8
#define MAX				2147483647

#define MOUSE_SLEEP		170
#define INITIAL_SLEEP	250
#define RETRY_SLEEP		2000
#define SMOOTH_SLEEP	12

#define SHORT_MESSAGE	1024
#define MAX_MESSAGE		65536
#define MAX_DISPLAY_MESSAGE 1048576

#define GET_TABLE_INTERVAL	200
#define COLOR_DIFF			20

#define SCORE_OFFSET				(long long int) 10000000
#define MEET_PUZZLE_SCORE			(long long int) 10000000000000000
#define PARTIAL_MEET_PUZZLE_SCORE	(long long int) 10000000000000
#define ELIMINATE_STOP_SCORE		(long long int) 100000000000000000

// CToS2Dlg 對話方塊
class CToS2Dlg : public CDialogEx
{
// 建構
public:
	CToS2Dlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_TOS2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit DisplayEdit;
	afx_msg void OnBnClickedOk();
	int ComboLimit;
	BOOL CheckNeedHighPower;
	BOOL CheckNeedEliminateSix;
	BOOL CheckNeedTwoSecond;
	BOOL CheckEmulateHuman;
	BOOL CheckPause;
	CComboBox ComboExecutionType;
	afx_msg void OnSelchangeComboType();
	BOOL CheckRealMouse;
	CButton ButtonOK;
	BOOL CheckNoOblique;
	DWORD ServerIP;
	CIPAddressCtrl ServerIPControl;
	int MinWaterKeep;
	int MinFireKeep;
	int MinWoodKeep;
	int MinLightKeep;
	int MinDarkKeep;
	int MinHeartKeep;
	int MaxWaterEliminate;
	int MaxFireEliminate;
	int MaxWoodEliminate;
	int MaxLightEliminate;
	int MaxDarkEliminate;
	int MaxHeartEliminate;
	BOOL CheckCountWaterScore;
	BOOL CheckCountFireScore;
	BOOL CheckCountWoodScore;
	BOOL CheckCountLightScore;
	BOOL CheckCountDarkScore;
	BOOL CheckCountHeartScore;
	afx_msg void OnBnClickedButtonDefault();
	BOOL CheckForceKeep;
	BOOL CheckPreview;
	int EditLowerBoundCombo;
	BOOL CheckDynamicStop;
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
};
