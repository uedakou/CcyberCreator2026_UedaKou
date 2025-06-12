//============================================
//
// ” “–‚½‚è”»’è[collision_box.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_BOX_H_
#define _COLLISION_BOX_H_
#include "collision_3D.h"
class CCollision3DBox : public CCollision3D
{
public:
	CCollision3DBox();
	~CCollision3DBox();

	static CCollision3DBox* crate();
private:
	D3DXVECTOR3 m_pos0;
	D3DXVECTOR3 m_pos1;
	D3DXVECTOR3 m_pos2;
	D3DXVECTOR3 m_pos3;
};



#endif // !_COLLISION_BOX_H_