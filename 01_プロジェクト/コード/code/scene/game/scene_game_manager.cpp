//===========================================
// 
// ゲームマネージャー[scene_game_manager.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_manager.h"	// ゲームマネージャー	
#include "game_data.h"			// ゲームデータ
#define g_bDebug 1
namespace nsThis = Scene::Game;
namespace Scene {
	namespace Game {
		class Play;						// ゲーム全体処理
		class CSceneDebug;				// デバッグ
		class CStage_Tutorial;			// チュートリアル
		class CScen_Game_StageSelect;	// ステージ選択
		//============================================
		// コンストラクタ
		//============================================
		CGameManager::CGameManager(nsPrev::CBase* scene) :
			CBase(scene, new CGameData())

		{

			m_pScene = makeScene<Play>(m_gameData);
#if g_bDebug
			m_pStageController = makeScene<CScen_Game_StageSelect>(m_gameData);
#else 
			m_pStageController = makeScene<CSceneDebug>(m_gameData);
#endif // 0
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
			if (m_pStageController != nullptr)
			{
				delete m_pStageController;
			}
			if (m_gameData != nullptr)
			{
				delete m_gameData;
			}
		}

		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CGameManager::Update()
		{
			if (m_pScene != nullptr)
			{
				auto p = m_pScene->Update();
				if (p != m_pScene)
				{
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
			if (m_pStageController != nullptr)
			{
				auto p = m_pStageController->Update();
				if (p != m_pStageController)
				{
					delete m_pStageController;

					auto p2 = dynamic_cast<CBase*>(p);
					if (p2 != nullptr)
					{
						m_pStageController = p2;
						return this;
					}
					else
					{
						m_pStageController = nullptr;
						return p;
					}
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