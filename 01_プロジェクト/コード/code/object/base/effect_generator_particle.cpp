//============================================
//
// エフェクトジェネレーター[effect_generator_paeticle.h]
// Author:Uedakou
// 
//============================================
#include "effect_generator_particle.h"	// エフェクトパーティクルジェネレーター
#include "effect_particle.h"	// エフェクトパーティクル

//============================================
// コンスト
//============================================
CEffectGeneratorPaeticle::CEffectGeneratorPaeticle()
{
	// 生成情報
	m_rot = { 0.0f, 0.0f, 0.0f };			// 向き
	m_fLength = 0.0f;						// 距離
	m_fDiffusion = 0.0f;					// 拡散量(角度)
	m_pCor = { 0.0f, 0.0f, 0.0f, 0.0f };	// 色
	m_aTexture = "data/TEXTURE/shadow000.jpg";					// テクスチャ
	m_nLifeParticle = 0;					// パーティクルのライフ
	// 時間管理
	m_nCreatSpan = 0;		// 生成間隔
	m_nCntCreatTime = 0;	// 生成時間
}
//============================================
// コンスト
//============================================
CEffectGeneratorPaeticle::~CEffectGeneratorPaeticle()
{
}
//============================================
// 初期化
//============================================
void CEffectGeneratorPaeticle::Init()
{
	CEffectGeneratorBase::Init();
}
//============================================
// 終了
//============================================
void CEffectGeneratorPaeticle::Uninit()
{
	CEffectGeneratorBase::Uninit();
}
//============================================
// 更新
//============================================
void CEffectGeneratorPaeticle::Update()
{
	if (IsDeathFlag() != true)
	{
		CEffectGeneratorBase::Update();
		m_nCntCreatTime--;
		if (m_nCntCreatTime <= 0)
		{
			m_nCntCreatTime = m_nCreatSpan;
			// +-乱数
			float B = 1000.0f;
			D3DXVECTOR3 RandRotA = {};
			RandRotA.x = (rand() %(int)(m_fDiffusion * 2.0f * B )) - m_fDiffusion * B;
			RandRotA.y = (rand() %(int)(m_fDiffusion * 2.0f * B )) - m_fDiffusion * B;
			RandRotA.z = (rand() %(int)(m_fDiffusion * 2.0f * B )) - m_fDiffusion * B;
			RandRotA /= (float)B;
			RandRotA += m_rot;
			D3DXVec3Normalize(&RandRotA, &RandRotA);

			D3DXVECTOR3 move = RandRotA * m_fLength;
			CEffectParticle::creat(GetPos(), move, m_pCor, m_aTexture, m_nLifeParticle);
		}
	}
}
//============================================
// 描画
//============================================
void CEffectGeneratorPaeticle::Draw()
{}
//============================================
// テクスチャ設定
//============================================
void CEffectGeneratorPaeticle::SetTexture(const char* aFileName)
{
	if (IsDeathFlag() != true)
	{
		m_aTexture = aFileName;
	}
}
//============================================
// 時間管理
//============================================
void CEffectGeneratorPaeticle::TimeController()
{
	//DWORD dwCuppentTime = 0;	// 現在時刻
	//DWORD dwExecLastTime = 0;
	//bool bDeath = false;
	//while (bDeath == false)
	//{
	//	dwCuppentTime = timeGetTime();	// 現在時刻を取得
	//	if ((dwCuppentTime - dwExecLastTime) >= m_nCreatSpan)
	//	{


	//		dwExecLastTime = dwCuppentTime;
	//	}
	//}
}
//============================================
// 生成
//============================================
CEffectGeneratorPaeticle* CEffectGeneratorPaeticle::creat(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan)
{
	CEffectGeneratorPaeticle* p = new CEffectGeneratorPaeticle();

	p->Init();

	// 生成情報
	D3DXVec3Normalize(&(p->m_rot),&rot);	// 向き
	p->m_fLength = fLength;			// 距離
	p->m_fDiffusion = AngleToRadian(Diffusion);	// 拡散量(角度)
	p->m_pCor = Cor;				// 色
	p->m_nLifeParticle = nParticleLife;		// パーティクルのライフ
	// 時間管理
	p->m_nCreatSpan = nCreatSpan;	// 生成間隔

	return p;
}
CEffectGeneratorPaeticle* CEffectGeneratorPaeticle::creat(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan, int nLife)
{
	CEffectGeneratorPaeticle* p = new CEffectGeneratorPaeticle();

	p->Init();

	// 生成情報
	D3DXVec3Normalize(&(p->m_rot), &rot);	// 向き
	p->m_fLength = fLength;			// 距離
	p->m_fDiffusion = AngleToRadian(Diffusion);	// 拡散量(角度)
	p->m_pCor = Cor;				// 色
	p->m_nLifeParticle = nParticleLife;		// パーティクルのライフ
	// 時間管理
	p->m_nCreatSpan = nCreatSpan;	// 生成間隔
	p->SetLifeSpan(nLife);

	return p;
}