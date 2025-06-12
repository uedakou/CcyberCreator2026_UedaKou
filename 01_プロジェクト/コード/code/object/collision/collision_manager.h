//============================================
//
// 当たり判定マネージャー[collision_manager.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_
#include "collision_3d.h"
#include "collision_2d.h"

#include "collision_3D_line.h"
#include "collision_3D_surface.h"
#include "collision_3D_box.h"
#include "collision_3D_suhere.h"
#include "collision_3D_capsule.h"



class CCollisionManager
{
public:
	CCollisionManager();
	~CCollisionManager();
	bool Hit(CCollision3D* A, CCollision3D* B);
private:
	// A Line
	bool HitSearch(CCollision3DLine* A, CCollision3DLine* B);
	bool HitSearch(CCollision3DLine* A, CCollision3DSurface* B);
	bool HitSearch(CCollision3DLine* A, CCollision3DBox* B);
	bool HitSearch(CCollision3DLine* A, CCollision3DSuhere* B);
	bool HitSearch(CCollision3DLine* A, CCollision3DCapsule* B);
	// A Surface
	bool HitSearch(CCollision3DSurface* A, CCollision3DLine* B);
	bool HitSearch(CCollision3DSurface* A, CCollision3DSurface* B);
	bool HitSearch(CCollision3DSurface* A, CCollision3DBox* B);
	bool HitSearch(CCollision3DSurface* A, CCollision3DSuhere* B);
	bool HitSearch(CCollision3DSurface* A, CCollision3DCapsule* B);
	// A Box
	bool HitSearch(CCollision3DBox* A, CCollision3DLine* B);
	bool HitSearch(CCollision3DBox* A, CCollision3DSurface* B);
	bool HitSearch(CCollision3DBox* A, CCollision3DBox* B);
	bool HitSearch(CCollision3DBox* A, CCollision3DSuhere* B);
	bool HitSearch(CCollision3DBox* A, CCollision3DCapsule* B);
	// A Suhere
	bool HitSearch(CCollision3DSuhere* A, CCollision3DLine* B);
	bool HitSearch(CCollision3DSuhere* A, CCollision3DSurface* B);
	bool HitSearch(CCollision3DSuhere* A, CCollision3DBox* B);
	bool HitSearch(CCollision3DSuhere* A, CCollision3DSuhere* B);
	bool HitSearch(CCollision3DSuhere* A, CCollision3DCapsule* B);
	// A Capsule
	bool HitSearch(CCollision3DCapsule* A, CCollision3DLine* B);
	bool HitSearch(CCollision3DCapsule* A, CCollision3DSurface* B);
	bool HitSearch(CCollision3DCapsule* A, CCollision3DBox* B);
	bool HitSearch(CCollision3DCapsule* A, CCollision3DSuhere* B);
	bool HitSearch(CCollision3DCapsule* A, CCollision3DCapsule* B);
	
	
};


#endif // !_COLLISION_MANAGER_H_

