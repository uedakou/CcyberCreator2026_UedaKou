//============================================
//
// アイテム(巻物)[scroll.cpp]
// Author:Uedakou
// 
//============================================
#ifndef _SCROLL_H_
#define _SCROLL_H_
#include "base/object_X.h"

class CScroll : public CObjectX
{
public:
	virtual ~CScroll();
	virtual void Init() override;	// 初期化
	virtual void Uninit() override;	// 終了
	virtual void Update() override;	// 更新
	virtual void Draw() override;	// 描画
	D3DXVECTOR3 GetCollisionSiz() { return s_Collision; }	// コリジョン取得

	static CScroll* clate(D3DXVECTOR3 pos);	// 生成
	static CScroll* clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 生成
private:	// プライベート
	CScroll();
	static const D3DXVECTOR3 s_Collision ;	// 当たり判定
};

#endif // !_SCROLL_H_