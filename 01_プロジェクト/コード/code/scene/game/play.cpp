//===========================================
// 
// ゲーム全体処理[play.h]
// Auther:UedaKou
// 
//===========================================
#include "play.h"// プレイシーン
#include "../../object/player.h"	// プレイヤー
#include "game_data.h"

namespace Scene {
	class CTitle;
	namespace Game {
		//============================================
		// コンストラクタ
		//============================================
		Play::Play(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			CPlayer* pPlayer = CPlayer::creat();
			pPlayer->SetReleaseScene(false);
			//pPlayer->SetNormalDraw(false);
			//pPlayer->SetPoseDraw(false);
			m_gameData->SetPlayer(pPlayer);

			CObject::ReleaseScene();

			CManager* pManager = CManager::GetInstance();
			CSound* pSound = pManager->GetSound();
			//pSound->PlaySound(CSound::SOUND_LABEL::SOUND_STAGE000);
			bPause = false;
		}
		Play::~Play()
		{
			CManager* pManager = CManager::GetInstance();
			CSound* pSound = pManager->GetSound();
			pSound->StopSound(CSound::SOUND_LABEL::SOUND_STAGE000);
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

			}
//#ifdef _DEBUG
//
//			if (Kye->GetTrigger(DIK_Z))
//			{
//				m_nScore++;
//			}
//			else if (Kye->GetTrigger(DIK_X))
//			{
//				m_nScore--;
//			}
//#endif // !_DEBUG
//			string Score = to_string(m_nScore);
//			Score.insert(0, 4 - Score.length(), '0');
//
//			string text = "SCORE : " + Score;
//			if (m_pText != nullptr)
//			{
//				m_pText->SetText(text);
//			}

			return this;
		}
		//============================================
		// 描画
		//============================================
		void Play::Draw() const
		{
			//if (m_pText != nullptr)
			//{
			//	m_pText->Draw();
			//}
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
			//CCamera* pCamera = CManager::GetInstance()->GetCamera();
			//if (pCamera->GetCameraControllreFpllow() == false)
			//{
			//	CObject* object[MAX_PRIORITY];
			//	CObject::GetAllObject(object);
			//	CObject* Next = nullptr;
			//	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
			//	{
			//		while (object[nCnt] != nullptr)
			//		{
			//			Next = object[nCnt]->GetNext();
			//			// キャラクターなら
			//			if (object[nCnt]->GetType() == CObject::TYPE::CHARACTER)
			//			{
			//				// プレイヤーなら
			//				if (static_cast<CCharacter*>(object[nCnt])->GetType() == CCharacter::TYPE::PLAYER)
			//				{
			//					// カメラを設定
			//					D3DXVECTOR3 posPlsyer = ((CPlayer*)object[nCnt])->GetPos();
			//					pCamera->SetCameraPosR(D3DXVECTOR3(posPlsyer));	// 注視点をプレイヤーにする
			//					D3DXVECTOR3 rotCumera = pCamera->GetCameraRot();	// カメラの向きを取得
			//					D3DXVECTOR3 posV;	// カメラの視点計算用

			//					posV.x = posPlsyer.x - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * sinf(rotCumera.y) * POS_CAMERA;
			//					posV.y = posPlsyer.y - sinf(rotCumera.x - (D3DX_PI * 0.5f)) * POS_CAMERA;
			//					posV.z = posPlsyer.z - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * cosf(rotCumera.y) * POS_CAMERA;

			//					pCamera->SetCameraPosV(D3DXVECTOR3(posV));	// 注視点をプレイヤーにする

			//					break;
			//				}
			//			}
			//			object[nCnt] = Next;
			//		}			

			//	}
			//}
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