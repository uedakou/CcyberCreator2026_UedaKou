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
#include "../collision/obb.h"	

#define PlayerMove true

//============================================
// コンスト
//============================================
CPlayer::CPlayer()
{
	m_fSpeed = PLAYER_SPEED;	// 初期速度設定
	m_fBrake = PLAYER_BRAKE;	// 初期ブレーキ設定
	m_fBoost = PLAYER_BOOST;	// 初期ブースト設定

	//m_bJump = false;	// ジャンプ可能か
	m_pLife = nullptr;
	SetAttcak(1);

	SetType(CObject::TYPE::PLAYER);
	m_pActivity = new PlayerActivityUsually(this);
	m_pEffect = nullptr;
}
//============================================
// デストラ
//============================================
CPlayer::~CPlayer()
{
	if (m_pLife != nullptr)
	{
		m_pLife = nullptr;
	}
	if (m_pEffect != nullptr)
	{
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
	CCharacter::SetCollisionX(PLAYER_SIZE);
	CObject::SetType(CObject::TYPE::PLAYER);
	CObjectMotion::SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	//SetMotion(1);
	SetLife(PLAYER_LIFE);
	m_pLife = CLife_2D::creat(D3DXVECTOR3(50.0f, 50.0f, 0.0f), PLAYER_LIFE);
	m_pLife->SetReleaseScene(false);
	m_pEffect = CEffectGeneratorPaeticle::creat(
		D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		10.0f,
		5.0f,
		D3DCOLOR_RGBA(255, 10, 0, 255),
		3,
		1
	);
	m_pEffect->SetReleaseScene(false);

}
//============================================
// 終了
//============================================
void CPlayer::Uninit()
{
	CCharacter::Uninit();
	// ライフ解放
	if (m_pLife != nullptr)
	{
		m_pLife->Release();
		m_pLife = nullptr;
	}

	// エフェクト解放
	if (m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
}
//============================================
// 更新
//============================================
void CPlayer::Update()
{
	//Controller();
	ActivityUpdate();	// 行動処理
	if (GetLife() > 0)
	{
		D3DXVECTOR3 rot = GetRot();
#if PlayerMove
		// 常時移動
		AddMovePos(D3DXVECTOR3(0.0f, 0.0f, PLAYER_SPEED));
#endif // PlayerMove

		// 移動減衰
		SetRotY((D3DX_PI - rot.y) * PLAYER_ROT_RESISTANCE + D3DX_PI);

		// 旧位置を記録
		D3DXVECTOR3 posOld = GetPos();
	}
	X coll = GetCollisionX();
	// 重力
	AddMovePosY(-2.5f);
	// 最下段で止める
	if (GetPosY() <= 0.0f)
	{
		//m_bJump = false;
		SetMovePosY(0.0f);
		SetPosY(0.0f);
	}
	D3DXVECTOR3 pos = GetPos();
	if (pos.x < -500.0f + coll.scl.x * 0.5f)
	{
		SetMovePosX(0.0f);
		SetPosX(-500.0f + coll.scl.x * 0.5f);
	}
	else if (pos.x > 500.0f - coll.scl.x * 0.5f)
	{
		SetMovePosX(0.0f);
		SetPosX(500.0f - coll.scl.x * 0.5f);
	}
	int life = GetLife();
	if (m_pLife != nullptr)
	{
		m_pLife->SetLife(life);
	}

	if (m_pEffect != nullptr)
	{
		m_pEffect->SetPos(pos);
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
		if (m_pActivity != nullptr)
		{
			delete m_pActivity;
			m_pActivity = nullptr;
		}
		m_pActivity = new PlayerActivityDeath(this);
	}
}
void CPlayer::Hit(int nCntInvincible, int nDamage)
{
	CCharacter::Hit(nCntInvincible, nDamage);
	if (GetLife() <= 0)
	{
		if (m_pActivity != nullptr)
		{
			delete m_pActivity;
			m_pActivity = nullptr;
		}
		m_pActivity = new PlayerActivityDeath(this);
	}
}
void CPlayer::Hit(D3DXVECTOR3 ShockRot, int nCntInvincible, int nDamage)
{
	CCharacter::Hit(ShockRot, nCntInvincible, nDamage);
	if (GetLife() <= 0)
	{
		if (m_pActivity != nullptr)
		{
			delete m_pActivity;
			m_pActivity = nullptr;
		}
		m_pActivity = new PlayerActivityDeath(this);
	}
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
// コントロール
//============================================
void CPlayer::Controller()
{
	CManager* instance = CManager::GetInstance();
	CInputKeyboard* pKey = instance->GetInKey();
	CInputMouse* pMous = instance->GetMouse();
	CInputJoypad* pJoy = instance->GetJoyKey();
	CSound* pSound = instance->GetSound();
	// 移動
	if (pKey->GetRepeat(DIK_W) /*||
		pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
	{// 前移動
		if (pKey->GetRepeat(DIK_D) /*||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
		{// 右移動
			AddMoveRot(D3DXVECTOR3(0.0f, PLAYER_ROLL, 0.0f));
			AddMovePos(D3DXVECTOR3(-cosf(D3DX_PI * 0.75f) * PLAYER_BEND, 0.0f, sinf(D3DX_PI * 0.75f) * PLAYER_MOVE));

			SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
		else if (pKey->GetRepeat(DIK_A)/* ||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
		{// 左移動
			AddMoveRot(D3DXVECTOR3(0.0f, -PLAYER_ROLL, 0.0f));
			AddMovePos(D3DXVECTOR3(cosf(D3DX_PI * 0.75f) * PLAYER_BEND, 0.0f, sinf(D3DX_PI * 0.75f) * PLAYER_MOVE));
			SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
		else
		{
			AddMovePos(D3DXVECTOR3(0.0f, 0.0f, PLAYER_MOVE));
			SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
	}
	else if (pKey->GetRepeat(DIK_S)/* ||
		pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
	{// 後ろ移動
		if (pKey->GetRepeat(DIK_D) /*||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
		{// 右移動
			AddMoveRot(D3DXVECTOR3(0.0f, PLAYER_ROLL, 0.0f));
			AddMovePos(D3DXVECTOR3(-cosf(D3DX_PI * 0.75f) * PLAYER_BEND, 0.0f, -sinf(D3DX_PI * 0.75f) * PLAYER_BRAKE));
			SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
		else if (pKey->GetRepeat(DIK_A)/* ||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
		{// 左移動
			AddMoveRot(D3DXVECTOR3(0.0f, -PLAYER_ROLL, 0.0f));
			AddMovePos(D3DXVECTOR3(cosf(D3DX_PI * 0.75f) * PLAYER_BEND, 0.0f, -sinf(D3DX_PI * 0.75f) * PLAYER_BRAKE));
			SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
		else
		{
			AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -PLAYER_BRAKE));
			SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
	}
	else if (pKey->GetRepeat(DIK_D) /*||
	pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
	{// 右移動
		AddMoveRot(D3DXVECTOR3(0.0f, PLAYER_ROLL, 0.0f));
		AddMovePos(D3DXVECTOR3(PLAYER_BEND, 0.0f, 0.0f));
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}
	else if (pKey->GetRepeat(DIK_A)/* ||
		pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
	{// 左移動
		AddMoveRot(D3DXVECTOR3(0.0f, -PLAYER_ROLL, 0.0f));
		AddMovePos(D3DXVECTOR3(-PLAYER_BEND, 0.0f, 0.0f));
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}
#if _DEBUG
	CCamera* pCamera = instance->GetCamera();

	if (pKey->GetRepeat(DIK_Q))
	{
		pCamera->AddCameraRot(CCamera::CENTER::R, D3DXVECTOR3(0.0f, -0.05f, 0.0f));
	}
	else if (pKey->GetRepeat(DIK_E))
	{
		pCamera->AddCameraRot(CCamera::CENTER::R, D3DXVECTOR3(0.0f, 0.05f, 0.0f));
	}

	if (pKey->GetTrigger(DIK_K))
	{
		AddLife(-1);
	}
	else if (pKey->GetTrigger(DIK_I))
	{
		AddLife(1);
	}

	if (pKey->GetTrigger(DIK_M))
	{
		SetMotion(0);
	}
	else if (pKey->GetTrigger(DIK_N))
	{
		SetMotion(1);

	}

#endif // _DEBUG
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
		return ACTIVITY_DETHILoop;
	}
	else
	{
		if (move.x > 0.5f)
		{
			return ACTIVITY_MOVE;
		}
	}

	return ACTIVITY_NEUTRAL;
}
//============================================
// 行動通常
//============================================
CPlayer::PlayerActivityUsually::PlayerActivityUsually(CPlayer* player) :
	PlayerActivity(player)
{
}
CPlayer::PlayerActivity* CPlayer::PlayerActivityUsually::update()
{
	CManager* pInstance = CManager::GetInstance();
	if (pInstance->GetCamera()->GetCameraControllreFpllow() == false)
	{// プレイヤーのコントロールするなら

		m_pPrimary->Controller();

		CInputKeyboard* pKey = pInstance->GetInKey();
		CInputMouse* pMous = pInstance->GetMouse();
		CInputJoypad* pJoy = pInstance->GetJoyKey();
		// 攻撃
		if (pKey->GetTrigger(DIK_SPACE)/*||
			pJoy->GetJoykyeTrigger(CInputJoypad::JOYKEY_B)*/)
		{
			if (pKey->GetRepeat(DIK_W) /*||
				pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
			{// 前移動
				if (pKey->GetRepeat(DIK_D) /*||
					pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
				{// 右移動
					m_pPrimary->AddMovePos(D3DXVECTOR3(-cosf(D3DX_PI * 0.75f) * PLAYER_BOOST, 0.0f, sinf(D3DX_PI * 0.75f) * PLAYER_MOVE));
					return new PlayerActivityAttack(m_pPrimary);
				}
				else if (pKey->GetRepeat(DIK_A)/* ||
					pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
				{// 左移動
					m_pPrimary->AddMovePos(D3DXVECTOR3(cosf(D3DX_PI * 0.75f) * PLAYER_BOOST, 0.0f, sinf(D3DX_PI * 0.75f) * PLAYER_BOOST));
					return new PlayerActivityAttack(m_pPrimary);
				}
				else
				{
					m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, PLAYER_BOOST));
					return new PlayerActivityAttack(m_pPrimary);
				}
			}
			else if (pKey->GetRepeat(DIK_S)/* ||
				pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
			{// 後ろ移動
				if (pKey->GetRepeat(DIK_D) /*||
					pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
				{// 右移動
					//SetMotion(1);
					m_pPrimary->AddMovePos(D3DXVECTOR3(-cosf(D3DX_PI * 0.75f) * PLAYER_BOOST, 0.0f, -sinf(D3DX_PI * 0.75f) * PLAYER_BOOST));
					return new PlayerActivityAttack(m_pPrimary);
				}
				else if (pKey->GetRepeat(DIK_A)/* ||
					pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
				{// 左移動
					//SetMotion(1);
					m_pPrimary->AddMovePos(D3DXVECTOR3(+cosf(D3DX_PI * 0.75f) * PLAYER_BOOST, 0.0f, -sinf(D3DX_PI * 0.75f) * PLAYER_BOOST));
					return new PlayerActivityAttack(m_pPrimary);
				}
				else
				{
					m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -PLAYER_BOOST));
					return new PlayerActivityAttack(m_pPrimary);
				}
			}
			else if (pKey->GetRepeat(DIK_D) /*||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
			{// 右移動
				//SetMotion(1);
				m_pPrimary->AddMovePos(D3DXVECTOR3(PLAYER_BOOST, 0.0f, 0.0f));
				return new PlayerActivityAttack(m_pPrimary);
			}
			else if (pKey->GetRepeat(DIK_A)/* ||
				pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
			{// 左移動
				//SetMotion(1);
				m_pPrimary->AddMovePos(D3DXVECTOR3(-PLAYER_BOOST, 0.0f, 0.0f));
				return new PlayerActivityAttack(m_pPrimary);
			}
			else
			{
				m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, PLAYER_BOOST));
				return new PlayerActivityAttack(m_pPrimary);
			}
		}
	}

	return this;
}
//============================================
// 行動攻撃
//============================================
CPlayer::PlayerActivityAttack::PlayerActivityAttack(CPlayer* player) :
	PlayerActivity(player)
{
	CManager* pInstance = CManager::GetInstance();
	CSound* pSound = pInstance->GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_BOUST000);

	nAttackCnt = PLAYER_ATTAC;
	player->SetInvincible(PLAYER_ATTAC);

	m_pEffect = CEffectGeneratorPaeticle::creat(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		15.0f,
		7.0f,
		D3DXCOLOR(0.0f, 0.1f, 1.0f, 1.0f),
		5,
		1,
		PLAYER_ATTAC);

}
CPlayer::PlayerActivity* CPlayer::PlayerActivityAttack::update()
{
	if (nAttackCnt > 0)
	{
		nAttackCnt--;
		m_pPrimary->Controller();

		// 当たり判定
		CObject* pTopObject[MAX_PRIORITY];
		CObject::GetAllObject(pTopObject);
		CObject* objrct = nullptr;
		CObject* Nextobjrct = nullptr;

		D3DXVECTOR3 playerPos = m_pPrimary->GetPos();
		D3DXVECTOR3 playerSiz = m_pPrimary->GetCollisionSiz();
		// プライオリティ
		for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
		{
			objrct = pTopObject[nCntPriority];	// オブジェクト格納
			while (objrct != nullptr)
			{
				// 種類が一致していたら
				Nextobjrct = objrct->GetNext();

				if (objrct->GetType() == CObject::TYPE::ENEMY)
				{
					CEnemy* pEnemy = (CEnemy*)objrct;
					D3DXVECTOR3 enemyPos = pEnemy->GetPos();
					D3DXVECTOR3 enemySiz = pEnemy->GetCollisionSiz();


					// OBB1とOBB2を初期化
					D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySiz.x, enemySiz.y, enemySiz.z);  // 敵の中心点とサイズ
					D3DXVECTOR3 center2(playerPos.x, playerPos.y, playerPos.z), halfWidths2(playerSiz.x, playerSiz.y, playerSiz.z);  // プレイヤーの中心点とサイズ

					D3DXMATRIX rotation1, rotation2;
					D3DXMatrixIdentity(&rotation1); // 回転なし
					D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

					OBB obb1(center1, halfWidths1, rotation1);
					OBB obb2(center2, halfWidths2, rotation2);

					// 衝突判定
					if (obb1.CheckOverlap(obb2))
					{
						//std::cout << "OBBは交差しています！" << std::endl;
						//Beep(1200, 300);
						pEnemy->Hit(60, m_pPrimary->GetAttcak());
					}
					else
					{
						//std::cout << "OBBは交差していません。" << std::endl;
					}
				}
				objrct = Nextobjrct;
			}
		}
		m_pEffect->SetPos(playerPos);
	}
	else
	{
		return new PlayerActivityUsually(m_pPrimary);
	}
	return this;
}
//============================================
// 行動ヒット
//============================================
CPlayer::PlayerActivityHit::PlayerActivityHit(CPlayer* player) :
	PlayerActivity(player)
{
	nDeathCnt = 30;
}
CPlayer::PlayerActivity* CPlayer::PlayerActivityHit::update()
{
	if (nDeathCnt > 0)
	{
		nDeathCnt--;
		CManager* pInstance = CManager::GetInstance();
		if (pInstance->GetCamera()->GetCameraControllreFpllow() == false)
		{// プレイヤーのコントロールするなら
			m_pPrimary->Controller();
		}
	}
	else
	{

	}
	return this;
}
//============================================
// 行動死亡
//============================================
CPlayer::PlayerActivityDeath::PlayerActivityDeath(CPlayer* player):
	PlayerActivity(player)
{
	nDeathCnt = 60;
}
CPlayer::PlayerActivity* CPlayer::PlayerActivityDeath::update()
{
	if (nDeathCnt > 0)
	{
		nDeathCnt--;
	}
	else
	{
		m_pPrimary->Release();
	}
	return this;
}