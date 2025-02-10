//===========================================
// 
// 地面[field.cpp]
// Auther:UedaKou
// 
//===========================================
#include "field.h"	// フィールド
#include "player.h"	// プレーヤー
//============================================
// コンストラクタ
//============================================
CField::CField():
	m_player(nullptr)
{
	SetType(FIELD);
}
//============================================
// デストラクタ
//============================================
CField::~CField()
{
}
//============================================
// 初期化
//============================================
void CField::Init()
{
	SetType(CObject::TYPE::FIELD);
	CObject3D::Init();
}
//============================================
// 終了
//============================================
void CField::Uninit()
{
	CObject3D::Uninit();
}
//============================================
// 更新
//============================================
void CField::Update()
{
	CObject3D::Update();
}
//============================================
// 描画
//============================================
void CField::Draw()
{
	CObject3D::Draw();
}
//============================================
// 生成
//============================================
CField* CField::creat(TYPE m_type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz)
{
	CField* pField = new CField();

	pField->SetX(pos, rot, siz);

	pField->Init();

	switch (m_type)
	{
	case TYPE::Null:
		break;
	case TYPE::Road:
		pField->CObject3D::SetTexture("data\\TEXTURE\\AsphaltLoad000.png");
		break;
	case TYPE::Grass:
		pField->CObject3D::SetTexture("data\\TEXTURE\\Glass000.png");
		break;

	default:
		break;
	}

	return pField;
}