
// ToS2Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ToS2.h"
#include "ToS2Dlg.h"
#include "TransparentDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CToS2Dlg 對話方塊

CToS2Dlg::CToS2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToS2Dlg::IDD, pParent)
	, ComboLimit(0)
	, CheckNeedHighPower(FALSE)
	, CheckNeedEliminateSix(FALSE)
	, CheckNeedTwoSecond(FALSE)
	, CheckEmulateHuman(TRUE)
	, CheckPause(FALSE)
	, CheckRealMouse(FALSE)
	, CheckNoOblique(TRUE)
	, ServerIP(0)
	, MinWaterKeep(-1)
	, MinFireKeep(-1)
	, MinWoodKeep(-1)
	, MinLightKeep(-1)
	, MinDarkKeep(-1)
	, MinHeartKeep(-1)
	, MaxWaterEliminate(-1)
	, MaxFireEliminate(-1)
	, MaxWoodEliminate(-1)
	, MaxLightEliminate(-1)
	, MaxDarkEliminate(-1)
	, MaxHeartEliminate(-1)
	, CheckCountWaterScore(TRUE)
	, CheckCountFireScore(TRUE)
	, CheckCountWoodScore(TRUE)
	, CheckCountLightScore(TRUE)
	, CheckCountDarkScore(TRUE)
	, CheckCountHeartScore(TRUE)
	, CheckForceKeep(FALSE)
	, CheckPreview(FALSE)
	, EditLowerBoundCombo(5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToS2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Display, DisplayEdit);
	DDX_Text(pDX, IDC_EDIT_Combo_Limit, ComboLimit);
	DDX_Check(pDX, IDC_CHECK_NeedHighPower, CheckNeedHighPower);
	DDX_Check(pDX, IDC_CHECK_Eliminate_Six, CheckNeedEliminateSix);
	DDX_Check(pDX, IDC_CHECK_Two_Second, CheckNeedTwoSecond);
	DDX_Check(pDX, IDC_CHECK_Emulate_Human, CheckEmulateHuman);
	DDX_Check(pDX, IDC_CHECK_Pause, CheckPause);
	DDX_Control(pDX, IDC_COMBO_Type, ComboExecutionType);
	DDX_Check(pDX, IDC_CHECK_Real_Mouse, CheckRealMouse);
	DDX_Control(pDX, IDOK, ButtonOK);
	DDX_Check(pDX, IDC_CHECK_No_Oblique, CheckNoOblique);
	DDX_IPAddress(pDX, IDC_IPADDRESS_Server_IP, ServerIP);
	DDX_Control(pDX, IDC_IPADDRESS_Server_IP, ServerIPControl);
	DDX_Text(pDX, IDC_EDIT_Min_Water_Keep, MinWaterKeep);
	DDX_Text(pDX, IDC_EDIT_Min_Fire_Keep, MinFireKeep);
	DDX_Text(pDX, IDC_EDIT_Min_Wood_Keep, MinWoodKeep);
	DDX_Text(pDX, IDC_EDIT_Min_Light_Keep, MinLightKeep);
	DDX_Text(pDX, IDC_EDIT_Min_Dark_Keep, MinDarkKeep);
	DDX_Text(pDX, IDC_EDIT_Min_Heart_Keep, MinHeartKeep);
	DDX_Text(pDX, IDC_EDIT_Max_Water_Eliminate, MaxWaterEliminate);
	DDX_Text(pDX, IDC_EDIT_Max_Fire_Eliminate, MaxFireEliminate);
	DDX_Text(pDX, IDC_EDIT_Max_Wood_Eliminate, MaxWoodEliminate);
	DDX_Text(pDX, IDC_EDIT_Max_Light_Eliminate, MaxLightEliminate);
	DDX_Text(pDX, IDC_EDIT_Max_Dark_Eliminate, MaxDarkEliminate);
	DDX_Text(pDX, IDC_EDIT_Max_Heart_Eliminate, MaxHeartEliminate);
	DDX_Check(pDX, IDC_CHECK_Count_Water_Score, CheckCountWaterScore);
	DDX_Check(pDX, IDC_CHECK_Count_Fire_Score, CheckCountFireScore);
	DDX_Check(pDX, IDC_CHECK_Count_Wood_Score, CheckCountWoodScore);
	DDX_Check(pDX, IDC_CHECK_Count_Light_Score, CheckCountLightScore);
	DDX_Check(pDX, IDC_CHECK_Count_Dark_Score, CheckCountDarkScore);
	DDX_Check(pDX, IDC_CHECK_Count_Heart_Score, CheckCountHeartScore);
	DDX_Check(pDX, IDC_CHECK_Force_Keep, CheckForceKeep);
	DDX_Check(pDX, IDC_CHECK_Preview, CheckPreview);
	DDX_Text(pDX, IDC_EDIT_Combo_Lower_Bound, EditLowerBoundCombo);
}

BEGIN_MESSAGE_MAP(CToS2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CToS2Dlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_Type, &CToS2Dlg::OnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_Default, &CToS2Dlg::OnBnClickedButtonDefault)
END_MESSAGE_MAP()

wchar_t DisplayMessage[MAX_DISPLAY_MESSAGE];
int TargetCombo = 0;
BOOL NeedHighPower = FALSE;
BOOL NeedEliminateSix = FALSE;
BOOL NeedTwoSecond = FALSE;
BOOL EmulateHuman = FALSE;
BOOL Pause = FALSE;
BOOL RealMouse = FALSE;
BOOL NoOblique = FALSE;
int ExecutionType = 0;
DWORD ServerIPAddress = 0;
BOOL ForceKeep = FALSE;
HWND TransparentWindow;
BOOL Preview;
int LowerBoundCombo = 0;

int MinKeep[6], MaxEliminate[6];
BOOL ColorCountScore[6];

const int TargetX[COLUMN] = {36, 116, 196, 276, 356, 436};
const int TargetY[ROW] = {426, 506, 586, 666, 746};

const int CornerX[COLUMN] = {0, 80, 160, 240, 320, 400};
const int CornerY[ROW] = {374, 454, 534, 614, 694};

const int CenterX[COLUMN] = {40, 120, 200, 280, 360, 440};
const int CenterY[ROW] = {414, 494, 574, 654, 734};

// CToS2Dlg 訊息處理常式

BOOL CToS2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	SetTimer(0, 100, NULL);

	ComboExecutionType.AddString(L"未選定");
	ComboExecutionType.AddString(L"完整獨立");
	ComboExecutionType.AddString(L"伺服端");
	ComboExecutionType.AddString(L"用戶端");
	ComboExecutionType.SetCurSel(0);

	CTransparentDlg *Dlg = new CTransparentDlg();
	Dlg->Create(IDD_TRANSPARENT_DIALOG, this);
	Dlg->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
	TransparentWindow = Dlg->m_hWnd;

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CToS2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CToS2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CToS2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

struct MyColorRef{
	BYTE Blue, Green, Red, Pending;
};

int CompareRGB(const struct MyColorRef PixelRGB, const BYTE Red, const BYTE Green, const BYTE Blue){
	if(PixelRGB.Red > Red - COLOR_DIFF && PixelRGB.Red < Red + COLOR_DIFF && PixelRGB.Green > Green - COLOR_DIFF && PixelRGB.Green < Green + COLOR_DIFF && PixelRGB.Blue > Blue - COLOR_DIFF && PixelRGB.Blue < Blue + COLOR_DIFF)
		return 1;
	else
		return 0;
}

int GetColorByRGB(const struct MyColorRef PixelRGB){
	int Color = 0;

	if(CompareRGB(PixelRGB, 90, 55, 0 ) || CompareRGB(PixelRGB, 88, 60, 20)){ // 暗黃
		if(Color == 0)
			Color = 1;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 214, 107, 5) || CompareRGB(PixelRGB, 219, 126, 39) || CompareRGB(PixelRGB, 183, 97, 14)){ // 亮黃
		if(Color == 0)
			Color = 1;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 200, 33, 113) || CompareRGB(PixelRGB, 171, 37, 101)){ // 暗粉
		if(Color == 0)
			Color = 2;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 255, 149, 176) || CompareRGB(PixelRGB, 254, 129, 161)){ // 亮粉
		if(Color == 0)
			Color = 2;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 47, 107, 139) || CompareRGB(PixelRGB, 50, 95, 119)){ // 暗藍
		if(Color == 0)
			Color = 3;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 254, 255, 255)){ // 亮藍
		if(Color == 0)
			Color = 3;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 124, 0, 126)){ // 暗紫
		if(Color == 0)
			Color = 4;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 201, 33, 245) || CompareRGB(PixelRGB, 200, 13, 245) || CompareRGB(PixelRGB, 180, 18, 217)){ // 亮紫
		if(Color == 0)
			Color = 4;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 40, 172, 28) || CompareRGB(PixelRGB, 44, 145, 35)){ // 暗綠
		if(Color == 0)
			Color = 5;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 26, 246, 5)){ // 亮綠
		if(Color == 0)
			Color = 5;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 136, 32, 9)){ // 暗紅
		if(Color == 0)
			Color = 6;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 241, 105, 100) || CompareRGB(PixelRGB, 238, 69, 62) || CompareRGB(PixelRGB, 244, 136, 134) || CompareRGB(PixelRGB, 203, 93, 91)){ // 亮紅
		if(Color == 0)
			Color = 6;
		else
			return 0;
	}
	if(CompareRGB(PixelRGB, 2, 26, 20)){ // 問號
		if(Color == 0)
			Color = 7;
		else
			return 0;
	}
	return Color;
}

struct MyColorRef GetPixelColor(const struct MyColorRef *ScreenColorBottom, const struct MyColorRef *ScreenColorTop, const int ScreenWidth, const int ScreenHeight, const RECT GameRect, const int X, const int Y){
	if(Y + GameRect.top >= 0)
		return ScreenColorBottom[(Y + GameRect.top) * ScreenWidth + (X + GameRect.left)];
	else
		return ScreenColorTop[(Y + GameRect.top + ScreenHeight) * ScreenWidth + (X + GameRect.left)];
}

int GetCurrentTable(const struct MyColorRef *ScreenColorBottom, const struct MyColorRef *ScreenColorTop, const int ScreenWidth, const int ScreenHeight, const RECT GameRect, unsigned int CurrentTable[COLUMN][ROW]){
	int Index1, Index2;
	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			int X = TargetX[Index1];
			int Y = TargetY[Index2];
		
			struct MyColorRef PixelRGB = GetPixelColor(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, X, Y);
			CurrentTable[Index1][Index2] = GetColorByRGB(PixelRGB);
			if(CurrentTable[Index1][Index2] == 0)
				return 0;
	}
	return 1;
}

int GetPuzzleTable(const struct MyColorRef *ScreenColorBottom, const struct MyColorRef *ScreenColorTop, const int ScreenWidth, const int ScreenHeight, const RECT GameRect, BOOL PuzzleTable[COLUMN][ROW]){
	int Index1, Index2;
	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			int Puzzle[4] = {0, 0, 0, 0};
			int Corner = 0;
			for(Corner = 0; Corner < 4; Corner++){
				int X = CornerX[Index1];
				int Y = CornerY[Index2];
				if(Corner == 0){
				}else if(Corner == 1){
					X += 78;
				}else if(Corner == 2){
					Y += 78;
				}else if(Corner == 3){
					X += 78;
					Y += 78;
				}

				struct MyColorRef PixelRGB = GetPixelColor(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, X, Y);
				if(PixelRGB.Blue > 110 && PixelRGB.Green > 80)
					Puzzle[Corner] = 1;
			}

			int IsPuzzle = 1;
			for(Corner = 0; Corner < 4; Corner++)
				if(Puzzle[Corner] == 0){
					IsPuzzle = 0;
					break;
				}

			if(IsPuzzle == 0)
				PuzzleTable[Index1][Index2] = FALSE;
			else
				PuzzleTable[Index1][Index2] = TRUE;
		}

	return 1;
}

int GetStopTable(const struct MyColorRef *ScreenColorBottom, const struct MyColorRef *ScreenColorTop, const int ScreenWidth, const int ScreenHeight, const RECT GameRect, BOOL StopTable[COLUMN][ROW]){
	int Index1, Index2;
	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			int X, Y;
			int WhiteCount = 0;

			for(X = CenterX[Index1] - 9; X < CenterX[Index1] + 5; X++)
				for(Y = CenterY[Index2] - 4; Y < CenterY[Index2] + 5; Y++){
					struct MyColorRef PixelRGB = GetPixelColor(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, X, Y);
					if(PixelRGB.Red == PixelRGB.Green && PixelRGB.Green == PixelRGB.Blue && PixelRGB.Blue > 245)
						WhiteCount++;
				}

			if(WhiteCount > 65)
				StopTable[Index1][Index2] = TRUE;
			else
				StopTable[Index1][Index2] = FALSE;
		}
	return 1;
}

void CaptureScreenBottom(const HDC ScreenDC, struct MyColorRef *ScreenColor, const int ScreenWidth, const int ScreenHeight){
	HDC MemDC;
	HBITMAP BMP1, BMP2;
	BITMAPINFO Info = {0};

	MemDC = CreateCompatibleDC(ScreenDC);
	BMP1 = CreateCompatibleBitmap(ScreenDC, ScreenWidth, ScreenHeight);
	BMP2 = (HBITMAP) SelectObject(MemDC, BMP1);

	StretchBlt(MemDC, 0, 0, ScreenWidth, ScreenHeight, ScreenDC, 0, 0, ScreenWidth, ScreenHeight, SRCCOPY);
	BMP1 = (HBITMAP) SelectObject(MemDC, BMP2);

	Info.bmiHeader.biSize = sizeof(Info.bmiHeader);
	Info.bmiHeader.biWidth = ScreenWidth;
	Info.bmiHeader.biHeight = -1 * ScreenHeight;
	Info.bmiHeader.biPlanes = 1;
	Info.bmiHeader.biBitCount = 32;
	Info.bmiHeader.biCompression = BI_RGB;
	Info.bmiHeader.biSizeImage = ScreenWidth * ScreenHeight * sizeof(struct MyColorRef);
	Info.bmiHeader.biSizeImage = 0;
	
	int bRes = 0;
	bRes = GetDIBits(ScreenDC, BMP1, 0, ScreenHeight, ScreenColor, &Info, DIB_RGB_COLORS);

	DeleteDC(MemDC);
	DeleteObject(BMP1);
	DeleteObject(BMP2);
}

void CaptureScreenTop(const HDC ScreenDC, struct MyColorRef *ScreenColor, const int ScreenWidth, const int ScreenHeight){
	HDC MemDC;
	HBITMAP BMP1, BMP2;
	BITMAPINFO Info = {0};

	MemDC = CreateCompatibleDC(ScreenDC);
	BMP1 = CreateCompatibleBitmap(ScreenDC, ScreenWidth, ScreenHeight);
	BMP2 = (HBITMAP) SelectObject(MemDC, BMP1);

	StretchBlt(MemDC, 0, 0, ScreenWidth, ScreenHeight, ScreenDC, 0, -1 * ScreenHeight, ScreenWidth, ScreenHeight, SRCCOPY);
	BMP1 = (HBITMAP) SelectObject(MemDC, BMP2);

	Info.bmiHeader.biSize = sizeof(Info.bmiHeader);
	Info.bmiHeader.biWidth = ScreenWidth;
	Info.bmiHeader.biHeight = -1 * ScreenHeight;
	Info.bmiHeader.biPlanes = 1;
	Info.bmiHeader.biBitCount = 32;
	Info.bmiHeader.biCompression = BI_RGB;
	Info.bmiHeader.biSizeImage = ScreenWidth * ScreenHeight * sizeof(struct MyColorRef);
	Info.bmiHeader.biSizeImage = 0;
	
	int bRes = 0;
	bRes = GetDIBits(ScreenDC, BMP1, 0, ScreenHeight, ScreenColor, &Info, DIB_RGB_COLORS);

	DeleteDC(MemDC);
	DeleteObject(BMP1);
	DeleteObject(BMP2);
}

