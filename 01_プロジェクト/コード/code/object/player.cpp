//============================================
//
// プレイヤー[player.cpp]
// Author:Uedakou
// 
//============================================
#include "player.h"	// プレイヤー
#include "../base/manager.h"	// マネージャー
#include "enemy.h"	// エネミー
#include "../scene/scene_base.h"	// シーンベース
#include <strsafe.h>
#include "collision/obb.h"		// OBB

#define PlayerMove true

//const int CPlayer::s_nLife = 1;			// プレイヤーライフ
const float CPlayer::s_fSpeed = 20.0f;	// プレイヤー速度
const bool CPlayer::s_bMove = true;		// プレイヤーが自動で動くかどうか
const float CPlayer::s_fLane = 200.0f;	// ラインの幅
const X CPlayer::s_Collision = { { 0.0f, 0.0f, 0.0f }, { 0.0f ,0.0f, 0.0f },{ 10.0f, 10.0f, 70.0f } };	// コリジョン大きさ

//============================================
// コンスト
//============================================
CPlayer::CPlayer()
{
	SetLife(s_nLife);
	m_fSpeed = s_fSpeed;	// 初期速度設定
	m_bMove = s_bMove;
	m_fLane = s_fLane;

	m_bSliding = false;	// ジャンプ可能か
	m_bJanp = false;	// ジャンプ可能か
	SetAttcak(1);

	m_pActivityStrategy = new PlayerNomarActivity(this);

	m_pEffect = nullptr;
}
//============================================
// デストラ
//============================================
CPlayer::~CPlayer()
{
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		m_pEffect->DeathFlag();
		m_pEffect = nullptr;
	}
}
//============================================
// 初期化
//============================================
void CPlayer::Init()
{
	//m_obje[0] = CObjectX::creat(pos, rot, siz, CObjectX::TYPE_X_PLAYER);
	CObjectMotion::Load(PLAYER_MOTIONFILE_A);
	CCharacter::Init();
	CCharacter::SetCollisionX(s_Collision);
	CObjectMotion::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	//SetMotion(1);
	SetLife(s_nLife);
	
}
//============================================
// 終了
//============================================
void CPlayer::Uninit()
{
	CCharacter::Uninit();
}
//============================================
// 更新
//============================================
void CPlayer::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKey = pManager->GetInKey();


	// 重力
	AddMovePosY(-2.5f);
	D3DXVECTOR3 pos = GetPos();
	// 下限設定
	if (pos.y <= 0.0f)
	{
		SetPosY(0.0f);
		SetMovePosY(0.0f);
	}

	// 自動移動がtrueなら
	if (m_bMove == true)
	{
		// m_fSpeed進める

		AddPosZ(m_fSpeed);
	}

	// 左に入力したら
	if (pKey->GetTrigger(DIK_W) ||
		pKey->GetTrigger(DIK_UP))
	{
		m_pActivityStrategy->InputUP();
	}
	// 右に入力したら
	else if (pKey->GetTrigger(DIK_S) ||
		pKey->GetTrigger(DIK_DOWN))
	{
		m_pActivityStrategy->InputDown();
	}
	// 左に入力したら
	else if (pKey->GetTrigger(DIK_A) ||
		pKey->GetTrigger(DIK_LEFT))
	{
		m_pActivityStrategy->InputLeft();
	}
	// 右に入力したら
	else if (pKey->GetTrigger(DIK_D) ||
		pKey->GetTrigger(DIK_RIGHT))
	{
		m_pActivityStrategy->InputRight();
	}
	// 更新
	ActivityStrategy* p = m_pActivityStrategy->Update();
	// 返り値が変わっていたら
	if (p != m_pActivityStrategy)
	{
		// 入れ替える
		delete m_pActivityStrategy;
		m_pActivityStrategy = p;
	}

	CCharacter::Update();
}
//============================================
// 描画
//============================================
void CPlayer::Draw()
{
	CCharacter::Draw();
}
//============================================
// ヒット処理
//============================================
void CPlayer::Hit(int nDamage)
{
	CCharacter::Hit(nDamage);
	if (GetLife() <= 0)
	{
		
		
	}
}
void CPlayer::Hit(int nCntInvincible, int nDamage)
{
}
void CPlayer::Hit(D3DXVECTOR3 ShockRot, int nCntInvincible, int nDamage)
{
}
//============================================
// 生成
//============================================
CPlayer* CPlayer::creat()
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();

	return pPlayer;
}
//============================================
// 移動減衰
//============================================
void CPlayer::MoveAttenuation()
{
	CCharacter::MoveAttenuation();
}
//============================================
// ループしないモーションの次のモーション
//============================================
int CPlayer::GetNextMotion()
{
	D3DXVECTOR3 move = GetMovePos();
	if (GetLife() <= 0)
	{
		// 死亡モーション
		//return static_cast<int>(Motion::ACTIVITY_DETHILoop); ;
	}
	else
	{
		if (GetMotion() == static_cast<int>(Motion::ACTIVITY_JANP))
		{
			return static_cast<int>(Motion::ACTIVITY_MOVE);
		}
	}

	return static_cast<int>(Motion::ACTIVITY_NEUTRAL);
}
/// <summary>
/// 基底更新
/// </summary>
/// <returns>this以外でストラテジーチェンジ</returns>
CPlayer::ActivityStrategy* CPlayer::ActivityStrategy::Update()
{
	switch (m_type)
	{
		//走りチェンジ
	case CPlayer::ActivityStrategy::Type::Ran:
		return new PlayerNomarActivity(m_pPrimary);
		break;
		//レーンチェンジ
	case CPlayer::ActivityStrategy::Type::LaneChangeL:
		return new PlayerLaneChangeActivity(m_pPrimary, PlayerLaneChangeActivity::LR::L);
		break;
	case CPlayer::ActivityStrategy::Type::LaneChangeR:
		return new PlayerLaneChangeActivity(m_pPrimary, PlayerLaneChangeActivity::LR::R);
		break;
		//ジャンプ
	case CPlayer::ActivityStrategy::Type::Janp:
		return new PlayerJanpActivity(m_pPrimary);
		break;
		//スライディング
	case CPlayer::ActivityStrategy::Type::Sliding:
		return new PlayerSlidingActivity(m_pPrimary);
		break;
	default:
		// 何もなければ続く
		return this;
		break;
	}

}
/// <summary>
/// 通常時ストラテジーコンストラクタ
/// </summary>
/// <param name="player">親</param>
CPlayer::PlayerNomarActivity::PlayerNomarActivity(CPlayer* player):
	ActivityStrategy(player)
{
	// 走りモーションに設定
	m_pPrimary->SetMotion(static_cast<int>(Motion::ACTIVITY_MOVE));
}
/// <summary>
/// 通常時ストラテジーデストラクタ
/// </summary>
CPlayer::PlayerNomarActivity::~PlayerNomarActivity()
{
}
/// <summary>
/// 通常時ジャンプ入力処理
/// </summary>
void CPlayer::PlayerNomarActivity::InputUP()
{
	if (m_bInUP)
	{
		m_type = Type::Janp;
	}
}
/// <summary>
/// 通常時スライディング処理
/// </summary>
void CPlayer::PlayerNomarActivity::InputDown()
{
	if (m_bInDown)
	{
		m_type = Type::Sliding;
	}
}
/// <summary>
/// 通常時左入力処理
/// </summary>
void CPlayer::PlayerNomarActivity::InputLeft()
{
	if (m_bInLeft)
	{
		m_type = Type::LaneChangeL;
	}
}
/// <summary>
/// 通常時入力右処理
/// </summary>
void CPlayer::PlayerNomarActivity::InputRight()
{
	if (m_bInRight)
	{
		m_type = Type::LaneChangeR;
	}
}
/// <summary>
/// レーンチェンジ時コンストラクタ
/// </summary>
/// <param name="player">親</param>
CPlayer::PlayerLaneChangeActivity::PlayerLaneChangeActivity(CPlayer* player, LR lr) :
	ActivityStrategy(player)

