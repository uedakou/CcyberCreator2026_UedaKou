//===========================================
// 
// ゲーム全体処理[play.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _OBJECT_SELECT_H_
#define _OBJECT_SELECT_H_
#include "base/object_2D.h"	// オブジェクト2D
#include "../base/pch.h"	// プリコンパイル
class CSelect : public CObject2D
{
public:
	CSelect() {};
	CSelect(int nP):
		CObject2D(nP)
	{};
	virtual ~CSelect() {};
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
private:
};

#endif // !_OBJECT_SELECT_H_