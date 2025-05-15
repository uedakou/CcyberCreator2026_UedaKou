//============================================
//
// ���U���g�V�[��[scene_result.cpp]
// Author:Uedakou
// 
//============================================
#include "scene_result.h"	// ���U���g
#include "../base/manager.h"	// �}�l�[�W���[
#include "../base_object/object_2D.h"	// �I�u�W�F�N�g2D
#include "../base/pch.h"	// �v���R���p�C��
#include "../base_object/text.h"	// �e�L�X�g
#include "../base_object/object_3D.h"	// �I�u�W�F�N�g�RD
#include "../base_object/motion.h"

#include <fstream>
#include "../base_object/object_billboard.h"


namespace Scene {
	class CTitle;

	//============================================
	// �����I�u�W�F�N�g�X�V
	//============================================
	CResult::CResult(CBase* scene) :
		CBase(*scene),
		m_nMAXCntFlashing(30)
	{
		CManager* pManager = CManager::GetInstance();
		CSound* pSound = pManager->GetSound();
		CCamera* pCamera = pManager->GetCamera();

		CObject::ReleaseScene();
		pSound->PlaySoundA(CSound::SOUND_LABEL::SOUND_REZULT000);

		// �w�i������
		m_pField[0] = CObject3D::creat(
			D3DXVECTOR3(0.0f, 0.0f, 4500.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[0]->SetBlock(1, 10);	// �u���b�N����ݒ�
		m_pField[0]->SetTexture("data\\TEXTURE\\AsphaltLoad000.png");	// �e�N�X�`���ݒ�
		m_pField[0]->SetType(CObject::TYPE::FIELD);
		m_pField[0]->SetReleaseScene(false);

		m_pField[1] = CObject3D::creat(
			D3DXVECTOR3(-2000.0f, 0.0f, 4500.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[1]->SetBlock(3, 10);
		m_pField[1]->SetTexture("data\\TEXTURE\\Glass000.png");
		m_pField[1]->SetType(CObject::TYPE::FIELD);
		m_pField[1]->SetReleaseScene(false);

		m_nCntField = 0;

		float fRand;
		CObjectBillbord* pBillbord = nullptr;
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			fRand = (float)(rand() % 100 / 10);
			pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);
		}

		// �����L���O����
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			// m_Ranc���J���łȂ���΍폜
			if (m_Ranc[nCnt] != nullptr)
			{
				Beep(900, 300);
				delete m_Ranc[nCnt];
				m_Ranc[nCnt] = nullptr;
			}
			m_Ranc[nCnt] = CText::creat(100, 0, 0, 3, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_PITCH, CText::FontType::Terminal);
			m_Ranc[nCnt]->SetSpace(100, 200 + 100* nCnt, SCREEN_W, SCREEN_H);	// �����X�y�[�X�ݒ�
			m_Ranc[nCnt]->SetReleaseScene(false);	// �V�[���Ń����[�X���Ȃ��悤�ɂ���
			m_nRanc[nCnt] = 0;	// �����L���O�̒��g��������
		}
		// �󂯎��X�R�A
		m_Score = nullptr;
		m_nScore = -1;
		// �_��
		m_nCntFlashing = 0;
		bFlashing = false;

		D3DXVECTOR3 CorPos = D3DXVECTOR3(-200.0f, 0.0f,2000.0f);
		m_pCor = nullptr;
		m_pCor = CObjectMotion::creat("data/CHARACTER/motion_Player.txt");
		m_pCor->SetPos(CorPos);
		m_pCor->SetRotY(AngleToRadian(180.0f));
		m_pCor->SetMotion(1);

		// �J����
		D3DXVECTOR3 CameraRPos = D3DXVECTOR3(CorPos.x + 50.0f, CorPos.y, CorPos.z + 80.0f);
		pCamera->SetCameraPosR(CameraRPos);	// �����_���v���C���[�ɂ���
		D3DXVECTOR3 rotCumera = pCamera->GetCameraRot();	// �J�����̌������擾
		D3DXVECTOR3 posV;	// �J�����̎��_�v�Z�p
		rotCumera.y = AngleToRadian(30.0f);
		pCamera->SetCameraRot(CCamera::CENTER::R, rotCumera);
		float Leng = 300.0f;
		posV.x = CameraRPos.x - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * sinf(rotCumera.y) * Leng;
		posV.y = CameraRPos.y - sinf(rotCumera.x - (D3DX_PI * 0.5f)) * Leng;
		posV.z = CameraRPos.z - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * cosf(rotCumera.y) * Leng;
		pCamera->SetCameraPosV(D3DXVECTOR3(posV));	// �����_���v���C���[�ɂ���
		LoadRanc();
	}
	//============================================
	// �����I�u�W�F�N�g�X�V
	//============================================
	CResult::~CResult()
	{
		CManager* pManager = CManager::GetInstance();
		// BGM���~�߂�
		CSound* pSound = pManager->GetSound();
		pSound->StopSound(CSound::SOUND_LABEL::SOUND_REZULT000);

		// �J�����̌�����߂�
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		D3DXVECTOR3 rotCumera = pCamera->GetCameraRot();	// �J�����̌������擾
		rotCumera.y = D3DX_PI;
		pCamera->SetCameraRot(CCamera::CENTER::R, rotCumera);

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_pField[nCnt] != nullptr)
			{
				m_pField[nCnt]->Release();
				m_pField[nCnt] = nullptr;
			}
		}
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			if (m_Ranc[nCnt] != nullptr)
			{
				m_Ranc[nCnt]->Release();
				m_Ranc[nCnt] = nullptr;
			}
		}
		if (m_Score != nullptr)
		{
			m_Score->Release();
			m_Score = nullptr;
		}

	}
	//============================================
	// �����I�u�W�F�N�g�X�V
	//============================================
	CBase* CResult::Update()
	{
		CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();
		if (pKey->GetTrigger(DIK_RETURN))
		{
			return makeScene<CTitle>();
		}
		// �w�i
		CObject* object[MAX_PRIORITY];
		CObject::GetAllObject(object);
		CObject* Next = nullptr;
		// �n�ʂ̓���
		if (m_nCntField % 20 == 0)
		{
			float fRand = (float)(rand() % 100 / 10);
			CObjectBillbord* pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 2750), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);
		}
		m_nCntField++;

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_pField[nCnt] != nullptr)
			{
				m_pField[nCnt]->AddTexUV(D3DXVECTOR2(0.0f, -0.01f), D3DXVECTOR2(0.0f, -0.01f));
			}
		}
		for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
		{
			while (object[nCnt] != nullptr)
			{
				Next = object[nCnt]->GetNext();
				if (object[nCnt]->GetType() == CObject::TYPE::BILLBOARD)
				{

					CObjectBillbord* pTree = (CObjectBillbord*)object[nCnt];
					pTree->AddPos(D3DXVECTOR3(0.0f, 0.0f, -10.0f));


					D3DXVECTOR3 pos = pTree->GetPos();
					if (pos.z <= -500.0f)
					{
						pTree->Release();
					}

				}
				object[nCnt] = Next;
			}
		}
		// �����L���O�����\��
		if (bFlashing)
		{
			m_nCntFlashing++;
			if (m_nCntFlashing >= m_nMAXCntFlashing)
			{
				bFlashing = false;
			}
		}
		else
		{
			m_nCntFlashing--;
			if (m_nCntFlashing <= 0)
			{
				bFlashing = true;
			}
		}
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			if (m_nRanc[nCnt] == m_nScore)
			{
				m_Ranc[nCnt]->SetCol(D3DXCOLOR(1.0f / m_nMAXCntFlashing * m_nCntFlashing, 1.0f / m_nMAXCntFlashing * m_nCntFlashing, 0.0f, 1.0f));
			}
		}

		return this;
	}
	//============================================
	// �����I�u�W�F�N�g�X�V
	//============================================
	void CResult::Draw()const
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			if (m_Ranc[nCnt] != nullptr)
			{
				string Score = to_string(m_nRanc[nCnt]);
				Score.insert(0, 4 - Score.length(), '0');

				string Text = to_string(nCnt + 1) + "�� : " + Score;
				m_Ranc[nCnt]->Print(Text);
			}
		}

		if (m_Score != nullptr)
		{
			string Score = to_string(m_nScore);
			Score.insert(0, 4 - Score.length(), '0');

			string Text = "You : " + Score;
			m_Score->Print(Text);
		}
	}

	void CResult::SetScore(int nScore)
	{
		bool nNowScoreRancIn(false);	// ���̃X�R�A�������N���肵����
		m_nScore = nScore;
		if (nScore > m_nRanc[4])
		{
			nNowScoreRancIn = true;
			m_nRanc[4] = nScore;
			//m_nScore = nScore;
		}
		else
		{
			m_Score = CText::creat(100, 0, 0, 3, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_PITCH, CText::FontType::Terminal);
			m_Score->SetSpace(800, 600, SCREEN_W, SCREEN_H);
			m_Score->SetReleaseScene(false);	// �V�[���Ń����[�X���Ȃ��悤�ɂ���
		}
		int nMax = 0;
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			nMax = nCnt;
			for (int nCnt1 = nCnt; nCnt1 < 5; nCnt1++)
			{
				if (m_nRanc[nCnt1] > m_nRanc[nCnt])
				{
					nMax = nCnt1;
				}
			}
			if (nCnt != nMax)
			{
				int a = m_nRanc[nCnt];
				m_nRanc[nCnt] = m_nRanc[nMax];
				m_nRanc[nMax] = a;
			}
		}
		
		ofstream file("data/Ranking.txt");

		if (!file) {
			std::cerr << "�t�@�C�����J���܂���ł����I" << std::endl;
			return ;
		}

		for (int i = 0; i < 5; i++) {
			file << "RANKING " << m_nRanc[i] << std::endl;
		}

		file.close();
	}

	//============================================
	// �|�[�Y���擾
	//============================================
	bool CResult::GetPose()
	{
		return false;
	}
	//============================================
	// �����L���O�ǂݍ���
	//============================================
	void CResult::LoadRanc()
	{
		ifstream file("data\\Ranking.txt");  // �ǂݍ��ރt�@�C���̃p�X���w��
		if (file.fail()) {
			cerr << "�t�@�C�����J���܂���ł���\n";
			Beep(1200, 300);
			return;
		}
		string str0, str1, str2, str3;	// ������i�[�p
		string skip;			// �X�L�b�v�p�i�[
		int nCntRank = 0;

		// ���o���Z�q>>���g���ăf���~�^�ŋ�؂�ꂽ�P��C�l��ǂݍ���
		while (file >> str0)
		{
			if (str0[0] == '#')
			{
				getline(file, skip);	// ��s�X�L�b�v
			}
			// ���f����
			else if (str0.compare("RANKING") == 0)
			{
				if (nCntRank <= 5)
				{
					file >> str1;	// �����N�X�R�A�����擾
					m_nRanc[nCntRank] = atoi(str1.c_str());
					getline(file, skip);	// ��s�X�L�b�v
					nCntRank++;
				}
			}
		}
		file.close();
	}

	void CResult::SaveRanc()
	{

	}

	template<>
	CBase* CBase::makeScene<CResult>() {
		return new CResult(this);
	}
}