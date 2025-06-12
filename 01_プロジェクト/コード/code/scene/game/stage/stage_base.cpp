//===========================================
// 
// ステージ000[stage_001.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_base.h"		// ステージ
#include "stage_000.h"		// ステージ000
#include "stage_001.h"		// ステージ001
#include "scene_debug.h"	// ステージデバッグ

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
#include "../../../object/scroll.h"	// スクロール

#include <fstream>	// ファイルの読み込みに必要
#include <iostream>	// ファイルの読み込みに必要

namespace Scene {
	namespace Game {
		class CScen_Game_StageSelect;

		const float CStage_Base::s_fCameraRot = 2.6f;	// 初期プレイヤーからのカメラの角度
		const D3DXVECTOR3 CStage_Base::NumScrollPos = { 100.0f, 100.0f, 0.0f };	// 初期プレイヤーからのカメラの角度
		const D3DXVECTOR3 CStage_Base::NumScrollSiz = { 100.0f, 100.0f, 0.0f };	// 初期プレイヤーからのカメラの角度
		//============================================
		// コンスト
		//============================================
		CStage_Base::CStage_Base(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData),
			m_nNumScroll(0), m_nNumScrollOld(0), m_bPose(false) , m_bCameraFollowPlayer(true) , m_fGool(0)
		{
			m_fCameraRot = s_fCameraRot;
			m_pStrategy = new Stage_Play_Strategy(this);
			// 巻物取得数表示

			for (int nCnt = 0; nCnt < static_cast<int>(CGameData::Stage::MAX); nCnt++)
			{
				// 巻物の大きさずつずらして並べる
				m_pNumScroll[nCnt] = CObject2D::creat(10, D3DXVECTOR3(NumScrollPos.x + NumScrollSiz.y * nCnt, NumScrollPos.y, NumScrollPos.z), NumScrollSiz);
				m_pNumScroll[nCnt]->SetTexture("data/TEXTURE/Scroll_000.png");
				m_pNumScroll[nCnt]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
			}
		}
		//============================================
		// デストラクタ
		//============================================
		CStage_Base::~CStage_Base()
		{
		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CStage_Base::Update()
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			CPlayer* pPlayer = m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤーの位置を取得

			nsPrev::CBase* result = this;
			// ストラテジーが有ったら更新する
			if (m_pStrategy != nullptr)
			{
				auto p = m_pStrategy->update(result);
				if (p != m_pStrategy)
				{
					delete m_pStrategy;
					m_pStrategy = p;
				}
			}
			if (m_nNumScroll != m_nNumScrollOld)
			{
				m_nNumScrollOld = m_nNumScroll;
				m_pNumScroll[m_nNumScrollOld]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			return result;
		}
		void CStage_Base::Draw() const
		{
		}
		//============================================
		// デストラクタ
		//============================================
		bool CStage_Base::GetPose()
		{
			return m_bPose;
		}
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pPrimary">親</param>
		CStage_Base::Stage_Play_Strategy::Stage_Play_Strategy(CStage_Base* pPrimary) :
			Stage_Strategy(pPrimary)
		{
		}
		/// <summary>
		/// 通常更新ストラテジ
		/// </summary>
		/// <returns></returns>
		CStage_Base::Stage_Strategy* CStage_Base::Stage_Play_Strategy::update(nsPrev::CBase*& owner)
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得
			CCamera* pCamera = pManager->GetCamera();		// カメラ取得
			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();
			D3DXVECTOR3 playerPos = pPlayer->GetPos();	// プレイヤーの位置を取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// ストラテジー取得
			// ポーズ入力
			if (pKey->GetTrigger(DIK_P))
			{
				m_pPrimary->m_bPose = !(m_pPrimary->m_bPose);
				// ポーズしたら
				if (m_pPrimary->m_bPose)
				{
					// プレイヤーの動きを止める
					pPlayer->SetMove(false);
				}
				// ポーズを解除したら
				else
				{
					// プレイヤーを動かす
					pPlayer->SetMove(true);
				}
			}
			if (m_pPrimary->m_bPose == false)
			{
				// ゴール判定
				if (playerPos.z > m_pPrimary->m_fGool)
				{
					return new Stage_Goal_Strategy(m_pPrimary);
				}

				// カメラをプレイヤーに追従させるなら
				if (m_pPrimary->m_bCameraFollowPlayer == true)
				{
					// プレイヤーが有るなら
					if (pPlayer != nullptr)
					{
						// カメラをプレイヤーに追従させる
						pCamera->SetPosV(D3DXVECTOR3(playerPos.x, playerPos.y + sinf(m_pPrimary->m_fCameraRot) * 300.0f, playerPos.z + cosf(m_pPrimary->m_fCameraRot) * 300.0f));	// カメラに適応
					}
				}
			}
			// 巻物とプレイヤーの当たり判定
			CObject* pObject[MAX_PRIORITY];
			CObject* pNext = nullptr;
			CObject::GetAllObject(pObject);
			for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
			{
				while (pObject[nCnt] != nullptr)
				{
					pNext = pObject[nCnt]->GetNext();
					if (CScroll* pScroll = dynamic_cast<CScroll*>(pObject[nCnt]))
					{
						D3DXVECTOR3 PLpos = pPlayer->GetPos();	// プレイヤー位置
						D3DXVECTOR3 PLcol = pPlayer->GetCollisionSiz();	// プレイヤーコリジョン
						D3DXVECTOR3 pos = pScroll->GetPos();	// 巻物位置
						D3DXVECTOR3 coll = pScroll->GetCollisionSiz();
						if (PLpos.z + PLcol.z * 0.5f > pos.z - coll.z * 0.5f &&
							PLpos.z - PLcol.z * 0.5f < pos.z + coll.z * 0.5f &&
							PLpos.x + PLcol.x * 0.5f > pos.x - coll.x * 0.5f &&
							PLpos.x - PLcol.x * 0.5f < pos.x + coll.x * 0.5f)
						{
							m_pPrimary->m_nNumScroll++;
							pScroll->Release();
						}
					}
					pObject[nCnt] = pNext;
				}
			}
			// プレイヤーの体力が０以下なら
			if (pPlayer->GetLife() <= 0)
			{
				return new Stage_Death_Strategy(m_pPrimary);
			}
#ifdef _DEBUG
			// デバッグ時ステージ移行
			if (pKey->GetTrigger(DIK_L))
			{
				return new Stage_Goal_Strategy(m_pPrimary);
			}
#endif // !_DEBUG

			return this;
		}

