//============================================
//
// 敵100[enemy100.cpp]
// Author:Uedakou
// 
//============================================
#include "enemy100.h"	// 敵100
#include "enemy000.h"	// 敵000
#include "player.h"		// プレイヤー
#include "../collision/obb.h"
#include "../base_object/effect_generator_particle.h"	// エフェクトパーティクル
#include "life_3d.h"

#define Enemy_100_Move true
//============================================
// コンスト
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
}
//============================================
// デストラクタ
//============================================
CEnemy100::~CEnemy100()
{
	if (m_pActivity != nullptr)
	{
		delete m_pActivity;
	}
}
//============================================
// 初期化
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
	CEnemy::SetType(CEnemy::ENEMY_TYPE::Enemy100);
}
//============================================
// 終了処理
//============================================
void CEnemy100::Uninit()
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
		m_pLife3D->SetPos(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z));
	}
	CEnemy::Update();
	if (m_pEffect != nullptr)
	{
		m_pEffect->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z - 100.0f));
	}
}
//============================================
// 描画
//============================================
void CEnemy100::Draw()
{
	CEnemy::Draw();
}
//============================================
// 次モーション取得
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
// 生成
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
// 基底
//============================================
CEnemy100::CActivity_Enemy100::CActivity_Enemy100(CEnemy100* p)
{
	m_pPrimary = p;
}
//============================================
// 索敵
//============================================
CEnemy100::CActivity_Enemy100_Search::CActivity_Enemy100_Search(CEnemy100* p):
	CActivity_Enemy100(p){}
CEnemy100::CActivity_Enemy100_Search::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Search::update()
{
	// プレイヤーを探す
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
				// プレイヤーを見つけたら次のUpdateに移行
				return new CActivity_Enemy100_Following(m_pPrimary);
			}
			pObject = pNext;
		}
	}
	return this;
}
//============================================
// 追跡
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
	// 常時移動
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, Enemy100_SPEED));
#endif // Enemy_100_Move

	// 並ぶ
	CObject* pObject = m_pPrimary->GetTarget();	// ターゲット取得
	D3DXVECTOR3 PlayerPos = ((CPlayer*)pObject)->GetPos();	// ターゲット位置取得
	D3DXVECTOR3 pos = m_pPrimary->GetPos();	// 自身位置取得
	// プレイヤーの前に並ぶ
	// 前後
	if (pos.z > PlayerPos.z + 1000.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy100_BRAKE));
	}
	else if (pos.z < PlayerPos.z + 1000.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, Enemy100_BRAKE));
	}
	// 左右
	if (PlayerPos.x - pos.x > 0.0f)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, Enemy100_BEND));
	}
	else
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy100_BEND));
	}
	// 攻撃する
	float fLeng = atan2f(PlayerPos.z - pos.z, PlayerPos.x - pos.x);
	if (fLeng < 200.0f)
	{// 200.0f以内にEnemy000_ATTACフレームいたら攻撃する
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
				D3DXVECTOR3 center2(enemypos + m_pPrimary->GetCollisionPos()), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixIdentity(&rotation2); // 回転なし
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転
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

					pPlayer->Hit(Normalize * 10.0f, 60, m_pPrimary->GetAttcak());
				}
				else
				{
					//std::cout << "OBBは交差していません。" << std::endl;
				}
			}
			objrct = Nextobjrct;
		}
	}
	return this;
}
//============================================
// タックル
//============================================
// タックル下がる
CEnemy100::CActivity_Enemy100_Tackle_000::CActivity_Enemy100_Tackle_000(CEnemy100* p):
	CActivity_Enemy100(p),
	m_MaxCnt(30)
{
	m_nCnt = 0;
}
CEnemy100::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Tackle_000::update()
{
#if Enemy_100_Move
	// 常時移動
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, Enemy100_SPEED));
#endif // Enemy_100_Move


	CObject* pObject = m_pPrimary->GetTarget(); // ターゲット取得
	D3DXVECTOR3 PlayerPos = ((CPlayer*)pObject)->GetPos();	// ターゲット位置取得
	D3DXVECTOR3 pos = m_pPrimary->GetPos();	// 自身位置取得
	// プレイヤーの前後をそろえる
	if (pos.z > PlayerPos.z)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, -Enemy100_BOOST));
	}
	else if (pos.z < PlayerPos.z)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0f, Enemy100_BOOST));
	}
	m_nCnt++;
	// 時間を過ぎたら次のUpdateに移行
	if (m_nCnt > m_MaxCnt)
	{
		return new CActivity_Enemy100_Tackle_001(m_pPrimary);
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
				D3DXVECTOR3 center2(enemypos + m_pPrimary->GetCollisionPos()), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixIdentity(&rotation2); // 回転なし
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転
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
	return this;
}
// タックル左右につぶす
CEnemy100::CActivity_Enemy100_Tackle_001::CActivity_Enemy100_Tackle_001(CEnemy100* p) : 
	CActivity_Enemy100(p),
	m_MaxCnt(30)
{
	m_nCnt = 0;
}
CEnemy100::CActivity_Enemy100* CEnemy100::CActivity_Enemy100_Tackle_001::update()
{
#if Enemy_100_Move
	// 常時移動
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, Enemy100_SPEED));
#endif // Enemy_100_Move

	CObject* pObject = m_pPrimary->GetTarget(); // ターゲット取得
	D3DXVECTOR3 PlayerPos = ((CPlayer*)pObject)->GetPos();	// ターゲット位置取得
	D3DXVECTOR3 pos = m_pPrimary->GetPos();	// 自身位置取得
	// プレイヤーの左右をそろえる
	if (pos.x > PlayerPos.x)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(-Enemy100_BOOST, 0.0f, 0.0f));
	}
	else if (pos.x < PlayerPos.x)
	{
		m_pPrimary->AddMovePos(D3DXVECTOR3(Enemy100_BOOST, 0.0f, 0.0f));
	}
	m_nCnt++;
	// 時間を過ぎたら次のUpdateに移行
	if (m_nCnt > m_MaxCnt)
	{
		return new CActivity_Enemy100_Following(m_pPrimary);
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
				D3DXVECTOR3 center2(enemypos + m_pPrimary->GetCollisionPos()), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixIdentity(&rotation2); // 回転なし
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転
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
	return this;
}
//============================================
// 召喚
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
	// 常時移動
	m_pPrimary->AddMovePos(D3DXVECTOR3(0.0f, 0.0, Enemy100_SPEED));
#endif // Enemy_100_Move

	D3DXVECTOR3 pos = m_pPrimary->GetPos();
	m_nCnt++;

	//if (m_nCnt == 15)
	//{
	//	CEnemy000::creat(D3DXVECTOR3(pos.x, 0.0f, pos.z - 10.0f));
	//}


	// 時間を過ぎたら次のUpdateに移行
	if (m_nCnt > m_MaxCnt)
	{
		CEnemy000::creat(D3DXVECTOR3(pos.x, 0.0f, pos.z - 10.0f));

		return new CActivity_Enemy100_Following(m_pPrimary);
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
				D3DXVECTOR3 center2(enemypos + m_pPrimary->GetCollisionPos()), halfWidths2(enemysiz.x, enemysiz.y, enemysiz.z);  // プレイヤーの中心点とサイズ

				D3DXMATRIX rotation1, rotation2;
				D3DXMatrixIdentity(&rotation1); // 回転なし
				D3DXMatrixIdentity(&rotation2); // 回転なし
				//D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転
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
	return this;
}
//============================================
// 死亡
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
		m_pPrimary->DeathFlag();
	}
	return this;
}