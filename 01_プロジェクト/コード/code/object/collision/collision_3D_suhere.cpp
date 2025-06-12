//============================================
//
// ‹…“–‚½‚è”»’è[collision_suhere.cpp]
// Author:Uedakou
// 
//============================================
#include "collision_3D_suhere.h"
CCollision3DSuhere::CCollision3DSuhere() :
	CCollision3D(CCollision3D::TYPE::Sphere)
{
}

CCollision3DSuhere::~CCollision3DSuhere()
{
}
CCollision3DSuhere* CCollision3DSuhere::crate()
{
	CCollision3DSuhere* pSuhere = new CCollision3DSuhere;

	return pSuhere;
}