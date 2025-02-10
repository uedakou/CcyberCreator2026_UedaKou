//============================================
//
// エフェクトジェネレーター[effect_generator_paeticle.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFECT_GENERATOR_PAETICLE_H_
#define _EFFECT_GENERATOR_PAETICLE_H_
#include "effect_generator_base.h"	// エフェクトジェネレーター

class CEffectGeneratorPaeticle : public CEffectGeneratorBase
{
public:
	CEffectGeneratorPaeticle();
	~CEffectGeneratorPaeticle();
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
	// 生成情報
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						// 向き
	void SetLength(float fLength) { m_fLength = fLength; }				// 距離
	void SetDiffusion(float fDiffusion) { m_fDiffusion = fDiffusion; }	// 拡散量(角度)
	void SetCole(D3DXCOLOR Cor) { m_pCor = Cor; }						// 色
	void SetTexture(const char* aFileName);
	void TimeController();

	static CEffectGeneratorPaeticle* creat(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan);	// 生成(向き,動き, 拡散角度,色,パーティクル生存時間, 間隔)
	static CEffectGeneratorPaeticle* creat(D3DXVECTOR3 rot, float fLength, float Diffusion, D3DXCOLOR Cor, int nParticleLife, int nCreatSpan, int nLife);	// 生成(向き,動き, 拡散角度,色,パーティクル生存時間, 間隔,ジェネレーター生存時間)
private:
	// 生成情報
	D3DXVECTOR3 m_rot;	// 向き
	float m_fLength;	// 運動量
	float m_fDiffusion;	// 拡散量(角度)
	D3DXCOLOR m_pCor;	// 色
	int m_nLifeParticle;			// パーティクルのライフ
	string m_aTexture;	// テクスチャ
	// 時間管理
	int m_nCreatSpan;		// 生成間隔
	int m_nCntCreatTime;	// 生成時間
};

#endif // !_EFFECT_GENERATOR__PAETICLE_H_