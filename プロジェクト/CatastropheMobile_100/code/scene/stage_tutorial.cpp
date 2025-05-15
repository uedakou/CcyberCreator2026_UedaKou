//===========================================
// 
// チュートリアルステージ[stage_tutorial.h]
// Auther:UedaKou
// 
//===========================================
#include "stage_tutorial.h"		// チュートリアル

#include "../object/player.h"	// プレイヤー
#include "../object/field.h"	// フィールド
#include "../base_object/object_2D.h"	// ポップアップ用2D
#include "../object/enemy000tutorial.h"	// 敵000
#include "../base_object/object_fade.h"	// フェード
#include "../base_object/object_billboard.h"	// ビルボー

namespace Scene {
	namespace Game {
		class CStage_000;
		//============================================
		// コンスト
		//============================================
		CStage_Tutorial::CStage_Tutorial(CBase* scene, CGameData* gameData) :
			CStageLode(scene, gameData)
		{
			CObject::ReleaseScene();

			m_nCntMakeFilde = 0;

			CPlayer* pPlayer = m_gameData->GetPlayer();
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
				m_gameData->SaveObject(CGameObjectSave::TYPE::BILLBOAD, pBillbord);


				fRand = (float)(rand() % 100 / 10);
				pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
				pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
				pBillbord->SetType(CObjectBillbord::TYPE::TREE);
				m_gameData->SaveObject(CGameObjectSave::TYPE::BILLBOAD, pBillbord);
			}

			m_pUpdate = new CTutorial000(gameData);

