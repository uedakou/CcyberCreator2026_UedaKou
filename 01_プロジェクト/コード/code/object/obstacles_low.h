//============================================
//
// 障害物(low)[obstacles_low.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_LOW_H_
#define _OBJECT_LOW_H_
#include "obstacles.h"

class CObstaclesLow : public CObstacles
{
public:
	virtual ~CObstaclesLow();
	virtual void Init() override;	// 初期化
	virtual void Uninit() override;	// 終了
	virtual void Update() override;	// 更新
	virtual void Draw() override;	// 描画

	virtual void HitTest() override;	// 当たり判定

	static CObstaclesLow* clate(D3DXVECTOR3 pos);	// 生成
	static CObstaclesLow* clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成
private:	// プライベート
	CObstaclesLow();

};

#endif // !_OBJECT_LOW_H_