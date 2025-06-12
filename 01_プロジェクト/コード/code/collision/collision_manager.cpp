//============================================
//
// 当たり判定マネージャー[collision_manager.h]
// Author:Uedakou
// 
//============================================
#include "collision_manager.h"	// コリジョンマネージャー


CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}
bool CCollisionManager::Hit(CCollision3D* A, CCollision3D* B)
{
	bool bHit = false;
	CCollision3D::TYPE Atype = A->GetType();
	CCollision3D::TYPE Btype = B->GetType();
	switch (Atype)
	{
	case CCollision3D::TYPE::Line:
		

		break;
	case CCollision3D::TYPE::Surface:


		break;
	case CCollision3D::TYPE::Box:


		break;
	case CCollision3D::TYPE::Sphere:


		break;
	case CCollision3D::TYPE::Capsule:


		break;
	default:
		break;
	}


	return bHit;
}

// A Line
bool CCollisionManager::HitSearch(CCollision3DLine* A, CCollision3DLine* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DLine* A, CCollision3DSurface* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DLine* A, CCollision3DBox* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DLine* A, CCollision3DSuhere* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DLine* A, CCollision3DCapsule* B)
{
	return false;
}
// A Surface
bool CCollisionManager::HitSearch(CCollision3DSurface* A, CCollision3DLine* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DSurface* A, CCollision3DSurface* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DSurface* A, CCollision3DBox* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DSurface* A, CCollision3DSuhere* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DSurface* A, CCollision3DCapsule* B)
{
	return false;
}
// A Box
bool CCollisionManager::HitSearch(CCollision3DBox* A, CCollision3DLine* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DBox* A, CCollision3DSurface* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DBox* A, CCollision3DBox* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DBox* A, CCollision3DSuhere* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DBox* A, CCollision3DCapsule* B)
{
	return false;
}
// A Suhere
bool CCollisionManager::HitSearch(CCollision3DSuhere* A, CCollision3DLine* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DSuhere* A, CCollision3DSurface* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DSuhere* A, CCollision3DBox* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DSuhere* A, CCollision3DSuhere* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DSuhere* A, CCollision3DCapsule* B)
{
	return false;
}

// A Capsule
bool CCollisionManager::HitSearch(CCollision3DCapsule* A, CCollision3DLine* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DCapsule* A, CCollision3DSurface* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DCapsule* A, CCollision3DBox* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DCapsule* A, CCollision3DSuhere* B)
{
	return false;
}
bool CCollisionManager::HitSearch(CCollision3DCapsule* A, CCollision3DCapsule* B)
{
	return false;
}