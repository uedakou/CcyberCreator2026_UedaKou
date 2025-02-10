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
			class CTutorial
			{
			public:
				CTutorial(CGameData* gameData) { m_gameData = gameData; }
				virtual ~CTutorial() {}
				virtual CTutorial*update () = 0;
			protected:
				CGameData* m_gameData;
			};
			// チュートリアル
			class CTutorial000 : public CTutorial
			{
			public:
				CTutorial000(CGameData* gamaData);
				~CTutorial000();
				virtual CTutorial* update();
			private:
				const int m_nMaxCnt;	// カウント最大値
				int m_nCnt;		// カウント
				CObject2D* m_pPopup;	// ポップアップ
				bool m_bNext;	// 次に行けるか
			};
			class CTutorial001 : public CTutorial
			{
			public:
				CTutorial001(CGameData* gamaData);
				~CTutorial001();
				virtual CTutorial* update();
			private:
				const int m_nMaxCnt;	// カウント最大値
				int m_nCnt;		// カウント
				CObject2D* m_pPopup;	// ポップアップ
				bool m_bNext;	// 次に行けるか
			};
			class CTutorial002 : public CTutorial
			{
			public:
				CTutorial002(CGameData* gamaData);
				~CTutorial002();
				virtual CTutorial* update();
			private:
				const int m_nMaxCnt;	// カウント最大値
				int m_nCnt;		// カウント
				CObject2D* m_pPopup;	// ポップアップ
				CEnemy000Tutorial* pEnemy;
				bool m_bNext;	// 次に行けるか
			};
			class CTutorialDebug : public CTutorial	// デバッグ
			{
			public:
				CTutorialDebug(CGameData* gamaData);
				~CTutorialDebug();
				virtual CTutorial* update();
			private:
				CEnemy000* m_pEnemy;
			};
		private:
			int m_nCntMakeFilde;
			CTutorial* m_pUpdate;
			CPlayer* m_player;
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
