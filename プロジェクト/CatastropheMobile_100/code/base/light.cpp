//============================================
//
// 光源[light.cpp]
// Author:Uedakou
// 
//============================================
#include "light.h"
#include "manager.h"
#include "manager.h"
#include <strsafe.h>


// グローバル変数宣言

CLight::CLight()
{
}

CLight::~CLight()
{
}
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイスへのポインタ
	D3DXVECTOR3 vecDir[3];	//設定用方向ベクトル
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{

		// ライトの情報をクリアする
		ZeroMemory(&m_light, sizeof(D3DLIGHT9));
		//	ライトの種類
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
		// ライトの拡散拡散設定
		m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		switch (nCntLight)
		{
		case 0:
			// ライトの方向設定
			vecDir[nCntLight] = D3DXVECTOR3(0.2f, -0.8f, -1.0f);
			break;
		case 1:
			// ライトの方向設定
			vecDir[nCntLight] = D3DXVECTOR3(-0.2f, 0.8f, 0.4f);
			break;
		case 2:
			// ライトの方向設定
			vecDir[nCntLight] = D3DXVECTOR3(0.8f, -0.8f, -0.4f);
			break;
		}
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		m_light[nCntLight].Direction = vecDir[nCntLight];
		// ライトを設定する
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);
		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
	// 
	return S_OK;
}
void CLight::Uninit(void)
{}
void CLight::Update(void)
{}