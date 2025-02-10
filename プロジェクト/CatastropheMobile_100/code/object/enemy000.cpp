//============================================
//
// 敵000[enemy000.cpp]
// Author:Uedakou
// 
//============================================
#include "enemy000.h"
#include "player.h"
#include "../collision/collision.h"
#include "../collision/obb.h"

#define EnemyMove true

//============================================
// コンスト
//============================================
CEnemy000::CEnemy000()
{
	m_fSpeed = Enemy000_SPEED;
	m_fBrake = Enemy000_BRAKE;
	m_fBoost = Enemy000_BOOST;
	m_pActivity = new CActivity_Enemy000_Search(this, Eneny000_COUNT_SURVIVAL);

	m_pLife3D = nullptr;
	SetType(CEnemy::ENEMY_TYPE::Enemy000);
	m_pEffect = CEffectGeneratorPaeticle::creat(D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		10.0f,
		5.0f,
		D3DCOLOR_RGBA(255, 10, 0, 255),
		3,
		1);

}
//============================================
// デストラクタ
//============================================
CEnemy000::~CEnemy000()
{
	if (m_pActivity != nullptr)
	{
		delete m_pActivity;
	}
}
//============================================
// 初期化
//============================================
void CEnemy000::Init()
{
	CEnemy::Init();
	SetAttcak(1);

	CObjectMotion::Load(Enemy000_MotionFilename);
	CCharacter::SetCollisionX(Enemy000_XSIZE);
	
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
				break;
			}
			pObject = pNext;
		}
	}

	CEnemy::SetType(CEnemy::ENEMY_TYPE::Enemy000);

	SetLife(Enemy000_LIFE);
	D3DXVECTOR3 pos = GetPos();
	m_pLife3D = CLife_3D::creat(D3DXVECTOR3(pos.x, pos.y, pos.z), Enemy000_LIFE);
}
//============================================
// 終了処理
//============================================
void CEnemy000::Uninit()
{
	CEnemy::Uninit();
	if (m_pLife3D != nullptr)
	{
		m_pLife3D->Uninit();
		m_pLife3D->DeathFlag();
		m_pLife3D = nullptr;
	}
}
//============================================
// 更新
//============================================
void CEnemy000::Update()
{
	X coll = GetCollisionX();
	D3DXVECTOR3 pos = GetPos();
	if (pos.x < -500.0f + coll.siz.x * 0.5f)
	{
		SetMovePosX(0.0f);
		SetPosX(-500.0f + coll.siz.x * 0.5f);
	}
	else if (pos.x > 500.0f - coll.siz.x * 0.5f)
	{
		SetMovePosX(0.0f);
		SetPosX(500.0f - coll.siz.x * 0.5f);
	}

	CEnemy::Update();
	ActivityUpdate();
	int life = GetLife();
	if (m_pLife3D != nullptr)
	{
		m_pLife3D->SetLife(life);
		m_pLife3D->SetPos(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z));
	}
	if (m_pEffect != nullptr)
	{
		m_pEffect->SetPos(pos);
	}
}
//============================================
// 描画
//============================================
void CEnemy000::Draw()
{
	CEnemy::Draw();
}
//============================================
// 次モーション取得
//============================================
int CEnemy000::GetNextMotion()
{
	return 0;
}
//============================================
// ヒット
//============================================
void CEnemy000::Hit(int nCntInvincible, int nDamage)
{
	CEnemy::Hit(nCntInvincible, nDamage);
	if (GetLife() <= 0)
	{
		if (m_pActivity != nullptr)
		{
			delete m_pActivity;
			m_pActivity = new CActivity_Enemy000_Death(this);
		}
	}
}
//============================================
// 行動基底コンスト
//============================================
CEnemy000::CActivity_Enemy000::CActivity_Enemy000(CEnemy000* p, int nS) :
	m_pPrimary(p),m_nCntSurvival(nS){}
//============================================
// 行動デスカウント
//============================================
CEnemy000::CActivity_Enemy000* CEnemy000::CActivity_Enemy000::DeathCnt()
{
	m_nCntSurvival--;
	if (m_nCntSurvival == 0)
	{
		return new CActivity_Enemy000_Death(m_pPrimary);
	}
	return this;
}
//============================================
// 行動索敵コンスト
//============================================
CEnemy000::CActivity_Enemy000_Search::CActivity_Enemy000_Search(CEnemy000* p, int nS):
	CActivity_Enemy000(p, nS) {}
