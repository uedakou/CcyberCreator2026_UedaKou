//===========================================
// 
// レンダラー[renderer.cpp]
// Auther:UedaKou
// 
//===========================================
#include "renderer.h"	// レンダラー
#include "main.h"		// メイン
#include "manager.h"	// マネージャー

#include "../object/base/object.h"		// オブジェクト
#include "../scene/game/stage/scene_debug.h"	// デバックシーン
#include "../object/base/text.h"


//============================================
// コンストラクタ
//============================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pText = nullptr;
}
//============================================
// デストラクタ
//============================================
CRenderer::~CRenderer()
{
	if (m_pText != nullptr)
	{
		m_pText->DeathFlag();
	}
}
//============================================
// 初期化処理
//============================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	// 現在のディスプレイモード取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//	デバイスのディスプレイのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_W;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_H;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファを16bit使う
	d3dpp.Windowed = bWindow;									// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル
	// Direct3Dデバイスの生成(描画処理と頂点処理をバードウェアで行う)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//	Direct3Dデバイスの生成
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//	Direct3Dデバイスの生成
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//m_pText = CText::creat();

	return S_OK;
}
//============================================
// 終了処理
//============================================
void CRenderer::Uninit(void)
{
	timeEndPeriod(1);	// fpsリセット
	CObject::ReleaseAll();
}
//============================================
// 更新処理
//============================================
void CRenderer::Update(void)
{
	CObject::UpdateAll();

	timeEndPeriod(1);	// fpsリセット
}
//============================================
// 描画処理
//============================================
void CRenderer::Draw(void)
{
	CManager* instance = CManager::GetInstance();
	CCamera* pCamera = instance->GetCamera();
	Scene::CBase* Scene = instance->GetSceneManager();
	//画面クリア(バックバッファ&Zバッファのクリア)
	m_pD3DDevice->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(50, 150, 255, 255),	// 背景色
		1.0f,
		0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CObject::CalculateDistanceToCamera();
		CObject::Sort();

		if (pCamera != nullptr)
		{
			pCamera->SetCamera();
		}

		CObject::DrawAll();
		Scene->Draw();

#ifdef _DEBUG
		//pCamera->DrawCamera();
		DrawFPS();

#endif // !_DEBUG
		m_pD3DDevice->EndScene();
	}
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//============================================
// FPS表示処理
//============================================
void CRenderer::DrawFPS(void)
{
	if (m_pText != nullptr)
	{
		int nCountFPS = GetFPS();
		string aStr;
		wsprintf(&aStr[0], "FPS:%d\n", nCountFPS);
		m_pText->SetText(aStr);
	}
}
//============================================
// デバイス取得処理
//============================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