		// ゴール時ストラテジー定数
		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_SelectPos{ SCREEN_W * 0.5f, SCREEN_H * 0.5f + 100.0f, 0.0f};
		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_SelectSiz {100.0f, 100.0f, 0.0f};
		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_PopupPos{ SCREEN_W * 0.5f, 200.0f, 0.0f};
		const D3DXVECTOR3 CStage_Base::Stage_Goal_Strategy::s_PopupSiz {100.0f, 100.0f, 0.0f};
		/// <summary>
		/// ゴール時コンスト
		/// </summary>
		/// <param name="pPrimary">親</param>
		CStage_Base::Stage_Goal_Strategy::Stage_Goal_Strategy(CStage_Base* pPrimary) :
			Stage_Strategy(pPrimary)
		{
			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();	// プレイヤー取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

			pPlActiv->SetInUP(false);		// 上入力設定
			pPlActiv->SetInDown(false);		// 下入力設定
			pPlActiv->SetInLeft(false);		// 左入力設定
			pPlActiv->SetInRight(false);	// 右入力設定

			// スクロール数を保存
			int nStage = 0;// ステージ
			if (dynamic_cast<CStage_000*>(this))nStage = 0;
			else if (dynamic_cast<CStage_001*>(this))nStage = 1;
			//else if(dynamic_cast<CStage_002*>(this))nStage = 1;



			// スクロール数が前より多ければ足す
			if (m_pPrimary->m_gameData->m_nScore[nStage] < m_pPrimary->m_nNumScroll)
			{
				m_pPrimary->m_gameData->m_nScore[nStage] = m_pPrimary->m_nNumScroll;
			}
			// 選択初期化
			m_nSelect = 0;
			m_nSelectOld = 0;

			// 選択肢生成
			for (int nCnt = 0; nCnt < static_cast<int>(SelectGoal::MAX); nCnt++)
			{
				m_pSelect[nCnt] = CObject2D::creat(6, D3DXVECTOR3(s_SelectPos.x, s_SelectPos.y + s_SelectSiz.x * nCnt, s_SelectPos.z), s_SelectSiz);
				switch (static_cast<SelectGoal>(nCnt))
				{
				case SelectGoal::StageSelect:	// ステージセレクトに戻る
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Select_StageSelect_000.png");
					break;
				case SelectGoal::ReTry:	// リトライ
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Retry_000.png");
					break;
				default:
					break;
				}
			}
			// 選択物カーソル
			m_pSelectBG = CObject2D::creat(5, m_pSelect[0]->GetPos(), m_pSelect[0]->GetSiz());

			// ポップアップ
			m_GoalPopup = CObject2D::creat(6, s_PopupPos, s_PopupSiz);// ポップアップ生成
			m_GoalPopup->SetTexture("data/TEXTURE/StageClear_000.png");

			// 背景
			m_BG = CObject2D::creat(4, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0.0f));// ポップアップ生成
			m_BG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		}