void PrintTable(const unsigned int CurrentTable[COLUMN][ROW], const BOOL PuzzleTable[COLUMN][ROW], const BOOL StopTable[COLUMN][ROW]){
	int Index1, Index2;
	wchar_t TitleLine[SHORT_MESSAGE];
	wchar_t TableLine[ROW][SHORT_MESSAGE];

	StrCpyW(TitleLine, L"");
	for(Index2 = 0; Index2 < ROW; Index2++)
		StrCpyW(TableLine[Index2], L"");

	StrCatW(TitleLine, L"目前盤面:\t\t");
	for(Index2 = 0; Index2 < ROW; Index2++){
		for(Index1 = 0; Index1 < COLUMN; Index1++){
			if(CurrentTable[Index1][Index2] == 1)
				StrCatW(TableLine[Index2], L"光");
			else if(CurrentTable[Index1][Index2] == 2)
				StrCatW(TableLine[Index2], L"心");
			else if(CurrentTable[Index1][Index2] == 3)
				StrCatW(TableLine[Index2], L"水");
			else if(CurrentTable[Index1][Index2] == 4)
				StrCatW(TableLine[Index2], L"暗");
			else if(CurrentTable[Index1][Index2] == 5)
				StrCatW(TableLine[Index2], L"木");
			else if(CurrentTable[Index1][Index2] == 6)
				StrCatW(TableLine[Index2], L"火");
			else if(CurrentTable[Index1][Index2] == 7)
				StrCatW(TableLine[Index2], L"？");
		}
		StrCatW(TableLine[Index2], L"\t");
	}

	StrCatW(TitleLine, L"拼圖盾位置:\t");
	for(Index2 = 0; Index2 < ROW; Index2++){
		for(Index1 = 0; Index1 < COLUMN; Index1++){
			if(PuzzleTable[Index1][Index2])
				StrCatW(TableLine[Index2], L"●");
			else
				StrCatW(TableLine[Index2], L"○");
		}
		StrCatW(TableLine[Index2], L"\t\t");
	}

	StrCatW(TitleLine, L"風化珠位置:\r\n");
	for(Index2 = 0; Index2 < ROW; Index2++){
		for(Index1 = 0; Index1 < COLUMN; Index1++){
			if(StopTable[Index1][Index2])
				StrCatW(TableLine[Index2], L"※");
			else
				StrCatW(TableLine[Index2], L"○");
		}
		StrCatW(TableLine[Index2], L"\r\n");
	}

	StrCatW(DisplayMessage, TitleLine);
	for(Index2 = 0; Index2 < ROW; Index2++)
		StrCatW(DisplayMessage, TableLine[Index2]);
}

int GetTable(unsigned int CurrentTable[COLUMN][ROW], BOOL PuzzleTable[COLUMN][ROW], BOOL StopTable[COLUMN][ROW]){
	static HWND GameApplication = NULL, GameWindow = NULL;
	static struct MyColorRef *ScreenColorBottom = NULL, *ScreenColorTop = NULL;

	if(IsWindow(GameWindow) == FALSE){
		GameApplication = FindWindowEx(NULL, NULL, NULL, L"BlueStacks App Player for Windows (beta-1)");
		GameWindow = FindWindowEx(GameApplication, NULL, NULL, L"_ctl.Window");
		SetWindowPos(GameApplication, HWND_TOPMOST, 0, 0, 486, 884, SWP_NOMOVE | SWP_SHOWWINDOW);
	}

	HDC ScreenDC = GetDC(HWND_DESKTOP);
	int ScreenWidth = GetDeviceCaps(ScreenDC, HORZRES);
	int ScreenHeight = GetDeviceCaps(ScreenDC, VERTRES);

	if(ScreenColorBottom == NULL){
		ScreenColorBottom = (struct MyColorRef*) malloc(sizeof(struct MyColorRef) * ScreenWidth * ScreenHeight);
	}
	if(ScreenColorTop == NULL){
		ScreenColorTop = (struct MyColorRef*) malloc(sizeof(struct MyColorRef) * ScreenWidth * ScreenHeight);
	}

	CaptureScreenBottom(ScreenDC, ScreenColorBottom, ScreenWidth, ScreenHeight);
	CaptureScreenTop(ScreenDC, ScreenColorTop, ScreenWidth, ScreenHeight);

	RECT GameRect;
	GetWindowRect(GameWindow, &GameRect);

	if(GameRect.top < -1 * ScreenHeight || GameRect.bottom > ScreenHeight || GameRect.left < 0 || GameRect.right > ScreenWidth)
		return 0;

	unsigned int FirstCurrentTable[COLUMN][ROW];
	BOOL FirstPuzzleTable[COLUMN][ROW], FirstStopTable[COLUMN][ROW];

	if(GetCurrentTable(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, FirstCurrentTable) == 0)
		return 0;
	
	if(GetPuzzleTable(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, FirstPuzzleTable) == 0)
		return 0;

	if(GetStopTable(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, FirstStopTable) == 0)
		return 0;

	Sleep(GET_TABLE_INTERVAL);

	CaptureScreenBottom(ScreenDC, ScreenColorBottom, ScreenWidth, ScreenHeight);
	CaptureScreenTop(ScreenDC, ScreenColorTop, ScreenWidth, ScreenHeight);
	ReleaseDC(HWND_DESKTOP, ScreenDC);

	if(GetCurrentTable(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, CurrentTable) == 0)
		return 0;

	if(GetPuzzleTable(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, PuzzleTable) == 0)
		return 0;

	if(GetStopTable(ScreenColorBottom, ScreenColorTop, ScreenWidth, ScreenHeight, GameRect, StopTable) == 0)
		return 0;

	int Index1, Index2;
	for(Index2 = 0; Index2 < ROW; Index2++){
		for(Index1 = 0; Index1 < COLUMN; Index1++){
			if(FirstCurrentTable[Index1][Index2] != CurrentTable[Index1][Index2] || FirstPuzzleTable[Index1][Index2] != PuzzleTable[Index1][Index2] || FirstStopTable[Index1][Index2] != StopTable[Index1][Index2])
				return 0;
		}
	}

	return 1;
}

struct DFSPath{
	int StartX, StartY;
	int ShortX, ShortY;
	int CurrentX, CurrentY;
	unsigned int Table[COLUMN][ROW];
	unsigned int ShortTable[COLUMN][ROW];
	int Touch[COLUMN][ROW];
	int StepSequence;
	int StepCount;
	int ShortStepSequence;
	int ShortStepCount;
	int FirstDirection, ShortLastDirection;
};

void TableMove(unsigned int Table[COLUMN][ROW], int Touch[COLUMN][ROW], const int CurrentX, const int CurrentY, const int TargetX, const int TargetY, const int TouchDiff){
	if(CurrentX == TargetX){
		if(CurrentY < TargetY){
			unsigned int Temp = Table[CurrentX][CurrentY];
			int MovingY;
			for(MovingY = CurrentY; MovingY < TargetY; MovingY++){
				Table[TargetX][MovingY] = Table[TargetX][MovingY + 1];
				Touch[TargetX][MovingY] += TouchDiff;
			}
			Table[TargetX][TargetY] = Temp;
			Touch[TargetX][TargetY] += TouchDiff;
		}else{
			unsigned int Temp = Table[CurrentX][CurrentY];
			int MovingY;
			for(MovingY = CurrentY; MovingY > TargetY; MovingY--){
				Table[TargetX][MovingY] = Table[TargetX][MovingY - 1];
				Touch[TargetX][MovingY] += TouchDiff;
			}
			Table[TargetX][TargetY] = Temp;
			Touch[TargetX][TargetY] += TouchDiff;
		}
	}else if(CurrentY == TargetY){
		if(CurrentX < TargetX){
			unsigned int Temp = Table[CurrentX][CurrentY];
			int MovingX;
			for(MovingX = CurrentX; MovingX < TargetX; MovingX++){
				Table[MovingX][TargetY] = Table[MovingX + 1][TargetY];
				Touch[MovingX][TargetY] += TouchDiff;
			}
			Table[TargetX][TargetY] = Temp;
			Touch[TargetX][TargetY] += TouchDiff;
		}else{
			unsigned int Temp = Table[CurrentX][CurrentY];
			int MovingX;
			for(MovingX = CurrentX; MovingX > TargetX; MovingX--){
				Table[MovingX][TargetY] = Table[MovingX - 1][TargetY];
				Touch[MovingX][TargetY] += TouchDiff;
			}
			Table[TargetX][TargetY] = Temp;
			Touch[TargetX][TargetY] += TouchDiff;
		}
	}		
}

void DFS(const int MovingType, struct DFSPath *PreBuildPath[COLUMN][ROW], unsigned int PreBuildPathCount[COLUMN][ROW], const int StartX, const int StartY, const int ShortX, const int ShortY, const int CurrentX, const int CurrentY, unsigned int Table[COLUMN][ROW], unsigned int ShortTable[COLUMN][ROW], int Touch[COLUMN][ROW], const int StepSequence, const int StepCount, const int ShortStepSequence, const int ShortStepCount, const int FirstDirection, const int LastDirection, const int ShortLastDirection){
	if(CurrentX < 0 || CurrentX >= COLUMN || CurrentY < 0 || CurrentY >= ROW)
		return;

	int MaxStep;
	if(MovingType == 0)
		MaxStep = SINGLE_MOVE_MAX_STEP;
	else if(MovingType == 1)
		MaxStep = MULTI_MOVE_MAX_STEP;

	if(StepCount == MaxStep || (StepCount != 0 && LastDirection == 0)){
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].StartX = StartX;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].StartY = StartY;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].ShortX = ShortX;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].ShortY = ShortY;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].CurrentX = CurrentX;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].CurrentY = CurrentY;
		int Index1, Index2;
		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++){
				PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].Table[Index1][Index2] = Table[Index1][Index2];
				PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].ShortTable[Index1][Index2] = ShortTable[Index1][Index2];
				PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].Touch[Index1][Index2] = Touch[Index1][Index2];
			}
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].StepSequence = StepSequence;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].StepCount = StepCount;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].ShortStepSequence = ShortStepSequence;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].ShortStepCount = ShortStepCount;

		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].FirstDirection = FirstDirection;
		PreBuildPath[StartX][StartY][PreBuildPathCount[StartX][StartY]].ShortLastDirection = ShortLastDirection;

		PreBuildPathCount[StartX][StartY]++;
		return;
	}

	int MaxDirection;
	if(MovingType == 0)
		MaxDirection = SINGLE_MOVE_DIRECTION;
	else if(MovingType == 1)
		MaxDirection = MULTI_MOVE_DIRECTION;

	int Direction;
	for(Direction = 0; Direction < MaxDirection + 1; Direction++){
		if(MovingType == 0){
			if(Direction == 0 && StepCount == 0)
				continue;
			if(Direction == 1 && LastDirection == 3)
				continue;
			if(Direction == 2 && LastDirection == 4)
				continue;
			if(Direction == 3 && LastDirection == 1)
				continue;
			if(Direction == 4 && LastDirection == 2)
				continue;
			if(Direction == 5 && LastDirection == 7)
				continue;
			if(Direction == 6 && LastDirection == 8)
				continue;
			if(Direction == 7 && LastDirection == 5)
				continue;
			if(Direction == 8 && LastDirection == 6)
				continue;
		}else if(MovingType == 1){
			if(Direction == 0 && StepCount == 0)
				continue;
			if((Direction == 1 || Direction == 2 || Direction == 3 || Direction == 4) && (LastDirection == 10 || LastDirection == 11 || LastDirection == 12 || LastDirection == 13))
				continue;
			if((Direction == 5 || Direction == 6 || Direction == 7 || Direction == 8 || Direction == 9) && (LastDirection == 14 || LastDirection == 15 || LastDirection == 16 || LastDirection == 17 || LastDirection == 18))
				continue;
			if((Direction == 10 || Direction == 11 || Direction == 12 || Direction == 13) && (LastDirection == 1 || LastDirection == 2 || LastDirection == 3 || LastDirection == 4))
				continue;
			if((Direction == 14 || Direction == 15 || Direction == 16 || Direction == 17 || Direction == 18) && (LastDirection == 5 || LastDirection == 6 || LastDirection == 7 || LastDirection == 8 || LastDirection == 9))
				continue;

			if((Direction == 1 || Direction == 2 || Direction == 3 || Direction == 4) && (LastDirection == 1 || LastDirection == 2 || LastDirection == 3 || LastDirection == 4))
				continue;
			if((Direction == 5 || Direction == 6 || Direction == 7 || Direction == 8 || Direction == 9) && (LastDirection == 5 || LastDirection == 6 || LastDirection == 7 || LastDirection == 8 || LastDirection == 9))
				continue;
			if((Direction == 10 || Direction == 11 || Direction == 12 || Direction == 13) && (LastDirection == 10 || LastDirection == 11 || LastDirection == 12 || LastDirection == 13))
				continue;
			if((Direction == 14 || Direction == 15 || Direction == 16 || Direction == 17 || Direction == 18) && (LastDirection == 14 || LastDirection == 15 || LastDirection == 16 || LastDirection == 17 || LastDirection == 18))
				continue;
		}

		int TargetX = CurrentX;
		int TargetY = CurrentY;

		if(MovingType == 0){
			if(Direction == 1 && CurrentY > 0){
				// 向上
				TargetY--;
			}else if(Direction == 2 && CurrentX < COLUMN - 1){
				// 向右
				TargetX++;
			}else if(Direction == 3 && CurrentY < ROW - 1){
				// 向下
				TargetY++;
			}else if(Direction == 4 && CurrentX > 0){
				// 向左
				TargetX--;
			}else if(Direction == 5 && CurrentY > 0 && CurrentX < COLUMN - 1){
				TargetX++;
				TargetY--;
			}else if(Direction == 6 && CurrentY < ROW - 1 && CurrentX < COLUMN - 1){
				TargetX++;
				TargetY++;
			}else if(Direction == 7 && CurrentY < ROW - 1 && CurrentX > 0){
				TargetX--;
				TargetY++;
			}else if(Direction == 8 && CurrentY > 0 && CurrentX > 0){
				TargetX--;
				TargetY--;
			}
		}else if(MovingType == 1){
			if(Direction == 1 && CurrentY > 0){
				TargetY -= 1;
			}else if(Direction == 2 && CurrentY > 1){
				TargetY -= 2;
			}else if(Direction == 3 && CurrentY > 2){
				TargetY -= 3;
			}else if(Direction == 4 && CurrentY > 3){
				TargetY -= 4;
			}else if(Direction == 5 && CurrentX < COLUMN - 1){
				TargetX += 1;
			}else if(Direction == 6 && CurrentX < COLUMN - 2){
				TargetX += 2;
			}else if(Direction == 7 && CurrentX < COLUMN - 3){
				TargetX += 3;
			}else if(Direction == 8 && CurrentX < COLUMN - 4){
				TargetX += 4;
			}else if(Direction == 9 && CurrentX < COLUMN - 5){
				TargetX += 5;
			}else if(Direction == 10 && CurrentY < ROW - 1){
				TargetY += 1;
			}else if(Direction == 11 && CurrentY < ROW - 2){
				TargetY += 2;
			}else if(Direction == 12 && CurrentY < ROW - 3){
				TargetY += 3;
			}else if(Direction == 13 && CurrentY < ROW - 4){
				TargetY += 4;
			}else if(Direction == 14 && CurrentX > 0){
				TargetX -= 1;
			}else if(Direction == 15 && CurrentX > 1){
				TargetX -= 2;
			}else if(Direction == 16 && CurrentX > 2){
				TargetX -= 3;
			}else if(Direction == 17 && CurrentX > 3){
				TargetX -= 4;
			}else if(Direction == 18 && CurrentX > 4){
				TargetX -= 5;
			}
		}

		if(Direction != 0 && CurrentX == TargetX && CurrentY == TargetY)
			continue;

		if(MovingType == 0){
			unsigned int Temp = Table[CurrentX][CurrentY];
			Table[CurrentX][CurrentY] = Table[TargetX][TargetY];
			Table[TargetX][TargetY] = Temp;
			Touch[TargetX][TargetY]++;
		}else if(MovingType == 1){
			TableMove(Table, Touch, CurrentX, CurrentY, TargetX, TargetY, 1);
		}

		int MaxShortStep;
		if(MovingType == 0)
			MaxShortStep = SINGLE_MOVE_MAX_SHORT_STEP;
		else if(MovingType == 1)
			MaxShortStep = MULTI_MOVE_MAX_SHORT_STEP;

		if(StepCount < MaxShortStep){
			if(MovingType == 0){
				unsigned int Temp = ShortTable[CurrentX][CurrentY];
				ShortTable[CurrentX][CurrentY] = ShortTable[TargetX][TargetY];
				ShortTable[TargetX][TargetY] = Temp;
			}else if(MovingType == 1){
				TableMove(ShortTable, Touch, CurrentX, CurrentY, TargetX, TargetY, 0);
			}

			DFS(MovingType, PreBuildPath, PreBuildPathCount, StartX, StartY, TargetX, TargetY, TargetX, TargetY, Table, ShortTable, Touch, StepSequence * (MaxDirection + 1) + Direction, StepCount + 1, ShortStepSequence * (MaxDirection + 1) + Direction, ShortStepCount + 1, (FirstDirection == 0 ? Direction : FirstDirection), Direction, (Direction != 0 ? Direction : LastDirection));

			if(MovingType == 0){
				unsigned int Temp = ShortTable[CurrentX][CurrentY];
				ShortTable[CurrentX][CurrentY] = ShortTable[TargetX][TargetY];
				ShortTable[TargetX][TargetY] = Temp;
			}else if(MovingType == 1){
				TableMove(ShortTable, Touch, TargetX, TargetY, CurrentX, CurrentY, 0);
			}
		}
		else{
			DFS(MovingType, PreBuildPath, PreBuildPathCount, StartX, StartY, ShortX, ShortY, TargetX, TargetY, Table, ShortTable, Touch, StepSequence * (MaxDirection + 1) + Direction, StepCount + 1, ShortStepSequence, ShortStepCount, (FirstDirection == 0 ? Direction : FirstDirection), Direction, ShortLastDirection);
		}

		if(MovingType == 0){
			Touch[TargetX][TargetY]--;
			unsigned int Temp = Table[CurrentX][CurrentY];
			Table[CurrentX][CurrentY] = Table[TargetX][TargetY];
			Table[TargetX][TargetY] = Temp;
		}else if(MovingType == 1){
			TableMove(Table, Touch, TargetX, TargetY, CurrentX, CurrentY, -1);
		}
	}
}

