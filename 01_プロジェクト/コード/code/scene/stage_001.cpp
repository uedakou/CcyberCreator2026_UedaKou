//===========================================
// 
// �X�e�[�W000[stage_000.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_001.h"	// �X�e�[�W000
#include "../object/enemy000.h"	// �G000
#include "../object/field.h"	// �t�B�[���h
#include "../object/player.h"	// �v���C���[
#include "../base_object/object_fade.h"	// �t�F�[�h
#include "../base_object/object_billboard.h"	// �r���{�[�h
#include "../object/enemy100.h"	// �G�l�~�[�g���b�N
#include "../base_object/object_2D.h"	// �I�u�W�F�N�g2D


namespace Scene {
	namespace Game {
		//============================================
		// �R���X�g
		//============================================
		CStage_001::CStage_001(CBase* scene, CGameData* gameData) :
			CStageLode(scene, gameData)
		{
			CObject::ReleaseScene();
			CPlayer* pPlayer = m_gameData->GetPlayer();	// �v���C���[�擾

			
			m_nCntMakeFilde = 0;	// �J�E���g���O�ɂ���
			

			// �t�B�[���h
			CField* pField = nullptr;
			// �A�X�t�@���g
			pField = CField::creat(CField::TYPE::Road,
				D3DXVECTOR3(0.0f, 0.0f, 4500.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(1, 10);
			pField->SetPlayer(pPlayer);
			m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);

			// �_�[�g
			pField = CField::creat(CField::TYPE::Grass,
				D3DXVECTOR3(2000.0f, 0.0f, 4500.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(3, 10);
			pField->SetPlayer(pPlayer);
			m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);


			pField = CField::creat(CField::TYPE::Grass,
				D3DXVECTOR3(-2000.0f, 0.0f, 4500.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(3, 10);
			pField->SetPlayer(pPlayer);
			m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);

			// �r���{�[�h
			CObjectBillbord* pBillbord = nullptr;
			float fRand = 0;
			for (int nCnt = 0; nCnt < 39; nCnt++)
			{
				fRand = (float)(rand() % 100 / 10);
				pBillbord = CObjectBillbord::creat(D3DXVECTOR3(700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
				pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
				pBillbord->SetType(CObjectBillbord::TYPE::TREE);

				m_gameData->SaveObject(CGameObjectSave::TYPE::TREE, pBillbord);

				fRand = (float)(rand() % 100 / 10);
				pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
				pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
				pBillbord->SetType(CObjectBillbord::TYPE::TREE);

				m_gameData->SaveObject(CGameObjectSave::TYPE::TREE, pBillbord);
			}

			CCreatEnemy* pEnemy = nullptr;
#if 0
			pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
			pEnemy->m_pos = D3DXVECTOR3(0.0f, 0.0f, 10000.0f);
			pEnemy->m_enemytype = CCreatEnemy::ENEMY_TYPE::Enemy000;

			pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
			pEnemy->m_pos = D3DXVECTOR3(0.0f, 0.0f, 20000.0f);
			pEnemy->m_enemytype = CCreatEnemy::ENEMY_TYPE::Enemy000;

			pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
			pEnemy->m_pos = D3DXVECTOR3(0.0f, 0.0f, 30000.0f);
			pEnemy->m_enemytype = CCreatEnemy::ENEMY_TYPE::Enemy000;

			pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
			pEnemy->m_pos = D3DXVECTOR3(0.0f, 0.0f, 40000.0f);
			pEnemy->m_enemytype = CCreatEnemy::ENEMY_TYPE::Enemy000;

			pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
			pEnemy->m_pos = D3DXVECTOR3(0.0f, 0.0f, 50000.0f);
			pEnemy->m_enemytype = CCreatEnemy::ENEMY_TYPE::Enemy000;

			pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
			pEnemy->m_pos = D3DXVECTOR3(0.0f, 0.0f, 60000.0f);
			pEnemy->m_enemytype = CCreatEnemy::ENEMY_TYPE::Enemy100;

#else
			pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
			pEnemy->m_pos = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
			pEnemy->m_enemytype = CCreatEnemy::ENEMY_TYPE::Enemy100;
#endif // 0
			CFade::creat(CFade::FADE_TYPE::WHITE_IN, 30);
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CStage_001::~CStage_001()
		{
			m_gameData->AllFlagDeath();
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		nsPrev::CBase* CStage_001::Update()
		{
			CStageLode::Update();
			CPlayer* pPlayer = m_gameData->GetPlayer();

			CObject* Top[MAX_PRIORITY];
			CObject::GetAllObject(Top);
			for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
			{
				CObject* pObject = Top[nCnt];
				CObject* pNext = nullptr;
				while (pObject != nullptr)
				{
					pNext = pObject->GetNext();
					switch (pObject->GetType())
					{
					case CObject::TYPE::PLAYER: {
						if (((CPlayer*)pObject)->GetPos().z >= 3000.0f + 1000.0f * m_nCntMakeFilde)
						{
							CField* pField = nullptr;
							pField = CField::creat(CField::TYPE::Road,
								D3DXVECTOR3(0.0f, 0.0f, 10000.0f + 1000 * m_nCntMakeFilde),
								D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
							pField->SetBlock(1, 1);
							pField->SetPlayer(((CPlayer*)pObject));
							m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);

							pField = CField::creat(CField::TYPE::Grass,
								D3DXVECTOR3(2000.0f, 0.0f, 10000.0f + 1000 * m_nCntMakeFilde),
								D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
							pField->SetBlock(3, 1);
							pField->SetPlayer(((CPlayer*)pObject));
							m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);

							pField = CField::creat(CField::TYPE::Grass,
								D3DXVECTOR3(-2000.0f, 0.0f, 10000.0f + 1000 * m_nCntMakeFilde),
								D3DXVECTOR3(0.0f, 0.0f, 0.0f),
								D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
							pField->SetBlock(3, 1);
							pField->SetPlayer(((CPlayer*)pObject));
							m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);

							// �r���{�[�h
							CObjectBillbord* pBillbord = nullptr;
							float fRand = 0;
							for (int nCnt = 0; nCnt < 4; nCnt++)
							{
								fRand = (float)(rand() % 100 / 10);
								pBillbord = CObjectBillbord::creat(D3DXVECTOR3(700.0f, 0.0f, 9750.0f + 1000 * m_nCntMakeFilde + 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
								pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
								pBillbord->SetType(CObjectBillbord::TYPE::TREE);
								m_gameData->SaveObject(CGameObjectSave::TYPE::BILLBOAD, pBillbord);

								fRand = (float)(rand() % 100 / 10);
								pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 9750.0f + 1000 * m_nCntMakeFilde + 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
								pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
								pBillbord->SetType(CObjectBillbord::TYPE::TREE);
								m_gameData->SaveObject(CGameObjectSave::TYPE::BILLBOAD, pBillbord);
							}
							m_nCntMakeFilde++;
						}
						break;
					}
					case CObject::TYPE::FIELD: {
						CField* pFade = (CField*)pObject;
						if (pPlayer != nullptr)
						{
							if (pPlayer->GetPos().z >= pFade->GetPos().z + 6000.0f)
							{
								pFade->Release();
							}
						}
						break;
					}
					case CObject::TYPE::BILLBOARD: {
						CObjectBillbord* pFade = (CObjectBillbord*)pObject;
						if (pPlayer != nullptr)
						{
							if (pPlayer->GetPos().z >= pFade->GetPos().z + 6000.0f)
							{
								pFade->Release();
							}
						}
						break;
					}
					case CObject::TYPE::ENEMY: {
						switch (((CEnemy*)pObject)->GetType())
						{
						case CEnemy::ENEMY_TYPE::Enemy000: {
							CEnemy000* pEnemy = (CEnemy000*)pObject;
							if (pPlayer != nullptr)
							{
								D3DXVECTOR3 playerPos = pPlayer->GetPos();
								if (playerPos.z - 1000.0f >= pEnemy->GetPos().z)
								{
									pEnemy->SetPosZ(playerPos.z - 1000.0f);
								}
							}
							break;
						}
						case CEnemy::ENEMY_TYPE::Enemy100: {
							CEnemy100* pEnemy = (CEnemy100*)pObject;
							if (pPlayer != nullptr)
							{
								D3DXVECTOR3 playerPos = pPlayer->GetPos();
								if (playerPos.z - 1000.0f >= pEnemy->GetPos().z)
								{
									pEnemy->SetPosZ(playerPos.z - 1000.0f);
								}
							}
							break;
						}
						default:
							break;
						}
						break;
					}
					default:
						break;
					}
					pObject = pNext;
				}
			}
			return this;
		}

		void CStage_001::Draw() const
		{
		}

		//============================================
		// �f�X�g���N�^
		//============================================
		bool CStage_001::GetPose()
		{
			return false;
		}

		//============================================
		// ����
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_001>(CGameData* gamaData) {
			return new CStage_001(this, gamaData);
		}
	}
}