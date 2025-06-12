//============================================
//
// アイテム(巻物)[scroll.cpp]
// Author:Uedakou
// 
//============================================
#include "scroll.h"	// トールオブジェクト
#include "player.h"	// プレイヤー

const D3DXVECTOR3 CScroll::s_Collision = { 100.0f, 100.0f, 200.0f };
/// <summary>
/// デストラクタ
/// </summary>
CScroll::~CScroll()
{
}
/// <summary>
/// 初期化
/// </summary>
void CScroll::Init()
{
	CObjectX::Init();
}
/// <summary>
/// 終了
/// </summary>
void CScroll::Uninit()
{
	CObjectX::Update();
}
/// <summary>
/// 更新
/// </summary>
void CScroll::Update()
{
	AddRotY(0.1f);
	CObjectX::Update();
}
/// <summary>
/// 描画
/// </summary>
void CScroll::Draw()
{
	CObjectX::Draw();
}
/// <summary>
/// 生成
/// </summary>
/// <param name="pos">生成位置</param>
/// <returns>生成下障害物</returns>
CScroll* CScroll::clate(D3DXVECTOR3 pos)
{
	CScroll* pToll = new CScroll();

	pToll->SetPos(pos);
	pToll->Init();	/// 初期化

	return pToll;
}
CScroll* CScroll::clate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CScroll* pToll = new CScroll();

	pToll->SetPos(pos);
	pToll->SetRot(rot);
	pToll->Init();	/// 初期化

	return pToll;
}
/// <summary>
/// コンストラクタ
/// </summary>
CScroll::CScroll()
{
	SetID(CModelX::Load("data/MODEL/Scroll/Scroll_000.x"));
}