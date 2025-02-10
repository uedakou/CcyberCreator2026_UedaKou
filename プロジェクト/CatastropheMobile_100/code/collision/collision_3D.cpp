//============================================
//
// 3D“–‚½‚è”»’è[collision.h]
// Author:Uedakou
// 
//============================================
#include "collision_3D.h"
CCollision3D::CCollision3D():
	CCollision(CCollision::TYPE::TYPE_3D)
{
	m_type = TYPE::Line;
}
CCollision3D::CCollision3D(TYPE type)
{
	m_type = type;
}
CCollision3D::~CCollision3D()
{

}