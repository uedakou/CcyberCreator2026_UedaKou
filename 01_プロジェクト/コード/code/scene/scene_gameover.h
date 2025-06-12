//============================================
//
// ゲームオーバーシーン[scene_result.h]
// Author:Uedakou
// 
//============================================
#ifndef _SCENE_GAMEOVER_H_
#define _SCENE_GAMEOVER_H_
#include "scene_base.h"




class CObject;	// オブジェクト
class CText;	// テクスト
class CObject3D;// オブジェクト３D
class CObjectMotion;
namespace Scene {
	class CGameOver : public CBase
	{
	public:
		CGameOver(CBase* scene);
		~CGameOver() override;
		virtual CBase* Update()	override;
		void Draw() const override;
		bool GetPose()override;
	private:
		CObject* m_pObject;
		CText* m_pText;
		CObject3D* m_pField[2];
		CObjectMotion* m_pCor;
	};
}

#endif // !_SCENE_GAMEOVER_H_