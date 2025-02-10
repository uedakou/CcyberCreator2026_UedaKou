//===========================================
// 
// ゲームマネージャー[scene_game_manager.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_GAME_MANAGER_H_
#define _SCENE_GAME_MANAGER_H_
#include "scene_game.h"
namespace Scene {
	namespace Game {
		class CGameManager : public CBase
		{
		public:
			CGameManager(nsPrev::CBase* pScene);
			~CGameManager();
		private:
			nsPrev::CBase* m_pScene;		// シーン
			nsPrev::CBase* m_pNextScene;	// 次シーン
			nsPrev::CBase* m_pStageController;	// ステージ生成

		public :
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;
			bool GetPose()override;
		};
	}
}





#endif // !_