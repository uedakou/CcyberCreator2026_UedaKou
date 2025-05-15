//===========================================
// 
// 2D表示ライフ[life_3d.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _LIFE_3D_
#define _LIFE_3D_
#include "../base_object/object_billboard.h"
#include "../base_object/text.h"

class CLife_3D : public CObjectBillbord
{
public:
	CLife_3D();
	~CLife_3D();
	void Init()		override;	// 初期化
	void Uninit()	override;	// 終了
	void Update()	override;	// 更新
	void Draw()		override;	// 描画
	void SetX(X pos) { CObjectBillbord::SetX(pos); }				// 位置設定
	void SetPos(D3DXVECTOR3 pos) { CObjectBillbord::SetPos(pos); }	// 位置設定

	void SetLifeOld(int nLifeOld) { m_nLifeOld = nLifeOld; }	// 1f前体力設定
	void SetLife(int nLife) { m_nLife = nLife; }				// 体力設定
	void SetMaxLife(int nMaxLife) { m_nMaxLife = nMaxLife; }	// 最大体力設定

	static CLife_3D* creat(D3DXVECTOR3 pos, int nLife);		// 生成
private:
	CObjectBillbord* m_lifeBG;	// 背景
	int m_nLifeOld;		// 1f前の体力
	int m_nLife;		// 現在体力
	int m_nMaxLife;		// 最大体力
	CText* m_pText;		// テキスト
	D3DXVECTOR3 posOld;	// 1f前の位置
};





#endif // _LIFE_3D_