void BuildDFSPath(const int MovingType, struct DFSPath *PreBuildPath[COLUMN][ROW], unsigned int PreBuildPathCount[COLUMN][ROW]){
	int Index1, Index2;
	#pragma omp parallel for private (Index1, Index2)
	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			unsigned int Table[COLUMN][ROW], ShortTable[COLUMN][ROW];
			int Touch[COLUMN][ROW];
			int Count = 0;

			int Index3, Index4;
			for(Index3 = 0; Index3 < COLUMN; Index3++)
				for(Index4 = 0; Index4 < ROW; Index4++){
					Table[Index3][Index4] = Count;
					ShortTable[Index3][Index4] = Count;
					Count++;

					Touch[Index3][Index4] = 0;
				}

			Touch[Index1][Index2]++;
			DFS(MovingType, PreBuildPath, PreBuildPathCount, Index1, Index2, Index1, Index2, Index1, Index2, Table, ShortTable, Touch, 0, 0, 0, 0, 0, 0, 0);
			Touch[Index1][Index2]--;
		}
}

struct BFSNode{
	int StartX, StartY;
	int ShortX, ShortY;
	int CurrentX, CurrentY;
	unsigned int DFSIndex[(SINGLE_MOVE_MAX_SEARCH > MULTI_MOVE_MAX_SEARCH ? SINGLE_MOVE_MAX_SEARCH : MULTI_MOVE_MAX_SEARCH)];
	unsigned int DFSCount;
	unsigned int Table[COLUMN][ROW];
	BOOL Searched;
	long long int Score;
	int LastDirection;
	int Combo;
};

struct XYPair{
	int X, Y;
};

void MarkDFS(int Mark[COLUMN][ROW], const BOOL PuzzleTable[COLUMN][ROW], int X, int Y, int *EliminateCount, int *PuzzleCount, int ThisColor){
	struct XYPair Pairs[COLUMN * ROW];
	memset(Pairs, 0, sizeof(struct XYPair) * COLUMN * ROW);

	int Pointer = 0;

	Pairs[Pointer].X = X;
	Pairs[Pointer].Y = Y;
	Mark[X][Y] = -1;
	Pointer++;

	while(Pointer > 0){
		// pop
		X = Pairs[Pointer - 1].X;
		Y = Pairs[Pointer - 1].Y;
		Pointer--;

		// handle
		(*EliminateCount)++;
		if(PuzzleTable[X][Y] == TRUE)
			(*PuzzleCount)++;

		// search
		if(X > 0 && Mark[X - 1][Y] == ThisColor){
			Pairs[Pointer].X = X - 1;
			Pairs[Pointer].Y = Y;
			Mark[X - 1][Y] = -1;
			Pointer++;
		}
		if(X < COLUMN - 1 && Mark[X + 1][Y] == ThisColor){
			Pairs[Pointer].X = X + 1;
			Pairs[Pointer].Y = Y;
			Mark[X + 1][Y] = -1;
			Pointer++;
		}
		if(Y > 0 && Mark[X][Y - 1] == ThisColor){
			Pairs[Pointer].X = X;
			Pairs[Pointer].Y = Y - 1;
			Mark[X][Y - 1] = -1;
			Pointer++;
		}
		if(Y < ROW - 1 && Mark[X][Y + 1] == ThisColor){
			Pairs[Pointer].X = X;
			Pairs[Pointer].Y = Y + 1;
			Mark[X][Y + 1] = -1;
			Pointer++;
		}
	}
}

long long int GetScore(const int EliminateCount, int ThisColor){
	if(NeedHighPower && EliminateCount > 4 && ColorCountScore[ThisColor - 1])
		return 10000 * SCORE_OFFSET + EliminateCount * SCORE_OFFSET;
	else if(ColorCountScore[ThisColor - 1])
		return 1000 * SCORE_OFFSET + EliminateCount * SCORE_OFFSET;
	else
		return 100 * SCORE_OFFSET + EliminateCount * SCORE_OFFSET;
}

long long int CountScore(int Mark[COLUMN][ROW], const BOOL PuzzleTable[COLUMN][ROW], BOOL *MeetPuzzle, int *MeetPuzzleCount, int *Combo, BOOL *IsEliminateSix, const int ColorCount[6], const int Table[COLUMN][ROW]){
	long long int Score = 0;
	int Index1, Index2, Index3, Index4;
	int TargetPuzzleCount = 0;

	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			if(PuzzleTable[Index1][Index2] == TRUE)
				TargetPuzzleCount++;
		}

	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			int ThisColor = Mark[Index1][Index2];
			if(ThisColor == -1)
				continue;

			int EliminateCount = 0, PuzzleCount = 0;
			MarkDFS(Mark, PuzzleTable, Index1, Index2, &EliminateCount, &PuzzleCount, ThisColor);

			if(PuzzleCount == TargetPuzzleCount){
				*MeetPuzzle = TRUE;
				*MeetPuzzleCount = 0;
			}else if(ColorCount[ThisColor - 1] >= TargetPuzzleCount && PuzzleCount != 0){
				PuzzleCount = 0;

				int MinDistance = MAX;
				for(Index3 = 0; Index3 < COLUMN; Index3++)
					for(Index4 = 0; Index4 < ROW; Index4++)
						if(PuzzleTable[Index3][Index4] == TRUE)
							if(Table[Index3][Index4] == ThisColor)
								PuzzleCount += 10;
							else{
								int Index5, Index6;
								for(Index5 = 0; Index5 < COLUMN; Index5++)
									for(Index6 = 0; Index6 < ROW; Index6++){
										if(PuzzleTable[Index5][Index6] == FALSE && Table[Index5][Index6] == ThisColor){
											int Distance = 0;
											Distance += (Index5 > Index3 ? Index5 - Index3 : Index3 - Index5);
											Distance += (Index6 > Index4 ? Index6 - Index4 : Index4 - Index6);
											if(MinDistance > Distance)
												MinDistance = Distance;
										}
									}
							}
				if(MinDistance != MAX)
					PuzzleCount += 10 - MinDistance;

				if(*MeetPuzzleCount < PuzzleCount)
					*MeetPuzzleCount = PuzzleCount;
			}

			Score += GetScore(EliminateCount, ThisColor);
			if(EliminateCount > 5 && ThisColor != 2)
				*IsEliminateSix = TRUE;

			(*Combo)++;
		}

	return Score;
}

