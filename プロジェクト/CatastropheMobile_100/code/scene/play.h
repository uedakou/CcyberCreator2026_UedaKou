//===========================================
// 
// �Q�[���S�̏���[play.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _PLAY_H_
#define _PLAY_H_
#include "scene_game.h"
#include "../base/main.h"		// ���C��
//#include "../base_object/save_object.h"	// �Z�[�u�I�u�W�F�N�g
//#include "game_data.h"					// �Q�[���f�[�^
#include "../base_object/text.h"	// �e�L�X�g


#define MAX_FIELD (16)	// �n�ʍő吔
#define MAX_ENEMY (64)	// �G�ő吔

class CObject;
namespace Scene {
	namespace Game {
		class Play : public CBase
		{
		public:
			Play(CBase* game, CGameData* gameData);
			virtual ~Play();
			nsPrev::CBase* Update()	override;
			bool GetPose()override;
			void Draw() const override;

		private:
			void CameraController();
		private:
			bool bPause;	// �|�[�Y
			CText* m_pText;	// �e�L�X�g
		};
	}
}





#endif // !_PLAY_H_