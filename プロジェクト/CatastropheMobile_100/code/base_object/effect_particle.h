//============================================
//
// エフェクト[effect_paeticle.h]
// Author:Uedakou
// 
//============================================
#ifndef _EFFCTO_PARTICLE_H_
#define _EFFCTO_PARTICLE_H_
#include "object_billboard.h"

class CEffectParticle : public CObjectBillbord
{
public:
	CEffectParticle();
	~CEffectParticle();

	void Update()override;
	void Draw()override;

	static CEffectParticle* creat(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR cor, string tex, int nLife);
private:
	// 基本情報
	D3DXVECTOR3 m_move;	// 動き
	D3DXCOLOR m_cor;		// 色
	// 時間管理
	int m_nLife;	// 寿命
};



#endif // !_EFFCTO_PARTICLE_H_