//===========================================
// 
// ゲームステージ選択[scene_game_stageselect.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_GAME_STAGESELECT_H_
#define _SCENE_GAME_STAGESELECT_H_
#include "scene_game.h"
#include "../../base/pch.h"
class CObject2D;

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect : public CBase
		{
		public:
			enum class Select {
				STAGE_000 = 0,	// ステージチュートリアル
				STAGE_001,	// ステージ1
				STAGE_002,	// ステージ2
				MAX
			};		// 次に移行するシーンの選択肢

			CScen_Game_StageSelect(CBase* scene, CGameData* gameData);
			virtual ~CScen_Game_StageSelect();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			bool m_bPose;
			bool m_bNext;	// 次のシーンに移行中かどうか
			int m_nSetlect;	// 現在選択中の次シーン
			int m_nCntPressHold;	// 長押し時間
			CObject2D* m_pStage[static_cast<int>(Select::MAX)];	// 選択肢オブジェクト
			CObject2D* m_pStageEvaluation;	// ステージ評価

			static const D3DXVECTOR3 s_SelectSiz;	// 選択肢大きさ
			static const D3DXVECTOR3 s_SelectEvaluationSiz;	// 選択評価大きさ
		};
	}
}
#endif // !_STAGE_TUTORIAL_H_
