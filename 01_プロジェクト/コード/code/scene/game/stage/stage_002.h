//===========================================
// 
// ステージ002[stage_002.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_002_H_
#define _STAGE_002_H_
#include "stage_base.h"	// シーンゲームベース
#include "./../../../base/pch.h"	// プリコンパイル
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_002 : public CStage_Base
		{
		public:
			CStage_002(CBase* game, CGameData* gameData);
			virtual ~CStage_002();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		protected:

		private:
			// メンバ変数の初期値
			static const float s_fGool;			// ゴール距離
			static const string s_aStage;		// ステージパス

		};
	}
}
#endif // !_STAGE_002_H_
