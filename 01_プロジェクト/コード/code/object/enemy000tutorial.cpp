//============================================
//
// �G000�`���[�g���A��[enemy000tutoreal.h]
// Author:Uedakou
// 
//============================================
#include "enemy000tutorial.h"	// �G000�`���[�g���A��
#include "player.h"		// �v���C���[
#include <strsafe.h>	// �e�L�X�g�̕`��ɕK�v


//============================================
// �R���X�g
//============================================
CEnemy000Tutorial::CEnemy000Tutorial()
{
	m_pActivity = new CActivity_Enemy000Tutoriale_Search(this);
}
//============================================
// �f�X�g���N�^
//============================================
CEnemy000Tutorial::~CEnemy000Tutorial()
{
}
//============================================
// ������
//============================================
void CEnemy000Tutorial::Init()
{
	CEnemy000::Init();
	SetAttcak(0);
}
//============================================
// �I��
//============================================
void CEnemy000Tutorial::Uninit()
{
	CEnemy000::Uninit();
}
//============================================
// �X�V
//============================================
void CEnemy000Tutorial::Update()
{
	CEnemy000::Update();
}
//============================================
// �`��
//============================================
void CEnemy000Tutorial::Draw()
{
	CEnemy000::Draw();
}
//============================================
// �R���X�g
//============================================
void CEnemy000Tutorial::Hit(int nCntInvincible, int nDamage)
{
	CEnemy000::Hit(nCntInvincible, nDamage);
}
//============================================
// ����
//============================================
CEnemy000Tutorial* CEnemy000Tutorial::creat(D3DXVECTOR3 pos)
{
	CEnemy000Tutorial* pEnemy000 = new CEnemy000Tutorial();
	pEnemy000->SetPos(pos);
	pEnemy000->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	pEnemy000->Init();

	return pEnemy000;
}
//============================================
// �s�����
//============================================
CEnemy000Tutorial::CActivity_Enemy000Tutoriale::CActivity_Enemy000Tutoriale(CEnemy000Tutorial* p):
	m_pPrimary(p)
{

}
//============================================
// �s�����G�R���X�g
//============================================
CEnemy000Tutorial::CActivity_Enemy000Tutoriale_Search::CActivity_Enemy000Tutoriale_Search(CEnemy000Tutorial* p): 
	CActivity_Enemy000Tutoriale(p)
{

}
//============================================
// �s�����G�X�V
//============================================
CEnemy000Tutorial::CActivity_Enemy000Tutoriale* CEnemy000Tutorial::CActivity_Enemy000Tutoriale_Search::update()
{
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
				return new CActivity_Enemy000Tutoriale_Following(m_pPrimary);
			}
			pObject = pNext;
		}
	}
	return this;
}
//============================================
// �s���Ǐ]�R���X�g
//============================================
CEnemy000Tutorial::CActivity_Enemy000Tutoriale_Following::CActivity_Enemy000Tutoriale_Following(CEnemy000Tutorial* p):
	CActivity_Enemy000Tutoriale(p)
{
}
//============================================
// �s���Ǐ]�X�V
//============================================
CEnemy000Tutorial::CActivity_Enemy000Tutoriale* CEnemy000Tutorial::CActivity_Enemy000Tutoriale_Following::update()
{
	// ��������
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, m_pPrimary->m_fSpeed));
	D3DXVECTOR3 PlayerPos = ((CPlayer*)m_pPrimary->GetTarget())->GetPos();
	D3DXVECTOR3 pos = m_pPrimary->GetPos();

	if (pos.z > PlayerPos.z + 500.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy000_BRAKE));
	}
	else if (pos.z < PlayerPos.z + 500.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, Enemy000_BRAKE));
	}

	if (pos.x > PlayerPos.x + 500.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(-Enemy000_BEND, 0.0f, 0.0f));
	}
	else if (pos.x < PlayerPos.x - 500.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(Enemy000_BEND, 0.0f, 0.0f));
	}
	else
	{
		float fRand = ((float)(rand() %
			(int)(10.0f * (Enemy000_BEND * 2)) -
			(int)(10.0f * Enemy000_BEND))) 
			/ 10.0f;

		m_pPrimary->AddMovePos(D3DXVECTOR3(fRand, 0.0f, 0.0f));
}

	return this;
}
//============================================
// �s�����S�R���X�g
//============================================
CEnemy000Tutorial::CActivity_Enemy000Tutoriale_Death::CActivity_Enemy000Tutoriale_Death(CEnemy000Tutorial* p):
	CActivity_Enemy000Tutoriale(p),
	m_nCntDeath(30)
{
}
//============================================
// �s�����S�X�V
//============================================
CEnemy000Tutorial::CActivity_Enemy000Tutoriale* CEnemy000Tutorial::CActivity_Enemy000Tutoriale_Death::update()
{
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy000_BOOST));
	if (m_nCntDeath > 0)
	{
		m_nCntDeath--;
	}
	else
{
		m_pPrimary->Release();
	}
	return this;
}
