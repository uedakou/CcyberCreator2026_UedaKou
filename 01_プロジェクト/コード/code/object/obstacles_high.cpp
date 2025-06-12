//============================================
//
// 障害物(toll)[obstacles_toll.cpp]
// Author:Uedakou
// 
//============================================
#include "obstacles_high.h"// ハイドオブジェクト
#include "player.h"
/// <summary>
/// デストラクタ
/// </summary>
CObstaclesHigh::~CObstaclesHigh()
{
}
/// <summary>
/// 初期化
/// </summary>
void CObstaclesHigh::Init()
{
	CObstacles::Init();
}
/// <summary>
/// 終了
/// </summary>
void CObstaclesHigh::Uninit()
{
	CObstacles::Uninit();
}
/// <summary>
/// 更新
/// </summary>
void CObstaclesHigh::Update()
{
	CObstacles::Update();
}
/// <summary>
/// 描画
/// </summary>
void CObstaclesHigh::Draw()
{
	CObstacles::Draw();
}
/// <summary>
/// 当たり判定
/// </summary>
void CObstaclesHigh::HitTest()
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
					if (player->IsSliding() != true)
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
CObstaclesHigh* CObstaclesHigh::clate(D3DXVECTOR3 pos)
{
	CObstaclesHigh* pHigh = new CObstaclesHigh();

	pHigh->SetPos(pos);
	pHigh->Init();	/// 初期化

	return pHigh;
}
CObstaclesHigh* CObstaclesHigh::clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObstaclesHigh* pHigh = new CObstaclesHigh();

	pHigh->SetPos(pos);
	pHigh->SetRot(rot);
	pHigh->Init();	/// 初期化

	return pHigh;
}
/// <summary>
/// コンストラクタ
/// </summary>
CObstaclesHigh::CObstaclesHigh()
{
	SetID(CModelX::Load("data/MODEL/Obstacles/Obstacles_High/000/Obstacles_High_000.x"));
}