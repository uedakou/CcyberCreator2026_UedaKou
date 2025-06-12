//============================================
//
// 障害物(high)[obstacles_high.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_HIGH_H_
#define _OBJECT_HIGH_H_

#include "obstacles.h"
class CObstaclesHigh : public CObstacles
{
public:
	virtual ~CObstaclesHigh();
	virtual void Init() override;	// 初期化
	virtual void Uninit() override;	// 終了
	virtual void Update() override;	// 更新
	virtual void Draw() override;	// 描画

	virtual void HitTest() override;	// 当たり判定

	static CObstaclesHigh* clate(D3DXVECTOR3 pos);	// 生成
	static CObstaclesHigh* clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成
private:	// プライベート
	CObstaclesHigh();

};

#endif // !_OBJECT_HIGH_H_