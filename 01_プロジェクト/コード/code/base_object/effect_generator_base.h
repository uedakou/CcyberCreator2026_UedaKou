//============================================
//
// エフェクトジェネレーター[effect_generator_base.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFECT_GENERATOR__BASE_H_
#define _EFFECT_GENERATOR__BASE_H_
#include "object.h"	// オブジェクト
class CEffectGeneratorBase : public CObject
{
public:
	CEffectGeneratorBase();
	~CEffectGeneratorBase();
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;

	// 時間
	void SetLifeSpan(int nSpan) { m_nLife = nSpan; }
	int GetLifeSpan() { return m_nLife; }
	int GetCntTime() { return m_nCntLifeTime; }

private:
	// 時間管理
	int m_nLife;	// エフェクトの寿命
	int m_nCntLifeTime;	// 現在の経過時間
};
#endif // !_EFFECT_GENERATOR__BASE_H_