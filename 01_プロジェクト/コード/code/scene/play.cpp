//===========================================
// 
// ゲーム全体処理[play.h]
// Auther:UedaKou
// 
//===========================================
#include "play.h"// プレイシーン
#include "game_data.h"			// ゲームデータ
#include "../object/field.h"	// フィールド
#include "../object/player.h"	// プレイヤー
#include "../object/enemy000.h"	// エネミー000
#include "../object/enemy100.h"	// エネミー100(トラック)
#include "scene_result.h"		// リザルトシーン

namespace Scene {
	class CTitle;
	class CResult;
	class CGameOver;
	namespace Game {
		//============================================
		// コンストラクタ
		//============================================
		Play::Play(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CObject::ReleaseScene();


			// プレイヤー生成
			CPlayer* pPlayer = CPlayer::creat();	// プレイヤー生成
			pPlayer->SetReleaseScene(false);	// シーンリリースで解放するか設定
			if (m_gameData != nullptr)
			{
				m_gameData->SetPlayer(pPlayer);	// プレイヤーを設定
				m_gameData->SetScore(0);		// スコアを初期化
			}

			CManager* pManager = CManager::GetInstance();
			CSound* pSound = pManager->GetSound();
			pSound->PlaySoundA(CSound::SOUND_LABEL::SOUND_STAGE000);
			bPause = false;

			m_pText = CText::creat(100, 0, 0, 3, FALSE, CText::FontType::Terminal);
			m_pText->SetSpace(800,  0, SCREEN_W, SCREEN_H);
			m_pText->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			m_pText->SetReleaseScene(false);

		}
		Play::~Play()
		{
			CManager* pManager = CManager::GetInstance();
			CSound* pSound = pManager->GetSound();
			pSound->StopSound(CSound::SOUND_LABEL::SOUND_STAGE000);
			// スコア描画テキストを解放
			if (m_pText != nullptr)
			{
				m_pText->Release();
				m_pText = nullptr;
			}
		}

		//============================================
		// 更新
		//============================================
		nsPrev::CBase* Play::Update()
		{
			CInputKeyboard* Kye = CManager::GetInstance()->GetInKey();
			if (Kye->GetTrigger(DIK_P))
			{// ポーズ
				bPause = bPause ? false : true;
			}
			// ポーズ中
			if (bPause)
			{
				if (Kye->GetTrigger(DIK_RETURN))
				{
					return nsPrev::CBase::makeScene<CTitle>();
				}
			}
			else
			{
				CameraController();	// カメラコントロール
				CObject* pObjectTop[MAX_PRIORITY];
				CObject:: GetAllObject(pObjectTop);
				for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
				{
					CObject* pObject = pObjectTop[nCnt];
					while (pObject != nullptr)
					{
						CObject* pNext = pObject->GetNext();
						CEnemy::ENEMY_TYPE type;
						switch (pObject->GetType())
						{
						case CObject::TYPE::PLAYER:
						{
							CPlayer* pPlayer = (CPlayer*)pObject;
							if (pPlayer->GetLife() <= 0)
							{
								return nsPrev::CBase::makeScene<CGameOver>();
							}
							break;
						}
						case CObject::TYPE::ENEMY:	// 敵
						{
							CEnemy* pEnemy = (CEnemy*)pObject;
							type = pEnemy->GetType();
							switch (type)
							{
							case CEnemy::ENEMY_TYPE::Enemy000:	// ボス100
								if (pObject->IsDeathFlag() == true)
								{
									m_gameData->AddScore(5);
								}
								break;
							case CEnemy::ENEMY_TYPE::Enemy100:	// ボス100
								if (pObject->IsDeathFlag() == true)
								{
									
									m_gameData->AddScore(100);
								}
								break;
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
			}
#ifdef _DEBUG
			if (Kye->GetTrigger(DIK_G))
			{
				return nsPrev::CBase::makeScene<CGameOver>();
			}
			else if (Kye->GetTrigger(DIK_T))
			{
				nsPrev::CBase* p = nsPrev::CBase::makeScene<CResult>();
				((CResult*)p)->SetScore(m_gameData->GetScore());
				return p;
			}
			if (Kye->GetTrigger(DIK_Z))
			{
				m_gameData->AddScore(1);
			}
			else if (Kye->GetTrigger(DIK_X))
			{
				m_gameData->AddScore(-1);
			}
#endif // !_DEBUG
			string Score = to_string(m_gameData->GetScore());
			Score.insert(0, 4 - Score.length(), '0');

			string text = "SCORE : " + Score;
			if (m_pText != nullptr)
			{
				m_pText->SetText(text);
			}

			return this;
		}
		//============================================
		// 描画
		//============================================
		void Play::Draw() const
		{
			if (m_pText != nullptr)
			{
				m_pText->Draw();
			}
		}
		
		//============================================
		// ポーズ中取得
		//============================================
		bool Play::GetPose()
		{
			if (bPause == true)
			{
				return true;
			}
			return false;
		}
		//============================================
		// カメラ制御
		//============================================
		void Play::CameraController()
		{
			CCamera* pCamera = CManager::GetInstance()->GetCamera();
			if (pCamera->GetCameraControllreFpllow() == false)
			{
				//CSaveObject* object = m_gameData->GetTop();
				//CSaveObject* Next = nullptr;
				CObject* object[MAX_PRIORITY];
				CObject::GetAllObject(object);
				CObject* Next = nullptr;
				for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
				{
					while (object[nCnt] != nullptr)
					{
						Next = object[nCnt]->GetNext();

						if (object[nCnt]->GetType() == CObject::TYPE::PLAYER)
						{
							D3DXVECTOR3 posPlsyer = ((CPlayer*)object[nCnt])->GetPos();
							pCamera->SetCameraPosR(D3DXVECTOR3(posPlsyer));	// 注視点をプレイヤーにする
							D3DXVECTOR3 rotCumera = pCamera->GetCameraRot();	// カメラの向きを取得
							D3DXVECTOR3 posV;	// カメラの視点計算用

							posV.x = posPlsyer.x - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * sinf(rotCumera.y) * POS_CAMERA;
							posV.y = posPlsyer.y - sinf(rotCumera.x - (D3DX_PI * 0.5f)) * POS_CAMERA;
							posV.z = posPlsyer.z - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * cosf(rotCumera.y) * POS_CAMERA;

							pCamera->SetCameraPosV(D3DXVECTOR3(posV));	// 注視点をプレイヤーにする

							break;
						}

						object[nCnt] = Next;
					}			

				}
			}
		}

		//============================================
		// 生成
		//============================================
		template<>
		nsPrev::CBase* CBase::makeScene<Play>(CGameData* gamaDate) {
			return new Play(this, gamaDate);
		}
	}
}