//===========================================
// 
// 2D表示ライフ[life_2d.cpp]
// Auther:UedaKou
// 
//===========================================
#include "life_2d.h"

//============================================
// コンスト
//============================================
CLife_2D::CLife_2D() :
	CObject2D(4)
{
	lifeBG = nullptr;
	m_nLifeOld = 0;
	m_nLife = 0;
	m_nMaxLife = 0;
	m_pText = CText::creat();
	//CObject::SetUpdate(false);
}
CLife_2D::CLife_2D(int nPriorith) :
	CObject2D(nPriorith)
{
	lifeBG = nullptr;
	m_nLifeOld = 0;
	m_nLife = 0;
	m_nMaxLife = 0;
	m_pText = CText::creat();
	//CObject::SetUpdate(false);
}
//============================================
// デストラクタ
//============================================
CLife_2D::~CLife_2D()
{
}
//============================================
// 初期化
//============================================
void CLife_2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイスへのポインタ
	CObject2D::Init();
	auto pVtxBuff = GetVtxBuff();
	auto pCor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	auto pX = GetX();

	VERTEX_2D* pVtx;		// 頂点情報へのポインタ
	// 頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標更新
	pVtx[0].pos = D3DXVECTOR3(pX.pos.x							, pX.pos.y - (pX.siz.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pX.pos.x + (pX.siz.x * m_nLife)	, pX.pos.y - (pX.siz.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pX.pos.x							, pX.pos.y + (pX.siz.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pX.pos.x + (pX.siz.x * m_nLife)	, pX.pos.y + (pX.siz.y * 0.5f), 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー設定
	pVtx[0].col = pCor;
	pVtx[1].col = pCor;
	pVtx[2].col = pCor;
	pVtx[3].col = pCor;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをロック
	pVtxBuff->Unlock();

	SetColor(pCor);

	lifeBG = CObject2D::creat(D3DXVECTOR3(pX.pos.x + (pX.siz.x * m_nMaxLife * 0.5f), pX.pos.y, 0.0f), D3DXVECTOR3(pX.siz.x * m_nMaxLife, pX.siz.y, 0.0f));
	lifeBG->SetNormalUpdate(false);
}
//============================================
// 終了
//============================================
void CLife_2D::Uninit()
{
	CObject2D::Uninit();
	if (lifeBG != nullptr &&
		lifeBG->IsDeathFlag() == false)
	{
		lifeBG->Uninit();
		lifeBG->DeathFlag();
		lifeBG = nullptr;
	}

}
//============================================
// 初期化
//============================================
void CLife_2D::Update()
{
	if (m_nLife != m_nLifeOld)
	{
		auto pVtxBuff = GetVtxBuff();
		auto pX = GetX();
		VERTEX_2D* pVtx;		// 頂点情報へのポインタ


		// 頂点バッファをロック
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標更新
		pVtx[0].pos = D3DXVECTOR3(pX.pos.x							, pX.pos.y - (pX.siz.y * 0.5f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pX.pos.x + (pX.siz.x * m_nLife)	, pX.pos.y - (pX.siz.y * 0.5f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pX.pos.x							, pX.pos.y + (pX.siz.y * 0.5f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pX.pos.x + (pX.siz.x * m_nLife)	, pX.pos.y + (pX.siz.y * 0.5f), 0.0f);

		// 頂点バッファをロック
		pVtxBuff->Unlock();

		m_nLifeOld = m_nLife;
	}
	CObject2D::Update();
}
//============================================
// 描画
//============================================
void CLife_2D::Draw()
{
	CObject2D::Draw();
	//m_pText
}

CLife_2D* CLife_2D::creat(D3DXVECTOR3 pos, int nLife)
{
	CLife_2D* p = new CLife_2D();

	p->SetPos(pos);
	p->SetSiz(D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	p->SetLifeOld(nLife);
	p->SetLife(nLife);
	p->SetMaxLife(nLife);


	p->Init();

	return p;
}
CLife_2D* CLife_2D::creat(int nPriorith, D3DXVECTOR3 pos, int nLife)
{
	CLife_2D* p = new CLife_2D(nPriorith);

	p->SetPos(pos);
	p->SetSiz(D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	p->SetLifeOld(nLife);
	p->SetLife(nLife);
	p->SetMaxLife(nLife);


	p->Init();

	return p;
}