long long int EvaluateScore(const unsigned int SourceTable[COLUMN][ROW], const BOOL PuzzleTable[COLUMN][ROW], const long long int LowerBoundScore, int *FinalCombo){
	int Index1, Index2;
	int Mark[COLUMN][ROW], LocalTable[COLUMN][ROW];
	int Combo = 0;
	long long int Score = 0;
	BOOL MeetPuzzle = FALSE;
	int MeetPuzzleCount = 0;
	long long int AdditionalScore = 0;
	long long int TotalAdditionalScore = 0;
	BOOL IsEliminateSix = FALSE;

	int FirstColorCount[6], SecondColorCount[6];

	for(Index1 = 0; Index1 < 6; Index1++){
		FirstColorCount[Index1] = 0;
		SecondColorCount[Index1] = 0;
	}

	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			LocalTable[Index1][Index2] = SourceTable[Index1][Index2];
			if(LocalTable[Index1][Index2] > 0 && LocalTable[Index1][Index2] < 7)
				FirstColorCount[LocalTable[Index1][Index2] - 1]++;
		}

	while(1){
		BOOL Change1 = FALSE;

		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++)
				Mark[Index1][Index2] = -1;

		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++){
				int ThisColor = LocalTable[Index1][Index2];
				if(ThisColor == -1 || ThisColor == 7)
					continue;

				// 上下
				if(Index2 > 0 && Index2 < ROW - 1 && LocalTable[Index1][Index2 - 1] == ThisColor && LocalTable[Index1][Index2 + 1] == ThisColor){
					Mark[Index1][Index2 - 1] = ThisColor;
					Mark[Index1][Index2] = ThisColor;
					Mark[Index1][Index2 + 1] = ThisColor;
					Change1 = TRUE;
				}
				// 左右
				if(Index1 > 0 && Index1 < COLUMN - 1 && LocalTable[Index1 - 1][Index2] == ThisColor && LocalTable[Index1 + 1][Index2] == ThisColor){
					Mark[Index1 - 1][Index2] = ThisColor;
					Mark[Index1][Index2] = ThisColor;
					Mark[Index1 + 1][Index2] = ThisColor;
					Change1 = TRUE;
				}
			}

		int TempTable[COLUMN][ROW];

		for(Index1 = 0; Index1 < COLUMN; Index1++){
			for(Index2 = 0; Index2 < ROW; Index2++){
				TempTable[Index1][Index2] = LocalTable[Index1][Index2];
				if(Mark[Index1][Index2] != -1){
					LocalTable[Index1][Index2] = -1;
				}
			}
		}

		Score += CountScore(Mark, PuzzleTable, &MeetPuzzle, &MeetPuzzleCount, &Combo, &IsEliminateSix, FirstColorCount, TempTable);

		for(Index1 = 0; Index1 < COLUMN; Index1++){
			int Pointer = ROW - 1;
			for(Index2 = ROW - 1; Index2 >= 0; Index2--){
				if(LocalTable[Index1][Index2] != -1){
					TempTable[Index1][Pointer] = LocalTable[Index1][Index2];
					Pointer--;
				}
			}
			for(; Pointer >= 0; Pointer--)
				TempTable[Index1][Pointer] = -1;
		}

		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++)
				LocalTable[Index1][Index2] = TempTable[Index1][Index2];

		if(Change1 == TRUE)
			Score -= AdditionalScore;
		else if(Change1 == FALSE){
			if(TargetCombo == 0)
				Score += AdditionalScore;
			else
				Score -= AdditionalScore;
			break;
		}

		AdditionalScore = 0;
		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++){
				if(LocalTable[Index1][Index2] == -1 || LocalTable[Index1][Index2] == 7)
					continue;
				if(Index1 > 1 && LocalTable[Index1][Index2] == LocalTable[Index1 - 1][Index2] && LocalTable[Index1 - 2][Index2] == -1)
					AdditionalScore += 1000;
				if(Index1 < COLUMN - 2 && LocalTable[Index1][Index2] == LocalTable[Index1 + 1][Index2] && LocalTable[Index1 + 2][Index2] == -1)
					AdditionalScore += 1000;
				if(Index2 > 1 && LocalTable[Index1][Index2] == LocalTable[Index1][Index2 - 1] && LocalTable[Index1][Index2 - 2] == -1)
					AdditionalScore += 1000;
				if(Index2 < ROW - 2 && LocalTable[Index1][Index2] == LocalTable[Index1][Index2 + 1] && LocalTable[Index1][Index2 + 2] == -1)
					AdditionalScore += 1000;
				if(Index1 < COLUMN - 2 && LocalTable[Index1 + 1][Index2] == -1 && LocalTable[Index1][Index2] == LocalTable[Index1 + 2][Index2])
					AdditionalScore += 1000;
			}

		TotalAdditionalScore += AdditionalScore;
	}

	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			if(LocalTable[Index1][Index2] > 0 && LocalTable[Index1][Index2] < 7)
				SecondColorCount[LocalTable[Index1][Index2] - 1]++;
		}

	for(Index1 = 0; Index1 < 6; Index1++){
		if(MinKeep[Index1] != -1 && FirstColorCount[Index1] >= MinKeep[Index1] && SecondColorCount[Index1] < MinKeep[Index1])
			return 0;
		if(MinKeep[Index1] != -1 && FirstColorCount[Index1] < MinKeep[Index1] && FirstColorCount[Index1] != SecondColorCount[Index1])
			return 0;
		if(MaxEliminate[Index1] != -1 && FirstColorCount[Index1] - SecondColorCount[Index1] > MaxEliminate[Index1])
			return 0;
	}

	*FinalCombo = Combo;

	if(TargetCombo != 0 && Combo > TargetCombo)
		return 0;

	if(TargetCombo != 0 && Combo == TargetCombo && TotalAdditionalScore != 0)
		return 0;

	if(NeedEliminateSix == TRUE && IsEliminateSix == TRUE)
		Score += 10000 * SCORE_OFFSET;

	if(Score != 0){
		if(MeetPuzzle == TRUE)
			Score += MEET_PUZZLE_SCORE;
		else
			Score += MeetPuzzleCount * PARTIAL_MEET_PUZZLE_SCORE;
	}

	if(Score < LowerBoundScore - SCORE_OFFSET)
		return 0;

	if(TargetCombo == 0 && Combo < LowerBoundCombo)
		return 0;

	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			if(LocalTable[Index1][Index2] == -1 || LocalTable[Index1][Index2] == 7)
				continue;

			if(ForceKeep){
				if(MinKeep[LocalTable[Index1][Index2] - 1] != -1 || MaxEliminate[LocalTable[Index1][Index2] - 1] != -1)
					if(Index2 > 1 && LocalTable[Index1][Index2 - 1] == -1)
						return 0;
			}

			if(Index1 > 1 && LocalTable[Index1][Index2] == LocalTable[Index1 - 1][Index2] && LocalTable[Index1 - 2][Index2] == -1)
				if(MinKeep[LocalTable[Index1][Index2] - 1] != -1 || MaxEliminate[LocalTable[Index1][Index2] - 1] != -1)
					return 0;
			if(Index1 < COLUMN - 2 && LocalTable[Index1][Index2] == LocalTable[Index1 + 1][Index2] && LocalTable[Index1 + 2][Index2] == -1)
				if(MinKeep[LocalTable[Index1][Index2] - 1] != -1 || MaxEliminate[LocalTable[Index1][Index2] - 1] != -1)
					return 0;
			if(Index2 > 1 && LocalTable[Index1][Index2] == LocalTable[Index1][Index2 - 1] && LocalTable[Index1][Index2 - 2] == -1)
				if(MinKeep[LocalTable[Index1][Index2] - 1] != -1 || MaxEliminate[LocalTable[Index1][Index2] - 1] != -1)
					return 0;
			if(Index2 < ROW - 2 && LocalTable[Index1][Index2] == LocalTable[Index1][Index2 + 1] && LocalTable[Index1][Index2 + 2] == -1)
				if(MinKeep[LocalTable[Index1][Index2] - 1] != -1 || MaxEliminate[LocalTable[Index1][Index2] - 1] != -1)
					return 0;
			if(Index1 < COLUMN - 2 && LocalTable[Index1 + 1][Index2] == -1 && LocalTable[Index1][Index2] == LocalTable[Index1 + 2][Index2])
				if(MinKeep[LocalTable[Index1][Index2] - 1] != -1 || MaxEliminate[LocalTable[Index1][Index2] - 1] != -1)
					return 0;
		}


	long long int NearScore = 0;
	int Index3, Index4;
	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			if(LocalTable[Index1][Index2] < 1 || LocalTable[Index1][Index2] > 6)
				continue;
			if(Index1 > 0 && LocalTable[Index1][Index2] == LocalTable[Index1 - 1][Index2]){
				NearScore += 100;
				for(Index3 = 0; Index3 < Index1; Index3++)
					for(Index4 = 0; Index4 < ROW; Index4++)
						if(LocalTable[Index1][Index2] == LocalTable[Index3][Index4]){
							int IndexX = Index1 - 1;
							int IndexY = Index2;
							int Diff1 = IndexX > Index3 ? IndexX - Index3 : Index3 - IndexX;
							int Diff2 = IndexY > Index4 ? IndexY - Index4 : Index4 - IndexY;
							NearScore += 6 - (Diff1 > Diff2 ? Diff1 : Diff2);
						}
				for(Index3 = Index1; Index3 < COLUMN; Index3++)
					for(Index4 = 0; Index4 < ROW; Index4++)
						if(LocalTable[Index1][Index2] == LocalTable[Index3][Index4]){
							int IndexX = Index1;
							int IndexY = Index2;
							int Diff1 = IndexX > Index3 ? IndexX - Index3 : Index3 - IndexX;
							int Diff2 = IndexY > Index4 ? IndexY - Index4 : Index4 - IndexY;
							NearScore += 6 - (Diff1 > Diff2 ? Diff1 : Diff2);
						}
			}
			if(Index2 > 0 && LocalTable[Index1][Index2] == LocalTable[Index1][Index2 - 1]){
				NearScore += 100;
				for(Index3 = 0; Index3 < COLUMN; Index3++)
					for(Index4 = 0; Index4 < Index2; Index4++)
						if(LocalTable[Index1][Index2] == LocalTable[Index3][Index4]){
							int IndexX = Index1;
							int IndexY = Index2 - 1;
							int Diff1 = IndexX > Index3 ? IndexX - Index3 : Index3 - IndexX;
							int Diff2 = IndexY > Index4 ? IndexY - Index4 : Index4 - IndexY;
							NearScore += 6 - (Diff1 > Diff2 ? Diff1 : Diff2);
						}
				for(Index3 = 0; Index3 < COLUMN; Index3++)
					for(Index4 = Index2; Index4 < ROW; Index4++)
						if(LocalTable[Index1][Index2] == LocalTable[Index3][Index4]){
							int IndexX = Index1;
							int IndexY = Index2;
							int Diff1 = IndexX > Index3 ? IndexX - Index3 : Index3 - IndexX;
							int Diff2 = IndexY > Index4 ? IndexY - Index4 : Index4 - IndexY;
							NearScore += 6 - (Diff1 > Diff2 ? Diff1 : Diff2);
						}
			}
		}

	Score += NearScore;

	int ColorIndex;
	for(ColorIndex = 1; ColorIndex < 7; ColorIndex++){
		int TotalCount = 0;
		int TotalX = 0, TotalY = 0;
		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++)
				if(LocalTable[Index1][Index2] == ColorIndex){
					TotalX += Index1;
					TotalY += Index2;
					TotalCount++;
				}
		
		if(TotalCount < 3)
			continue;

		int TotalDistance = 0;
		int AvgX = TotalX / TotalCount;
		int AvgY = TotalY / TotalCount;
		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++){
				if(LocalTable[Index1][Index2] == ColorIndex){
					TotalDistance += (Index1 > AvgX ? Index1 - AvgX : AvgX - Index1);
					TotalDistance += (Index2 > AvgY ? Index2 - AvgY : AvgY - Index2);
				}
			}
		TotalDistance /= TotalCount;

		Score += (10 - TotalDistance) * 100000;
	}

	return Score;
}

BOOL PushToDestination(struct BFSNode DestinationPool[MAX_REAL_KEEP_COUNT], const struct BFSNode NewNode, unsigned int *DestinationCount, long long int *LowerBoundScore){
	if(*DestinationCount < MAX_REAL_KEEP_COUNT){
		DestinationPool[*DestinationCount] = NewNode;
		(*DestinationCount)++;
		return TRUE;
	}else{
		int LowestIndex = 0;
		long long int LowestScore = DestinationPool[LowestIndex].Score;
		int Index = 0;
		for(Index = 0; Index < MAX_REAL_KEEP_COUNT; Index++){
			if(DestinationPool[Index].Score < LowestScore){
				LowestIndex = Index;
				LowestScore = DestinationPool[Index].Score;
			}
		}

		*LowerBoundScore = LowestScore;
		if(LowestScore < NewNode.Score){
			DestinationPool[LowestIndex] = NewNode;
			return TRUE;
		}
	}
	return FALSE;
}

void MoveDestinationToSource(struct BFSNode SourcePool[MAX_KEEP_COUNT], unsigned int *SourceCount, struct BFSNode DestinationPool[MAX_REAL_KEEP_COUNT], const unsigned int *DestinationCount){
	unsigned int Index = 0;

	int HighestIndex = 0;
	long long int HighestScore = DestinationPool[HighestIndex].Score;
	for(Index = 0; Index < *DestinationCount; Index++){
		if(HighestScore < DestinationPool[Index].Score){
			HighestScore = DestinationPool[Index].Score;
			HighestIndex = Index;
		}

		SourcePool[Index] = DestinationPool[Index];
		DestinationPool[Index].Searched = TRUE;
	}
	*SourceCount = *DestinationCount;

	wchar_t LocalMessage[MAX_MESSAGE];
	swprintf_s(LocalMessage, L"連擊數: %d, 拼圖盾: %s, 原始分數: %lld\r\n", DestinationPool[HighestIndex].Combo, (DestinationPool[HighestIndex].Score >= MEET_PUZZLE_SCORE ? L"已達成" : L"未達成"), DestinationPool[HighestIndex].Score);
	StrCatW(DisplayMessage, LocalMessage);
}

void MoveDestinationToBackup(struct BFSNode BackupPool[MAX_KEEP_COUNT * 50], unsigned int *BackupCount, const struct BFSNode DestinationPool[MAX_REAL_KEEP_COUNT], const unsigned int *DestinationCount){
	unsigned int Index = 0;
	for(Index = 0; Index < *DestinationCount; Index++){
		BackupPool[*BackupCount] = DestinationPool[Index];
		(*BackupCount)++;
	}
}

