//===========================================
// 
// フェード[object_fade.cpp]
// Auther:UedaKou
// 
//===========================================
#include "object_fade.h"


//============================================
// コンストラクタ
//============================================
CFade::CFade() :
	CObject2D(5)
{
	m_nCnt = 0;
	m_nCntMax = 0;
	m_type = WHITE_OUT;
}
//============================================
// デストラ
//============================================
CFade::~CFade()
{
}
//============================================
// 初期化
//============================================
void CFade::Init()
{
	CObject2D::Init();
}
//============================================
// 終了
//============================================
void CFade::Uninit()
{

}
//============================================
// 更新
//============================================
void CFade::Update()
{
	if (m_nCnt < m_nCntMax)
	{
		m_nCnt++;
	}
	else
	{
		Release();
	}
	switch (m_type)
	{
	case FADE_TYPE::WHITE_OUT:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f / m_nCntMax) *  m_nCnt));
		break;
	case FADE_TYPE::WHITE_IN:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f / m_nCntMax) * m_nCnt));
		break;
	case FADE_TYPE::BLACK_OUT:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f / m_nCntMax) * m_nCnt));
		break;
	case FADE_TYPE::BLACK_IN:
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (1.0f / m_nCntMax) * m_nCnt));
		break;
	}
	CObject2D::Update();
}
//============================================
// 描画
//============================================
void CFade::Draw()
{
	CObject2D::Draw();
}
//============================================
// 描画
//============================================
CFade* CFade::creat(FADE_TYPE type, int nCnt)
{
	CFade* pFade = new CFade;
	pFade->m_nCnt = 0;
	pFade->m_nCntMax = nCnt;
	pFade->m_type = type;
	switch (type)
	{
	case FADE_TYPE::WHITE_OUT:
		pFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		break;
	case FADE_TYPE::WHITE_IN:
		pFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case FADE_TYPE::BLACK_OUT:
		pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		break;
	case FADE_TYPE::BLACK_IN:
		pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	}
	pFade->SetSiz(D3DXVECTOR3(SCREEN_W, SCREEN_H, 0.0f));
	pFade->SetPos(D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f));
	pFade->Init();
	return pFade;
}