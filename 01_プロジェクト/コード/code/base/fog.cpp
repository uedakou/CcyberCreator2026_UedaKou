//===========================================
// 
// フォグ[fog.h]
// Auther:UedaKou
// 
//===========================================
#include "fog.h"
#include "manager.h"
CFog::CFog()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// フォグ有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	// フォグカラー
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	// フォグパラメータ
	m_type = EXP;
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);

	// 距離指定

	m_fFogStartPos = 100.0f;
	m_fFogEndPos = 10000.0f;
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogEndPos));

	// 密度指定
	m_m_fFogDensity = 0.0002f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_m_fFogDensity));
}

CFog::~CFog()
{

}

void CFog::SetFogType(FogType type)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// フォグパラメータ
	m_type = type;
	switch (type)
	{
	case EXP:
		pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
		break;
	case LINEAR:
		pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
		break;
	default:
		break;
	}
}
void CFog::SetFogLinear(float fStart, float fEnd)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 距離指定
	m_fFogStartPos = fStart;
	m_fFogEndPos = fEnd;
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogStartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogEndPos));

}
void CFog::SetFogDensity(float fDensity)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 密度指定
	m_m_fFogDensity = fDensity;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_m_fFogDensity));
}

CFog* CFog::creat()
{
	return new CFog;
}