{
	m_LR = lr;
	m_type = Type::Ran;
	if (lr == LR::L)
	{
		//m_pPrimary->AddPosX(-m_pPrimary->m_fLane);	// 左に移動
		float posX = m_pPrimary->GetPosX();	// プレイヤーの位置取得
		// プレイヤーがレーン外に出ていたら
		if (posX > -m_pPrimary->m_fLane)
		{
			m_nCnt = s_nCnt;
		}

	}
	else
	{
		//m_pPrimary->AddPosX(m_pPrimary->m_fLane);	// 右に移動
		float posX = m_pPrimary->GetPosX();	// プレイヤーの位置取得
		// プレイヤーがレーン外に出ていたら
		if (posX < m_pPrimary->m_fLane)
		{
			m_nCnt = -s_nCnt;
		}
	}
}
/// <summary>
/// レーンチェンジ時デストラクタ
/// </summary>
CPlayer::PlayerLaneChangeActivity::~PlayerLaneChangeActivity()
{
}
/// <summary>
/// レーンチェンジ時更新
/// </summary>
/// <returns></returns>
CPlayer::ActivityStrategy* CPlayer::PlayerLaneChangeActivity::Update()
{
	// ０に向かい１動く
	int nRot = (m_nCnt < 0) - (m_nCnt > 0);
	m_nCnt += nRot;
	m_pPrimary->AddPosX(s_fLane / s_nCnt * nRot);


	if (m_nCnt == 0)
	{
		//m_pPrimary->AddPosX(s_fLane);
		return ActivityStrategy::Update();
	}
	return this;
}
/// <summary>
/// レーンチェンジ時ジャンプ入力
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputUP()
{
}
/// <summary>
/// レーンチェンジ時スライティング入力
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputDown()
{
}
/// <summary>
/// レーンチェンジ時左入力
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputLeft()
{
}
/// <summary>
/// レーンチェンジ時右入力
/// </summary>
void CPlayer::PlayerLaneChangeActivity::InputRight()
{
}
/// <summary>
/// ジャンプ時コンストラクタ
/// </summary>
/// <param name="player">親</param>
CPlayer::PlayerJanpActivity::PlayerJanpActivity(CPlayer* player) :
	ActivityStrategy(player)
{
	m_pPrimary->SetMotion(static_cast<int>(Motion::ACTIVITY_JANP));	// モーション設定
	m_pPrimary->m_bJanp = true;	// ジャンプ中かどうか設定
	m_type = Type::Ran;			// 次を走りに
	m_pPrimary->AddMovePosY(20.0f);
}
/// <summary>
/// ジャンプ時デストラクタ
/// </summary>
CPlayer::PlayerJanpActivity::~PlayerJanpActivity()
{
	m_pPrimary->m_bJanp = false;	// ジャンプ中かどうか設定
}
/// <summary>
/// ジャンプ時更新
/// </summary>
/// <returns></returns>
CPlayer::ActivityStrategy* CPlayer::PlayerJanpActivity::Update()
{
	// 着地したら通常に変える
	if (m_pPrimary->GetPosY() <= 0.0f)
	{
		return ActivityStrategy::Update();
	}
	return this;
}
/// <summary>
/// ジャンプ時ジャンプ入力
/// </summary>
void CPlayer::PlayerJanpActivity::InputUP()
{
}
// ジャンプ時スライディング入力
void CPlayer::PlayerJanpActivity::InputDown()
{
}
/// <summary>
/// ジャンプ時左入力
/// </summary>
void CPlayer::PlayerJanpActivity::InputLeft()
{
}
/// <summary>
/// ジャンプ時右入力
/// </summary>
void CPlayer::PlayerJanpActivity::InputRight()
{
}
/// <summary>
/// スライディング時コンストラクタ
/// </summary>
/// <param name="player">親</param>
CPlayer::PlayerSlidingActivity::PlayerSlidingActivity(CPlayer* player) :
	ActivityStrategy(player)
{
	m_pPrimary->SetMotion(static_cast<int>(Motion::ACTIVITY_SLIDING));	// モーション設定
	m_pPrimary->m_bSliding = true;	// スライディング中かどうか設定
	m_type = Type::Ran;			// 次を走りに
	m_nCnt = 0;					// カウント初期化
}
/// <summary>
/// スライディング時デストラクタ
/// </summary>
CPlayer::PlayerSlidingActivity::~PlayerSlidingActivity()
{
	m_pPrimary->m_bSliding = false;	// スライディング中かどうか設定
}
/// <summary>
/// スライティング時アップデート
/// </summary>
/// <returns></returns>
CPlayer::ActivityStrategy* CPlayer::PlayerSlidingActivity::Update()
{
	m_nCnt++;
	if (m_nCnt >= s_nCnt)
	{
		return ActivityStrategy::Update();
	}
	return this;
}
/// <summary>
/// スライディング時ジャンプ入力
/// </summary>
void CPlayer::PlayerSlidingActivity::InputUP()
{
}
/// <summary>
/// スライディング時スライティング入力
/// </summary>
void CPlayer::PlayerSlidingActivity::InputDown()
{
}
/// <summary>
/// スライディング時左入力
/// </summary>
void CPlayer::PlayerSlidingActivity::InputLeft()
{
}
/// <summary>
/// スライディング時右入力
/// </summary>
void CPlayer::PlayerSlidingActivity::InputRight()
{
}