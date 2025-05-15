//===========================================
// 
// 3D表示ライフ[life_2d.cpp]
// Auther:UedaKou
// 
//===========================================
#include "life_3d.h"

//============================================
// コンスト
//============================================
CLife_3D::CLife_3D() :
	CObjectBillbord(5)
{
	m_lifeBG = nullptr;
	m_nLifeOld = 0;
	m_nLife = 0;
	m_nMaxLife = 0;
	//m_pText = CText::creat();
	posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//CObject::SetUpdate(true);
}
//============================================
// デストラクタ
//============================================
CLife_3D::~CLife_3D()
{
}
//============================================
// 初期化
//============================================
void CLife_3D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイスへのポインタ
	CObjectBillbord::Init();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXCOLOR Cor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	X pX = GetX();
	D3DXVECTOR3 siz = GetSiz();
	posOld = pX.pos;
	VERTEX_3D* pVtx;		// 頂点情報へのポインタ
	// 頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標更新
	pVtx[0].pos = D3DXVECTOR3(- (siz.x * m_nMaxLife * 0.5f),siz.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ (siz.x * m_nMaxLife * 0.5f),siz.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- (siz.x * m_nMaxLife * 0.5f),0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ (siz.x * m_nMaxLife * 0.5f),0.0f, 0.0f);

	// 頂点バッファをロック
	pVtxBuff->Unlock();

	SetColor(Cor);
	m_lifeBG = CObjectBillbord::creat(4,D3DXVECTOR3(pX.pos.x , pX.pos.y, pX.pos.z), D3DXVECTOR3(siz.x * m_nMaxLife, siz.y, 0.0f));
	m_lifeBG->SetReleaseScene(false);

}
//============================================
// 終了
//============================================
void CLife_3D::Uninit()
{
	CObjectBillbord::Uninit();
	if (m_lifeBG != nullptr)
	{
		m_lifeBG->Release();
		m_lifeBG = nullptr;
	}
}
//============================================
// 初期化
//============================================
void CLife_3D::Update()
{
	if (m_nLife != m_nLifeOld)
	{
		auto pVtxBuff = GetVtxBuff();
		auto siz = GetSiz();
		VERTEX_3D* pVtx;		// 頂点情報へのポインタ

		// 頂点バッファをロック
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標更新
		pVtx[0].pos = D3DXVECTOR3(-(siz.x * m_nMaxLife * 0.5f)						, siz.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(-(siz.x * m_nMaxLife * 0.5f) + (siz.x * m_nLife)	, siz.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-(siz.x * m_nMaxLife * 0.5f)						, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(-(siz.x * m_nMaxLife * 0.5f) + (siz.x * m_nLife)	, 0.0f, 0.0f);

		// 頂点バッファをロック
		pVtxBuff->Unlock();

		m_nLifeOld = m_nLife;
	}
	CObjectBillbord::Update();
	D3DXVECTOR3 pos = GetPos();
	if (m_lifeBG != nullptr)
	{
		m_lifeBG->SetPos(D3DXVECTOR3(pos.x, pos.y , pos.z));
	}
}
//============================================
// 描画
//============================================
void CLife_3D::Draw()
{
	CObjectBillbord::Draw();
}

CLife_3D* CLife_3D::creat(D3DXVECTOR3 pos, int nLife)
{
	CLife_3D* p = new CLife_3D();

	p->SetPos(pos);
	p->SetSiz(D3DXVECTOR3(5.0f, 4.0f, 0.0f));
	p->SetLifeOld(nLife);
	p->SetLife(nLife);
	p->SetMaxLife(nLife);

	p->Init();

	return p;
}
