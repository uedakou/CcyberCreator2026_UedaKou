//============================================
//
// ‹…“–‚½‚è”»’è[collision_suhere.cpp]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_SUHERE_H_
#define _COLLISION_SUHERE_H_
#include "collision_3D.h"
class CCollision3DSuhere : public CCollision3D
{
public:
	CCollision3DSuhere();
	~CCollision3DSuhere();

	static CCollision3DSuhere* crate();
private:

};



#endif // !_COLLISION_SUHERE_H_