//===========================================
// 
// メイン[main.cpp]
// Auther:UedaKou
// 
//===========================================
#include "main.h"		// [main.h]読み込み]
#include "manager.h"	// マネージャー

// グローバル宣言
int g_nCountFPS = 0;

//============================================
// メイン関数
//============================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hindtscePrev, _In_ LPSTR LpCmdline, _In_ int nCmdShow)
{
	CManager* instance = CManager::GetInstance();// マネージャーインスタンス

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							// ウィンドウのスタイル
		WindowProc,							// ウィンドウプロシャーシ
		0,									// ０にする（通常は使用しない）
		0,									// ０にする（通常は使用しない）
		hInstance,							// インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		// タスクバーアイコン
		LoadCursor(NULL, IDC_ARROW),		// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			// クライアント領域の背景色
		NULL,								// メニューバー
		CLASS_NAME,							// ウィンドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)		// ファイルのアイコン
	};
	HWND hWnd;
	MSG msg;

	RECT rect = { 0,0,SCREEN_W,SCREEN_H };

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//	ウィンドウを生成
	hWnd = CreateWindowEx(0,	// 拡張ウィンドウスタイル
		CLASS_NAME,				// ウィンドウクラスの名前
		WINDOW_NAME,			// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル
		0,//CW_USEDEFAULT,		// ウィンドウの左上のx座標
		0,//CW_USEDEFAULT,		// ウィンドウの左上のy座標
		(rect.right - rect.left),	// ウィンドウの幅
		(rect.bottom - rect.top),	// ウィンドウの高さ
		NULL,
		NULL,
		hInstance,
		NULL);

	// ウィンドウ表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	DWORD dwCuppentTime;	// 現在時刻
	DWORD dwExecLastTime;	// 最後に処理した時刻
	DWORD dwFrameCount;		// フレームカウント
	DWORD dwFPSLostTime;	// 最後にFPSを計測した時刻

	if (FAILED(instance->Init(hInstance, hWnd, TRUE)))
	{// 初期化処理
		return -1;
	}

	timeBeginPeriod(1);	// 分解能を設定 
	dwCuppentTime = 0;	// 初期化する
	dwExecLastTime = timeGetTime();	// 現在時刻を取得
	dwFrameCount = 0;
	dwFPSLostTime = timeGetTime();
	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// WM_QUITメッセージを受け取ったらメッセージループを抜ける
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			dwCuppentTime = timeGetTime();	// 現在時刻を取得

			if ((dwCuppentTime - dwFPSLostTime) >= 500)
			{// 0.5秒
				// FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCuppentTime - dwFPSLostTime);
				dwFPSLostTime = dwCuppentTime;
				dwFrameCount = 0;

			}
			if ((dwCuppentTime - dwExecLastTime) >= (1000 / FPS))
			{// 60文の1秒経過
				instance->Update();	// 更新


				instance->Draw();	// 描画
			}

		}
		// メッセージの設定
		if (CManager::GetEnd() == true)
		{
			break;
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//============================================
//　ウィンドウプロシャーシ
//============================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	CManager* instance = CManager::GetInstance();// マネージャーインスタンス


	switch (uMsg)
	{
	case WM_CREATE: // ウィンドウハンドル
		break;

	case WM_DESTROY:
		// WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				instance->Uninit();
				// ウィンドウを破棄する
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_COMMAND: // ボタンが押された

		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			instance->Uninit();
			// ウィンドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;//0を返さないと終了してしまう
		}
		break;

	case WM_LBUTTONDOWN:	// マウス左クリックのメッセージ
		// ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
int GetFPS()
{
	return g_nCountFPS;
}