void SearchBestPath(const int MovingType, const unsigned int CurrentTable[COLUMN][ROW], const BOOL PuzzleTable[COLUMN][ROW], const BOOL StopTable[COLUMN][ROW], struct DFSPath *PreBuildPath[COLUMN][ROW], const unsigned int PreBuildPathCount[COLUMN][ROW], struct BFSNode *BestPath){
	struct BFSNode SourcePool[MAX_KEEP_COUNT];
	struct BFSNode DestinationPool[MAX_REAL_KEEP_COUNT];
	struct BFSNode BackupPool[MAX_KEEP_COUNT * 50];

	unsigned int SourceCount = 0, DestinationCount = 0, BackupCount = 0;

	memset(SourcePool, 0, sizeof(struct BFSNode) * MAX_KEEP_COUNT);
	memset(DestinationPool, 0, sizeof(struct BFSNode) * MAX_REAL_KEEP_COUNT);
	memset(BackupPool, 0, sizeof(struct BFSNode) * MAX_KEEP_COUNT * 50);

	int ColorCount[7] = {0, 0, 0, 0, 0, 0, 0};
	int Index1, Index2;
	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++)
			ColorCount[CurrentTable[Index1][Index2] - 1]++;

	int MaxCombo = 0;
	for(Index1 = 0; Index1 < 7; Index1++)
		MaxCombo += ColorCount[Index1] / 3;

	wchar_t LocalMessage[MAX_MESSAGE];
	swprintf_s(LocalMessage, L"最多可能連擊數為 %d\r\n", MaxCombo);
	StrCatW(DisplayMessage, LocalMessage);

	for(Index1 = 0; Index1 < COLUMN; Index1++)
		for(Index2 = 0; Index2 < ROW; Index2++){
			SourcePool[SourceCount].StartX = Index1;
			SourcePool[SourceCount].StartY = Index2;
			SourcePool[SourceCount].ShortX = Index1;
			SourcePool[SourceCount].ShortY = Index2;
			SourcePool[SourceCount].CurrentX = Index1;
			SourcePool[SourceCount].CurrentY = Index2;

			int Index3, Index4;
			for(Index3 = 0; Index3 < COLUMN; Index3++)
				for(Index4 = 0; Index4 < ROW; Index4++)
					SourcePool[SourceCount].Table[Index3][Index4] = CurrentTable[Index3][Index4];

			SourcePool[SourceCount].DFSCount = 0;
			SourcePool[SourceCount].Score = 0;
			SourcePool[SourceCount].Searched = FALSE;
			SourcePool[SourceCount].LastDirection = 0;
			SourcePool[SourceCount].Combo = 0;
			SourceCount++;
		}

	int SearchRound = 0;
	long long int LowerBoundScore = 0;

	int Index;
	static struct BFSNode *ShortPathBest[MAX_KEEP_COUNT];
	for(Index = 0; Index < MAX_KEEP_COUNT; Index++){
		ShortPathBest[Index] = (struct BFSNode *) malloc(sizeof(struct BFSNode) * MAX_SHORT_PATH_COUNT);
		memset(ShortPathBest[Index], 0, sizeof(struct BFSNode) * MAX_SHORT_PATH_COUNT);
	}

	int Max2sSearch, MaxSearch;
	if(MovingType == 0){
		Max2sSearch = SINGLE_MOVE_MAX_2S_SEARCH;
		MaxSearch = SINGLE_MOVE_MAX_SEARCH;
	}else if(MovingType == 1){
		Max2sSearch = MULTI_MOVE_MAX_2S_SEARCH;
		MaxSearch = MULTI_MOVE_MAX_SEARCH;
	}

	for(SearchRound = 0; SearchRound < (NeedTwoSecond ? Max2sSearch : MaxSearch); SearchRound++){
		int BFSIndex;
		BOOL ImproveFlag = FALSE;

		if(Pause)
			return;

		DWORD StartTime = GetTickCount();

		#pragma omp parallel for private (Index1, Index2) schedule (dynamic, 1)
		for(BFSIndex = 0; BFSIndex < (int) SourceCount; BFSIndex++){
			struct BFSNode CurrentNode = SourcePool[BFSIndex];
			if(CurrentNode.Searched == TRUE)
				continue;

			unsigned int ShortPathIndex = 0;
			memset(ShortPathBest[BFSIndex], 0, sizeof(struct BFSNode) * MAX_SHORT_PATH_COUNT);

			unsigned int DFSIndex;
			int LastShortStepSequence = -1;
			for(DFSIndex = 0; DFSIndex < PreBuildPathCount[CurrentNode.ShortX][CurrentNode.ShortY]; DFSIndex++){
				struct BFSNode NewNode = CurrentNode;
				struct DFSPath ThisPath = PreBuildPath[CurrentNode.ShortX][CurrentNode.ShortY][DFSIndex];

				int PrevDirection = CurrentNode.LastDirection;
				int NextDirection = ThisPath.FirstDirection;

				if(MovingType == 0){
					if(PrevDirection == 1 && NextDirection == 3)
						continue;
					if(PrevDirection == 2 && NextDirection == 4)
						continue;
					if(PrevDirection == 3 && NextDirection == 1)
						continue;
					if(PrevDirection == 4 && NextDirection == 2)
						continue;
					if(PrevDirection == 5 && NextDirection == 7)
						continue;
					if(PrevDirection == 6 && NextDirection == 8)
						continue;
					if(PrevDirection == 7 && NextDirection == 5)
						continue;
					if(PrevDirection == 8 && NextDirection == 6)
						continue;
				}else if(MovingType == 1){
					if((PrevDirection == 1 || PrevDirection == 2 || PrevDirection == 3 || PrevDirection == 4) && (NextDirection == 10 || NextDirection == 11 || NextDirection == 12 || NextDirection == 13))
						continue;
					if((PrevDirection == 10 || PrevDirection == 11 || PrevDirection == 12 || PrevDirection == 13) && (NextDirection == 1 || NextDirection == 2 || NextDirection == 3 || NextDirection == 4))
						continue;
					if((PrevDirection == 5 || PrevDirection == 6 || PrevDirection == 7 || PrevDirection == 8 || PrevDirection == 9) && (NextDirection == 14 || NextDirection == 15 || NextDirection == 16 || NextDirection == 17 || NextDirection == 18))
						continue;
					if((PrevDirection == 14 || PrevDirection == 15 || PrevDirection == 16 || PrevDirection == 17 || PrevDirection == 18) && (NextDirection == 5 || NextDirection == 6 || NextDirection == 7 || NextDirection == 8 || NextDirection == 9))
						continue;
				}

				NewNode.Score = 0;
				NewNode.Combo = 0;

				BOOL StopCollision = FALSE;
				for(Index1 = 0; Index1 < COLUMN; Index1++){
					for(Index2 = 0; Index2 < ROW; Index2++){
						if(ThisPath.Touch[Index1][Index2] > 0 && StopTable[Index1][Index2] == TRUE){
							StopCollision = TRUE;
							break;
						}
					}
					if(StopCollision)
						break;
				}

				if(StopCollision)
					continue;

				NewNode.ShortX = ThisPath.ShortX;
				NewNode.ShortY = ThisPath.ShortY;
				NewNode.CurrentX = ThisPath.CurrentX;
				NewNode.CurrentY = ThisPath.CurrentY;

				for(Index1 = 0; Index1 < COLUMN; Index1++)
					for(Index2 = 0; Index2 < ROW; Index2++){
						int Number = ThisPath.Table[Index1][Index2];
						int RemapX = Number / ROW;
						int RemapY = Number % ROW;
						NewNode.Table[Index1][Index2] = CurrentNode.Table[RemapX][RemapY];
					}

				NewNode.DFSIndex[NewNode.DFSCount] = DFSIndex;
				NewNode.DFSCount++;
				NewNode.Searched = FALSE;

				NewNode.Score = EvaluateScore(NewNode.Table, PuzzleTable, LowerBoundScore, &(NewNode.Combo));

				if(NewNode.Score <= LowerBoundScore)
					continue;

				for(Index1 = 0; Index1 < COLUMN; Index1++)
					for(Index2 = 0; Index2 < ROW; Index2++){
						int Number = ThisPath.ShortTable[Index1][Index2];
						int RemapX = Number / ROW;
						int RemapY = Number % ROW;
						NewNode.Table[Index1][Index2] = CurrentNode.Table[RemapX][RemapY];
					}

				NewNode.LastDirection = ThisPath.ShortLastDirection;

				if(NewNode.Score > ShortPathBest[BFSIndex][ThisPath.ShortStepSequence].Score)
					ShortPathBest[BFSIndex][ThisPath.ShortStepSequence] = NewNode;

				if(LastShortStepSequence != ThisPath.ShortStepSequence){
					if(LastShortStepSequence != -1){
						#pragma omp critical
						{
							if(PushToDestination(DestinationPool, ShortPathBest[BFSIndex][LastShortStepSequence], &DestinationCount, &LowerBoundScore))
								ImproveFlag = TRUE;
							ShortPathBest[BFSIndex][LastShortStepSequence].Score = 0;
						}					
					}
					LastShortStepSequence = ThisPath.ShortStepSequence;
				}
			}

			if(LastShortStepSequence != -1){
				#pragma omp critical
				{
					if(PushToDestination(DestinationPool, ShortPathBest[BFSIndex][LastShortStepSequence], &DestinationCount, &LowerBoundScore))
						ImproveFlag = TRUE;
				}
			}
		}

		DWORD EndTime = GetTickCount();

		swprintf_s(LocalMessage, L"第 %d 回搜尋，花費 %d 毫秒 (最多 %d 回，目標連擊數 %d): ", SearchRound + 1, EndTime - StartTime, (NeedTwoSecond ? Max2sSearch  : MaxSearch), TargetCombo);
		StrCatW(DisplayMessage, LocalMessage);

		MoveDestinationToSource(SourcePool, &SourceCount, DestinationPool, &DestinationCount);
		MoveDestinationToBackup(BackupPool, &BackupCount, DestinationPool, &DestinationCount);
		if(ImproveFlag == FALSE)
			break;
	}

	for(Index = 0; Index < MAX_KEEP_COUNT; Index++)
		free(ShortPathBest[Index]);

	int HighestIndex = 0;
	long long int HighestScore = BackupPool[HighestIndex].Score;
	unsigned int HighestStep = BackupPool[HighestIndex].DFSCount;

	for(Index = 0; Index < (int) BackupCount; Index++){
		if(BackupPool[Index].Score / (SCORE_OFFSET * 100) > HighestScore / (SCORE_OFFSET * 100)){
			HighestIndex = Index;
			HighestScore = BackupPool[Index].Score;
			HighestStep = BackupPool[Index].DFSCount;
		}else if(BackupPool[Index].Score / (SCORE_OFFSET * 100) == HighestScore / (SCORE_OFFSET * 100) && BackupPool[Index].DFSCount < HighestStep){
			HighestIndex = Index;
			HighestScore = BackupPool[Index].Score;
			HighestStep = BackupPool[Index].DFSCount;
		}else if(BackupPool[Index].Score / (SCORE_OFFSET * 100) == HighestScore / (SCORE_OFFSET * 100) && BackupPool[Index].DFSCount == HighestStep && BackupPool[Index].Score > HighestScore){
			HighestIndex = Index;
			HighestScore = BackupPool[Index].Score;
			HighestStep = BackupPool[Index].DFSCount;
		}
	}

	*BestPath = BackupPool[HighestIndex];
	return;
}

int RandomPosition(int Amount){
	int Index;
	int ReturnValue = 0;
	for(Index = 0; Index < Amount; Index++){
		unsigned int RandomNumber;
		rand_s(&RandomNumber);
		RandomNumber = RandomNumber % 3;
		RandomNumber--;
		ReturnValue += RandomNumber;
	}

	return ReturnValue;
}

