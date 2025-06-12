//============================================
//
// 障害物[obstacles.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBSTACLES_H_
#define _OBSTACLES_H_
#include "base/object_X.h"

class CPlayer;	// プレイヤー
class CObstacles : public CObjectX
{
public:
	virtual ~CObstacles();
	virtual void Init() override;	// 初期化
	virtual void Uninit() override;	// 終了
	virtual void Update() override;	// 更新
	virtual void Draw() override;	// 描画

	virtual void HitTest() = 0;	// 当たり判定
private:	// プライベート

protected:
	CObstacles();
	static const D3DXVECTOR3 s_Collision;	// オブジェクトコリジョン
};

#endif // !_OBSTACLES_H_