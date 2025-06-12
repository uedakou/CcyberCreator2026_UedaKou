//===========================================
// 
// ステージ000[stage_000.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_000.h"	// ステージ000
#include "../object/enemy000.h"	// 敵000
#include "../object/field.h"	// フィールド
#include "../object/player.h"	// プレイヤー
#include "../base_object/object_fade.h"	// フェード
#include "../base_object/object_billboard.h"	// ビルボード
#include "../object/enemy100.h"		// 敵100


namespace Scene {
	class CResult;
	namespace Game {
		const D3DXVECTOR3 CStage_000::s_pPUsiz = { 500.0f, 100.0f, 0.0f };	// ポップアップサイズ設定
		const D3DXVECTOR3 CStage_000::s_pPUpos = { SCREEN_W * 0.5f -100.0f, s_pPUsiz.y * 0.5f, 0.0f };	// ポップアップ位置
		const string CStage_000::s_PUTextyure = "data/TEXTURE/Instructions_000.png";	// ポップアップ位置
		class CStage_001;
		//============================================
		// コンスト
		//============================================
		CStage_000::CStage_000(CBase* scene, CGameData* gameData) :
			CStageLode(scene, gameData)
		{
			CObject::ReleaseScene();

			m_nCntMakeFilde = 0;
			CPlayer* pPlayer = gameData->GetPlayer();
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// プレイヤー位置設定

			m_gameData->SaveObject(CGameObjectSave::TYPE::PLAYER, pPlayer);

			// ポップアップを生成
			m_pPU = CObject2D::creat(7, s_pPUpos, s_pPUsiz);	// 生成
			m_pPU->SetTexture(s_PUTextyure);	// テクスチャ設定
			m_pPU->SetReleaseScene(false);

			// フィールド
			CField* pField = nullptr;
			// アスファルト
			pField = CField::creat(CField::TYPE::Road,
				D3DXVECTOR3(0.0f, 0.0f, 4500.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
			pField->SetBlock(1, 10);
			pField->SetPlayer(pPlayer);
			m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);

			// ダート
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

			// ビルボード
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
#if 1
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
		// デストラクタ
		//============================================
		CStage_000::~CStage_000()
		{
			m_gameData->AllFlagDeath();
			// ポップアップが有ったら解放する
			if (m_pPU!= nullptr)
			{
				m_pPU->Release();
				m_pPU = nullptr;
			}
		}
		//============================================
		// デストラクタ
		//============================================
		nsPrev::CBase* CStage_000::Update()
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

							// ビルボード
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
								if (playerPos.z  - 1000.0f>= pEnemy->GetPos().z)
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
								if (pEnemy->GetLife() <= 0)
								{
									return nsPrev::CBase::makeScene<CResult>();
								}
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

		void CStage_000::Draw() const
		{
		}

		//============================================
		// デストラクタ
		//============================================
		bool CStage_000::GetPose()
		{
			return false;
		}

		//============================================
		// 生成
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_000>(CGameData* gamaData) {
			return new CStage_000(this, gamaData);
		}
	}
}