		/// <summary>
		/// ゴール時デストラクタ
		/// </summary>
		CStage_Base::Stage_Goal_Strategy::~Stage_Goal_Strategy()
		{
			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();	// プレイヤー取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

			pPlActiv->SetInUP(true);		// 上入力設定
			pPlActiv->SetInDown(true);		// 下入力設定
			pPlActiv->SetInLeft(true);		// 左入力設定
			pPlActiv->SetInRight(true);	// 右入力設定
			// セレクト解放
			for (int nCnt = 0; nCnt < static_cast<int>(SelectGoal::MAX); nCnt++)
			{
				if (m_pSelect[nCnt] != nullptr)
				{
					m_pSelect[nCnt]->Release();
					m_pSelect[nCnt] = nullptr;
				}
			}
			// ポップアップ解放
			if (m_GoalPopup != nullptr)
			{
				m_GoalPopup->Release();
				m_GoalPopup = nullptr;
			}
		}
		/// <summary>
		/// クリア更新
		/// </summary>
		/// <param name="owner">次シーン</param>
		/// <returns>this以外次のストラテジー</returns>
		CStage_Base::Stage_Strategy* CStage_Base::Stage_Goal_Strategy::update(nsPrev::CBase*& owner)
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得

			m_nSelectOld = m_nSelect;	//旧位置保存

			// 上選択
			if (pKey->GetTrigger(DIK_W) ||
				pKey->GetTrigger(DIK_UP))
			{
				m_nSelect--;
				if (m_nSelect < 0)
				{
					m_nSelect = static_cast<int>(SelectGoal::MAX) - 1;
				}
			}
			// 下選択
			else if (pKey->GetTrigger(DIK_S) ||
				pKey->GetTrigger(DIK_DOWN))
			{
				m_nSelect++;
				if (m_nSelect >= static_cast<int>(SelectGoal::MAX))
				{
					m_nSelect = 0;
				}
			}
			// 選択が変更していたら
			if (m_nSelect != m_nSelectOld)
			{
				// 位置を変える
				m_pSelectBG->SetPos(m_pSelect[m_nSelect]->GetPos());
			}

