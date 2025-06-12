//============================================
//
// –Ê“–‚½‚è”»’è[collision_surface.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_SURFACE_H_
#define _COLLISION_SURFACE_H_
#include "collision_3D.h"
class CCollision3DSurface : public CCollision3D
{
public:
	CCollision3DSurface();
	~CCollision3DSurface();

	static CCollision3DSurface* crate(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3);
private:
	D3DXVECTOR3 m_pos0;
	D3DXVECTOR3 m_pos1;
	D3DXVECTOR3 m_pos2;
	D3DXVECTOR3 m_pos3;
};



#endif // !_COLLISION_SURFACE_H_