void DisableWindow(BOOL Disable){
	HWND GameApplication = NULL, GameWindow = NULL;
	if(IsWindow(GameWindow) == FALSE){
		GameApplication = FindWindowEx(NULL, NULL, NULL, L"BlueStacks App Player for Windows (beta-1)");
		GameWindow = FindWindowEx(GameApplication, NULL, NULL, L"_ctl.Window");
	}

	if(IsWindow(GameWindow) == FALSE)
		return;

	if(IsWindow(TransparentWindow) == FALSE)
		return;

	RECT AppRect;
	GetWindowRect(GameApplication, &AppRect);
	
	if(Disable){
		EnableWindow(GameApplication, FALSE);
		SetWindowLong(TransparentWindow, GWL_EXSTYLE, GetWindowLong(TransparentWindow, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(TransparentWindow, 0, 1, LWA_ALPHA);
		SetWindowPos(TransparentWindow, HWND_TOPMOST, AppRect.left - 5, AppRect.top - 5, AppRect.right - AppRect.left + 10, AppRect.bottom - AppRect.top + 10, SWP_SHOWWINDOW | SWP_NOACTIVATE);
		SetWindowPos(GameApplication, HWND_NOTOPMOST, 0, 0, 486, 884, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}else{
		EnableWindow(GameApplication, TRUE);
		SetWindowLong(TransparentWindow, GWL_EXSTYLE, GetWindowLong(TransparentWindow, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(TransparentWindow, 0, 1, LWA_ALPHA);
		SetWindowPos(GameApplication, HWND_TOPMOST, 0, 0, 486, 884, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
		SetWindowPos(TransparentWindow, HWND_NOTOPMOST, AppRect.left - 5, AppRect.top - 5, AppRect.right - AppRect.left + 10, AppRect.bottom - AppRect.top + 10, SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}
}

void MouseClick(const HWND GameApplication, const HWND GameWindow, const int X, const int Y, const int ScreenWidth, const int ScreenHeight, const int Delay, const int Left, const int Top, const int AppLeft, const int AppTop, const int AppRight, const int AppBottom, POINT *LastPosition, const BOOL IsMouseDown){
	POINT CurrentPosition;
	GetCursorPos(&CurrentPosition);

	if(!RealMouse)
		CurrentPosition = *LastPosition;

	int Index, LocalX, LocalY;
	int MoveCount = Delay / SMOOTH_SLEEP;
	for(Index = 1; Index < MoveCount + 1; Index++){
		INPUT Input;
		Input.type = INPUT_MOUSE;

		LocalX = (CurrentPosition.x * (MoveCount - Index) + X * Index) / MoveCount + (IsMouseDown ? 0 : RandomPosition(3));
		LocalY = (CurrentPosition.y * (MoveCount - Index) + Y * Index) / MoveCount + (IsMouseDown ? 0 : RandomPosition(3));
		Input.mi.dx =  LocalX * 65536 / ScreenWidth;
		Input.mi.dy =  LocalY * 65536 / ScreenHeight;

		int Index1, Index2;
		BOOL InCritical = FALSE;
		for(Index1 = 0; Index1 < COLUMN; Index1++){
			for(Index2 = 0; Index2 < ROW; Index2++){
				if(LocalX - CornerX[Index1] - Left < 2 && LocalX - CornerX[Index1] - Left > -2){
					InCritical = TRUE;
					break;
				}
				if(LocalY - CornerY[Index2] - Top < 2 && LocalY - CornerY[Index2] - Top > -2){
					InCritical = TRUE;
					break;
				}
			}
			if(InCritical == TRUE)
				break;
		}

		if(InCritical)
			continue;

		Input.mi.mouseData = 0;
		Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | (IsMouseDown ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP);
		Input.mi.time = 0;
		Input.mi.dwExtraInfo = 0;

		DisableWindow(TRUE);

		if(IsMouseDown){
			if(RealMouse)
				SendInput(1, &Input, sizeof(Input));
			SendNotifyMessage(GameApplication, WM_LBUTTONDOWN, MK_LBUTTON, (LocalX - Left) + (LocalY - Top + 1 /* correction for window mismatch? */) * 65536);
		}else{
			if(RealMouse)
				SendInput(1, &Input, sizeof(Input));
			SendNotifyMessage(GameApplication, WM_LBUTTONUP, 0, (LocalX - Left) + (LocalY - Top + 1 /* correction for window mismatch? */) * 65536);
		}

		Sleep(Delay / MoveCount);
	}
	LastPosition->x = X;
	LastPosition->y = Y;
}

struct MouseActions{
	int StartX;
	int StartY;
	struct XYPair MousePoints[((SINGLE_MOVE_MAX_SEARCH > MULTI_MOVE_MAX_SEARCH ? SINGLE_MOVE_MAX_SEARCH : MULTI_MOVE_MAX_SEARCH) * (SINGLE_MOVE_MAX_SHORT_STEP > MULTI_MOVE_MAX_SHORT_STEP ? SINGLE_MOVE_MAX_SHORT_STEP : MULTI_MOVE_MAX_SHORT_STEP) + (SINGLE_MOVE_MAX_STEP > MULTI_MOVE_MAX_STEP ? SINGLE_MOVE_MAX_STEP : MULTI_MOVE_MAX_STEP)) * 100];
	int MousePointCount;
	int DirectionSequence[(SINGLE_MOVE_MAX_SEARCH > MULTI_MOVE_MAX_SEARCH ? SINGLE_MOVE_MAX_SEARCH : MULTI_MOVE_MAX_SEARCH) * (SINGLE_MOVE_MAX_SHORT_STEP > MULTI_MOVE_MAX_SHORT_STEP ? SINGLE_MOVE_MAX_SHORT_STEP : MULTI_MOVE_MAX_SHORT_STEP) + (SINGLE_MOVE_MAX_STEP > MULTI_MOVE_MAX_STEP ? SINGLE_MOVE_MAX_STEP : MULTI_MOVE_MAX_STEP)];
	int DirectionCount;
};

int Move(const int MovingType, const struct BFSNode Path, struct DFSPath *PreBuildPath[COLUMN][ROW], const BOOL StopTable[COLUMN][ROW], struct MouseActions *MouseAction, wchar_t URL[MAX_MESSAGE]){
	int ButtonDownX = Path.StartX;
	int ButtonDownY = Path.StartY;

	int StepCount = 0;
	StrCatW(DisplayMessage, L"移動路徑:\r\n");

	wchar_t LocalMessage[MAX_MESSAGE];
	swprintf_s(LocalMessage, L"(%d, %d)->", ButtonDownX, ButtonDownY);
	StrCatW(DisplayMessage, LocalMessage);
	if(StepCount % 10 == 9)
		StrCatW(DisplayMessage, L"\r\n");

	if(StopTable[ButtonDownX][ButtonDownY] == TRUE){
		return 0;
	}

	StrCatW(URL, L"&route=");
	swprintf_s(LocalMessage, L"%d%d,", Path.StartX, Path.StartY + 5);
	StrCatW(URL, LocalMessage);

	if(EmulateHuman == FALSE){
		MouseAction->MousePoints[MouseAction->MousePointCount].X = ButtonDownX;
		MouseAction->MousePoints[MouseAction->MousePointCount].Y = ButtonDownY;
		MouseAction->MousePointCount++;
	}else{
		MouseAction->StartX = ButtonDownX;
		MouseAction->StartY = ButtonDownY;
	}
	StepCount++;

	unsigned int Index1;
	int Index2;
	int CurrentX = Path.StartX;
	int CurrentY = Path.StartY;

	for(Index1 = 0; Index1 < Path.DFSCount; Index1++){
		int Directions[(SINGLE_MOVE_MAX_STEP > MULTI_MOVE_MAX_STEP ? SINGLE_MOVE_MAX_STEP : MULTI_MOVE_MAX_STEP)];
		unsigned int DirectionCount = 0;
		int StepSequence = 0;
		if(Index1 < Path.DFSCount - 1){
			StepSequence = PreBuildPath[CurrentX][CurrentY][Path.DFSIndex[Index1]].ShortStepSequence;
			DirectionCount = PreBuildPath[CurrentX][CurrentY][Path.DFSIndex[Index1]].ShortStepCount;
		}else{
			StepSequence = PreBuildPath[CurrentX][CurrentY][Path.DFSIndex[Index1]].StepSequence;
			DirectionCount = PreBuildPath[CurrentX][CurrentY][Path.DFSIndex[Index1]].StepCount;
		}
		int TempX = CurrentX;
		int TempY = CurrentY;
		CurrentX = PreBuildPath[TempX][TempY][Path.DFSIndex[Index1]].ShortX;
		CurrentY = PreBuildPath[TempX][TempY][Path.DFSIndex[Index1]].ShortY;

		int MaxDirection;
		if(MovingType == 0)
			MaxDirection = SINGLE_MOVE_DIRECTION;
		else if(MovingType == 1)
			MaxDirection = MULTI_MOVE_DIRECTION;

		for(Index2 = 0; Index2 < (int) DirectionCount; Index2++){
			Directions[Index2] = StepSequence % (MaxDirection + 1);
			StepSequence /= (MaxDirection + 1);
		}

		for(Index2 = (int) DirectionCount - 1; Index2 >= 0; Index2--){
			if(MovingType == 0){
				if(Directions[Index2] == 1){ // 向上
					StrCatW(URL, L"6");
					ButtonDownY--;
				}else if(Directions[Index2] == 2){ // 向右
					StrCatW(URL, L"4");
					ButtonDownX++;
				}else if(Directions[Index2] == 3){ // 向下
					StrCatW(URL, L"1");
					ButtonDownY++;
				}else if(Directions[Index2] == 4){ // 向左
					StrCatW(URL, L"3");
					ButtonDownX--;
				}else if(Directions[Index2] == 5){ // 向右上
					StrCatW(URL, L"7");
					ButtonDownX++;
					ButtonDownY--;
				}else if(Directions[Index2] == 6){ // 向右下
					StrCatW(URL, L"2");
					ButtonDownX++;
					ButtonDownY++;
				}else if(Directions[Index2] == 7){ // 向左下
					StrCatW(URL, L"0");
					ButtonDownX--;
					ButtonDownY++;
				}else if(Directions[Index2] == 8){ // 向左上
					StrCatW(URL, L"5");
					ButtonDownX--;
					ButtonDownY--;
				}else if(Directions[Index2] == 0)
					continue;
			}else if(MovingType == 1){
				if(Directions[Index2] == 1){
					StrCatW(URL, L"6");
					ButtonDownY -= 1;
				}else if(Directions[Index2] == 2){
					StrCatW(URL, L"66");
					ButtonDownY -= 2;
				}else if(Directions[Index2] == 3){
					StrCatW(URL, L"666");
					ButtonDownY -= 3;
				}else if(Directions[Index2] == 4){
					StrCatW(URL, L"6666");
					ButtonDownY -= 4;
				}else if(Directions[Index2] == 5){
					StrCatW(URL, L"4");
					ButtonDownX += 1;
				}else if(Directions[Index2] == 6){
					StrCatW(URL, L"44");
					ButtonDownX += 2;
				}else if(Directions[Index2] == 7){
					StrCatW(URL, L"444");
					ButtonDownX += 3;
				}else if(Directions[Index2] == 8){
					StrCatW(URL, L"4444");
					ButtonDownX += 4;
				}else if(Directions[Index2] == 9){
					StrCatW(URL, L"44444");
					ButtonDownX += 5;
				}else if(Directions[Index2] == 10){
					StrCatW(URL, L"1");
					ButtonDownY += 1;
				}else if(Directions[Index2] == 11){
					StrCatW(URL, L"11");
					ButtonDownY += 2;
				}else if(Directions[Index2] == 12){
					StrCatW(URL, L"111");
					ButtonDownY += 3;
				}else if(Directions[Index2] == 13){
					StrCatW(URL, L"1111");
					ButtonDownY += 4;
				}else if(Directions[Index2] == 14){
					StrCatW(URL, L"3");
					ButtonDownX -= 1;
				}else if(Directions[Index2] == 15){
					StrCatW(URL, L"33");
					ButtonDownX -= 2;
				}else if(Directions[Index2] == 16){
					StrCatW(URL, L"333");
					ButtonDownX -= 3;
				}else if(Directions[Index2] == 17){
					StrCatW(URL, L"3333");
					ButtonDownX -= 4;
				}else if(Directions[Index2] == 18){
					StrCatW(URL, L"33333");
					ButtonDownX -= 5;
				}else if(Directions[Index2] == 0)
					continue;
			}

			if(EmulateHuman == TRUE){
				MouseAction->DirectionSequence[MouseAction->DirectionCount] = Directions[Index2];
				MouseAction->DirectionCount++;
			}

			swprintf_s(LocalMessage, L"(%d, %d)->", ButtonDownX, ButtonDownY);
			StrCatW(DisplayMessage, LocalMessage);
			if(StepCount % 10 == 9)
				StrCatW(DisplayMessage, L"\r\n");

			if(StopTable[ButtonDownX][ButtonDownY] == TRUE){
				return 0;
			}

			if(EmulateHuman == FALSE){
				MouseAction->MousePoints[MouseAction->MousePointCount].X = ButtonDownX;
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = ButtonDownY;
				MouseAction->MousePointCount++;
			}
			StepCount++;
		}
	}

	if(EmulateHuman){
		MouseAction->DirectionSequence[MouseAction->DirectionCount] = 0;
		MouseAction->DirectionCount++;
	}

	StrCatW(URL, L"&ctwMode=false");
	if(Preview){
		ShellExecute(NULL, L"open", URL, 0, 0, 1);
		if(AfxMessageBox(L"是否執行本次計算結果？", MB_OKCANCEL) == IDCANCEL)
			return 0;
	}
	return 1;
}

void MoveMouse(const struct MouseActions *MouseAction){
	static HWND GameApplication = NULL, GameWindow = NULL;
	HDC ScreenDC = GetDC(HWND_DESKTOP);
	int ScreenWidth = GetDeviceCaps(ScreenDC, HORZRES);
	int ScreenHeight = GetDeviceCaps(ScreenDC, VERTRES);
	ReleaseDC(HWND_DESKTOP, ScreenDC);

	if(IsWindow(GameWindow) == FALSE){
		GameApplication = FindWindowEx(NULL, NULL, NULL, L"BlueStacks App Player for Windows (beta-1)");
		GameWindow = FindWindowEx(GameApplication, NULL, NULL, L"_ctl.Window");
	}

	if(IsWindow(GameWindow) == FALSE)
		return;

	RECT GameRect;
	GetWindowRect(GameWindow, &GameRect);
	RECT ApplicationRect;
	GetWindowRect(GameApplication, &ApplicationRect);

	POINT LastPosition;
	LastPosition.x = (ApplicationRect.left + ApplicationRect.right) / 2;
	LastPosition.y = (ApplicationRect.top + ApplicationRect.bottom) / 2;

	int Index = 0;
	MouseClick(GameApplication, GameWindow, CenterX[MouseAction->MousePoints[Index].X] + GameRect.left, CenterY[MouseAction->MousePoints[Index].Y] + GameRect.top, ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, FALSE);
	for(Index = 0; Index < MouseAction->MousePointCount; Index++){
		MouseClick(GameApplication, GameWindow, CenterX[MouseAction->MousePoints[Index].X] + GameRect.left, CenterY[MouseAction->MousePoints[Index].Y] + GameRect.top, ScreenWidth, ScreenHeight, MOUSE_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
		if(Index == 0)
			Sleep(INITIAL_SLEEP);
	}
	MouseClick(GameApplication, GameWindow, CenterX[MouseAction->MousePoints[Index - 1].X] + GameRect.left, CenterY[MouseAction->MousePoints[Index - 1].Y] + GameRect.top, ScreenWidth, ScreenHeight, MOUSE_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
	MouseClick(GameApplication, GameWindow, CenterX[MouseAction->MousePoints[Index - 1].X] + GameRect.left, CenterY[MouseAction->MousePoints[Index - 1].Y] + GameRect.top, ScreenWidth, ScreenHeight, MOUSE_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, FALSE);
}

void MoveMouseHuman(const int MovingType, struct MouseActions *MouseAction){
	// sitos: need to optimize the path of multi-move scheme
	while(1){
		MouseAction->MousePointCount = 0;

		MouseAction->MousePoints[MouseAction->MousePointCount].X = CenterX[MouseAction->StartX] + RandomPosition(3);
		MouseAction->MousePoints[MouseAction->MousePointCount].Y = CenterY[MouseAction->StartY] + RandomPosition(3);
		MouseAction->MousePointCount++;

		int NextX = MouseAction->StartX;
		int NextY = MouseAction->StartY;

		if(MovingType == 0){
			if(MouseAction->DirectionSequence[0] == 1){
				NextY--;
			}else if(MouseAction->DirectionSequence[0] == 2){
				NextX++;
			}else if(MouseAction->DirectionSequence[0] == 3){
				NextY++;
			}else if(MouseAction->DirectionSequence[0] == 4){
				NextX--;
			}else if(MouseAction->DirectionSequence[0] == 5){
				NextX++;
				NextY--;
			}else if(MouseAction->DirectionSequence[0] == 6){
				NextX++;
				NextY++;
			}else if(MouseAction->DirectionSequence[0] == 7){
				NextX--;
				NextY++;
			}else if(MouseAction->DirectionSequence[0] == 8){
				NextX--;
				NextY--;
			}
		}else if(MovingType == 1){
			if(MouseAction->DirectionSequence[0] == 1 || MouseAction->DirectionSequence[0] == 2 || MouseAction->DirectionSequence[0] == 3 || MouseAction->DirectionSequence[0] == 4)
				NextY--;
			else if(MouseAction->DirectionSequence[0] == 5 || MouseAction->DirectionSequence[0] == 6 || MouseAction->DirectionSequence[0] == 7 || MouseAction->DirectionSequence[0] == 8 || MouseAction->DirectionSequence[0] == 9)
				NextX++;
			else if(MouseAction->DirectionSequence[0] == 10 || MouseAction->DirectionSequence[0] == 11 || MouseAction->DirectionSequence[0] == 12 || MouseAction->DirectionSequence[0] == 13)
				NextY++;
			else if(MouseAction->DirectionSequence[0] == 14 || MouseAction->DirectionSequence[0] == 15 || MouseAction->DirectionSequence[0] == 16 || MouseAction->DirectionSequence[0] == 17 || MouseAction->DirectionSequence[0] == 18)
				NextX--;
		}

		MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[MouseAction->StartX] * 5 + CenterX[NextX] * 1) / 6 + RandomPosition(3);
		MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[MouseAction->StartY] * 5 + CenterY[NextY] * 1) / 6 + RandomPosition(3);
		MouseAction->MousePointCount++;

		if(MovingType == 0){
			MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[MouseAction->StartX] * 4 + CenterX[NextX] * 2) / 6;
			MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[MouseAction->StartY] * 4 + CenterY[NextY] * 2) / 6;
			MouseAction->MousePointCount++;
		}else if(MovingType == 1){
			MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[MouseAction->StartX] * 4 + CenterX[NextX] * 2) / 6 + RandomPosition(3);
			MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[MouseAction->StartY] * 4 + CenterY[NextY] * 2) / 6 + RandomPosition(3);
			MouseAction->MousePointCount++;
		}

		int X0 = MouseAction->StartX;
		int Y0 = MouseAction->StartY;
		int RealX0 = X0;
		int RealY0 = Y0;

		int Index;
		for(Index = 0; Index < MouseAction->DirectionCount - 1; Index++){
			int Direction = MouseAction->DirectionSequence[Index];
			int NextDirection = MouseAction->DirectionSequence[Index + 1];

			RealX0 = X0;
			RealY0 = Y0;

			int X1 = X0, Y1 = Y0, X2 = X1, Y2 = Y1;
			int RealX2 = X0;
			int RealY2 = Y0;
			if(MovingType == 0){
				if(Direction == 1){
					X1 = X0;
					Y1 = Y0 - 1;
				}else if(Direction == 2){
					X1 = X0 + 1;
					Y1 = Y0;
				}else if(Direction == 3){
					X1 = X0;
					Y1 = Y0 + 1;
				}else if(Direction == 4){
					X1 = X0 - 1;
					Y1 = Y0;
				}else if(Direction == 5){
					X1 = X0 + 1;
					Y1 = Y0 - 1;
				}else if(Direction == 6){
					X1 = X0 + 1;
					Y1 = Y0 + 1;
				}else if(Direction == 7){
					X1 = X0 - 1;
					Y1 = Y0 + 1;
				}else if(Direction == 8){
					X1 = X0 - 1;
					Y1 = Y0 - 1;
				}
			}else if(MovingType == 1){
				if(Direction == 1){
					Y1 = Y0 - 1;
					Y0 = Y1 + 1;
				}else if(Direction == 2){
					Y1 = Y0 - 2;
					Y0 = Y1 + 1;
				}else if(Direction == 3){
					Y1 = Y0 - 3;
					Y0 = Y1 + 1;
				}else if(Direction == 4){
					Y1 = Y0 - 4;
					Y0 = Y1 + 1;
				}else if(Direction == 5){
					X1 = X0 + 1;
					X0 = X1 - 1;
				}else if(Direction == 6){
					X1 = X0 + 2;
					X0 = X1 - 1;
				}else if(Direction == 7){
					X1 = X0 + 3;
					X0 = X1 - 1;
				}else if(Direction == 8){
					X1 = X0 + 4;
					X0 = X1 - 1;
				}else if(Direction == 9){
					X1 = X0 + 5;
					X0 = X1 - 1;
				}else if(Direction == 10){
					Y1 = Y0 + 1;
					Y0 = Y1 - 1;
				}else if(Direction == 11){
					Y1 = Y0 + 2;
					Y0 = Y1 - 1;
				}else if(Direction == 12){
					Y1 = Y0 + 3;
					Y0 = Y1 - 1;
				}else if(Direction == 13){
					Y1 = Y0 + 4;
					Y0 = Y1 - 1;
				}else if(Direction == 14){
					X1 = X0 - 1;
					X0 = X1 + 1;
				}else if(Direction == 15){
					X1 = X0 - 2;
					X0 = X1 + 1;
				}else if(Direction == 16){
					X1 = X0 - 3;
					X0 = X1 + 1;
				}else if(Direction == 17){
					X1 = X0 - 4;
					X0 = X1 + 1;
				}else if(Direction == 18){
					X1 = X0 - 5;
					X0 = X1 + 1;
				}
			}

			if(MovingType == 0){
				if(NextDirection == 1){
					X2 = X1;
					Y2 = Y1 - 1;
				}else if(NextDirection == 2){
					X2 = X1 + 1;
					Y2 = Y1;
				}else if(NextDirection == 3){
					X2 = X1;
					Y2 = Y1 + 1;
				}else if(NextDirection == 4){
					X2 = X1 - 1;
					Y2 = Y1;
				}else if(NextDirection == 5){
					X2 = X1 + 1;
					Y2 = Y1 - 1;
				}else if(NextDirection == 6){
					X2 = X1 + 1;
					Y2 = Y1 + 1;
				}else if(NextDirection == 7){
					X2 = X1 - 1;
					Y2 = Y1 + 1;
				}else if(NextDirection == 8){
					X2 = X1 - 1;
					Y2 = Y1 - 1;
				}
			}else if(MovingType == 1){
				if(NextDirection == 1){
					X2 = X1;
					Y2 = Y1 - 1;
					RealX2 = X1;
					RealY2 = Y1 - 1;
				}else if(NextDirection == 2){
					X2 = X1;
					Y2 = Y1 - 1;
					RealX2 = X1;
					RealY2 = Y1 - 2;
				}else if(NextDirection == 3){
					X2 = X1;
					Y2 = Y1 - 1;
					RealX2 = X1;
					RealY2 = Y1 - 3;
				}else if(NextDirection == 4){
					X2 = X1;
					Y2 = Y1 - 1;
					RealX2 = X1;
					RealY2 = Y1 - 4;
				}else if(NextDirection == 5){
					Y2 = Y1;
					X2 = X1 + 1;
					RealY2 = Y1;
					RealX2 = X1 + 1;
				}else if(NextDirection == 6){
					Y2 = Y1;
					X2 = X1 + 1;
					RealY2 = Y1;
					RealX2 = X1 + 2;
				}else if(NextDirection == 7){
					Y2 = Y1;
					X2 = X1 + 1;
					RealY2 = Y1;
					RealX2 = X1 + 3;
				}else if(NextDirection == 8){
					Y2 = Y1;
					X2 = X1 + 1;
					RealY2 = Y1;
					RealX2 = X1 + 4;
				}else if(NextDirection == 9){
					Y2 = Y1;
					X2 = X1 + 1;
					RealY2 = Y1;
					RealX2 = X1 + 5;
				}else if(NextDirection == 10){
					X2 = X1;
					Y2 = Y1 + 1;
					RealX2 = X1;
					RealY2 = Y1 + 1;
				}else if(NextDirection == 11){
					X2 = X1;
					Y2 = Y1 + 1;
					RealX2 = X1;
					RealY2 = Y1 + 2;
				}else if(NextDirection == 12){
					X2 = X1;
					Y2 = Y1 + 1;
					RealX2 = X1;
					RealY2 = Y1 + 3;
				}else if(NextDirection == 13){
					X2 = X1;
					Y2 = Y1 + 1;
					RealX2 = X1;
					RealY2 = Y1 + 4;
				}else if(NextDirection == 14){
					Y2 = Y1;
					X2 = X1 - 1;
					RealY2 = Y1;
					RealX2 = X1 - 1;
				}else if(NextDirection == 15){
					Y2 = Y1;
					X2 = X1 - 1;
					RealY2 = Y1;
					RealX2 = X1 - 2;
				}else if(NextDirection == 16){
					Y2 = Y1;
					X2 = X1 - 1;
					RealY2 = Y1;
					RealX2 = X1 - 3;
				}else if(NextDirection == 17){
					Y2 = Y1;
					X2 = X1 - 1;
					RealY2 = Y1;
					RealX2 = X1 - 4;
				}else if(NextDirection == 18){
					Y2 = Y1;
					X2 = X1 - 1;
					RealY2 = Y1;
					RealX2 = X1 - 5;
				}			
			}

			if(MovingType == 1 && Direction != 1 && Direction != 5 && Direction != 10 && Direction != 14){
				int Distance = (RealX0 - X1) + (RealY0 - Y1);
				if(Distance < 0)
					Distance = Distance * -1;
				Distance--;

				int StayCount;
				if(Distance == 1)
					StayCount = 2;
				if(Distance == 2)
					StayCount = 3;
				if(Distance == 3)
					StayCount = 4;
				if(Distance == 4)
					StayCount = 5;

				if(StayCount == 2){
					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 47 + CenterX[X1] * 33) / 80 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 47 + CenterY[Y1] * 33) / 80 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 33 + CenterX[X1] * 47) / 80 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 33 + CenterY[Y1] * 47) / 80 + RandomPosition(3);
					MouseAction->MousePointCount++;
				}else if(StayCount == 3){
					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 80 + CenterX[X1] * 40) / 120 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 80 + CenterY[Y1] * 40) / 120 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 60 + CenterX[X1] * 60) / 120 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 60 + CenterY[Y1] * 60) / 120 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 40 + CenterX[X1] * 80) / 120 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 40 + CenterY[Y1] * 80) / 120 + RandomPosition(3);
					MouseAction->MousePointCount++;
				}else if(StayCount == 4){
					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 116 + CenterX[X1] * 44) / 160 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 116 + CenterY[Y1] * 44) / 160 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 92 + CenterX[X1] * 68) / 160 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 92 + CenterY[Y1] * 68) / 160 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 68 + CenterX[X1] * 92) / 160 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 68 + CenterY[Y1] * 92) / 160 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 44 + CenterX[X1] * 116) / 160 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 44 + CenterY[Y1] * 116) / 160 + RandomPosition(3);
					MouseAction->MousePointCount++;
				}else if(StayCount == 5){
					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 154 + CenterX[X1] * 46) / 200 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 154 + CenterY[Y1] * 46) / 200 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 128 + CenterX[X1] * 72) / 200 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 128 + CenterY[Y1] * 72) / 200 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 100 + CenterX[X1] * 100) / 200 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 100 + CenterY[Y1] * 100) / 200 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 72 + CenterX[X1] * 128) / 200 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 72 + CenterY[Y1] * 128) / 200 + RandomPosition(3);
					MouseAction->MousePointCount++;

					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[RealX0] * 46 + CenterX[X1] * 154) / 200 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[RealY0] * 46 + CenterY[Y1] * 154) / 200 + RandomPosition(3);
					MouseAction->MousePointCount++;
				}
			}

			if(NextDirection == 0){
				if(MovingType == 0){
					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[X0] * 2 + CenterX[X1] * 4) / 6;
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[Y0] * 2 + CenterY[Y1] * 4) / 6;
					MouseAction->MousePointCount++;
				}else{
					MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[X0] * 2 + CenterX[X1] * 4) / 6 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[Y0] * 2 + CenterY[Y1] * 4) / 6 + RandomPosition(3);
					MouseAction->MousePointCount++;
				}

				MouseAction->MousePoints[MouseAction->MousePointCount].X = (CenterX[X0] * 1 + CenterX[X1] * 5) / 6 + RandomPosition(3);
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = (CenterY[Y0] * 1 + CenterY[Y1] * 5) / 6 + RandomPosition(3);
				MouseAction->MousePointCount++;

				MouseAction->MousePoints[MouseAction->MousePointCount].X = CenterX[X1] + RandomPosition(3);
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = CenterY[Y1] + RandomPosition(3);
				MouseAction->MousePointCount++;

				MouseAction->MousePoints[MouseAction->MousePointCount].X = CenterX[X1] + RandomPosition(3);
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = CenterY[Y1] + RandomPosition(3);
				MouseAction->MousePointCount++;

				MouseAction->MousePoints[MouseAction->MousePointCount].X = CenterX[X1] + RandomPosition(3);
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = CenterY[Y1] + RandomPosition(3);
				MouseAction->MousePointCount++;

				MouseAction->MousePoints[MouseAction->MousePointCount].X = CenterX[X1] + RandomPosition(3);
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = CenterY[Y1] + RandomPosition(3);
				MouseAction->MousePointCount++;
				break;
			}

			int PointX1 = (CenterX[X0] + CenterX[X1]) / 2;
			int PointY1 = (CenterY[Y0] + CenterY[Y1]) / 2;
			int PointX7 = (CenterX[X1] + CenterX[X2]) / 2;
			int PointY7 = (CenterY[Y1] + CenterY[Y2]) / 2;

			int PointX3 = (CenterX[X1] * 2 + PointX1) / 3;
			int PointY3 = (CenterY[Y1] * 2 + PointY1) / 3;
			int PointX5 = (CenterX[X1] * 2 + PointX7) / 3;
			int PointY5 = (CenterY[Y1] * 2 + PointY7) / 3;

			int PointX2 = (PointX1 + PointX3) / 2;
			int PointY2 = (PointY1 + PointY3) / 2;
			int PointX4 = (PointX3 + PointX5) / 2;
			int PointY4 = (PointY3 + PointY5) / 2;
			int PointX6 = (PointX5 + PointX7) / 2;
			int PointY6 = (PointY5 + PointY7) / 2;

			if(MovingType == 0){
				MouseAction->MousePoints[MouseAction->MousePointCount].X = PointX2;
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = PointY2;
				MouseAction->MousePointCount++;
			}else{
				MouseAction->MousePoints[MouseAction->MousePointCount].X = PointX2 + RandomPosition(3);
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = PointY2 + RandomPosition(3);
				MouseAction->MousePointCount++;
			}

			MouseAction->MousePoints[MouseAction->MousePointCount].X = (PointX2 + PointX3 + PointX4) / 3 + RandomPosition(3);
			MouseAction->MousePoints[MouseAction->MousePointCount].Y = (PointY2 + PointY3 + PointY4) / 3 + RandomPosition(3);
			MouseAction->MousePointCount++;

			MouseAction->MousePoints[MouseAction->MousePointCount].X = PointX4 + RandomPosition(3);
			MouseAction->MousePoints[MouseAction->MousePointCount].Y = PointY4 + RandomPosition(3);
			MouseAction->MousePointCount++;

			unsigned int RandomNumber;
			rand_s(&RandomNumber);

			if(RandomNumber % 5 == 0){
				unsigned int RepeatCount;
				rand_s(&RepeatCount);
				RepeatCount = RepeatCount % 5;
				RepeatCount++;

				int Index1;
				for(Index1 = 0; Index1 < (int) RepeatCount; Index1++){
					MouseAction->MousePoints[MouseAction->MousePointCount].X = PointX4 + RandomPosition(3);
					MouseAction->MousePoints[MouseAction->MousePointCount].Y = PointY4 + RandomPosition(3);
					MouseAction->MousePointCount++;
				}
			}

			MouseAction->MousePoints[MouseAction->MousePointCount].X = (PointX4 + PointX5 + PointX6) / 3 + RandomPosition(3);
			MouseAction->MousePoints[MouseAction->MousePointCount].Y = (PointY4 + PointY5 + PointY6) / 3 + RandomPosition(3);
			MouseAction->MousePointCount++;

			if(MovingType == 0){
				MouseAction->MousePoints[MouseAction->MousePointCount].X = PointX6 + RandomPosition(3);
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = PointY6 + RandomPosition(3);
				MouseAction->MousePointCount++;
			}else{
				MouseAction->MousePoints[MouseAction->MousePointCount].X = PointX6 + RandomPosition(3);
				MouseAction->MousePoints[MouseAction->MousePointCount].Y = PointY6 + RandomPosition(3);
				MouseAction->MousePointCount++;
			}

			X0 = X1;
			Y0 = Y1;
		}

		int MaxSmoothStep, Max2sSmoothStep;
		if(MovingType == 0){
			MaxSmoothStep = SINGLE_MOVE_MAX_SMOOTH_STEP;
			Max2sSmoothStep = SINGLE_MOVE_MAX_2S_SMOOTH_STEP;
		}else if(MovingType == 1){
			MaxSmoothStep = MULTI_MOVE_MAX_SMOOTH_STEP;
			Max2sSmoothStep = MULTI_MOVE_MAX_2S_SMOOTH_STEP;
		}

		if(NeedTwoSecond == FALSE && MouseAction->MousePointCount < MaxSmoothStep)
			break;

		if(NeedTwoSecond == TRUE && MouseAction->MousePointCount < Max2sSmoothStep)
			break;
	}

	if(MovingType == 1){
		int GlobalShiftX = RandomPosition(12);
		int GlobalShiftY = RandomPosition(12);
		int Index;
		for(Index = 0; Index < MouseAction->MousePointCount; Index++){
			MouseAction->MousePoints[Index].X += GlobalShiftX;
			MouseAction->MousePoints[Index].Y += GlobalShiftY;
		}
	}

	static HWND GameApplication = NULL, GameWindow = NULL;
	HDC ScreenDC = GetDC(HWND_DESKTOP);
	int ScreenWidth = GetDeviceCaps(ScreenDC, HORZRES);
	int ScreenHeight = GetDeviceCaps(ScreenDC, VERTRES);
	ReleaseDC(HWND_DESKTOP, ScreenDC);

	if(IsWindow(GameWindow) == FALSE){
		GameApplication = FindWindowEx(NULL, NULL, NULL, L"BlueStacks App Player for Windows (beta-1)");
		GameWindow = FindWindowEx(GameApplication, NULL, NULL, L"_ctl.Window");
	}

	if(IsWindow(GameWindow) == FALSE)
		return;

	RECT GameRect;
	GetWindowRect(GameWindow, &GameRect);
	RECT ApplicationRect;
	GetWindowRect(GameApplication, &ApplicationRect);

	POINT LastPosition;
	LastPosition.x = (ApplicationRect.left + ApplicationRect.right) / 2;
	LastPosition.y = (ApplicationRect.top + ApplicationRect.bottom) / 2;

	int LocalSleep;
	LocalSleep = (NeedTwoSecond ? 1800 : 4800) / (MouseAction->MousePointCount);

	int Index = 0;
	if(RealMouse)
		MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index].X + GameRect.left, MouseAction->MousePoints[Index].Y + GameRect.top, ScreenWidth, ScreenHeight, INITIAL_SLEEP * 4, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, FALSE);
	else
		MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index].X + GameRect.left, MouseAction->MousePoints[Index].Y + GameRect.top, ScreenWidth, ScreenHeight, LocalSleep, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, FALSE);
	for(Index = 0; Index < MouseAction->MousePointCount; Index++){
		if(Index == 0){
			MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index].X + GameRect.left + RandomPosition(3), MouseAction->MousePoints[Index].Y + GameRect.top + RandomPosition(3), ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
			MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index].X + GameRect.left + RandomPosition(3), MouseAction->MousePoints[Index].Y + GameRect.top + RandomPosition(3), ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
			MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index].X + GameRect.left + RandomPosition(3), MouseAction->MousePoints[Index].Y + GameRect.top + RandomPosition(3), ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
			MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index].X + GameRect.left + RandomPosition(3), MouseAction->MousePoints[Index].Y + GameRect.top + RandomPosition(3), ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
		}
		else
			MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index].X + GameRect.left, MouseAction->MousePoints[Index].Y + GameRect.top, ScreenWidth, ScreenHeight, LocalSleep, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
	}
	MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index - 1].X + GameRect.left + RandomPosition(3), MouseAction->MousePoints[Index - 1].Y + GameRect.top + RandomPosition(3), ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
	MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index - 1].X + GameRect.left + RandomPosition(3), MouseAction->MousePoints[Index - 1].Y + GameRect.top + RandomPosition(3), ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
	MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index - 1].X + GameRect.left + RandomPosition(3), MouseAction->MousePoints[Index - 1].Y + GameRect.top + RandomPosition(3), ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
	MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index - 1].X + GameRect.left + RandomPosition(3), MouseAction->MousePoints[Index - 1].Y + GameRect.top + RandomPosition(3), ScreenWidth, ScreenHeight, INITIAL_SLEEP, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, TRUE);
	MouseClick(GameApplication, GameWindow, MouseAction->MousePoints[Index - 1].X + GameRect.left, MouseAction->MousePoints[Index - 1].Y + GameRect.top, ScreenWidth, ScreenHeight, LocalSleep, GameRect.left, GameRect.top, ApplicationRect.left, ApplicationRect.top, ApplicationRect.right, ApplicationRect.bottom, &LastPosition, FALSE);
}

