//===========================================
// 
// ステージ000[stage_000.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_000_
#define _STAGE_000_
#include "scene_game.h"
#include "stage_load.h"
#include "../object/player.h"

namespace Scene {
	namespace Game {
		class CStage_000 : public CStageLode
		{
		public:
			CStage_000(CBase* game, CGameData* gameData);
			~CStage_000();
			virtual nsPrev::CBase* Update()	override;
			void Draw() const override;
			virtual bool GetPose()override;
		private:
			int m_nCntMakeFilde;
			CPlayer* m_player;
		};
	}
}
#endif // !_STAGE_000_
