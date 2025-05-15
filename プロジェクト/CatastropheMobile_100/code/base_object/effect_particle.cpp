//============================================
//
// エフェクト[effect_paeticle.h]
// Author:Uedakou
// 
//============================================
#include "effect_particle.h"

CEffectParticle::CEffectParticle()
{
	m_move = { 0.0f, 0.0f, 0.0f };
	m_cor = { 0.0f, 0.0f, 0.0f , 0.0f };
	m_nLife = 0;
	SetSiz(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
}

CEffectParticle::~CEffectParticle()
{
}

void CEffectParticle::Update()
{
	CObjectBillbord::Update();

	AddPos(m_move);
	m_nLife--;
	if (m_nLife <= 0)
	{
		Release();
	}
}
void CEffectParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	LPDIRECT3DTEXTURE9 pTexture = GetTexture();
	D3DXMATRIX mtxWorld = GetMaxWorld();	// ワールドマトリクス
	D3DXMATRIX mtxTrans;	// 計算用マトリクス
	D3DXMATRIX matView;

	X x = GetX();
	if (!pDevice) {
		// デバイスが無効な場合のエラーハンドリング
		return;
	}

	// ワールドマトリクスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ビューマトリクスの取得
	if (FAILED(pDevice->GetTransform(D3DTS_VIEW, &matView))) {
		// ビューマトリクス取得失敗時の処理
		return;
	}

	// ビューマトリクスの逆行列を計算
	if (D3DXMatrixInverse(&mtxWorld, NULL, &matView) == NULL) {
		// 逆行列計算失敗時の処理
		return;
	}
	// ワールドマトリクスの位置を初期化
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;
	// オブジェクトの位置を反映
	D3DXMatrixTranslation(&mtxTrans, x.pos.x, x.pos.y, x.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
	// ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	// 頂点バッファを設定
	if (pVtxBuff) {
		pDevice->SetStreamSource(0, pVtxBuff, 0, sizeof(VERTEX_3D));
	}
	else {
		// 頂点バッファが無効な場合の処理
		return;
	}
	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// αブレンディング
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// テクスチャ
	pDevice->SetTexture(0, pTexture);
	//	ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

CEffectParticle* CEffectParticle::creat(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR cor, string tex, int nLife)
{
	CEffectParticle* p = new CEffectParticle();
	p->SetPos(pos);
	p->Init();
	p->SetColor(cor);
	p->SetTexture(tex.c_str());
	p->m_move = move;
	p->m_nLife = nLife;

	return p;
}
