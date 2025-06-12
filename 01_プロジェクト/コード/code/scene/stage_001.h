//===========================================
// 
// �X�e�[�W000[stage_000.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_001_
#define _STAGE_001_
#include "scene_game.h"	// ���Q�[���V�[��
#include "stage_load.h"	// �X�e�[�W�ǂݍ��݃V�[��


namespace Scene {
	namespace Game {
		class CStage_001 : public CStageLode
		{
		public:
			CStage_001(CBase* game, CGameData* gameData);
			~CStage_001();
			virtual nsPrev::CBase* Update()	override;	// �X�V
			void Draw() const override;	// �`��
			virtual bool GetPose()override;	// �|�[�Y���Ă��邩�ǂ���
		private:
			int m_nCntMakeFilde;	// �t�B�[���h�����J�E���g
		};
	}
}
#endif // !_STAGE_000_
