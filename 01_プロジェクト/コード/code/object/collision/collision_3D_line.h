//============================================
//
// ê¸ìñÇΩÇËîªíË[collision_line.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_LINE_H_
#define _COLLISION_LINE_H_
#include "collision_3D.h"

class CCollision3DLine : public CCollision3D
{
public:
	CCollision3DLine();
	~CCollision3DLine();

	void SetState(D3DXVECTOR3 pos) { posState = pos; }
	void SetEnd(D3DXVECTOR3 pos) { posEnd = pos; }

	D3DXVECTOR3 GetState() { return posState; }
	D3DXVECTOR3 GetEnd() { return posEnd; }

	static CCollision3DLine* crate(D3DXVECTOR3 state, D3DXVECTOR3 end);

private:
	D3DXVECTOR3 posState;
	D3DXVECTOR3 posEnd;
};






#endif // !_COLLISION_LINE_H_