//===========================================
// 
// �f�o�b�N�V�[��[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_DEBUG_H_
#include "scene_game.h"	// �x�[�X�V�[��

class CField;
class CPlayer;

namespace Scene {
	namespace Game {
		class CSceneDebug : public CBase
		{
		public:
			CSceneDebug(CBase* scene, CGameData* gameData);
			~CSceneDebug()		override;
			CBase* Update()	override;	// �X�V
			void Draw() const override;	// �`��
			bool GetPose()override;
		private:
			CField* m_pField;

			CPlayer* m_pPlayer;
		};
	}
}



#endif // !_SCENE_DEBUG_H_
