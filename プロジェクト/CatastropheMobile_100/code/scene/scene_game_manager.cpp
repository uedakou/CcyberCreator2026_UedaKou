//===========================================
// 
// ゲームマネージャー[scene_game_manager.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_manager.h"	// ゲームマネージャー	
#include "game_data.h"			// ゲームデータ

namespace nsThis = Scene::Game;
namespace Scene {
	namespace Game {
		class Play;
		class CSceneDebug;
		class CStage_000;
		class CSceneDebug;
		class CStage_Tutorial;
		//============================================
		// コンストラクタ
		//============================================
		CGameManager::CGameManager(nsPrev::CBase* scene) :
			CBase(scene, new CGameData()),
			m_pScene(makeScene<Play>(m_gameData)),
#if 1
			m_pStageController(makeScene<CStage_Tutorial>(m_gameData))
#else 
			m_pStageController(makeScene<CSceneDebug>(m_gameData))
#endif // 0

		{
			//CObject::ReleaseAll();

			m_pNextScene = nullptr;
		}
		//============================================
		// デストラクタ
		//============================================
		CGameManager::~CGameManager()
		{
			if (m_pScene != nullptr)
			{
				delete m_pScene;
			}
			if (m_pStageController)
			{
				delete m_pStageController;
			}
		}

		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CGameManager::Update()
		{
			{
				auto p = m_pScene->Update();
				if (p != m_pScene)
				{
					m_pNextScene = p;
					delete m_pScene;
					auto p2 = dynamic_cast<CBase*>(p);
					if (p2 != nullptr)
					{
						m_pScene = p2;
						return this;
					}
					else
					{
						m_pScene = nullptr;
						return p;
					}
				}
			}
			{
				auto p = m_pStageController->Update();
				if (p != m_pStageController)
				{
					delete m_pStageController;

					if (true)
					{

					}
					m_pStageController = p;
					return this;
				}
			}
			return this;
		}
		//============================================
		// 描画
		//============================================
		void CGameManager::Draw() const
		{
			if (m_pScene != nullptr)
			{
				m_pScene->Draw();
			}
			if (m_pStageController != nullptr)
			{
				m_pStageController->Draw();
			}
		}
		//============================================
		// コンストラクタ
		//============================================

		//============================================
		// ポーズ中取得
		//============================================
		bool CGameManager::GetPose()
		{
			if (m_pScene != nullptr)
			{
				return m_pScene->GetPose();
			}
			return false;
		}
	}
	template<>
	Scene::CBase* nsThis::nsPrev::CBase::makeScene<nsThis::CGameManager>() {
		return new nsThis::CGameManager(this);
	}
}