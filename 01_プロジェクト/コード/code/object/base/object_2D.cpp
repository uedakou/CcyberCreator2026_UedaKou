//===========================================
// 
// ポリゴン2[object_2D.cpp]
// Auther:UedaKou
// 
//===========================================
#include "object_2D.h"	// オブジェクト２D
#include "../../base/manager.h"	// マネージャー
#include "../../base/main.h"	// メイン


//============================================
// コンストラクタ
//============================================
CObject2D::CObject2D()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}
CObject2D::CObject2D(int nPriority):
	CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
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
	pVtx[0].pos = D3DXVECTOR3(x.pos.x - (m_siz.x * x.scl.x * 0.5f), x.pos.y - (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(x.pos.x + (m_siz.x * x.scl.x * 0.5f), x.pos.y - (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(x.pos.x - (m_siz.x * x.scl.x * 0.5f), x.pos.y + (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x.pos.x + (m_siz.x * x.scl.x * 0.5f), x.pos.y + (m_siz.y * x.scl.y * 0.5f), 0.0f);

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
void CObject2D::SetX(X x)
{
	CObject::SetX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz)
{
	CObject::SetPos(pos);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
/// <summary>
/// 座標を設定します
/// </summary>
/// <param name="pos">設定する座標</param>
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	CObject::SetPos(pos);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetPosX(const float x)
{
	CObject::SetPosX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetPosY(const float y)
{
	CObject::SetPosY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetPosZ(const float z)
{
	CObject::SetPosZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetRot(const D3DXVECTOR3 rot)
{
	CObject::SetRot(rot);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetRotX(const float x)
{
	CObject::SetRotX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetRotY(const float y)
{
	CObject::SetRotY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetRotZ(const float z)
{
	CObject::SetRotZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetScl(const D3DXVECTOR3 siz)
{
	CObject::SetScl(siz);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetSclX(const float x)
{
	CObject::SetSclX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetSclY(const float y)
{
	CObject::SetSclY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetSclZ(const float z)
{
	CObject::SetSclZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}
void CObject2D::SetUV(float nUp, float nLeft, float nDown, float nRight)
{
	VERTEX_2D* pVtx;		// 頂点情報へのポインタ
	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(nLeft, nUp);
	pVtx[1].tex = D3DXVECTOR2(nRight, nUp);
	pVtx[2].tex = D3DXVECTOR2(nLeft, nDown);
	pVtx[3].tex = D3DXVECTOR2(nRight, nDown);

	// 頂点バッファをロック
	m_pVtxBuff->Unlock();
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

void CObject2D::AddX(X x)
{
	CObject::AddX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 siz)
{
	CObject::AddX(pos, rot, siz);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddPos(const D3DXVECTOR3 pos)
{
	CObject::AddPos(pos);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddPosX(const float x)
{
	CObject::AddPosX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddPosY(const float y)
{
	CObject::AddPosY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddPosZ(const float z)
{
	CObject::AddPosZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddRot(const D3DXVECTOR3 rot)
{
	CObject::AddRot(rot);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddRotX(const float x)
{
	CObject::AddRotX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddRotY(const float y)
{
	CObject::AddRotY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddRotZ(const float z)
{
	CObject::AddRotZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddScl(const D3DXVECTOR3 siz)
{
	CObject::AddScl(siz);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddSclX(const float x)
{
	CObject::AddSclX(x);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddSclY(const float y)
{
	CObject::AddSclY(y);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
}

void CObject2D::AddSclZ(const float z)
{
	CObject::AddSclZ(z);
	if (m_pVtxBuff == nullptr)
	{
		return;
	}
	SetVtxPos();
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

void CObject2D::SetVtxPos()
{
	X x = GetX();

	VERTEX_2D* pVtx;		// 頂点情報へのポインタ
	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標更新
	pVtx[0].pos = D3DXVECTOR3(x.pos.x - (m_siz.x * x.scl.x * 0.5f), x.pos.y - (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(x.pos.x + (m_siz.x * x.scl.x * 0.5f), x.pos.y - (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(x.pos.x - (m_siz.x * x.scl.x * 0.5f), x.pos.y + (m_siz.y * x.scl.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(x.pos.x + (m_siz.x * x.scl.x * 0.5f), x.pos.y + (m_siz.y * x.scl.y * 0.5f), 0.0f);

	// 頂点バッファをロック
	m_pVtxBuff->Unlock();
}