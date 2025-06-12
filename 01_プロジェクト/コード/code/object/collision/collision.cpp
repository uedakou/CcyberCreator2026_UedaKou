//============================================
//
// 当たり判定[collision.cpp]
// Author:Uedakou
// 
//============================================
#include "collision.h"
#include "../../base/manager.h"	// マネージャー
#define OBB false

CCollision::CCollision()
{
	m_type = TYPE::TYPE_2D;
}
CCollision::CCollision(TYPE type)
{
	m_type = type;
}
CCollision::~CCollision()
{
}

bool CCollision::Hit(D3DXVECTOR3 pos0, D3DXVECTOR3 collision0, D3DXVECTOR3 pos1, D3DXVECTOR3 collision1)
{
	CManager* Instance = CManager::GetInstance();
	CSound* Sound = Instance->GetSound();
#if OBB
// OBBなら

#else
// OBBでないなら
	{
		float Col0XA = pos0.x + (collision0.x * 0.5f);
		float Col0XS = pos0.x - (collision0.x * 0.5f);
		float Col0YA = pos0.y + (collision0.y * 0.5f);
		float Col0YS = pos0.y - (collision0.y * 0.5f);
		float Col0ZA = pos0.z + (collision0.z * 0.5f);
		float Col0ZS = pos0.z - (collision0.z * 0.5f);

		float Col1XA = pos1.x - (collision1.x * 0.5f);
		float Col1XS = pos1.x + (collision1.x * 0.5f);
		float Col1YA = pos1.y - (collision1.y * 0.5f);
		float Col1YS = pos1.y + (collision1.y * 0.5f);
		float Col1ZA = pos1.z - (collision1.z * 0.5f);
		float Col1ZS = pos1.z + (collision1.z * 0.5f);

		if (Col0XA > Col1XA &&
			Col0XS < Col1XS &&
			Col0YA > Col1YA &&
			Col0YS < Col1YS &&
			Col0ZA > Col1ZA &&
			Col0ZS < Col1ZS)
		{
			return true;
		}
	}

#endif // OBB

	return false;
}


