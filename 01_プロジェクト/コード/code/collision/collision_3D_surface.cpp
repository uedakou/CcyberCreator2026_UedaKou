//============================================
//
// –Ê“–‚½‚è”»’è[collision_surface.h]
// Author:Uedakou
// 
//============================================
#include "collision_3D_surface.h"
CCollision3DSurface::CCollision3DSurface() :
	CCollision3D(CCollision3D::TYPE::Surface)
{
}

CCollision3DSurface::~CCollision3DSurface()
{
}
CCollision3DSurface* CCollision3DSurface::crate(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3)
{
	CCollision3DSurface* pSurface = new CCollision3DSurface;

	pSurface->m_pos0 = pos0;
	pSurface->m_pos1 = pos1;
	pSurface->m_pos2 = pos2;
	pSurface->m_pos3 = pos3;

	return pSurface;
}