//===========================================
// 
// ステージ000[stage_000.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_001_
#define _STAGE_001_
#include "scene_game.h"
#include "stage_load.h"
#include "../object/player.h"

namespace Scene {
	namespace Game {
		class CStage_001 : public CStageLode
		{
		public:
			CStage_001(CBase* game, CGameData* gameData);
			~CStage_001();
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
