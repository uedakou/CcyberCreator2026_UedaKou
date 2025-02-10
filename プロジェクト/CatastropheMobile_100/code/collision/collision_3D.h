//============================================
//
// 3D当たり判定[collision.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_3D_H_
#define _COLLISION_3D_H_
#include "collision.h"	// コリジョン

// 基底
class CCollision3D : public CCollision
{
public:
	typedef enum {
		Line = 0,	// 線
		Surface,	// 面
		Box,		// 箱
		Sphere,		// 球
		Capsule,	// カプセル
		MAX
	}TYPE;

	CCollision3D();
	CCollision3D(TYPE type);
	~CCollision3D();
	TYPE GetType() { return m_type; }	// 種類取得

private:
	TYPE m_type;
};

#endif // !_COLLISION_H_
