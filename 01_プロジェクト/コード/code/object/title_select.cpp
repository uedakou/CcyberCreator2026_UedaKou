//===========================================
// 
// ƒZƒŒƒNƒg[title_select.h]
// Auther:UedaKou
// 
//===========================================
#include "title_select.h"


CTitleSelect::CTitleSelect()
{

}
CTitleSelect::CTitleSelect(int nP):
	CSelect(nP)

{

}
CTitleSelect::~CTitleSelect()
{

}
void CTitleSelect::Init()
{
	CObject2D::Init();
}
void CTitleSelect::Uninit()
{
	CObject2D::Uninit();
}
void CTitleSelect::Update()
{
	CObject2D::Update();
}
void CTitleSelect::Draw()
{
	CObject2D::Draw();
}
CTitleSelect* CTitleSelect::creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz, int type)
{
	CTitleSelect* pSelect = new CTitleSelect();

	pSelect->SetPos(pos);
	pSelect->SetSiz(siz);
	pSelect->Init();
	switch (type)
	{
	case STATE:
		pSelect->SetTexture("data\\TEXTURE\\START.png");
		break;
	case END:
		pSelect->SetTexture("data\\TEXTURE\\QUITGAME.png");
		break;
	default:
		break;
	}

	return pSelect;
}
CTitleSelect* CTitleSelect::creat(int nP, D3DXVECTOR3 pos, D3DXVECTOR3 siz, int type)
{
	CTitleSelect* pSelect = new CTitleSelect(nP);

	pSelect->SetPos(pos);
	pSelect->SetSiz(siz);
	pSelect->Init();
	switch (type)
	{
	case STATE:
		pSelect->SetTexture("data\\TEXTURE\\START.png");
		break;
	case END:
		pSelect->SetTexture("data\\TEXTURE\\QUITGAME.png");
		break;
	default:
		break;
	}

	return pSelect;
}