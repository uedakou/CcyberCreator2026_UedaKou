//============================================
//
// 障害物(toll)[obstacles_toll.cpp]
// Author:Uedakou
// 
//============================================
#include "obstacles_tall.h"	// トールオブジェクト
#include "player.h"

/// <summary>
/// デストラクタ
/// </summary>
CObstaclesToll::~CObstaclesToll()
{
}
/// <summary>
/// 初期化
/// </summary>
void CObstaclesToll::Init()
{
	CObstacles::Init();
}
/// <summary>
/// 終了
/// </summary>
void CObstaclesToll::Uninit()
{
	CObstacles::Update();
}
/// <summary>
/// 更新
/// </summary>
void CObstaclesToll::Update()
{
	CObstacles::Update();
}
/// <summary>
/// 描画
/// </summary>
void CObstaclesToll::Draw()
{
	CObstacles::Draw();
}
/// <summary>
/// 当たり判定
/// </summary>
void CObstaclesToll::HitTest()
{
	CObject* pObject[MAX_PRIORITY];
	CObject* pNext = nullptr;
	CObject::GetAllObject(pObject);
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		while (pObject[nCnt] != nullptr)
		{
			pNext = pObject[nCnt]->GetNext();
			if (CPlayer* player = dynamic_cast<CPlayer*>(pObject[nCnt]))
			{
				D3DXVECTOR3 PLpos = player->GetPos();
				D3DXVECTOR3 PLcol = player->GetCollisionSiz();
				D3DXVECTOR3 pos = GetPos();

				if (PLpos.z + PLcol.z * 0.5f > pos.z - s_Collision.z * 0.5f &&
					PLpos.z - PLcol.z * 0.5f < pos.z + s_Collision.z * 0.5f &&
					PLpos.x + PLcol.x * 0.5f > pos.x - s_Collision.x * 0.5f &&
					PLpos.x - PLcol.x * 0.5f < pos.x + s_Collision.x * 0.5f)
				{
					player->Hit(1);
				}
				break;
			}
			pObject[nCnt] = pNext;
		}
	}
}
/// <summary>
/// 生成
/// </summary>
/// <param name="pos">生成位置</param>
/// <returns>生成下障害物</returns>
CObstaclesToll* CObstaclesToll::clate(D3DXVECTOR3 pos)
{
	CObstaclesToll* pToll = new CObstaclesToll();

	pToll->SetPos(pos);
	pToll->Init();	/// 初期化

	return pToll;
}
CObstaclesToll* CObstaclesToll::clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObstaclesToll* pToll = new CObstaclesToll();

	pToll->SetPos(pos);
	pToll->SetRot(rot);
	pToll->Init();	/// 初期化

	return pToll;
}
/// <summary>
/// コンストラクタ
/// </summary>
CObstaclesToll::CObstaclesToll()
{
	SetID(CModelX::Load("data/MODEL/Obstacles/Obstacles_Tall/Obstacles_Tall_000.x"));
}