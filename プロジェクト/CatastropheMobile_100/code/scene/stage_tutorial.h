//===========================================
// 
// �`���[�g���A���X�e�[�W[stage_tutorial.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_TUTORIAL_H_
#define _STAGE_TUTORIAL_H_
#include "scene_game.h"
#include "stage_load.h"
class CEnemy000Tutorial;
class CEnemy000;
class CObject2D;

namespace Scene {
	namespace Game {
		class CStage_Tutorial : public CStageLode
		{
		public:
			CStage_Tutorial(CBase* game, CGameData* gameData);
			virtual ~CStage_Tutorial();
			virtual nsPrev::CBase* Update()	override;
			virtual bool GetPose()override;
		private:
			// ���
			class CTutorialStrategy
			{
			public:
				CTutorialStrategy(CGameData* gameData) { m_gameData = gameData; }
				virtual ~CTutorialStrategy() {}
				virtual CTutorialStrategy*update () = 0;
			protected:
				CGameData* m_gameData;
			};
			// �`���[�g���A��
			class CTutorial000 : public CTutorialStrategy
			{
			public:
				CTutorial000(CGameData* gamaData);
				~CTutorial000();
				virtual CTutorialStrategy* update();
			private:
				const int m_nMaxCnt;	// �J�E���g�ő�l
				int m_nCnt;		// �J�E���g
				CObject2D* m_pPopup;	// �|�b�v�A�b�v
				bool m_bNext;	// ���ɍs���邩
			};
			class CTutorial001 : public CTutorialStrategy
			{
			public:
				CTutorial001(CGameData* gamaData);
				~CTutorial001();
				virtual CTutorialStrategy* update();
			private:
				const int m_nMaxCnt;	// �J�E���g�ő�l
				int m_nCnt;		// �J�E���g
				CObject2D* m_pPopup;	// �|�b�v�A�b�v
				bool m_bNext;	// ���ɍs���邩
			};
			class CTutorial002 : public CTutorialStrategy
			{
			public:
				CTutorial002(CGameData* gamaData);
				~CTutorial002();
				virtual CTutorialStrategy* update();
			private:
				const int m_nMaxCnt;	// �J�E���g�ő�l
				int m_nCnt;		// �J�E���g
				CObject2D* m_pPopup;	// �|�b�v�A�b�v
				CEnemy000Tutorial* m_pEnemy;	// �`���[�g���A���G
				bool m_bNext;	// ���ɍs���邩
				static const float m_fEnemyPosZ;
			};
		private:
			int m_nCntMakeFilde;
			CTutorialStrategy* m_pUpdate;	// 
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
