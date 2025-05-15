//===========================================
// 
// 2D�\�����C�t[life_2d.cpp]
// Auther:UedaKou
// 
//===========================================
#include "life_2d.h"

//============================================
// �R���X�g
//============================================
CLife_2D::CLife_2D() :
	CObject2D(4)
{
	lifeBG = nullptr;
	m_nLifeOld = 0;
	m_nLife = 0;
	m_nMaxLife = 0;
	//m_pText = CText::creat();
	//CObject::SetUpdate(false);
}
CLife_2D::CLife_2D(int nPriorith) :
	CObject2D(nPriorith)
{
	lifeBG = nullptr;
	m_nLifeOld = 0;
	m_nLife = 0;
	m_nMaxLife = 0;
	//m_pText = CText::creat();
	//CObject::SetUpdate(false);
}
//============================================
// �f�X�g���N�^
//============================================
CLife_2D::~CLife_2D()
{
}
//============================================
// ������
//============================================
void CLife_2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// �f�o�C�X�ւ̃|�C���^
	CObject2D::Init();
	auto pVtxBuff = GetVtxBuff();
	auto pCor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	auto pX = GetX();
	D3DXVECTOR3 siz = GetSiz();

	VERTEX_2D* pVtx;		// ���_���ւ̃|�C���^
	// ���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�X�V
	pVtx[0].pos = D3DXVECTOR3(pX.pos.x						, pX.pos.y - (siz.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pX.pos.x + (siz.x * m_nLife)	, pX.pos.y - (siz.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pX.pos.x						, pX.pos.y + (siz.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pX.pos.x + (siz.x * m_nLife)	, pX.pos.y + (siz.y * 0.5f), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�ݒ�
	pVtx[0].col = pCor;
	pVtx[1].col = pCor;
	pVtx[2].col = pCor;
	pVtx[3].col = pCor;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�����b�N
	pVtxBuff->Unlock();

	SetColor(pCor);

	// �̗͔w���
	lifeBG = CObject2D::creat(D3DXVECTOR3(pX.pos.x + (siz.x * m_nMaxLife * 0.5f), pX.pos.y, 0.0f), D3DXVECTOR3(siz.x * m_nMaxLife, siz.y, 0.0f));	// ����
	lifeBG->SetNormalUpdate(false);	// �ʏ�X�V����߂�
	lifeBG->SetReleaseScene(false);	// �V�[�������[�X����߂�
}
//============================================
// �I��
//============================================
void CLife_2D::Uninit()
{
	CObject2D::Uninit();
	// �̗͔w����
	if (lifeBG != nullptr)
	{
		lifeBG->Release();
		lifeBG = nullptr;
	}

}
//============================================
// ������
//============================================
void CLife_2D::Update()
{
	// ���C�t���ϓ����Ă�����
	if (m_nLife != m_nLifeOld)
	{

		auto pVtxBuff = GetVtxBuff();	// �o�b�t�@�擾
		auto pX = GetX();	// �g�����X�t�H�[������
		D3DXVECTOR3 siz = GetSiz();	// �T�C�Y�擾
		VERTEX_2D* pVtx;		// ���_���ւ̃|�C���^


		// ���_�o�b�t�@�����b�N
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�X�V
		pVtx[0].pos = D3DXVECTOR3(pX.pos.x						, pX.pos.y - (siz.y * 0.5f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pX.pos.x + (siz.x * m_nLife)	, pX.pos.y - (siz.y * 0.5f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pX.pos.x						, pX.pos.y + (siz.y * 0.5f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pX.pos.x + (siz.x * m_nLife)	, pX.pos.y + (siz.y * 0.5f), 0.0f);

		// ���_�o�b�t�@�����b�N
		pVtxBuff->Unlock();

		m_nLifeOld = m_nLife;
	}
	CObject2D::Update();
}
//============================================
// �`��
//============================================
void CLife_2D::Draw()
{
	CObject2D::Draw();
	//m_pText
}

CLife_2D* CLife_2D::creat(D3DXVECTOR3 pos, int nLife)
{
	CLife_2D* p = new CLife_2D();

	p->SetPos(pos);
	p->SetSiz(D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	p->SetLifeOld(nLife);
	p->SetLife(nLife);
	p->SetMaxLife(nLife);


	p->Init();

	return p;
}
CLife_2D* CLife_2D::creat(int nPriorith, D3DXVECTOR3 pos, int nLife)
{
	CLife_2D* p = new CLife_2D(nPriorith);

	p->SetPos(pos);
	p->SetSiz(D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	p->SetLifeOld(nLife);
	p->SetLife(nLife);
	p->SetMaxLife(nLife);


	p->Init();

	return p;
}
