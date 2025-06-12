//============================================
//
// �Q�[���I�[�o�[�V�[��[scene_result.h]
// Author:Uedakou
// 
//============================================
#ifndef _SCENE_GAMEOVER_H_
#define _SCENE_GAMEOVER_H_
#include "scene_base.h"




class CObject;	// �I�u�W�F�N�g
class CText;	// �e�N�X�g
class CObject3D;// �I�u�W�F�N�g�RD
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