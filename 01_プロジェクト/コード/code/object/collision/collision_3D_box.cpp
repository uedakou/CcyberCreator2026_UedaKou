//============================================
//
// ” “–‚½‚è”»’è[collision_box.cpp]
// Author:Uedakou
// 
//============================================
#include "collision_3D_box.h"
CCollision3DBox::CCollision3DBox() :
	CCollision3D(CCollision3D::TYPE::Box)
{
}

CCollision3DBox::~CCollision3DBox()
{
}
CCollision3DBox* CCollision3DBox::crate()
{
	CCollision3DBox* pBox = new CCollision3DBox;

	return pBox;
}