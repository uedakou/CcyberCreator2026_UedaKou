//============================================
//
// 障害物(toll)[obstacles_toll.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_TOLL_H_
#define _OBJECT_TOLL_H_

#include "obstacles.h"
class CObstaclesToll : public CObstacles
{
public:
	virtual ~CObstaclesToll();
	virtual void Init() override;	// 初期化
	virtual void Uninit() override;	// 終了
	virtual void Update() override;	// 更新
	virtual void Draw() override;	// 描画

	virtual void HitTest() override;	// 当たり判定

	static CObstaclesToll* clate(D3DXVECTOR3 pos);	// 生成
	static CObstaclesToll* clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成
private:	// プライベート
	CObstaclesToll();
};

#endif // !_OBJECT_TOLL_H_