			if (pKey->GetTrigger(DIK_RETURN) ||
				pKey->GetTrigger(DIK_SPACE))
			{
				switch (static_cast<SelectGoal>(m_nSelect))
				{
				case SelectGoal::ReTry:	// リトライ
					m_pPrimary;
					if (dynamic_cast<CStage_000*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CStage_000>(m_pPrimary->m_gameData);
					}
					else if (dynamic_cast<CStage_001*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CStage_001>(m_pPrimary->m_gameData);
					}
					else if (dynamic_cast<CSceneDebug*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CSceneDebug>(m_pPrimary->m_gameData);
					}
					break;
				case SelectGoal::StageSelect:	// ステージセレクト
					owner = m_pPrimary->makeScene<CScen_Game_StageSelect>(m_pPrimary->m_gameData);
					break;
				default:
					break;
				}
			}
			return this;
		}

		// 死亡時ストラテジー定数
		const int CStage_Base::Stage_Death_Strategy::s_nPLMotionCnt = 30;
		const D3DXVECTOR3 CStage_Base::Stage_Death_Strategy::s_SelectPos{ SCREEN_W * 0.5f, SCREEN_H * 0.5f + 100.0f, 0.0f };
		const D3DXVECTOR3 CStage_Base::Stage_Death_Strategy::s_SelectSiz{ 100.0f, 100.0f, 0.0f };
		const D3DXVECTOR3 CStage_Base::Stage_Death_Strategy::s_PopupPos{ SCREEN_W * 0.5f, 200.0f, 0.0f };
		const D3DXVECTOR3 CStage_Base::Stage_Death_Strategy::s_PopupSiz{ 100.0f, 100.0f, 0.0f };
		/// <summary>
		/// 死亡ストラテジーコンスト
		/// </summary>
		/// <param name="pPrimary">親</param>
		CStage_Base::Stage_Death_Strategy::Stage_Death_Strategy(CStage_Base* pPrimary) :
			Stage_Strategy(pPrimary)
		{

			CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();	// プレイヤー取得
			CPlayer::ActivityStrategy* pPlActiv = pPlayer->GetActivity();	// 行動ストラテジー取得

						// プレイヤー設定
			pPlayer->SetMotion(static_cast<int>(CPlayer::Motion::ACTIVITY_DEATH));	// モーション設定
			pPlayer->SetMove(false);	// 動きを設定

			pPlActiv->SetInUP(false);		// 上入力設定
			pPlActiv->SetInDown(false);		// 下入力設定
			pPlActiv->SetInLeft(false);		// 左入力設定
			pPlActiv->SetInRight(false);	// 右入力設定

			// スクロール数を保存
			int nStage = 0;// ステージ
			if (dynamic_cast<CStage_000*>(this))nStage = 0;
			else if (dynamic_cast<CStage_001*>(this))nStage = 1;
			//else if(dynamic_cast<CStage_002*>(this))nStage = 1;



			// スクロール数が前より多ければ足す
			if (m_pPrimary->m_gameData->m_nScore[nStage] < m_pPrimary->m_nNumScroll)
			{
				m_pPrimary->m_gameData->m_nScore[nStage] = m_pPrimary->m_nNumScroll;
			}
			// 選択初期化
			m_nSelect = 0;
			m_nSelectOld = 0;

			// 選択肢生成
			for (int nCnt = 0; nCnt < static_cast<int>(SelectGoal::MAX); nCnt++)
			{
				m_pSelect[nCnt] = CObject2D::creat(6, D3DXVECTOR3(s_SelectPos.x, s_SelectPos.y + s_SelectSiz.x * nCnt, s_SelectPos.z), s_SelectSiz);
				switch (static_cast<SelectGoal>(nCnt))
				{
				case SelectGoal::StageSelect:	// ステージセレクトに戻る
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Select_StageSelect_000.png");
					break;
				case SelectGoal::ReTry:	// リトライ
					m_pSelect[nCnt]->SetTexture("data/TEXTURE/Retry_000.png");
					break;
				default:
					break;
				}
			}
			// 選択物カーソル
			m_pSelectBG = CObject2D::creat(5, m_pSelect[0]->GetPos(), m_pSelect[0]->GetSiz());

			// ポップアップ
			m_GoalPopup = CObject2D::creat(6, s_PopupPos, s_PopupSiz);// ポップアップ生成
			m_GoalPopup->SetTexture("data/TEXTURE/StageClear_000.png");

			// 背景
			m_BG = CObject2D::creat(4, D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0.0f));// ポップアップ生成
			m_BG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		}
		/// <summary>
		/// 死亡ストラテジ
		/// </summary>
		CStage_Base::Stage_Death_Strategy::~Stage_Death_Strategy()
		{
		}
		/// <summary>
		/// ストラテジー更新
		/// </summary>
		/// <param name="owner"></param>
		/// <returns></returns>
		CStage_Base::Stage_Strategy* CStage_Base::Stage_Death_Strategy::update(nsPrev::CBase*& owner)
		{
			CManager* pManager = CManager::GetInstance();	// マネージャー取得
			CInputKeyboard* pKey = pManager->GetInKey();	// キーボード情報取得

			m_nSelectOld = m_nSelect;	//旧位置保存

			// 上選択
			if (pKey->GetTrigger(DIK_W) ||
				pKey->GetTrigger(DIK_UP))
			{
				m_nSelect--;
				if (m_nSelect < 0)
				{
					m_nSelect = static_cast<int>(SelectGoal::MAX) - 1;
				}
			}
			// 下選択
			else if (pKey->GetTrigger(DIK_S) ||
				pKey->GetTrigger(DIK_DOWN))
			{
				m_nSelect++;
				if (m_nSelect >= static_cast<int>(SelectGoal::MAX))
				{
					m_nSelect = 0;
				}
			}
			// 選択が変更していたら
			if (m_nSelect != m_nSelectOld)
			{
				// 位置を変える
				m_pSelectBG->SetPos(m_pSelect[m_nSelect]->GetPos());
			}

			if (pKey->GetTrigger(DIK_RETURN) ||
				pKey->GetTrigger(DIK_SPACE))
			{
				switch (static_cast<SelectGoal>(m_nSelect))
				{
				case SelectGoal::ReTry:	// リトライ
					m_pPrimary;
					if (dynamic_cast<CStage_000*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CStage_000>(m_pPrimary->m_gameData);
					}
					else if (dynamic_cast<CStage_001*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CStage_001>(m_pPrimary->m_gameData);
					}
					else if (dynamic_cast<CSceneDebug*>(m_pPrimary))
					{
						owner = m_pPrimary->makeScene<CSceneDebug>(m_pPrimary->m_gameData);
					}
					break;
				case SelectGoal::StageSelect:	// ステージセレクト
					owner = m_pPrimary->makeScene<CScen_Game_StageSelect>(m_pPrimary->m_gameData);
					break;
				default:
					break;
				}
			}

			if (m_nPLMotionCnt <= s_nPLMotionCnt)
			{
				m_nPLMotionCnt++;
				if (m_nPLMotionCnt == s_nPLMotionCnt)
				{
					CPlayer* pPlayer = m_pPrimary->m_gameData->GetPlayer();	// プレイヤー取得
					pPlayer->SetMotionMove(false);
				}
			}
			return this;
		}
		/// <summary>
		/// ステージ読み込み
		/// </summary>
		void CStage_Base::Load(const string& filePath)
		{
			ifstream file(filePath.c_str());  // 読み込むファイルのパスを指定
			if (file.fail()) {
				MessageBoxA(nullptr, "開けませんでした", "エラー", MB_OK);
			}
			string str0, str1, str2, str3;	// 文字列格納用
			string _;	// スキップ用格納
			string aModelFile[MAX_MOTION_MODEL];	// モデルファイル

		// 抽出演算子>>を使ってデリミタで区切られた単語，値を読み込む
			while (file >> str0)
			{
				// コメントアウト
				if (str0[0] == '#')
				{
					getline(file, _);	// 一行スキップ
				}
				// 障害物TALL
				else if (str0.compare("OBSTACLES") == 0)
				{
					int nType = 0;	// 種類
					D3DXVECTOR3 pos = {};	// 位置
					D3DXVECTOR3 rot = {};	// 向き

					while (file >> str1 &&
						str1.compare("END_OBSTACLES") != 0)
					{
						// コメントアウト
						if (str1[0] == '#')
						{
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("TYPE") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル数を取得
							nType = atoi(str2.c_str());
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("POS") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル数を取得
							pos.x = stof(str2.c_str());
							file >> str2;	// モデル数を取得
							pos.y = stof(str2.c_str());
							file >> str2;	// モデル数を取得
							pos.z = stof(str2.c_str());
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("ROT") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル名を取得
							rot.x = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// モデル名を取得
							rot.y = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// モデル名を取得
							rot.z = AngleToRadian(stof(str2.c_str()));
							getline(file, _);	// 一行スキップ
						}
					}
					// 障害物生成
					switch (nType)
					{
					case 0:
						CObstaclesToll::clate(pos, rot);
						break;
					case 1:
						CObstaclesHigh::clate(pos, rot);
						break;
					case 2:
						CObstaclesLow::clate(pos, rot);
						break;
					case 3:
						CScroll::clate(pos, rot);
						break;
					default:
#ifdef _DEBUG
						OutputDebugStringA("デバッグ出力：存在しない障害物を生成しようとしました。\n");
						Beep(1200, 300);
#endif // _DEBUG
						break;
					}

				}
				else if (str0.compare("OBJECT") == 0)
				{
					int nType = 0;	// 種類
					D3DXVECTOR3 pos = {};	// 位置
					D3DXVECTOR3 rot = {};	// 向き
					CObjectX* pObject = nullptr;	// オブジェクト

					while (file >> str1 &&
						str1.compare("END_OBJECT") != 0)
					{
						// コメントアウト
						if (str1[0] == '#')
						{
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("TYPE") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル数を取得
							nType = atoi(str2.c_str());
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("POS") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル数を取得
							pos.x = stof(str2.c_str());
							file >> str2;	// モデル数を取得
							pos.y = stof(str2.c_str());
							file >> str2;	// モデル数を取得
							pos.z = stof(str2.c_str());
							getline(file, _);	// 一行スキップ
						}
						if (str1.compare("ROT") == 0)
						{
							file >> _;	// 一文スキップ
							file >> str2;	// モデル名を取得
							rot.x = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// モデル名を取得
							rot.y = AngleToRadian(stof(str2.c_str()));
							file >> str2;	// モデル名を取得
							rot.z = AngleToRadian(stof(str2.c_str()));
							getline(file, _);	// 一行スキップ
						}
					}	/* !while (file >> str1 &&
					str1.compare("END_OBSTACLES") != 0)*/
					// 種類別生成
					if (nType == 0)
					{
						pObject = CObjectX::creat("data/MODEL/Building/Building_000.x");
					}
					else if (nType == 1)
					{
						pObject = CObjectX::creat("data/MODEL/Building/Building_001.x");
					}
					else
					{
						OutputDebugStringA("デバッグ出力：存在しないオブジェクトを生成しようとしました。\n");
						Beep(1200, 300);
					}
					if (pObject != nullptr)
					{
						pObject->SetPos(pos);
						pObject->SetRot(rot);
					}

				}
			}
			// ファイルを閉じる
			file.close();
		}

	}
}