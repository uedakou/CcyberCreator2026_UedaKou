//============================================
//
// 当たり判定[collision.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "../base/pch.h"	// プリコンパイル

// 基底
class CCollision
{
public:
	typedef enum {
		TYPE_2D = 0,
		TYPE_3D,
		MAX,
	}TYPE;
	CCollision();
	CCollision(TYPE type);
	~CCollision();
	TYPE GetType() { return m_type; }	// 種類取得
	// いつか消す
	static bool Hit(D3DXVECTOR3 pos0, D3DXVECTOR3 collision0, D3DXVECTOR3 pos1, D3DXVECTOR3 collision1);
	// Collision
	bool OnCollisionEnter(CCollision * collision);	// 当たった
	bool OnCollisionStay(CCollision * collision);	// 当たっている
	bool OnCollisionExit(CCollision * collision);	// 離れた
	// Trigger
	bool OnTriggerEnter(CCollision * collision);	// すり抜けた
	bool OnTriggerStay(CCollision * collision);	// すり抜けている
	bool OnTriggerExit(CCollision * collision);	// 通り抜けた

private:
	TYPE m_type;
};

#endif // !_COLLISION_H_