//============================================
// 行動索敵更新
//============================================
CEnemy000::CActivity_Enemy000* CEnemy000::CActivity_Enemy000_Search::update()
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
				return new CActivity_Enemy000_Following(m_pPrimary, m_nCntSurvival);
			}
			pObject = pNext;
		}
	}

	// 生存時間を削る
	auto p = DeathCnt();
	if (p != this)
	{
		return p;
	}
	return this;
}
//============================================
// 行動追従コンスト
//============================================
CEnemy000::CActivity_Enemy000_Following::CActivity_Enemy000_Following(CEnemy000* p, int nS) :
	CActivity_Enemy000(p, nS)
{
	m_nCntAttac = Enemy000_ATTAC;
}
//============================================
// 行動追従更新
//============================================
CEnemy000::CActivity_Enemy000* CEnemy000::CActivity_Enemy000_Following::update()
{
#if EnemyMove

	// 並走する
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, m_pPrimary->m_fSpeed));
	D3DXVECTOR3 PlayerPos = ((CPlayer*)m_pPrimary->GetTarget())->GetPos();
	D3DXVECTOR3 pos = m_pPrimary->GetPos();
	if (pos.z > PlayerPos.z + 200.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy000_BRAKE));
	}
	else if (pos.z < PlayerPos.z + 200.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, Enemy000_BRAKE));
	}

	if (pos.x > PlayerPos.x)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(-Enemy000_BEND, 0.0f, 0.0f));
	}
	else
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(Enemy000_BEND, 0.0f, 0.0f));
	}

	// 一定時間並走したら攻撃する
	float fLeng = 0.0f;
	{
		float X = pos.x - PlayerPos.x;
		float Z = pos.z - PlayerPos.z;
		fLeng = sqrtf(Z * Z + X * X);
	}
	
	if (fLeng < 300.0f)
	{// 300.0f以内にEnemy000_ATTACフレームいたら攻撃する
		m_nCntAttac--;
		if (m_nCntAttac <= 0)
		{
			return new CActivity_Enemy000_Tackle(m_pPrimary, m_nCntSurvival);
		}
	}
	else
	{
		if (m_nCntAttac < Enemy000_ATTAC)
		{// カウントが最大以下なら増やす
			m_nCntAttac++;
		}
	}

