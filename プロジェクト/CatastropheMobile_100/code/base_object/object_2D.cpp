//===========================================
// 
// ポリゴン2[object_2D.cpp]
// Auther:UedaKou
// 
//===========================================
#include "object_2D.h"	// オブジェクト２D
#include "../base/manager.h"	// マネージャー
#include "../base/main.h"		// 


//============================================
// コンストラクタ
//============================================
CObject2D::CObject2D()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetType(CObject::TYPE::OBJECT2D);
}
CObject2D::CObject2D(int nPriority):
	CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetType(CObject::TYPE::OBJECT2D);
}
//============================================
// デストラクト
//============================================
CObject2D::~CObject2D()
{
}
//============================================
// 初期化
//============================================
void CObject2D::Init()
{
	

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイスへのポインタ
	X x = GetX();

	// デバイスの取得
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D* pVtx;		// 頂点情報へのポインタ
	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標更新
	pVtx[0].pos = D3DXVECTOR3(x.pos.x - (x.siz.x * 0.5f), x.pos.y - (x.siz.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(x.pos.x + (x.siz.x * 0.5f), x.pos.y - (x.siz.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(x.pos.x - (x.siz.x * 0.5f), x.pos.y + (x.siz.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x.pos.x + (x.siz.x * 0.5f), x.pos.y + (x.siz.y * 0.5f), 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをロック
	m_pVtxBuff->Unlock();
}
//============================================
// 終了
//============================================
void CObject2D::Uninit()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイスへのポインタ

	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//============================================
// 更新
//============================================
void CObject2D::Update()
{
}
//============================================
// 描画
//============================================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイスへのポインタ

	// 頂点バッファにデータをストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャ
	pDevice->SetTexture(0, m_pTexture);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	// プレイヤーの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}
//============================================
// テクスチャセット
//============================================
void CObject2D::SetTexture(const LPDIRECT3DTEXTURE9 ptex)
{
	m_pTexture = ptex;
}
void CObject2D::SetTexture(const char aName[MAX_TXT])
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイス取得
	LPDIRECT3DTEXTURE9 ptex;
	D3DXCreateTextureFromFile(
		pDevice,
		aName,
		&ptex);

	SetTexture(ptex);
}
void CObject2D::SetTexture(std::string aName)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイス取得
	LPDIRECT3DTEXTURE9 ptex;
	D3DXCreateTextureFromFile(
		pDevice,
		aName.c_str(),
		&ptex);

	SetTexture(ptex);
}
//============================================
// 生成
//============================================
CObject2D* CObject2D::creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	CObject2D* pObject = new CObject2D;

	pObject->SetPos(pos);
	pObject->SetSiz(siz);
	pObject->Init();

	return pObject;
}
CObject2D* CObject2D::creat(int nPriority, D3DXVECTOR3 pos, D3DXVECTOR3 siz)
{
	CObject2D* pObject = new CObject2D(nPriority);

	pObject->SetPos(pos);
	pObject->SetSiz(siz);
	pObject->Init();

	return pObject;
}
//============================================
// カラー設定
//============================================
void CObject2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	VERTEX_2D* pVtx;		// 頂点情報へのポインタ
	if (m_pVtxBuff != nullptr)
	{
		// 頂点バッファをロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点カラー設定
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		// 頂点バッファをロック
		m_pVtxBuff->Unlock();
	}
}