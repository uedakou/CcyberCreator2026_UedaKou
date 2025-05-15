//===========================================
// 
// �Q�[���}�l�[�W���[[scene_game_manager.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_game_manager.h"	// �Q�[���}�l�[�W���[	
#include "game_data.h"			// �Q�[���f�[�^
#include "../object/player.h"	//�@�v���C���[

namespace nsThis = Scene::Game;
namespace Scene {
	namespace Game {
		class Play;
		class CSceneDebug;
		class CStage_000;
		class CSceneDebug;
		class CStage_Tutorial;
		//============================================
		// �R���X�g���N�^
		//============================================
		CGameManager::CGameManager(nsPrev::CBase* scene) :
			CBase(scene, new CGameData()),
			m_pScene(makeScene<Play>(m_gameData))
#if 1
			,m_pStageController(makeScene<CStage_Tutorial>(m_gameData))
#else 
#endif // 0
		{
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CGameManager::~CGameManager()
		{
			// �Ǘ��V�[��
			if (m_pScene != nullptr)
			{
				delete m_pScene;
			}
			// �����V�[��
			if (m_pStageController != nullptr)
			{
				delete m_pStageController;
			}
			// �v���C���[�������[�X
			CPlayer* pPlayer = m_gameData->GetPlayer();
			if (pPlayer != nullptr)
			{
				pPlayer->Release();
				m_gameData->SetPlayer(nullptr);
				pPlayer = nullptr;
			}
		}

		//============================================
		// �X�V
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
		// �`��
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
		// �R���X�g���N�^
		//============================================

		//============================================
		// �|�[�Y���擾
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