//===========================================
// 
// デバックシーン[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_debug.h"	// デバックシーン
#include "../../../base/manager.h"		// マネージャー
#include "../game_data.h"		// ゲームデータ
#include "../../../object/base/object_3D.h"	// ３Dオブジェクト
#include "../../../object/base/text.h"	// ３Dオブジェクト
#include "../../../object/obstacles_tall.h"	// 障害物
#include "../../../object/obstacles_high.h"	// 障害物
#include "../../../object/obstacles_low.h"	// 障害物

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const bool CSceneDebug::s_bCameraFollowPlayer = true;
		const float CSceneDebug::s_fCameraRot = 2.6f;
		const float CSceneDebug::s_fGool = 2000.0f;
		//============================================
		// コンストラクタ
		//============================================
		CSceneDebug::CSceneDebug(CBase* scene, CGameData* gameData) :
			CStage_Base(scene, gameData)
		{
			CObject::ReleaseScene();	// シーンリリース

			CPlayer* pPlayer = m_gameData->GetPlayer();
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

			
			m_bPose = false;	// ポーズ状態設定
			m_fGool = s_fGool;

			// プレイヤー設定
			pPlayer->SetNormalUpdate(true);	// 通常時更新設定
			pPlayer->SetNormalDraw(true);	// 通常時描画設定
			pPlayer->SetPoseDraw(true);		// ポーズ時描画設定
			pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// 位置を初期位置に戻す
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_MOVE));	// モーション設定
			pPlayer->SetMotionMove(true);	// モーションの動きを設定
			pPlayer->SetMove(true);	// 動きを設定
			pPlayer->SetLife(1);	// 体力設定

			// カメラ向き
			CManager* pManager = CManager::GetInstance();
			CCamera* pCamera = pManager->GetCamera();
			pCamera->SetRotX(1.3f);

			m_fCameraRot = s_fCameraRot;	// カメラがプレイヤーを追従するかどうか

			m_bCameraFollowPlayer = s_bCameraFollowPlayer;// カメラがプレイヤーを追従するかどうか

			//フィールド生成
			CObject3D* pField = nullptr;
			pField = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, s_fGool * 0.5f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(100.0f, 0.0f, 100.0f + 1000.0f));
			pField->SetBlock(100, static_cast<int>(s_fGool / 100.0f) + 1000);
			pField->SetTexture("data/TEXTURE/Provisional/Glass000.png");

			// 障害物
			CObstaclesToll::clate(D3DXVECTOR3(0.0f, 0.0f, 1000.0f));

			//CObstaclesHigh::clate(D3DXVECTOR3(0.0f, 0.0f, 2000.0f));

			//CObstaclesLow::clate(D3DXVECTOR3(0.0f, 0.0f, 3000.0f));



		}
		//============================================
		// デストラクタ
		//============================================
		CSceneDebug::~CSceneDebug()
		{
			int a = 0;
		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CSceneDebug::Update()
		{
			//CManager* pManager = CManager::GetInstance();	// マネージャー取得
			//CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			//CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			//CPlayer* pPlayer = m_gameData->GetPlayer();

			return CStage_Base::Update();;
			
			return this;
		}
		//============================================
		// 描画
		//============================================
		void CSceneDebug::Draw() const
		{
			return CStage_Base::Draw();;
		}

		//============================================
		// ポーズ中取得
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