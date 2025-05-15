//===========================================
// 
// チュートリアルステージ[stage_tutorial.h]
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
			// 基底
			class CTutorialStrategy
			{
			public:
				CTutorialStrategy(CGameData* gameData) { m_gameData = gameData; }
				virtual ~CTutorialStrategy() {}
				virtual CTutorialStrategy*update () = 0;
			protected:
				CGameData* m_gameData;
			};
			// チュートリアル
			class CTutorial000 : public CTutorialStrategy
			{
			public:
				CTutorial000(CGameData* gamaData);
				~CTutorial000();
				virtual CTutorialStrategy* update();
			private:
				const int m_nMaxCnt;	// カウント最大値
				int m_nCnt;		// カウント
				CObject2D* m_pPopup;	// ポップアップ
				bool m_bNext;	// 次に行けるか
			};
			class CTutorial001 : public CTutorialStrategy
			{
			public:
				CTutorial001(CGameData* gamaData);
				~CTutorial001();
				virtual CTutorialStrategy* update();
			private:
				const int m_nMaxCnt;	// カウント最大値
				int m_nCnt;		// カウント
				CObject2D* m_pPopup;	// ポップアップ
				bool m_bNext;	// 次に行けるか
			};
			class CTutorial002 : public CTutorialStrategy
			{
			public:
				CTutorial002(CGameData* gamaData);
				~CTutorial002();
				virtual CTutorialStrategy* update();
			private:
				const int m_nMaxCnt;	// カウント最大値
				int m_nCnt;		// カウント
				CObject2D* m_pPopup;	// ポップアップ
				CEnemy000Tutorial* m_pEnemy;	// チュートリアル敵
				bool m_bNext;	// 次に行けるか
				static const float m_fEnemyPosZ;
			};
		private:
			int m_nCntMakeFilde;
			CTutorialStrategy* m_pUpdate;	// 
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
