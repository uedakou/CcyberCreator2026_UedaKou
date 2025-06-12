//=================================
// 
// 有向境界ボックス クラス　obb.h
//outher kida ibuki 
// 
//==================================
#ifndef _OBB_H_
#define _OBB_H_
#include "../../base/pch.h"

class OBB
{
public:
	OBB(const D3DXVECTOR3& center, const D3DXVECTOR3& halfwidths, const D3DXMATRIX& rotationMatrix);
	D3DXVECTOR3 GetCenter() const { return center; }  // 中心を取得
	D3DXVECTOR3 GetAxis(int index) const { return axes[index]; }  // 軸を取得
	D3DXVECTOR3 GetHalfwidths() const { return halfWidths; }      // 半幅を取得
	D3DXVECTOR3 GetVertex(int index) const;   // 頂点を取得
	bool CheckOverlap(const OBB& other) const;  // OBB同士の衝突判定
private:
	float ProjectOntoAxis(const D3DXVECTOR3& axis) const;   // 指定軸への投影距離を計算

	D3DXVECTOR3 center;   // 中心位置
	D3DXVECTOR3 axes[3];  // ローカル軸(x,y,z)
	D3DXVECTOR3 halfWidths;  // 各軸方向の半分の長さ

};

#endif