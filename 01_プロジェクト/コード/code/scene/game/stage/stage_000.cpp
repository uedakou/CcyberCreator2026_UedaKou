//===========================================
// 
// ステージ000[stage_000.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_000.h"		// チュートリアル

#include "../../../object/player.h"	// プレイヤー
#include "../../../object/base/object_2D.h"	// ポップアップ用2D
#include "../../../object/base/object_3D.h"	// ポップアップ用3D
#include "../../../object/base/object_X.h"	// ポップアップ用X
#include "../../../object/base/object_fade.h"	// フェード
#include "../../../object/base/object_billboard.h"	// ビルボード
#include "../game_data.h"	// ゲームデータ
#include "../../../object/base/text.h"	// テキスト
#include "../../../object/obstacles_tall.h"	// 障害物
#include "../../../object/obstacles_high.h"	// 障害物
#include "../../../object/obstacles_low.h"	// 障害物
namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const float CStage_000::s_fGool = 15000.0f;	// ゴール距離
		const string CStage_000::s_aStage = "data/STAGE/Stage_000.txt";	// チュートリアルのポップアップの大きさ

		const float CStage_000::s_fTutorialRange = 200.0f;	// チュートリアル当たり判定範囲
		// チュートリアル
		const float CStage_000::s_fTutorial_000 = 2000.0f;		// チュートリアルイベント
		const float CStage_000::s_fTutorial_001 = 4000.0f;		// チュートリアルイベント
		const float CStage_000::s_fTutorial_002 = 6000.0f;		// チュートリアルイベント
		const float CStage_000::s_fTutorial_003 = 8000.0f;		// チュートリアルイベント

		const bool CStage_000::s_bCanShownTutorial_000 = false;	// チュートリアルイベント
		const bool CStage_000::s_bCanShownTutorial_001 = false;		// チュートリアルイベント
		const bool CStage_000::s_bCanShownTutorial_002 = false;		// チュートリアルイベント
		const bool CStage_000::s_bCanShownTutorial_003 = false;		// チュートリアルイベント

		const D3DXVECTOR3 CStage_000::s_TutorialPopupPos = { 1000.0f, 300.0f, 0.0f };	// チュートリアルのポップアップの位置
		const D3DXVECTOR3 CStage_000::s_TutorialPopupSiz = { 300.0f, 200.0f, 0.0f };	// チュートリアルのポップアップの大きさ

		//============================================
		// コンスト
		//============================================
		CStage_000::CStage_000(CBase* scene, CGameData* gameData) :
			CStage_Base(scene, gameData)
		{
			CPlayer* pPlayer = m_gameData->GetPlayer();	// プレイヤー取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

			// メンバ変数設定
			m_bPose = false;	// ポーズ状態設定
			m_fGool = s_fGool;	// ゴール距離設定

			m_fTutorialRange = s_fTutorialRange;	// チュートリアルイベント発生の範囲初期化

			m_bCanShownTutorial_000 = s_bCanShownTutorial_000;	// チュートリアルイベントフラグ
			m_bCanShownTutorial_001 = s_bCanShownTutorial_001;	// チュートリアルイベントフラグ
			m_bCanShownTutorial_002 = s_bCanShownTutorial_002;	// チュートリアルイベントフラグ
			m_bCanShownTutorial_003 = s_bCanShownTutorial_003;	// チュートリアルイベントフラグ

			m_bHasShownTutorial_000 = false;	// イベントを行ったかどうか
			m_bHasShownTutorial_001 = false;	// イベントを行ったかどうか
			m_bHasShownTutorial_002 = false;	// イベントを行ったかどうか
			m_bHasShownTutorial_003 = false;	// イベントを行ったかどうか

			for (int nCnt = 0; nCnt < static_cast<int>(TUTORIAL::MAX); nCnt++)
			{
				m_pTutorealPopup[nCnt] = CObject2D::creat(D3DXVECTOR3(s_TutorialPopupPos), D3DXVECTOR3(s_TutorialPopupSiz));// 生成
				m_pTutorealPopup[nCnt]->SetPoseDraw(false);
				m_pTutorealPopup[nCnt]->SetNormalDraw(false);
				switch (static_cast<TUTORIAL>(nCnt))
				{
				case TUTORIAL::Tutorial_000:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Tutorial_000.png");
					break;
				case TUTORIAL::Tutorial_001:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Tutorial_001.png");
					break;
				case TUTORIAL::Tutorial_002:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Tutorial_002.png");
					break;
				case TUTORIAL::Tutorial_003:
					m_pTutorealPopup[nCnt]->SetTexture("data/TEXTURE/Tutorial_003.png");
					break;
				default:
					Beep(1000, 300);
					break;
				}
			}

			// プレイヤー設定
			pPlayer->SetNormalUpdate(true);	// 通常時更新設定
			pPlayer->SetNormalDraw(true);	// 通常時描画設定
			pPlayer->SetPoseDraw(true);		// ポーズ時描画設定
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 位置を初期位置に戻す
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// モーション設定
			pPlayer->SetMotionMove(true);	// モーションの動きを設定
			pPlayer->SetMove(true);	// 動きを設定
			pPlayer->SetLife(1);	// 体力設定

			pPlActiv->SetInUP(false);		// 上入力設定
			pPlActiv->SetInDown(false);		// 下入力設定
			pPlActiv->SetInLeft(false);		// 左入力設定
			pPlActiv->SetInRight(false);	// 右入力設定

			//フィールド生成
			CObject3D* pField = nullptr;
			pField = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, s_fGool * 0.5f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 0.0f, 100.0f + 1000.0f));
			pField->SetBlock(100, static_cast<int>(s_fGool / 100.0f) + 1000);
			pField->SetTexture("data/TEXTURE/Load_000.png");

			// カメラ向き
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();
			pCamera->SetRotX(1.3f);


			// ステージ読み込み
			Load(s_aStage);
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_000::~CStage_000()
		{
			CPlayer* pPlayer = m_gameData->GetPlayer();	// プレイヤー取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

			pPlActiv->SetInUP(true);		// 上入力設定
			pPlActiv->SetInDown(true);		// 下入力設定
			pPlActiv->SetInLeft(true);		// 左入力設定
			pPlActiv->SetInRight(true);	// 右入力設定
		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CStage_000::Update()
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤーの位置を取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// ストラテジー取得
			;
			bool bGoal = (dynamic_cast<CStage_Base::Stage_Goal_Strategy*>(CStage_Base::m_pStrategy));

			if (m_bPose == false &&
				bGoal != true)
			{
				// チュートリアルイベント発動
				if (playerPos.z > s_fGool &&
					playerPos.z < s_fGool + 3.0f)
				{
					return makeScene<CScen_Game_StageSelect>(m_gameData);
				}
				else if (playerPos.z < s_fTutorial_000 &&
					playerPos.z > s_fTutorial_000 - m_fTutorialRange)
				{
					if (m_bCanShownTutorial_000 == false)
					{
						pPlayer->SetMove(false);	// 動きを止める
						pPlayer->SetMotionMove(false);	// モーションの動きを設定
						pPlActiv->SetInLeft(true);		// 左入力設定
						pPlActiv->SetInRight(true);	// 右入力設定

						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(true);		// ポップアップを表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(true);	// ポップアップを表示

						m_bCanShownTutorial_000 = true;		// フラグを立てる
					}
				}
				else if (playerPos.z < s_fTutorial_001 &&
					playerPos.z > s_fTutorial_001 - m_fTutorialRange)
				{
					if (m_bCanShownTutorial_001 == false)
					{
						pPlayer->SetMove(false);	// 動きを止める
						pPlayer->SetMotionMove(false);	// モーションの動きを設定
						pPlActiv->SetInUP(true);		// 上入力設定
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetPoseDraw(true);		// ポップアップを表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetNormalDraw(true);	// ポップアップを表示
						m_bCanShownTutorial_001 = true;		// フラグを立てる
					}
				}
				else if (playerPos.z < s_fTutorial_002 &&
					playerPos.z > s_fTutorial_002 - m_fTutorialRange)
				{
					if (m_bCanShownTutorial_002 == false)
					{
						pPlayer->SetMove(false);	// 動きを止める
						pPlayer->SetMotionMove(false);	// モーションの動きを設定
						pPlActiv->SetInDown(true);		// 下入力設定
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetPoseDraw(true);		// ポップアップを表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetNormalDraw(true);	// ポップアップを表示
						m_bCanShownTutorial_002 = true;
					}
				}
				else if (playerPos.z < s_fTutorial_003 &&
					playerPos.z > s_fTutorial_003 - m_fTutorialRange)
				{
					if (m_bCanShownTutorial_003 == false)
					{
						pPlayer->SetMove(false);	// 動きを止める
						pPlayer->SetMotionMove(false);	// モーションの動きを設定
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetPoseDraw(true);		// ポップアップを表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetNormalDraw(true);	// ポップアップを表示
						m_bCanShownTutorial_003 = true;
					}
				}

				// チュートリアルイベント
				if (m_bCanShownTutorial_000 &&
					m_bHasShownTutorial_000 == false)
				{
					// 左に入力したら
					if (pKey->GetTrigger(DIK_A) ||
						pKey->GetTrigger(DIK_LEFT))
					{
						m_bHasShownTutorial_000 = true;
						pPlayer->SetMove(true);			// 動かす
						pPlayer->SetMotionMove(true);	// モーションの動きを設定
						pPlActiv->InputLeft();	// 左入力
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(false);		// ポップアップを非表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(false);	// ポップアップを非表示
					}

					if (pKey->GetTrigger(DIK_D) ||
						pKey->GetTrigger(DIK_RIGHT))
					{
						m_bHasShownTutorial_000 = true;
						pPlayer->SetMove(true);			// 動かす
						pPlayer->SetMotionMove(true);	// モーションの動きを設定
						pPlActiv->InputRight();	// 右入力
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetPoseDraw(false);		// ポップアップを非表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_000)]->SetNormalDraw(false);	// ポップアップを非表示
					}
				}
				else if (m_bCanShownTutorial_001 &&
					m_bHasShownTutorial_001 == false)
				{
					// 左に入力したら
					if (pKey->GetTrigger(DIK_W) ||
						pKey->GetTrigger(DIK_UP))
					{
						m_bHasShownTutorial_001 = true;
						pPlayer->SetMove(true);			// 動かす
						pPlayer->SetMotionMove(true);	// モーションの動きを設定
						pPlActiv->InputUP();	// 上入力
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetPoseDraw(false);		// ポップアップを非表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_001)]->SetNormalDraw(false);	// ポップアップを非表示
					}
				}
				else if (m_bCanShownTutorial_002 &&
					m_bHasShownTutorial_002 == false)
				{
					// 右に入力したら
					if (pKey->GetTrigger(DIK_S) ||
						pKey->GetTrigger(DIK_DOWN))
					{
						m_bHasShownTutorial_002 = true;
						pPlayer->SetMove(true);			// 動かす
						pPlayer->SetMotionMove(true);	// モーションの動きを設定
						pPlActiv->InputDown();	// 下入力
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetPoseDraw(false);		// ポップアップを非表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_002)]->SetNormalDraw(false);	// ポップアップを非表示
					}
				}
				else if (m_bCanShownTutorial_003 &&
					m_bHasShownTutorial_003 == false)
				{
					// 何か入力したら
					if (pKey->GetTrigger())
					{
						m_bHasShownTutorial_003 = true;
						pPlayer->SetMove(true);			// 動かす
						pPlayer->SetMotionMove(true);	// モーションの動きを設定
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetPoseDraw(false);		// ポップアップを非表示
						m_pTutorealPopup[static_cast<int>(TUTORIAL::Tutorial_003)]->SetNormalDraw(false);	// ポップアップを非表示
					}
				}
			}

			return CStage_Base::Update();
		}
		void CStage_000::Draw() const
		{
			CStage_Base::Draw();
		}
		//============================================
		// デストラクタ
		//============================================
		bool CStage_000::GetPose()
		{
			return m_bPose;
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