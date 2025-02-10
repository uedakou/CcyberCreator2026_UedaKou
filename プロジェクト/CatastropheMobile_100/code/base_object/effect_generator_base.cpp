//============================================
//
// エフェクトジェネレーター[effect_generator_base.cpp]
// Author:Uedakou
// 
//============================================
#include "effect_generator_base.h"	// エフェクトジェネレーター
//============================================
// コンスト
//============================================
CEffectGeneratorBase::CEffectGeneratorBase()
{
	m_nLife = -1;
	m_nCntLifeTime = 0;
	SetNormalDraw(false);	// 通常描画をしない
	SetPoseDraw(false);		// ポーズ中描画しない

}
//============================================
// デストラ
//============================================
CEffectGeneratorBase::~CEffectGeneratorBase()
{
}
//============================================
// 初期化
//============================================
void CEffectGeneratorBase::Init()
{
}
//============================================
// 終了
//============================================
void CEffectGeneratorBase::Uninit()
{
}
//============================================
// 更新
//============================================
void CEffectGeneratorBase::Update()
{
	m_nCntLifeTime++;
	if (m_nLife != -1 &&
		m_nCntLifeTime >= m_nLife)
	{
		DeathFlag();
	}
}
//============================================
// 描画
//============================================
void CEffectGeneratorBase::Draw()
{
}