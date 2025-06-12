//=================================
// 
// 有向境界ボックス クラス　obb.cpp
//outher kida ibuki 
// 
//==================================

#include "obb.h"
//========================================
// コンストラクタ
//========================================
OBB::OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfWidths, const D3DXMATRIX& rotationMatrix)
{
	this->center = center;
	this->halfWidths = halfWidths;

	// 回転行列からローカル軸を設定
	axes[0] = D3DXVECTOR3(rotationMatrix._11, rotationMatrix._12, rotationMatrix._13);  // x軸
	axes[1] = D3DXVECTOR3(rotationMatrix._21, rotationMatrix._22, rotationMatrix._23);  // y軸
	axes[2] = D3DXVECTOR3(rotationMatrix._31, rotationMatrix._32, rotationMatrix._33);  // z軸

}
//========================================
// 頂点を取得
//========================================
D3DXVECTOR3 OBB::GetVertex(int index) const
{
	D3DXVECTOR3 vertex = center;

	int signX = (index & 1) ? 1 : -1;
	int signY = (index & 2) ? 1 : -1;
	int signZ = (index & 4) ? 1 : -1;

	vertex += axes[0] * (signX * halfWidths.x);
	vertex += axes[1] * (signY * halfWidths.y);
	vertex += axes[2] * (signZ * halfWidths.z);

	return vertex;
}
//========================================
// OBB同士の衝突判定
//========================================
bool OBB::CheckOverlap(const OBB& other) const
{
    D3DXVECTOR3 axesToTest[15];
    int axisIndex = 0;

    // 自身と他のOBBの軸
    for (int i = 0; i < 3; ++i) 
    {
        axesToTest[axisIndex++] = axes[i];
        axesToTest[axisIndex++] = other.axes[i];
    }

    // 軸のクロス積
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j) 
        {
            D3DXVECTOR3 crossAxis;
            D3DXVec3Cross(&crossAxis, &axes[i], &other.axes[j]);
            if (D3DXVec3Length(&crossAxis) > 0.0001f)
            { // 有効な軸
                axesToTest[axisIndex++] = crossAxis;
            }
        }
    }

    // 中心間の距離
    D3DXVECTOR3 t = other.center - center;

    // 分離軸ごとに判定
    for (int i = 0; i < axisIndex; ++i)
    {
        const D3DXVECTOR3& axis = axesToTest[i];
        D3DXVECTOR3 normAxis;
        D3DXVec3Normalize(&normAxis, &axis);

        // 各OBBを軸に投影
        float projection1 = ProjectOntoAxis(normAxis);
        float projection2 = other.ProjectOntoAxis(normAxis);
        float centerDistance = fabs(D3DXVec3Dot(&t, &normAxis));

        // 投影が分離している場合
        if (centerDistance > projection1 + projection2)
        {
            return false;
        }
    }

    return true;  // 分離していない -> 衝突
}
//========================================
// 指定軸への投影距離を計算
//========================================
float OBB::ProjectOntoAxis(const D3DXVECTOR3& axis) const
{
    return fabs(D3DXVec3Dot(&axes[0], &axis) * halfWidths.x) +
        fabs(D3DXVec3Dot(&axes[1], &axis) * halfWidths.y) +
        fabs(D3DXVec3Dot(&axes[2], &axis) * halfWidths.z);
}

#if 0
// 使い方
CObject* pTopObject[NUM_MAX_PRIORITY];
CObject::GetObj(pTopObject);
for (int nPriority = 0; nPriority < NUM_MAX_PRIORITY; nPriority++)
{
	//オブジェクト取得
	CObject* pObj = pTopObject[nPriority];

	//種類の取得
	while (pObj != nullptr)
	{
		CObject::TYPE type = pObj->GetType();
		CObject* pNext = pObj->GetNext(); // 次のポインタを取得
		if (type == CObject::TYPE::ENEMY_X)
		{
			CEnemyX* pEnemy = (CEnemyX*)pObj; //ダウンキャスト
			D3DXVECTOR3 enemyPos = pEnemy->GetPos();
			D3DXVECTOR3 enemySize = pEnemy->GetSize();
			// OBB1とOBB2を初期化
			D3DXVECTOR3 center1(enemyPos.x, enemyPos.y, enemyPos.z), halfWidths1(enemySize.x, enemySize.y, enemySize.z);  // 敵の中心点とサイズ
			D3DXVECTOR3 center2(m_pos.x, m_pos.y, m_pos.z), halfWidths2(m_size.x, m_size.y, m_size.z);  // プレイヤーの中心点とサイズ

			D3DXMATRIX rotation1, rotation2;
			D3DXMatrixIdentity(&rotation1); // 回転なし
			D3DXMatrixRotationY(&rotation2, D3DXToRadian(45)); // 45度回転

			OBB obb1(center1, halfWidths1, rotation1);
			OBB obb2(center2, halfWidths2, rotation2);

			// 衝突判定
			if (obb1.CheckOverlap(obb2))
			{
				//std::cout << "OBBは交差しています！" << std::endl;
			}
			else
			{
				//std::cout << "OBBは交差していません。" << std::endl;
			}

		}

		pObj = pNext; // オブジェクトのポインタを次に進める
	}
}


#endif