void MainFunction(const SOCKET Connection){
	static BOOL DFSPathFlag = FALSE;
	static struct DFSPath *SingleMovePreBuildPath[COLUMN][ROW];
	static struct DFSPath *MultiMovePreBuildPath[COLUMN][ROW];
	static unsigned int SingleMovePreBuildPathCount[COLUMN][ROW];
	static unsigned int MultiMovePreBuildPathCount[COLUMN][ROW];
	static BOOL CleanDisplayMessage = TRUE;

	if(Pause){
		Sleep(RETRY_SLEEP);
		return;
	}

	if(DFSPathFlag == FALSE){
		StrCatW(DisplayMessage, L"正在初始化搜尋路徑...\r\n");
		int Index1, Index2;
		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++){
				SingleMovePreBuildPathCount[Index1][Index2] = 0;
				SingleMovePreBuildPath[Index1][Index2] = (struct DFSPath *) malloc(sizeof(struct DFSPath) * SINGLE_MOVE_MAX_PATH_COUNT);
				MultiMovePreBuildPathCount[Index1][Index2] = 0;
				MultiMovePreBuildPath[Index1][Index2] = (struct DFSPath *) malloc(sizeof(struct DFSPath) * MULTI_MOVE_MAX_PATH_COUNT);
			}
		BuildDFSPath(0, SingleMovePreBuildPath, SingleMovePreBuildPathCount);
		BuildDFSPath(1, MultiMovePreBuildPath, MultiMovePreBuildPathCount);
		DFSPathFlag = TRUE;
	}	

	unsigned int CurrentTable[COLUMN][ROW];
	BOOL PuzzleTable[COLUMN][ROW];
	BOOL StopTable[COLUMN][ROW];
	int CurrentTableResult = 0;

	if(ExecutionType == 1 || ExecutionType == 3){
		CurrentTableResult= GetTable(CurrentTable, PuzzleTable, StopTable);
		if(CurrentTableResult == 0 || Pause){
			Sleep(RETRY_SLEEP);
			return;
		}

		if(CleanDisplayMessage == TRUE){
			StrCpyW(DisplayMessage, L"");
			CleanDisplayMessage = FALSE;
		}

		PrintTable(CurrentTable, PuzzleTable, StopTable);
	}

	if(ExecutionType == 3){
		char SocketMessage[1024];
		memset(SocketMessage, 0, 1024);
		char *Pointer = SocketMessage;

		memcpy(Pointer, CurrentTable, sizeof(CurrentTable));
		Pointer += sizeof(CurrentTable);
		memcpy(Pointer, PuzzleTable, sizeof(PuzzleTable));
		Pointer += sizeof(PuzzleTable);
		memcpy(Pointer, StopTable, sizeof(StopTable));
		Pointer += sizeof(StopTable);
		memcpy(Pointer, &NeedEliminateSix, sizeof(NeedEliminateSix));
		Pointer += sizeof(NeedEliminateSix);
		memcpy(Pointer, &NeedHighPower, sizeof(NeedHighPower));
		Pointer += sizeof(NeedHighPower);
		memcpy(Pointer, &NeedTwoSecond, sizeof(NeedTwoSecond));
		Pointer += sizeof(NeedTwoSecond);
		memcpy(Pointer, &TargetCombo, sizeof(TargetCombo));
		Pointer += sizeof(TargetCombo);

		memcpy(Pointer, &NoOblique, sizeof(NoOblique));
		Pointer += sizeof(NoOblique);
		memcpy(Pointer, &ForceKeep, sizeof(ForceKeep));
		Pointer += sizeof(ForceKeep);
		memcpy(Pointer, MinKeep, sizeof(MinKeep));
		Pointer += sizeof(MinKeep);
		memcpy(Pointer, MaxEliminate, sizeof(MaxEliminate));
		Pointer += sizeof(MaxEliminate);
		memcpy(Pointer, ColorCountScore, sizeof(ColorCountScore));
		Pointer += sizeof(ColorCountScore);

		memcpy(Pointer, &LowerBoundCombo, sizeof(LowerBoundCombo));
		Pointer += sizeof(LowerBoundCombo);

		send(Connection, SocketMessage, (int) (Pointer - SocketMessage), 0);
	}

	if(ExecutionType == 2){
		char SocketMessage[1024];
		memset(SocketMessage, 0, 1024);
		recv(Connection, SocketMessage, 1024, 0);
		char *Pointer = SocketMessage;
		
		memcpy(CurrentTable, Pointer, sizeof(CurrentTable));
		Pointer += sizeof(CurrentTable);
		memcpy(PuzzleTable, Pointer, sizeof(PuzzleTable));
		Pointer += sizeof(PuzzleTable);
		memcpy(StopTable, Pointer, sizeof(StopTable));
		Pointer += sizeof(StopTable);
		memcpy(&NeedEliminateSix, Pointer, sizeof(NeedEliminateSix));
		Pointer += sizeof(NeedEliminateSix);
		memcpy(&NeedHighPower, Pointer, sizeof(NeedHighPower));
		Pointer += sizeof(NeedHighPower);
		memcpy(&NeedTwoSecond, Pointer, sizeof(NeedTwoSecond));
		Pointer += sizeof(NeedTwoSecond);
		memcpy(&TargetCombo, Pointer, sizeof(TargetCombo));
		Pointer += sizeof(TargetCombo);

		memcpy(&NoOblique, Pointer, sizeof(NoOblique));
		Pointer += sizeof(NoOblique);
		memcpy(&ForceKeep, Pointer, sizeof(ForceKeep));
		Pointer += sizeof(ForceKeep);
		memcpy(MinKeep, Pointer, sizeof(MinKeep));
		Pointer += sizeof(MinKeep);
		memcpy(MaxEliminate, Pointer, sizeof(MaxEliminate));
		Pointer += sizeof(MaxEliminate);
		memcpy(ColorCountScore, Pointer, sizeof(ColorCountScore));
		Pointer += sizeof(ColorCountScore);

		memcpy(&LowerBoundCombo, Pointer, sizeof(LowerBoundCombo));
		Pointer += sizeof(LowerBoundCombo);
	}

	int MovingType;
	if(NoOblique)
		MovingType = 1;
	else
		MovingType = 0;

	struct BFSNode BestPath;
	memset(&BestPath, 0, sizeof(BestPath));

	if(ExecutionType == 1 || ExecutionType == 2){
		StrCatW(DisplayMessage, L"開始搜尋路徑...\r\n");
	
		if(MovingType == 0)
			SearchBestPath(MovingType, CurrentTable, PuzzleTable, StopTable, SingleMovePreBuildPath, SingleMovePreBuildPathCount, &BestPath);
		else if(MovingType == 1)
			SearchBestPath(MovingType, CurrentTable, PuzzleTable, StopTable, MultiMovePreBuildPath, MultiMovePreBuildPathCount, &BestPath);

		if(Pause)
			return;

		if(BestPath.Score == 0){
			StrCatW(DisplayMessage, L"找不到適合的解\r\n");
			return;
		}
	}

	if(ExecutionType == 2){
		char SocketMessage[1024];
		memset(SocketMessage, 0, 1024);

		memcpy(SocketMessage, &BestPath, sizeof(BestPath));
		send(Connection, SocketMessage, sizeof(BestPath), 0);
	}

	if(ExecutionType == 3){
		char SocketMessage[1024];
		memset(SocketMessage, 0, 1024);

		recv(Connection, SocketMessage, 1024, 0);
		memcpy(&BestPath, SocketMessage, sizeof(BestPath));
	}

	if(ExecutionType == 1 || ExecutionType == 3){
		unsigned int CurrentTable2[COLUMN][ROW];
		BOOL PuzzleTable2[COLUMN][ROW];
		BOOL StopTable2[COLUMN][ROW];

		CurrentTableResult = GetTable(CurrentTable2, PuzzleTable2, StopTable2);
		if(CurrentTableResult == 0 || Pause){
			Sleep(RETRY_SLEEP);
			return;
		}

		int Index1, Index2;
		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++){
				if(CurrentTable[Index1][Index2] != CurrentTable2[Index1][Index2]){
					Sleep(RETRY_SLEEP);
					return;
				}
				if(PuzzleTable[Index1][Index2] != PuzzleTable2[Index1][Index2]){
					Sleep(RETRY_SLEEP);
					return;
				}
				if(StopTable[Index1][Index2] != StopTable2[Index1][Index2]){
					Sleep(RETRY_SLEEP);
					return;
				}
			}


		StrCatW(DisplayMessage, L"移動滑鼠...\r\n");

		struct MouseActions MouseAction;
		MouseAction.MousePointCount = 0;
		MouseAction.DirectionCount = 0;

		wchar_t LocalMessage[MAX_MESSAGE];

		swprintf_s(LocalMessage, L"預計效果: 連擊數: %d, 拼圖盾: %s, 原始分數: %lld\r\n", BestPath.Combo, (BestPath.Score >= MEET_PUZZLE_SCORE ? L"已達成" : L"未達成"), BestPath.Score);
		StrCatW(DisplayMessage, LocalMessage);

		wchar_t URL[MAX_MESSAGE];
		StrCpyW(URL, L"http://serizawa.web5.jp/puzzdra_theory_maker/index.html?layout=");

		for(Index2 = 0; Index2 < ROW; Index2++)
			for(Index1 = 0; Index1 < COLUMN; Index1++)
				if(CurrentTable[Index1][Index2] == 1)
					StrCatW(URL, L"3");
				else if(CurrentTable[Index1][Index2] == 2)
					StrCatW(URL, L"5");
				else if(CurrentTable[Index1][Index2] == 3)
					StrCatW(URL, L"2");
				else if(CurrentTable[Index1][Index2] == 4)
					StrCatW(URL, L"4");
				else if(CurrentTable[Index1][Index2] == 5)
					StrCatW(URL, L"1");
				else if(CurrentTable[Index1][Index2] == 6)
					StrCatW(URL, L"0");
				else if(CurrentTable[Index1][Index2] == 7)
					StrCatW(URL, L"6");

		struct DFSPath *PreBuildPath[COLUMN][ROW];
		for(Index1 = 0; Index1 < COLUMN; Index1++)
			for(Index2 = 0; Index2 < ROW; Index2++)
				if(MovingType == 0)
					PreBuildPath[Index1][Index2] = SingleMovePreBuildPath[Index1][Index2];
				else
					PreBuildPath[Index1][Index2] = MultiMovePreBuildPath[Index1][Index2];

		if(Pause)
			return;

		if(Move(MovingType, BestPath, PreBuildPath, StopTable, &MouseAction, URL)){
			DisableWindow(TRUE);
			if(EmulateHuman == FALSE)
				MoveMouse(&MouseAction);
			else
				MoveMouseHuman(MovingType, &MouseAction);
			DisableWindow(FALSE);
			CleanDisplayMessage = TRUE;
		}
	}
}