			CFade::creat(CFade::FADE_TYPE::WHITE_IN, 30);
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Tutorial::~CStage_Tutorial()
		{
			// 更新を削除
			if (m_pUpdate != nullptr)
			{
				delete m_pUpdate;
			}
			// スコア
			CGameObjectSave* pObject = m_gameData->GetTop();
			CGameObjectSave* pNext = nullptr;
			while (pObject != nullptr)
			{
				pNext = pObject->GetNext();
				if (pObject->GetType() == CGameObjectSave::SCORE)
				{
					CObject* pText = pObject->GetMyObject();
					//pText->SetNormalDraw(true);
					//pText->SetPoseDraw(true);
				}
				pObject = pNext;
			}
			m_gameData->AllFlagDeath();
		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CStage_Tutorial::Update()
		{
			CManager* manager = CManager::GetInstance();	// マネージャー
			bool b = manager->GetSceneManager()->GetPose();	// ポーズ状態取得
			// ポーズでなければ
			if (b == false)
			{
				CPlayer* pPlayer = m_gameData->GetPlayer();
				if (pPlayer != nullptr)
				{
					if (pPlayer->GetPos().z >= 3000.0f + 1000.0f * m_nCntMakeFilde)
					{
						CField* pField = nullptr;
						pField = CField::creat(CField::TYPE::Road,
							D3DXVECTOR3(0.0f, 0.0f, 10000.0f + 1000.0f * m_nCntMakeFilde),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
						pField->SetBlock(1, 1);
						pField->SetPlayer(pPlayer);
						m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);


						pField = CField::creat(CField::TYPE::Grass,
							D3DXVECTOR3(2000.0f, 0.0f, 10000.0f + 1000.0f * m_nCntMakeFilde),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
						pField->SetBlock(3, 1);
						pField->SetPlayer(pPlayer);
						m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);


						pField = CField::creat(CField::TYPE::Grass,
							D3DXVECTOR3(-2000.0f, 0.0f, 10000.0f + 1000.0f * m_nCntMakeFilde),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
						m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, pField);

						pField->SetBlock(3, 1);
						pField->SetPlayer(pPlayer);

						// ビルボード
						CObjectBillbord* pBillbord = nullptr;
						float fRand = 0;
						for (int nCnt = 0; nCnt < 4; nCnt++)
						{
							fRand = (float)(rand() % 100 / 10);
							pBillbord = CObjectBillbord::creat(D3DXVECTOR3(700.0f, 0.0f, 9750.0f + 1000 * m_nCntMakeFilde + 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
							pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
							pBillbord->SetType(CObjectBillbord::TYPE::TREE);
							m_gameData->SaveObject(CGameObjectSave::TYPE::TREE, pBillbord);

							fRand = (float)(rand() % 100 / 10);
							pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 9750.0f + 1000 * m_nCntMakeFilde + 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
							pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
							pBillbord->SetType(CObjectBillbord::TYPE::TREE);
							m_gameData->SaveObject(CGameObjectSave::TYPE::TREE, pBillbord);
						}
						m_nCntMakeFilde++;
					}
				}




				CInputKeyboard* Key = manager->GetInKey();	// キーボード入力
				CStageLode::Update();// 生成部分更新

				CObject* Top[MAX_PRIORITY];	// トップ取得
				CObject::GetAllObject(Top);	// 先頭取得
				// 地面生成
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
									if (pPlayer->GetPos().z >= pEnemy->GetPos().z + 500.0f)
									{
										pEnemy->SetPosZ(pPlayer->GetPos().z - 500.0f);
									}

								}
								break;
							}
							case CEnemy::ENEMY_TYPE::Enemy100: {

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

				// チュートリアル更新
				CTutorialStrategy* p = m_pUpdate->update();
				if (p != m_pUpdate)
				{
					delete m_pUpdate;
					m_pUpdate = p;
					if (p == nullptr)
					{
						return makeScene<CStage_000>(m_gameData);
					}
				}
#if _Debug
				if (Key->GetTrigger(DIK_RETURN))
				{
					return makeScene<CStage_000>(m_gameData);
				}
#endif // _Debug

			}
			return this;
		}
		//============================================
		// デストラクタ
		//============================================
		bool CStage_Tutorial::GetPose()
		{
			return false;
		}

		//============================================
		// 生成
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<CStage_Tutorial>(CGameData* gamaData) {
			return new CStage_Tutorial(this, gamaData);
		}

		//============================================
		// チュートリアル
		//============================================
		//============================================
		// コンストラクタ
		//============================================
		CStage_Tutorial::CTutorial000::CTutorial000(CGameData* gamaData):
			CTutorialStrategy(gamaData),
			m_nMaxCnt(60)
		{
			m_nCnt = 0;
			m_pPopup = CObject2D::creat(4, D3DXVECTOR3(900.0f, 200.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f));
			m_gameData->SaveObject(CGameObjectSave::TYPE::FIELD, m_pPopup);

			m_pPopup->SetTexture("data\\TEXTURE\\Tutorial_popup_000.png");
			m_pPopup->SetReleaseScene(false);
			m_bNext = false;
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Tutorial::CTutorial000::~CTutorial000()
		{
			if (m_pPopup != nullptr)
			{
				m_pPopup->Release();
				m_pPopup = nullptr;
			}
		}
		//============================================
		// 更新
		//============================================
		CStage_Tutorial::CTutorialStrategy* CStage_Tutorial::CTutorial000::update()
		{
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* pKey = pManager->GetInKey();
			if (pKey->GetTrigger(DIK_W)||
				pKey->GetTrigger(DIK_A)||
				pKey->GetTrigger(DIK_S)||
				pKey->GetTrigger(DIK_D))
			{
				m_bNext = true;
			}
			if (m_bNext)
			{
				m_nCnt++;
				if (m_nCnt >= m_nMaxCnt)
				{
					return new CTutorial001(m_gameData);
				}
			}
			return this;
		}
		//============================================
		// コンストラクト
		//============================================
		CStage_Tutorial::CTutorial001::CTutorial001(CGameData* gamaData):
			CTutorialStrategy(gamaData),
			m_nMaxCnt(60)
		{
			m_nCnt = 0;
			m_pPopup = CObject2D::creat(4, D3DXVECTOR3(900.0f, 200.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f));

			m_pPopup->SetTexture("data\\TEXTURE\\Tutorial_popup_001.png");
			m_pPopup->SetReleaseScene(false);	// シーンで

			m_bNext = false;
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Tutorial::CTutorial001::~CTutorial001()
		{
			if (m_pPopup != nullptr)
			{
				m_pPopup->Release();
				m_pPopup = nullptr;
			}
		}
		//============================================
		// 更新
		//============================================
		CStage_Tutorial::CTutorialStrategy* CStage_Tutorial::CTutorial001::update()
		{
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* pKey = pManager->GetInKey();
			if (pKey->GetTrigger(DIK_SPACE) )
			{
				m_bNext = true;
			}
			if (m_bNext)
			{
				m_nCnt++;
				if (m_nCnt >= m_nMaxCnt)
				{
					return new CTutorial002(m_gameData);
				}
			}

			return this;
		}
		//============================================
		// コンストラク
		//============================================
		const float CStage_Tutorial::CTutorial002::m_fEnemyPosZ = 3000.0f;	
		CStage_Tutorial::CTutorial002::CTutorial002(CGameData* gamaData):
			CTutorialStrategy(gamaData),
			m_nMaxCnt(60)
		{
			m_nCnt = 0;	// カウントを０にする
			m_bNext = false;

			m_pPopup = CObject2D::creat(4, D3DXVECTOR3(900.0f, 200.0f, 0.0f), D3DXVECTOR3(300.0f, 200.0f, 0.0f));	// ポップアップを生成
			m_pPopup->SetTexture("data\\TEXTURE\\Tutorial_popup_002.png");	// テクスチャ設定
			m_pPopup->SetReleaseScene(false);	// シーンリリースで解放するかどうか

			CPlayer* pPlayer = gamaData->GetPlayer();
			D3DXVECTOR3 pos = pPlayer->GetPos();
			m_pEnemy = CEnemy000Tutorial::creat(D3DXVECTOR3(pos.x, pos.y, pos.z + m_fEnemyPosZ));
			m_pEnemy->SetMovePos(D3DXVECTOR3(0.0f, 0.0f, 40.0f));
			m_pEnemy->SetReleaseScene(false);
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Tutorial::CTutorial002::~CTutorial002()
		{
			// ポップアップ死亡フラグを立てる
			if (m_pPopup != nullptr)
			{
				m_pPopup->Release();
				m_pPopup = nullptr;
			}
			// 敵死亡フラグを立てる
			if (m_pEnemy != nullptr)
			{
				m_pEnemy->Release();
				m_pPopup = nullptr;
			}
		}
		//============================================
		// 更新
		//============================================
		CStage_Tutorial::CTutorialStrategy* CStage_Tutorial::CTutorial002::update()
		{
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* pKey = pManager->GetInKey();
			if (m_pEnemy->GetLife() <= 0)

			{
				m_bNext = true;
			}
			if (m_bNext)
			{
				m_nCnt++;
				if (m_nCnt >= m_nMaxCnt)
				{
					CFade::creat(CFade::FADE_TYPE::WHITE_OUT, 30);

					return nullptr;
				}
			}
			return this;
		}
	}
}