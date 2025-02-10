//============================================
//
// ƒJƒvƒZƒ‹“–‚½‚è”»’è[collision_capsule.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_CAPSULE_H_
#define _COLLISION_CAPSULE_H_
#include "collision_3D.h"
class CCollision3DCapsule : public CCollision3D
{
public:
	CCollision3DCapsule();
	~CCollision3DCapsule();

	static CCollision3DCapsule* crate();
private:

};



#endif // !_COLLISION_CAPSULE_H_