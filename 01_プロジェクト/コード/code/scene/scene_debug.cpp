//===========================================
// 
// �f�o�b�N�V�[��[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_debug.h"	// �f�o�b�N�V�[��
#include "../base/manager.h"		// �}�l�[�W���[
#include "../object/field.h"		// �t�B�[���h


namespace Scene {
	namespace Game {
		//============================================
		// �R���X�g���N�^
		//============================================
		CSceneDebug::CSceneDebug(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			m_pField = CField::creat(CField::TYPE::Road, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CSceneDebug::~CSceneDebug()
		{
			m_pField->Release();
		}
		//============================================
		// �X�V
		//============================================
		CBase* CSceneDebug::Update()
		{
			m_pField->Update();

			return this;
		}
		//============================================
		// �`��
		//============================================
		void CSceneDebug::Draw() const
		{
		}

		//============================================
		// �|�[�Y���擾
		//============================================
		bool CSceneDebug::GetPose()
		{
			return false;
		}

		template<>
		nsPrev::CBase* CBase::makeScene<CSceneDebug>(CGameData* gamaData) {
			return new CSceneDebug(this, gamaData);
		}
	}
}