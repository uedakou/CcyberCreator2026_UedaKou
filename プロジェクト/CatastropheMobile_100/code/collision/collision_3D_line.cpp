//============================================
//
// ü“–‚½‚è”»’è[collision_line.cpp]
// Author:Uedakou
// 
//============================================
#include "collision_3D_line.h"
CCollision3DLine::CCollision3DLine():
	CCollision3D(CCollision3D::TYPE::Line)
{
	
}

CCollision3DLine::~CCollision3DLine()
{
}
CCollision3DLine* CCollision3DLine::crate(D3DXVECTOR3 state, D3DXVECTOR3 end)
{
	CCollision3DLine* pLine = new CCollision3DLine;

	pLine->posState = state;
	pLine->posEnd = end;

	return pLine;
}