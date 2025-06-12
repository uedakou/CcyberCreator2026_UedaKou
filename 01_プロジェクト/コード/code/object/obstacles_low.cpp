//============================================
//
// 障害物(toll)[obstacles_toll.cpp]
// Author:Uedakou
// 
//============================================
#include "obstacles_low.h"// ロウオブジェクト
#include "player.h"

/// <summary>
/// デストラクタ
/// </summary>
CObstaclesLow::~CObstaclesLow()
{
}
/// <summary>
/// 初期化
/// </summary>
void CObstaclesLow::Init()
{
	CObstacles::Init();
}
/// <summary>
/// 終了
/// </summary>
void CObstaclesLow::Uninit()
{
	CObstacles::Uninit();
}
/// <summary>
/// 更新
/// </summary>
void CObstaclesLow::Update()
{
	CObstacles::Update();
}
/// <summary>
/// 描画
/// </summary>
void CObstaclesLow::Draw()
{
	CObstacles::Draw();
}
/// <summary>
/// 当たり判定
/// </summary>
void CObstaclesLow::HitTest()
{
	CObject* pObject[MAX_PRIORITY];
	CObject* pNext = nullptr;
	CObject::GetAllObject(pObject);
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		while (pObject[nCnt] != nullptr)
		{
			pNext = pObject[nCnt]->GetNext();
			CPlayer* player = dynamic_cast<CPlayer*>(pObject[nCnt]);
			if (player)
			{
				D3DXVECTOR3 PLpos = player->GetPos();
				D3DXVECTOR3 PLcol = player->GetCollisionSiz();
				D3DXVECTOR3 pos = GetPos();
				if (PLpos.z + PLcol.z * 0.5f > pos.z - s_Collision.z * 0.5f &&
					PLpos.z - PLcol.z * 0.5f < pos.z + s_Collision.z * 0.5f &&
					PLpos.x + PLcol.x * 0.5f > pos.x - s_Collision.x * 0.5f &&
					PLpos.x - PLcol.x * 0.5f < pos.x + s_Collision.x * 0.5f)
				{
					if (player->IsJanp() != true)
					{
						player->Hit(1);
					}
				}
			}
			pObject[nCnt] = pNext;
		}
	}
}
/// <summary>
/// 生成
/// </summary>
/// <param name="pos">生成位置</param>
/// <returns>生成したオブジェクト</returns>
CObstaclesLow* CObstaclesLow::clate(D3DXVECTOR3 pos)
{
	CObstaclesLow* pLow = new CObstaclesLow();

	pLow->SetPos(pos);
	pLow->Init();	/// 初期化

	return pLow;
}
CObstaclesLow* CObstaclesLow::clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObstaclesLow* pLow = new CObstaclesLow();

	pLow->SetPos(pos);
	pLow->SetRot(rot);
	pLow->Init();	/// 初期化

	return pLow;
}
/// <summary>
/// コンストラクタ
/// </summary>
CObstaclesLow::CObstaclesLow()
{
	SetID(CModelX::Load("data/MODEL/Obstacles/Obstacles_Low/000/Obstacles_Low_000.x"));
}