void CToS2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	static wchar_t LocalMessage[MAX_MESSAGE] = {0};
	UpdateData(TRUE);
	TargetCombo = ComboLimit;
	NeedHighPower = CheckNeedHighPower;
	NeedEliminateSix = CheckNeedEliminateSix;
	NeedTwoSecond = CheckNeedTwoSecond;
	EmulateHuman = CheckEmulateHuman;
	RealMouse = CheckRealMouse;
	Pause = CheckPause;
	NoOblique = CheckNoOblique;
	ServerIPAddress = ServerIP;
	ForceKeep = CheckForceKeep;
	Preview = CheckPreview;
	LowerBoundCombo = EditLowerBoundCombo;

	MinKeep[0] = MinLightKeep;
	MinKeep[1] = MinHeartKeep;
	MinKeep[2] = MinWaterKeep;
	MinKeep[3] = MinDarkKeep;
	MinKeep[4] = MinWoodKeep;
	MinKeep[5] = MinFireKeep;

	MaxEliminate[0] = MaxLightEliminate;
	MaxEliminate[1] = MaxHeartEliminate;
	MaxEliminate[2] = MaxWaterEliminate;
	MaxEliminate[3] = MaxDarkEliminate;
	MaxEliminate[4] = MaxWoodEliminate;
	MaxEliminate[5] = MaxFireEliminate;

	ColorCountScore[0] = CheckCountLightScore;
	ColorCountScore[1] = CheckCountHeartScore;
	ColorCountScore[2] = CheckCountWaterScore;
	ColorCountScore[3] = CheckCountDarkScore;
	ColorCountScore[4] = CheckCountWoodScore;
	ColorCountScore[5] = CheckCountFireScore;

	ExecutionType = ComboExecutionType.GetCurSel();

	if(StrCmpW(DisplayMessage, LocalMessage)){
		DisplayEdit.SetWindowTextW(DisplayMessage);
		DisplayEdit.SetSel(MAX, MAX);
		UpdateData(FALSE);
		StrCpyW(LocalMessage, DisplayMessage);
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

void MyThread(void *pParam){
	WSADATA WsaData;

	struct sockaddr_in ServerSocketAddr;
	SOCKET ServerSocket;

	struct sockaddr_in ConnectionAddr;
	int ConnectionAddrLen = sizeof(ConnectionAddr);
	SOCKET Connection = 0;


	if(ExecutionType == 2 || ExecutionType == 3){
		while(WSAStartup(0x101, &WsaData))
			Sleep(RETRY_SLEEP);
	}

	if(ExecutionType == 2){
		memset(&ServerSocketAddr, 0, sizeof(ServerSocketAddr));
		ServerSocketAddr.sin_family = AF_INET;
		ServerSocketAddr.sin_port = htons(SERVER_PORT);
		ServerSocketAddr.sin_addr.s_addr = INADDR_ANY;

		ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

		char OptVal = TRUE;
		int OptLen = sizeof(char);
		setsockopt(ServerSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char *) &OptVal, OptLen);

		while(bind(ServerSocket, (struct sockaddr *) &ServerSocketAddr, sizeof(ServerSocketAddr)))
			Sleep(RETRY_SLEEP);

		while(listen(ServerSocket, 1024))
			Sleep(RETRY_SLEEP);

		while((Connection = accept(ServerSocket, (struct sockaddr *) &ConnectionAddr, &ConnectionAddrLen)) == INVALID_SOCKET)
			Sleep(RETRY_SLEEP);
		
		StrCatW(DisplayMessage, L"已完成網路功能初始化\r\n");
	}

	if(ExecutionType == 3){
		ConnectionAddrLen = sizeof(ConnectionAddrLen);
		ConnectionAddr.sin_family = AF_INET;
		ConnectionAddr.sin_addr.s_addr = htonl(ServerIPAddress);
		ConnectionAddr.sin_port = htons(SERVER_PORT);

		while((Connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
			Sleep(RETRY_SLEEP);

		while(connect(Connection, (SOCKADDR *) &ConnectionAddr, sizeof(ConnectionAddr)) == SOCKET_ERROR)
			Sleep(RETRY_SLEEP);
		
		StrCatW(DisplayMessage, L"已完成網路功能初始化\r\n");
	}


	while(1){
		MainFunction(Connection);
	}
}

void MyBeginThread(void){
	AfxBeginThread((AFX_THREADPROC) MyThread, NULL);
}

void CToS2Dlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	ComboExecutionType.SetCurSel(1);
	OnSelchangeComboType();

	ComboExecutionType.EnableWindow(FALSE);
	ButtonOK.EnableWindow(FALSE);
	ServerIPControl.EnableWindow(FALSE);

	// CDialogEx::OnOK();
}

void CToS2Dlg::OnSelchangeComboType()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	ComboExecutionType.EnableWindow(FALSE);
	ButtonOK.EnableWindow(FALSE);
	ServerIPControl.EnableWindow(FALSE);
	MyBeginThread();
}


void CToS2Dlg::OnBnClickedButtonDefault()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	MinLightKeep = MinHeartKeep = MinWaterKeep = MinDarkKeep = MinWoodKeep = MinFireKeep = -1;
	MaxLightEliminate = MaxHeartEliminate = MaxWaterEliminate = MaxDarkEliminate = MaxWoodEliminate = MaxFireEliminate = -1;
	CheckCountLightScore = CheckCountHeartScore = CheckCountWaterScore = CheckCountDarkScore = CheckCountWoodScore = CheckCountFireScore = TRUE;
	UpdateData(FALSE);
}
