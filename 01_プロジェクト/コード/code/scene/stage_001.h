//===========================================
// 
// ステージ000[stage_000.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_001_
#define _STAGE_001_
#include "scene_game.h"	// 基底ゲームシーン
#include "stage_load.h"	// ステージ読み込みシーン


namespace Scene {
	namespace Game {
		class CStage_001 : public CStageLode
		{
		public:
			CStage_001(CBase* game, CGameData* gameData);
			~CStage_001();
			virtual nsPrev::CBase* Update()	override;	// 更新
			void Draw() const override;	// 描画
			virtual bool GetPose()override;	// ポーズしているかどうか
		private:
			int m_nCntMakeFilde;	// フィールド生成カウント
		};
	}
}
#endif // !_STAGE_000_
