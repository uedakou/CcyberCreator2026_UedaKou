//============================================
//
// �v���C���[[player.cpp]
// Author:Uedakou
// 
//============================================
#include "player.h"	// �v���C���[
#include "../base/manager.h"	// �}�l�[�W���[
#include "enemy.h"	// �G�l�~�[
#include "../scene/scene_base.h"	// �V�[���x�[�X
#include <strsafe.h>
#include "../collision/obb.h"	

#define PlayerMove true

//============================================
// �R���X�g
//============================================
CPlayer::CPlayer()
{
	m_fSpeed = PLAYER_SPEED;	// �������x�ݒ�
	m_fBrake = PLAYER_BRAKE;	// �����u���[�L�ݒ�
	m_fBoost = PLAYER_BOOST;	// �����u�[�X�g�ݒ�

	//m_bJump = false;	// �W�����v�\��
	m_pLife = nullptr;
	SetAttcak(1);

	SetType(CObject::TYPE::PLAYER);
	m_pActivity = new PlayerActivityUsually(this);
	m_pEffect = nullptr;
}
//============================================
// �f�X�g��
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
// ������
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
// �I��
//============================================
void CPlayer::Uninit()
{
	CCharacter::Uninit();
	// ���C�t���
	if (m_pLife != nullptr)
	{
		m_pLife->Release();
		m_pLife = nullptr;
	}

	// �G�t�F�N�g���
	if (m_pEffect)
	{
		m_pEffect->Release();
		m_pEffect = nullptr;
	}
}
//============================================
// �X�V
//============================================
void CPlayer::Update()
{
	//Controller();
	ActivityUpdate();	// �s������
	if (GetLife() > 0)
	{
		D3DXVECTOR3 rot = GetRot();
#if PlayerMove
		// �펞�ړ�
		AddMovePos(D3DXVECTOR3(0.0f, 0.0f, PLAYER_SPEED));
#endif // PlayerMove

		// �ړ�����
		SetRotY((D3DX_PI - rot.y) * PLAYER_ROT_RESISTANCE + D3DX_PI);

		// ���ʒu���L�^
		D3DXVECTOR3 posOld = GetPos();
	}
	X coll = GetCollisionX();
	// �d��
	AddMovePosY(-2.5f);
	// �ŉ��i�Ŏ~�߂�
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
// �`��
//============================================
void CPlayer::Draw()
{
	CCharacter::Draw();
}
//============================================
// �q�b�g����
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
// ����
//============================================
CPlayer* CPlayer::creat()
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();

	return pPlayer;
}
//============================================
// �R���g���[��
//============================================
void CPlayer::Controller()
{
	CManager* instance = CManager::GetInstance();
	CInputKeyboard* pKey = instance->GetInKey();
	CInputMouse* pMous = instance->GetMouse();
	CInputJoypad* pJoy = instance->GetJoyKey();
	CSound* pSound = instance->GetSound();
	// �ړ�
	if (pKey->GetRepeat(DIK_W) /*||
		pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
	{// �O�ړ�
		if (pKey->GetRepeat(DIK_D) /*||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
		{// �E�ړ�
			AddMoveRot(D3DXVECTOR3(0.0f, PLAYER_ROLL, 0.0f));
			AddMovePos(D3DXVECTOR3(-cosf(D3DX_PI * 0.75f) * PLAYER_BEND, 0.0f, sinf(D3DX_PI * 0.75f) * PLAYER_MOVE));

			SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
		else if (pKey->GetRepeat(DIK_A)/* ||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
		{// ���ړ�
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
	{// ���ړ�
		if (pKey->GetRepeat(DIK_D) /*||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
		{// �E�ړ�
			AddMoveRot(D3DXVECTOR3(0.0f, PLAYER_ROLL, 0.0f));
			AddMovePos(D3DXVECTOR3(-cosf(D3DX_PI * 0.75f) * PLAYER_BEND, 0.0f, -sinf(D3DX_PI * 0.75f) * PLAYER_BRAKE));
			SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
		}
		else if (pKey->GetRepeat(DIK_A)/* ||
			pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
		{// ���ړ�
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
	{// �E�ړ�
		AddMoveRot(D3DXVECTOR3(0.0f, PLAYER_ROLL, 0.0f));
		AddMovePos(D3DXVECTOR3(PLAYER_BEND, 0.0f, 0.0f));
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}
	else if (pKey->GetRepeat(DIK_A)/* ||
		pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
	{// ���ړ�
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
// �ړ�����
//============================================
void CPlayer::MoveAttenuation()
{
	CCharacter::MoveAttenuation();
}
//============================================
// ���[�v���Ȃ����[�V�����̎��̃��[�V����
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
// �s���ʏ�
//============================================
CPlayer::PlayerActivityUsually::PlayerActivityUsually(CPlayer* player) :
	PlayerActivity(player)
{
}
CPlayer::PlayerActivity* CPlayer::PlayerActivityUsually::update()
{
	CManager* pInstance = CManager::GetInstance();
	if (pInstance->GetCamera()->GetCameraControllreFpllow() == false)
	{// �v���C���[�̃R���g���[������Ȃ�

		m_pPrimary->Controller();

		CInputKeyboard* pKey = pInstance->GetInKey();
		CInputMouse* pMous = pInstance->GetMouse();
		CInputJoypad* pJoy = pInstance->GetJoyKey();
		// �U��
		if (pKey->GetTrigger(DIK_SPACE)/*||
			pJoy->GetJoykyeTrigger(CInputJoypad::JOYKEY_B)*/)
		{
			if (pKey->GetRepeat(DIK_W) /*||
				pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
			{// �O�ړ�
				if (pKey->GetRepeat(DIK_D) /*||
					pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
				{// �E�ړ�
					m_pPrimary->AddMovePos(D3DXVECTOR3(-cosf(D3DX_PI * 0.75f) * PLAYER_BOOST, 0.0f, sinf(D3DX_PI * 0.75f) * PLAYER_MOVE));
					return new PlayerActivityAttack(m_pPrimary);
				}
				else if (pKey->GetRepeat(DIK_A)/* ||
					pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
				{// ���ړ�
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
			{// ���ړ�
				if (pKey->GetRepeat(DIK_D) /*||
					pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_RIGHT)*/)
				{// �E�ړ�
					//SetMotion(1);
					m_pPrimary->AddMovePos(D3DXVECTOR3(-cosf(D3DX_PI * 0.75f) * PLAYER_BOOST, 0.0f, -sinf(D3DX_PI * 0.75f) * PLAYER_BOOST));
					return new PlayerActivityAttack(m_pPrimary);
				}
				else if (pKey->GetRepeat(DIK_A)/* ||
					pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
				{// ���ړ�
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
			{// �E�ړ�
				//SetMotion(1);
				m_pPrimary->AddMovePos(D3DXVECTOR3(PLAYER_BOOST, 0.0f, 0.0f));
				return new PlayerActivityAttack(m_pPrimary);
			}
			else if (pKey->GetRepeat(DIK_A)/* ||
				pJoy->GetJoystickRepeat(CInputJoypad::JOYSTICK_LEFT, CInputJoypad::STICKANGLE_LEFT)*/)
			{// ���ړ�
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
// �s���U��
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

		// �����蔻��
		CObject* pTopObject[MAX_PRIORITY];
		CObject::GetAllObject(pTopObject);
		CObject* objrct = nullptr;
		CObject* Nextobjrct = nullptr;

		D3DXVECTOR3 playerPos = m_pPrimary->GetPos();
		D3DXVECTOR3 playerSiz = m_pPrimary->GetCollisionSiz();
		// �v���C�I���e�B
		for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
		{
			objrct = pTopObject[nCntPriority];	// �I�u�W�F�N�g�i�[
			while (objrct != nullptr)
			{
				// ��ނ���v���Ă�����
				Nextobjrct = objrct->GetNext();

				if (objrct->GetType() == CObject::TYPE::ENEMY)
				{
					CEnemy* pEnemy = (CEnemy*)objrct;
					D3DXVECTOR3 enemyPos = pEnemy->GetPos();
					D3DXVECTOR3 enemySiz = pEnemy->GetCollisionSiz();


					// OBB1��OBB2��������
					D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySiz.x, enemySiz.y, enemySiz.z);  // �G�̒��S�_�ƃT�C�Y
					D3DXVECTOR3 center2(playerPos.x, playerPos.y, playerPos.z), halfWidths2(playerSiz.x, playerSiz.y, playerSiz.z);  // �v���C���[�̒��S�_�ƃT�C�Y

					D3DXMATRIX rotation1, rotation2;
					D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
					D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]

					OBB obb1(center1, halfWidths1, rotation1);
					OBB obb2(center2, halfWidths2, rotation2);

					// �Փ˔���
					if (obb1.CheckOverlap(obb2))
					{
						//std::cout << "OBB�͌������Ă��܂��I" << std::endl;
						//Beep(1200, 300);
						pEnemy->Hit(60, m_pPrimary->GetAttcak());
					}
					else
					{
						//std::cout << "OBB�͌������Ă��܂���B" << std::endl;
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
// �s���q�b�g
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
		{// �v���C���[�̃R���g���[������Ȃ�
			m_pPrimary->Controller();
		}
	}
	else
	{

	}
	return this;
}
//============================================
// �s�����S
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