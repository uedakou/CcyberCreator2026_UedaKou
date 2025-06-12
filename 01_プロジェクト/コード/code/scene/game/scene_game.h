//===========================================
// 
// ゲームシーンベース[scene_game.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_
#include "../scene_base.h"
#include "game_data.h"
namespace Scene {
    namespace Game {
        namespace nsPrev = Scene;
        class CBase : public nsPrev::CBase
        {
        protected:
            CBase(nsPrev::CBase* scene, CGameData* const gameData) :
                nsPrev::CBase(*scene),
                m_gameData(gameData)
            {
                CObject::ReleaseScene();
            }	// シーンリリース}
            CBase(const CBase&) = default;

        public:
            virtual ~CBase() = default;

        protected:

            CGameData* const m_gameData;
        public:

            virtual  nsPrev::CBase* Update() override = 0;
            virtual void Draw() const override = 0;
            bool GetPose()override = 0;

            //実体生成用関数
            template<typename T>
            nsPrev::CBase* makeScene(CGameData* gamaData);

        };
    }
}
#endif // !_SCENE_GAME_H_