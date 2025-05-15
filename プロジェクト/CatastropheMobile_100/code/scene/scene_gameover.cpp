//============================================
//
// �Q�[���I�[�o�[�V�[��[scene_result.cpp]
// Author:Uedakou
// 
//============================================
#include "scene_gameover.h"	// ���U���g
#include "../base/manager.h"	// �}�l�[�W���[
#include "../base_object/object_2D.h"	// �I�u�W�F�N�g2D
#include "../base/pch.h"	// �v���R���p�C��
#include "../base_object/object_billboard.h"	// �r���{�[�h
#include "../base_object/text.h"		// �e�N�X�g
#include "../base_object/object_3D.h"	// �I�u�W�F�N�g�RD�|���S��
#include "../base_object/motion.h"	// �I�u�W�F�N�g�RD�|���S��
#include "../base/calculation.h"	// �v�Z�p

namespace Scene {
	class CTitle;

	//============================================
	// �����I�u�W�F�N�g�X�V
	//============================================
	CGameOver::CGameOver(CBase* scene) :
		CBase(*scene)
	{
		CObject::ReleaseScene();

		CManager* pManager = CManager::GetInstance();
		CSound* pSound = pManager->GetSound();
		CCamera* pCamera = pManager->GetCamera();
		pSound->PlaySoundA(CSound::SOUND_LABEL::SOUND_REZULT000);	// BGM

#if 0
		CObject2D* object = CObject2D::creat(D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_W, 0.0f));
		object->SetTexture("data\\TEXTURE\\Result000.png");
		m_pObject = object;
#else 
		m_pObject = nullptr;
#endif // 0
		// �e�L�X�g
		m_pText = nullptr;
		m_pText = CText::creat(300, 100, 0, 2, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_PITCH, CText::FontType::Terminal);
		m_pText->SetCol(D3DXCOLOR(0.8f, 0.0f, 0.1f, 1.0f));

		// �w�i
		m_pField[0] = CObject3D::creat(
			D3DXVECTOR3(0.0f, 0.0f, 500.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[0]->SetBlock(1, 5);
		m_pField[0]->SetTexture("data\\TEXTURE\\AsphaltLoad000.png");
		m_pField[0]->SetType(CObject::TYPE::FIELD);
		m_pField[1] = CObject3D::creat(
			D3DXVECTOR3(-2000.0f, 0.0f, 500.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[1]->SetBlock(3, 5);
		m_pField[1]->SetTexture("data\\TEXTURE\\Glass000.png");
		m_pField[1]->SetType(CObject::TYPE::FIELD);

		float fRand;
		CObjectBillbord* pBillbord = nullptr;
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			fRand = (float)(rand() % 100 / 10);
			pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);
		}
		D3DXVECTOR3 CorPos = D3DXVECTOR3(-650.0f, 0.0f, 450.0f);
		m_pCor = nullptr;
		m_pCor = CObjectMotion::creat("data\\CHARACTER\\motion_Player.txt");
		m_pCor->SetPos(CorPos);
		m_pCor->SetRotY(AngleToRadian(130.0f));

		// �J����
		D3DXVECTOR3 CameraRPos = D3DXVECTOR3(CorPos.x + 50.0f, CorPos.y, CorPos.z + 80.0f);
		pCamera->SetCameraPosR(CameraRPos);	// �����_���v���C���[�ɂ���
		D3DXVECTOR3 rotCumera = pCamera->GetCameraRot();	// �J�����̌������擾
		D3DXVECTOR3 posV;	// �J�����̎��_�v�Z�p
		float Rot = AngleToRadian(140.0f);
		float Leng = 300.0f;
		posV.x = CameraRPos.x - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * sinf(Rot) * Leng;
		posV.y = CameraRPos.y - sinf(rotCumera.x - (D3DX_PI * 0.5f)) * Leng;
		posV.z = CameraRPos.z - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * cosf(Rot) * Leng;

		pCamera->SetCameraPosV(D3DXVECTOR3(posV));	// �����_���v���C���[�ɂ���
	}
	//============================================
	// �����I�u�W�F�N�g�X�V
	//============================================
	CGameOver::~CGameOver()
	{
		CManager* pManager = CManager::GetInstance();
		CSound* pSound = pManager->GetSound();
		pSound->StopSound(CSound::SOUND_LABEL::SOUND_REZULT000);
		//
		if (m_pObject != nullptr)
		{
			m_pObject->Release();
			m_pObject = nullptr;
		}
		if (m_pCor != nullptr)
		{
			m_pCor->Release();
			m_pCor = nullptr;
		}
	}
	//============================================
	// �����I�u�W�F�N�g�X�V
	//============================================
	CBase* CGameOver::Update()
	{
		CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();

		if (pKey->GetTrigger(DIK_RETURN))
		{
			return makeScene<CTitle>();
		}
		return this;
	}
	//============================================
	// �����I�u�W�F�N�g�X�V
	//============================================
	void CGameOver::Draw()const
	{
		if (m_pText != nullptr)
		{
			m_pText->Print("GameOver");
		}
	}

	//============================================
	// �|�[�Y���擾
	//============================================
	bool CGameOver::GetPose()
	{
		return false;
	}

	template<>
	CBase* CBase::makeScene<CGameOver>() {
		return new CGameOver(this);
	}
}