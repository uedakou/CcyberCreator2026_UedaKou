//============================================
//
// �G100[enemy100.cpp]
// Author:Uedakou
// 
//============================================
#include "enemy100.h"	// �G100
#include "enemy000.h"	// �G000
#include "player.h"		// �v���C���[
#include "../collision/obb.h"
#include "../base_object/effect_generator_particle.h"	// �G�t�F�N�g�p�[�e�B�N��
#include "life_3d.h"

#define Enemy_100_Move true
//============================================
// �R���X�g
//============================================
CEnemy100::CEnemy100()
{
	m_pActivity = new CActivity_Enemy100_Search(this);

	m_fSpeed = Enemy100_SPEED;
	m_fBrake = Enemy100_BRAKE;
	m_fBoost = Enemy100_BOOST;
	m_nCntSurvival = Eneny100_COUNT_SURVIVAL;

	SetType(CEnemy::ENEMY_TYPE::Enemy100);
	m_pLife3D = nullptr;
	m_pEffect = CEffectGeneratorPaeticle::creat(
		D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		20.0f,
		5.0f,
		D3DCOLOR_RGBA(255, 10, 0, 255),
		5,
		1);
	CEnemy::SetType(CEnemy::ENEMY_TYPE::Enemy100);
}
//============================================
// �f�X�g���N�^
//============================================
CEnemy100::~CEnemy100()
{
	if (m_pActivity != nullptr)
	{
		delete m_pActivity;
	}
}
//============================================
// ������
//============================================
void CEnemy100::Init()
{
	CObjectMotion::Load("data\\CHARACTER\\motion_Enemy100.txt");
	CCharacter::SetCollisionX(Enemy100_SIZE);

	CEnemy::Init();

	SetLife(10);
	SetAttcak(3);

	CObjectMotion::SetMotion(1);

	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		CObject* pObject = GetMyObject(nCnt);
		CObject* pNext = nullptr;
		while (pObject != nullptr)
		{
			pNext = pObject->GetNext();
			if (pObject->GetType() == CObject::TYPE::PLAYER)
			{
				CEnemy::SetTarget(pObject);
			}
			pObject = pNext;
		}
	}
	SetLife(Enemy000_LIFE);
	D3DXVECTOR3 pos = GetPos();
	m_pLife3D = CLife_3D::creat(D3DXVECTOR3(pos.x, pos.y, pos.z), Enemy000_LIFE);
}
//============================================
// �I������
//============================================
void CEnemy100::Uninit()
{
	CEnemy::Uninit();
	if (m_pLife3D != nullptr)
	{
		m_pLife3D->Uninit();
		m_pLife3D->Release();
		m_pLife3D = nullptr;
	}
}
//============================================
// �X�V
//============================================
void CEnemy100::Update()
{
	//D3DXVECTOR3 move = GetMovePos();
#if 1
	ActivityUpdate();
#endif // 0


	D3DXVECTOR3 pos = GetPos();
	if (pos.x < -500.0f * 0.5f)
	{
		SetMovePosX(0.0f);
		SetPosX(-500.0f * 0.5f);
	}
	else if (pos.x > 500.0f * 0.5f)
	{
		SetMovePosX(0.0f);
		SetPosX(500.0f * 0.5f);
	}
	int life = GetLife();
	if (m_pLife3D != nullptr)
	{
		m_pLife3D->SetLife(life);
		m_pLife3D->SetPos(D3DXVECTOR3(pos.x, pos.y + 70.0f, pos.z));
	}
	CEnemy::Update();
	if (m_pEffect != nullptr)
	{
		m_pEffect->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z - 100.0f));
	}
}
//============================================
// �`��
//============================================
void CEnemy100::Draw()
{
	CEnemy::Draw();
}
//============================================
// �����[�V�����擾
//============================================
int CEnemy100::GetNextMotion()
{
	return 0;
}
void CEnemy100::Hit(int nCntInvincible, int nDamage)
{
	CEnemy::Hit(nCntInvincible, nDamage);
	if (GetLife() <= 0)
	{
		if (m_pActivity != nullptr)
		{
			delete m_pActivity;
			m_pActivity = new CActivity_Enemy100_Dethe(this);
		}
	}
}
//============================================
// ����
//============================================
CEnemy100* CEnemy100::creat(D3DXVECTOR3 pos)
{
	CEnemy100* pEnemy100 = new CEnemy100();
	pEnemy100->SetPos(pos);
	pEnemy100->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	pEnemy100->Init();
	return pEnemy100;
}
//============================================
// ���
//============================================
CEnemy100::CActivity_Enemy100::CActivity_Enemy100(CEnemy100* p)
{
	m_pPrimary = p;
}
//============================================
// ���G
//============================================
CEnemy100::CActivity_Enemy100_Search::CActivity_Enemy100_Search(CEnemy100* p):
	CActivity_Enemy100(p){}
