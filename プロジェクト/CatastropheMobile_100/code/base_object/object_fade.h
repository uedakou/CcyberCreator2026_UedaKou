//===========================================
// 
// フェード[object_fade.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _FADE_H_
#define _FADE_H_
#include "object_2D.h"	// オブジェクト2D
#include "../base/manager.h"	// マネージャー

class CFade: public CObject2D
{
public:
	typedef enum {
		WHITE_OUT = 0,	// 白塗り
		WHITE_IN,
		BLACK_OUT,
		BLACK_IN,
		MAX
	}FADE_TYPE;
	CFade();
	~CFade()		override;
	void Init()	override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
	static CFade* creat(FADE_TYPE type, int nCnt);
private:
	int m_nCnt;
	int m_nCntMax;
	FADE_TYPE m_type;
};




#endif // !_FADE_H_