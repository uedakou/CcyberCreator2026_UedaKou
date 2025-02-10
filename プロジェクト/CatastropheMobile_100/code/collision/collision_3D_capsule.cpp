//============================================
//
// ƒJƒvƒZƒ‹“–‚½‚è”»’è[collision_capsule.cpp]
// Author:Uedakou
// 
//============================================
#include "collision_3D_capsule.h"
CCollision3DCapsule::CCollision3DCapsule() :
	CCollision3D(CCollision3D::TYPE::Capsule)
{
}

CCollision3DCapsule::~CCollision3DCapsule()
{
}
CCollision3DCapsule* CCollision3DCapsule::crate()
{
	CCollision3DCapsule* pCapsule = new CCollision3DCapsule;

	return pCapsule;
}