CEnemy100::CActivity_Enemy100_Search::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Search::update()
{
	// �v���C���[��T��
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		CObject* pObject = GetMyObject(nCnt);
		CObject* pNext = nullptr;
		while (pObject != nullptr)
		{
			pNext = pObject->GetNext();
			if (pObject->GetType() == CObject::TYPE::PLAYER)
			{
				m_pPrimary->SetTarget(pObject);
				// �v���C���[���������玟��Update�Ɉڍs
				return new CActivity_Enemy100_Following(m_pPrimary);
			}
			pObject = pNext;
		}
	}
	return this;
}
//============================================
// �ǐ�
//============================================
CEnemy100::CActivity_Enemy100_Following::CActivity_Enemy100_Following(CEnemy100* p):
	CActivity_Enemy100(p),
	m_MaxCnt(120)
{
	m_nCnt = 0;
}
CEnemy100::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Following::update()
{
#if Enemy_100_Move
	// �펞�ړ�
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, Enemy100_SPEED));
#endif // Enemy_100_Move

	// ����
	CObject* pObject = m_pPrimary->GetTarget();	// �^�[�Q�b�g�擾
	D3DXVECTOR3 PlayerPos = ((CPlayer*)pObject)->GetPos();	// �^�[�Q�b�g�ʒu�擾
	D3DXVECTOR3 pos = m_pPrimary->GetPos();	// ���g�ʒu�擾
	// �v���C���[�̑O�ɕ���
	// �O��
	if (pos.z > PlayerPos.z + 1000.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy100_BRAKE));
	}
	else if (pos.z < PlayerPos.z + 1000.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, Enemy100_BRAKE));
	}
	// ���E
	if (PlayerPos.x - pos.x > 0.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, Enemy100_BEND));
	}
	else
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy100_BEND));
	}
	// �U������
	float fLeng = atan2f(PlayerPos.z - pos.z, PlayerPos.x - pos.x);
	if (fLeng < 200.0f)
	{// 200.0f�ȓ���Enemy000_ATTAC�t���[��������U������
		m_nCnt++;
		if (m_nCnt == m_MaxCnt)
		{
			int nRand = 0;

#ifndef _DEBUG
			nRand = rand() % MAX;
#else
			if (1)
			{
				nRand = 0;
			}
			else
			{
				nRand = rand() % MAX;
			}
#endif
			switch (nRand)
			{
			case TACKL:
				return new CActivity_Enemy100_Tackle_000(m_pPrimary);

				break;
			case SUMMON:
				return new CActivity_Enemy100_Summon(m_pPrimary);
				break;
			}
		}
	}
	else
	{
		if (m_nCnt > 0)
		{
			m_nCnt--;
		}
	}
	// �����蔻��
	CObject* pTopObject[MAX_PRIORITY];
	CObject::GetAllObject(pTopObject);
	CObject* objrct = nullptr;
	CObject* Nextobjrct = nullptr;

	D3DXVECTOR3 enemypos = m_pPrimary->GetPos();
	D3DXVECTOR3 enemysiz = m_pPrimary->GetCollisionSiz();
	// �v���C�I���e�B
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		objrct = pTopObject[nCntPriority];	// �I�u�W�F�N�g�i�[
		while (objrct != nullptr)
		{
			// ��ނ���v���Ă�����
			Nextobjrct = objrct->GetNext();
			if (objrct->GetType() == CObject::TYPE::PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)objrct;
				D3DXVECTOR3 playerpos = pPlayer->GetPos();
				D3DXVECTOR3 playerSiz = pPlayer->GetCollisionSiz();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(playerpos.x, playerpos.y, playerpos.z), halfWidths1(playerSiz.x, playerSiz.y, playerSiz.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(enemypos + m_pPrimary->GetCollisionPos()), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixIdentity(&rotation2); // ��]�Ȃ�
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]
				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);
				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{
					//std::cout << "OBB�͌������Ă��܂��I" << std::endl;
					D3DXVECTOR3 ShockRot = D3DXVECTOR3(
						atan2(enemypos.x, playerpos.x),
						atan2(enemypos.y, playerpos.y),
						atan2(enemypos.z, playerpos.z));
					D3DXVECTOR3 Normalize;
					D3DXVec3Normalize(&Normalize, &ShockRot);

					pPlayer->Hit(Normalize * 10.0f, 60, m_pPrimary->GetAttcak());
				}
				else
				{
					//std::cout << "OBB�͌������Ă��܂���B" << std::endl;
				}
			}
			objrct = Nextobjrct;
		}
	}
	return this;
}
//============================================
// �^�b�N��
//============================================
// �^�b�N��������
CEnemy100::CActivity_Enemy100_Tackle_000::CActivity_Enemy100_Tackle_000(CEnemy100* p):
	CActivity_Enemy100(p),
	m_MaxCnt(30)
{
	m_nCnt = 0;
}
CEnemy100::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Tackle_000::update()
{
#if Enemy_100_Move
	// �펞�ړ�
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, Enemy100_SPEED));
#endif // Enemy_100_Move


	CObject* pObject = m_pPrimary->GetTarget(); // �^�[�Q�b�g�擾
	D3DXVECTOR3 PlayerPos = ((CPlayer*)pObject)->GetPos();	// �^�[�Q�b�g�ʒu�擾
	D3DXVECTOR3 pos = m_pPrimary->GetPos();	// ���g�ʒu�擾
	// �v���C���[�̑O������낦��
	if (pos.z > PlayerPos.z)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy100_BOOST));
	}
	else if (pos.z < PlayerPos.z)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, Enemy100_BOOST));
	}
	m_nCnt++;
	// ���Ԃ��߂����玟��Update�Ɉڍs
	if (m_nCnt > m_MaxCnt)
	{
		return new CActivity_Enemy100_Tackle_001(m_pPrimary);
	}
	// �����蔻��
	CObject* pTopObject[MAX_PRIORITY];
	CObject::GetAllObject(pTopObject);
	CObject* objrct = nullptr;
	CObject* Nextobjrct = nullptr;

	D3DXVECTOR3 enemypos = m_pPrimary->GetPos();
	D3DXVECTOR3 enemysiz = m_pPrimary->GetCollisionSiz();
	// �v���C�I���e�B
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		objrct = pTopObject[nCntPriority];	// �I�u�W�F�N�g�i�[
		while (objrct != nullptr)
		{
			// ��ނ���v���Ă�����
			Nextobjrct = objrct->GetNext();
			if (objrct->GetType() == CObject::TYPE::PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)objrct;
				D3DXVECTOR3 playerpos = pPlayer->GetPos();
				D3DXVECTOR3 playerSiz = pPlayer->GetCollisionSiz();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(playerpos.x, playerpos.y, playerpos.z), halfWidths1(playerSiz.x, playerSiz.y, playerSiz.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(enemypos + m_pPrimary->GetCollisionPos()), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixIdentity(&rotation2); // ��]�Ȃ�
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]
				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);
				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{
					//std::cout << "OBB�͌������Ă��܂��I" << std::endl;
					D3DXVECTOR3 ShockRot = D3DXVECTOR3(
						atan2(enemypos.x, playerpos.x),
						atan2(enemypos.y, playerpos.y),
						atan2(enemypos.z, playerpos.z));
					D3DXVECTOR3 Normalize;
					D3DXVec3Normalize(&Normalize, &ShockRot);

					pPlayer->Hit(Normalize * 10.0f, 10, m_pPrimary->GetAttcak());
				}
				else
				{
					//std::cout << "OBB�͌������Ă��܂���B" << std::endl;
				}
			}
			objrct = Nextobjrct;
		}
	}
	return this;
}
// �^�b�N�����E�ɂԂ�
CEnemy100::CActivity_Enemy100_Tackle_001::CActivity_Enemy100_Tackle_001(CEnemy100* p) : 
	CActivity_Enemy100(p),
	m_MaxCnt(30)
{
	m_nCnt = 0;
}
CEnemy100::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Tackle_001::update()
{
#if Enemy_100_Move
	// �펞�ړ�
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, Enemy100_SPEED));
#endif // Enemy_100_Move

	CObject* pObject = m_pPrimary->GetTarget(); // �^�[�Q�b�g�擾
	D3DXVECTOR3 PlayerPos = ((CPlayer*)pObject)->GetPos();	// �^�[�Q�b�g�ʒu�擾
	D3DXVECTOR3 pos = m_pPrimary->GetPos();	// ���g�ʒu�擾
	// �v���C���[�̍��E�����낦��
	if (pos.x > PlayerPos.x)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(-Enemy100_BOOST, 0.0f, 0.0f));
	}
	else if (pos.x < PlayerPos.x)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(Enemy100_BOOST, 0.0f, 0.0f));
	}
	m_nCnt++;
	// ���Ԃ��߂����玟��Update�Ɉڍs
	if (m_nCnt > m_MaxCnt)
	{
		return new CActivity_Enemy100_Following(m_pPrimary);
	}
	// �����蔻��
	CObject* pTopObject[MAX_PRIORITY];
	CObject::GetAllObject(pTopObject);
	CObject* objrct = nullptr;
	CObject* Nextobjrct = nullptr;

	D3DXVECTOR3 enemypos = m_pPrimary->GetPos();
	D3DXVECTOR3 enemysiz = m_pPrimary->GetCollisionSiz();
	// �v���C�I���e�B
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		objrct = pTopObject[nCntPriority];	// �I�u�W�F�N�g�i�[
		while (objrct != nullptr)
		{
			// ��ނ���v���Ă�����
			Nextobjrct = objrct->GetNext();
			if (objrct->GetType() == CObject::TYPE::PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)objrct;
				D3DXVECTOR3 playerpos = pPlayer->GetPos();
				D3DXVECTOR3 playerSiz = pPlayer->GetCollisionSiz();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(playerpos.x, playerpos.y, playerpos.z), halfWidths1(playerSiz.x, playerSiz.y, playerSiz.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(enemypos + m_pPrimary->GetCollisionPos()), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixIdentity(&rotation2); // ��]�Ȃ�
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]
				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);
				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{
					//std::cout << "OBB�͌������Ă��܂��I" << std::endl;
					D3DXVECTOR3 ShockRot = D3DXVECTOR3(
						atan2(enemypos.x, playerpos.x),
						atan2(enemypos.y, playerpos.y),
						atan2(enemypos.z, playerpos.z));
					D3DXVECTOR3 Normalize;
					D3DXVec3Normalize(&Normalize, &ShockRot);

					pPlayer->Hit(Normalize * 10.0f, 10, m_pPrimary->GetAttcak());
				}
				else
				{
					//std::cout << "OBB�͌������Ă��܂���B" << std::endl;
				}
			}
			objrct = Nextobjrct;
		}
	}
	return this;
}
//============================================
// ����
//============================================
CEnemy100::CActivity_Enemy100_Summon::CActivity_Enemy100_Summon(CEnemy100* p):
	CActivity_Enemy100(p),
	m_MaxCnt(30)
{
	m_nCnt = 0;
}
CEnemy100::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Summon::update()
{
#if Enemy_100_Move
	// �펞�ړ�
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, Enemy100_SPEED));
#endif // Enemy_100_Move

	D3DXVECTOR3 pos = m_pPrimary->GetPos();
	m_nCnt++;

	//if (m_nCnt == 15)
	//{
	//	CEnemy000::creat(D3DXVECTOR3(pos.x, 0.0f, pos.z - 10.0f));
	//}


	// ���Ԃ��߂����玟��Update�Ɉڍs
	if (m_nCnt > m_MaxCnt)
	{
		CEnemy000::creat(D3DXVECTOR3(pos.x, 0.0f, pos.z - 10.0f));

		return new CActivity_Enemy100_Following(m_pPrimary);
	}

	// �����蔻��
	CObject* pTopObject[MAX_PRIORITY];
	CObject::GetAllObject(pTopObject);
	CObject* objrct = nullptr;
	CObject* Nextobjrct = nullptr;

	D3DXVECTOR3 enemypos = m_pPrimary->GetPos();
	D3DXVECTOR3 enemysiz = m_pPrimary->GetCollisionSiz();
	// �v���C�I���e�B
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		objrct = pTopObject[nCntPriority];	// �I�u�W�F�N�g�i�[
		while (objrct != nullptr)
		{
			// ��ނ���v���Ă�����
			Nextobjrct = objrct->GetNext();
			if (objrct->GetType() == CObject::TYPE::PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)objrct;
				D3DXVECTOR3 playerpos = pPlayer->GetPos();
				D3DXVECTOR3 playerSiz = pPlayer->GetCollisionSiz();
				// OBB1��OBB2��������
				D3DXVECTOR3 center1(playerpos.x, playerpos.y, playerpos.z), halfWidths1(playerSiz.x, playerSiz.y, playerSiz.z);  // �G�̒��S�_�ƃT�C�Y
				D3DXVECTOR3 center2(enemypos + m_pPrimary->GetCollisionPos()), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // �v���C���[�̒��S�_�ƃT�C�Y

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // ��]�Ȃ�
				D3DXMatrixIdentity(&rotation2); // ��]�Ȃ�
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45�x��]
				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);
				// �Փ˔���
				if (obb1.CheckOverlap(obb2))
				{
					//std::cout << "OBB�͌������Ă��܂��I" << std::endl;
					D3DXVECTOR3 ShockRot = D3DXVECTOR3(
						atan2(enemypos.x, playerpos.x),
						atan2(enemypos.y, playerpos.y),
						atan2(enemypos.z, playerpos.z));
					D3DXVECTOR3 Normalize;
					D3DXVec3Normalize(&Normalize, &ShockRot);

					pPlayer->Hit(Normalize * 10.0f, 10, m_pPrimary->GetAttcak());
				}
				else
				{
					//std::cout << "OBB�͌������Ă��܂���B" << std::endl;
				}
			}
			objrct = Nextobjrct;
		}
	}
	return this;
}
//============================================
// ���S
//============================================
CEnemy100::CActivity_Enemy100_Dethe::CActivity_Enemy100_Dethe(CEnemy100* p):
	CActivity_Enemy100(p),
	m_MaxCnt(120)
{
	m_nCnt = 0;
}
CEnemy100::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Dethe::update()
{
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, -Enemy100_BRAKE));

	m_nCnt++;
	if (m_nCnt >= m_MaxCnt)
	{
		m_pPrimary->Release();
	}
	return this;
}