#endif // EnemyMove
	// 当たり判定
	CObject* pTopObject[MAX_PRIORITY];
	CObject::GetAllObject(pTopObject);
	CObject* objrct = nullptr;
	CObject* Nextobjrct = nullptr;

	D3DXVECTOR3 enemypos = m_pPrimary->GetPos();
	D3DXVECTOR3 enemysiz = m_pPrimary->GetCollisionSiz();
	// プライオリティ
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		objrct = pTopObject[nCntPriority];	// オブジェクト格納
		while (objrct != nullptr)
		{
			// 種類が一致していたら
			Nextobjrct = objrct->GetNext();
			if (objrct->GetType() == CObject::TYPE::PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)objrct;
				D3DXVECTOR3 playerpos = pPlayer->GetPos();
				D3DXVECTOR3 playerSiz = pPlayer->GetCollisionSiz();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(playerpos.x, playerpos.y, playerpos.z), halfWidths1(playerSiz.x, playerSiz.y, playerSiz.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(enemypos.x, enemypos.y, enemypos.z), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixIdentity(&rotation2); // 回転なし
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転
				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);
				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{
#if 0
					//std::cout << "OBBは交差しています！" << std::endl;
					D3DXVECTOR3 ShockRot = D3DXVECTOR3(
						atan2(enemypos.x, playerpos.x),
						atan2(enemypos.y, playerpos.y),
						atan2(enemypos.z, playerpos.z));
					D3DXVECTOR3 Normalize;
					D3DXVec3Normalize(&Normalize, &ShockRot);

					pPlayer->Hit(Normalize * 10.0f, 60, m_pPrimary->GetAttcak());
#else
					CManager* pInstance = CManager::GetInstance();
					CSound* pSound = pInstance->GetSound();
					if (pSound->IsPlaySound(CSound::SOUND_LABEL::SOUND_BEEP) == false)
					{
						pSound->PlaySound(CSound::SOUND_LABEL::SOUND_BEEP);
					}
#endif
				}
				else
				{
					CManager* pInstance = CManager::GetInstance();
					CSound* pSound = pInstance->GetSound();
					//std::cout << "OBBは交差していません。" << std::endl;
					if (pSound->IsPlaySound(CSound::SOUND_LABEL::SOUND_BEEP) == true)
					{
						pSound->StopSound(CSound::SOUND_LABEL::SOUND_BEEP);
					}
				}
			}
			objrct = Nextobjrct;
		}
	}
	//// 生存時間を削る
	//auto p = DeathCnt();
	//if (p != this)
	//{
	//	return p;
	//}

	return this;
}
//===========================================
// 行動タックルコンスト
//============================================
CEnemy000::CActivity_Enemy000_Tackle::CActivity_Enemy000_Tackle(CEnemy000* p, int nS) :
	CActivity_Enemy000(p, nS)
{
	m_nCnt = Enemy000_ATTAC_COOL_DOWN;

	CPlayer* player = nullptr;
	if (p->GetTarget() != nullptr)
	{
		if (p->GetTarget()->GetType() == PLAYER)
		{
			player = (CPlayer*)p->GetTarget();
		}
		D3DXVECTOR3 pos = p->GetPos();
		D3DXVECTOR3 posPlayer = player->GetPos();


		float fAngle = atan2f(posPlayer.z - pos.z, posPlayer.x - pos.x);
		m_Move.x = cosf(fAngle) * Enemy000_BOOST;
		m_Move.z = sinf(fAngle) * Enemy000_BOOST;
	}
	m_pEffect = CEffectGeneratorPaeticle::creat(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		15.0f,
		7.0f,
		D3DXCOLOR(0.0f, 0.1f, 1.0f, 1.0f),
		5,
		1,
		PLAYER_ATTAC
	);
}
//============================================
// 行動タックル更新
//============================================
CEnemy000::CActivity_Enemy000* CEnemy000::CActivity_Enemy000_Tackle::update()
{
	if (m_nCnt > 0)
	{
		m_nCnt--;

		m_pPrimary->AddMovePos(m_Move);
	}
	else
	{
		return new CActivity_Enemy000_Following(m_pPrimary, m_nCntSurvival);
	}
	// 当たり判定
	CObject* pTopObject[MAX_PRIORITY];
	CObject::GetAllObject(pTopObject);
	CObject* objrct = nullptr;
	CObject* Nextobjrct = nullptr;

	D3DXVECTOR3 enemypos = m_pPrimary->GetPos();
	D3DXVECTOR3 enemysiz = m_pPrimary->GetCollisionSiz();
	// プライオリティ
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		objrct = pTopObject[nCntPriority];	// オブジェクト格納
		while (objrct != nullptr)
		{
			// 種類が一致していたら
			Nextobjrct = objrct->GetNext();
			if (objrct->GetType() == CObject::TYPE::PLAYER)
			{
				CPlayer* pPlayer = (CPlayer*)objrct;
				D3DXVECTOR3 playerpos = pPlayer->GetPos();
				D3DXVECTOR3 playerSiz = pPlayer->GetCollisionSiz();
				// OBB1とOBB2を初期化
				D3DXVECTOR3 center1(playerpos.x, playerpos.y, playerpos.z), halfWidths1(playerSiz.x, playerSiz.y, playerSiz.z);  // 敵の中心点とサイズ
				D3DXVECTOR3 center2(enemypos.x, enemypos.y, enemypos.z), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転
				OBB obb1(center1, halfWidths1, rotation1);
				OBB obb2(center2, halfWidths2, rotation2);
				// 衝突判定
				if (obb1.CheckOverlap(obb2))
				{
					//std::cout << "OBBは交差しています！" << std::endl;
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
					//std::cout << "OBBは交差していません。" << std::endl;
				}
			}
			objrct = Nextobjrct;
		}
	}
	// 生存時間を削る
	auto p = DeathCnt();
	if (p != this)
	{
		return p;
	}

	return this;
}
//============================================
// 行動死亡コンストラクタ
//============================================
CEnemy000::CActivity_Enemy000_Death::CActivity_Enemy000_Death(CEnemy000* p):
	CActivity_Enemy000(p, 0)
{
	m_nCntDeath = Enemy000_DEATHCNT;
}
//============================================
// 行動死亡更新
//============================================
CEnemy000::CActivity_Enemy000* CEnemy000::CActivity_Enemy000_Death::update()
{
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy000_BOOST));
	if (m_nCntDeath > 0)
	{
		m_nCntDeath--;
	}
	else
	{
		m_pPrimary->DeathFlag();
	}
	return this;
}
//============================================
// 行動基底コンスト
//============================================
CEnemy000* CEnemy000::creat(D3DXVECTOR3 pos)
{
	CEnemy000* pEnemy000 = new CEnemy000();
	pEnemy000->SetPos(pos);
	pEnemy000->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	pEnemy000->Init();
	return pEnemy000;
}