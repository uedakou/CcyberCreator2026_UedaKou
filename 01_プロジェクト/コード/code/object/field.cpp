//===========================================
// 
// �n��[field.cpp]
// Auther:UedaKou
// 
//===========================================
#include "field.h"	// �t�B�[���h
#include "player.h"	// �v���[���[
//============================================
// �R���X�g���N�^
//============================================
CField::CField():
	m_player(nullptr)
{
	SetType(FIELD);
}
//============================================
// �f�X�g���N�^
//============================================
CField::~CField()
{
}
//============================================
// ������
//============================================
void CField::Init()
{
	SetType(CObject::TYPE::FIELD);
	CObject3D::Init();
}
//============================================
// �I��
//============================================
void CField::Uninit()
{
	CObject3D::Uninit();
}
//============================================
// �X�V
//============================================
void CField::Update()
{
	CObject3D::Update();
}
//============================================
// �`��
//============================================
void CField::Draw()
{
	CObject3D::Draw();
}
//============================================
// ����
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