//============================================
//
// 2D“–‚½‚è”»’è[collision.h]
// Author:Uedakou
// 
//============================================
#ifndef _COLLISION_2D_H_
#define _COLLISION_2D_H_
#include "collision.h"	// ƒRƒŠƒWƒ‡ƒ“

// Šî’ê
class CCollision2D : public CCollision
{
public:
	typedef enum {
		Line = 0,	// ü
		Surface,	// –Ê
		Circle,		// ‹…
		MAX
	}TYPE;

	CCollision2D();
	~CCollision2D();
	TYPE GetType() { return type; }	// í—Şæ“¾

private:
	TYPE type;
};
#endif // !_COLLISION_2D_H_
