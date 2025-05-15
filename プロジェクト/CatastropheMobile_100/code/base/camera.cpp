//============================================
//
// カメラ[camera.cpp]
// Author:Uedakou
// 
//============================================
#include "camera.h"	// カメラ
#include "manager.h"	// マネージャー
#include <strsafe.h>	// StringCbPrintfを使用するにのに必要
#include "../base_object/object.h"	// オブジェクト
#include "../object/player.h"	// プレイヤー

#include "../base_object/text.h"


//============================================
// コンスト
//============================================
CCamera::CCamera():
	m_fMoveSpeed(10.0f),
	m_fMoveFastSpeed(50.0f)
{
	m_posV = CAMERA_V;	// 視点
	m_posR = CAMERA_R;	// 焦点
	m_vecU = CAMERA_U;	// 上方向

	m_rot = D3DXVECTOR3(
		atan2f((m_posV.z - m_posR.z), (m_posV.y - m_posR.y)),
		atan2f((m_posV.x - m_posR.x), (m_posV.z - m_posR.z)),
		0.0f);		// 向き

	m_rotTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き(目標)
	m_bRotTarget = false;						// 補正回転中可動か
	m_bCameraTipe = CAMERA_TYPE;				// カメラ遠近投影
	m_bCumeraController = CAMERA_CONTROLLER;			// プレイヤー追従

	//m_pTex = CText::creat();
}
//============================================
// デストラ
//============================================
CCamera::~CCamera()
{
}
//============================================
// 初期化処理
//============================================
HRESULT CCamera::Init(void)
{

	return S_OK;
}
//============================================
// 終了処理
//============================================
void CCamera::Uninit(void)
{}
//============================================
// 更新処理
//============================================
void CCamera::Update(void)
{
	CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();	// キーボード入力
	if (pKey->GetTrigger(DIK_F2))
	{
		m_bCumeraController = m_bCumeraController ? false : true;
	}
	if (m_bCumeraController)
	{
		Controller();
		// 四方補正回転
		if (m_bRotTarget == true)
		{
			// 四方補正回転適応
			float fRotY = (m_rotTarget.y - m_rot.y);
			if (fRotY >= D3DX_PI)
			{
				fRotY -= TAU;
			}
			else if (fRotY <= -D3DX_PI)
			{
				fRotY += TAU;
			}

			m_rot.y += fRotY * 0.1f;

			if (m_rot.y >= D3DX_PI)
			{
				m_rot.y -= TAU;
			}
			else if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
			// 回転が完了したら
			if (m_rot.y - m_rotTarget.y <= 0.005f &&
				m_rot.y - m_rotTarget.y >= 0.005f)
			{
				m_bRotTarget = false;
			}
		}
		m_posR.x = m_posV.x + cosf(m_rot.x - (D3DX_PI * 0.5f)) * sinf(m_rot.y) * POS_CAMERA;
		m_posR.y = m_posV.y + sinf(m_rot.x - (D3DX_PI * 0.5f)) * POS_CAMERA;
		m_posR.z = m_posV.z + cosf(m_rot.x - (D3DX_PI * 0.5f)) * cosf(m_rot.y) *	POS_CAMERA;
	}
	if (pKey->GetTrigger(DIK_F1))
	{
		m_bCameraTipe = m_bCameraTipe ? false : true;
	}

}
//============================================
// 描画処理
//============================================
void CCamera::SetCamera(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイスへのポインタ
	// プロジェクションマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	if (m_bCameraTipe)
	{// 遠近投影
		// プロジェクションマトリクスを作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_W / (float)SCREEN_H,
			50.0f, 10000.0f);

	}
	else
	{// 正投影
		D3DXMatrixOrthoLH(
			&m_mtxProjection,
			(float)SCREEN_W,
			(float)SCREEN_H,
			10.0f,
			10000.0f);

	}
#if _DEBUG
	// DrawCamera();

#endif // _DEBUG


	// プロジェクションマトリクスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);


	// ビューマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	// ビューマトリクスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);
	// ビューマトリクスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//============================================
// カメラ向き設定
//============================================
void CCamera::SetCameraRot(CENTER centor, D3DXVECTOR3 rot)
{
	switch (centor)
	{
	case CENTER::V:

		break;
	case CENTER::R:

		break;
	default:
		break;
	}
	m_rot = rot;
}
void CCamera::AddCameraRot(CENTER centor, D3DXVECTOR3 rot)
{
	switch (centor)
	{
	case CENTER::V:

		break;
	case CENTER::R:

		m_rot += rot;
		if (m_rot.y <= -D3DX_PI)
		{
			m_rot.y += TAU;
		}
		break;
	default:
		break;
	}
}
//============================================
// カメラ情報描画
//============================================
void CCamera::DrawCamera()
{
	//char aStr0[256];
	//CManager* instance = CManager::GetInstance();
	//D3DXVECTOR3 CameraPos = instance->GetCamera()->GetCameraPosV();

	//// 文字列に代入
	//if (FAILED(StringCbPrintf(aStr0, sizeof(aStr0) / sizeof(aStr0[0]),
	//	TEXT("CameraPosV X:%f  Y:%f  Z:%f"), CameraPos.x, CameraPos.y, CameraPos.z)))
	//{
	//	// 失敗時処理
	//}
	//m_pTex->Print(aStr0);


	//D3DXVECTOR3 CameraRot = instance->GetCamera()->GetCameraRot();
	//// 文字列に代入
	//if (FAILED(StringCbPrintf(aStr0, sizeof(aStr0) / sizeof(aStr0[0]),
	//	TEXT("\nCameraRot:%f  Y:%f  Z:%f"), CameraRot.x, CameraRot.y, CameraRot.z)))
	//{
	//	// 失敗時処理
	//}
	//// テキストの描画
	//m_pTex->Print(aStr0);
}
//============================================
// 操作
//============================================
void CCamera::Controller()
{
	CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();
	// 回転
	if (pKey->GetTrigger(DIK_Q))
	{
		if (pKey->GetRepeat(DIK_LSHIFT))
		{
			m_bRotTarget = true;
			if (m_rot.y <= 0.0f + 0.005f &&
				m_rot.y > -(D3DX_PI * 0.5f )+ 0.005f)
			{
				m_rotTarget.y = -(D3DX_PI * 0.5f);
			}
			else if (m_rot.y <= -(D3DX_PI * 0.5f) + 0.005f &&
				m_rot.y > -D3DX_PI + 0.005f)
			{
				m_rotTarget.y = -D3DX_PI;
			}
			else if (m_rot.y <= -D3DX_PI + 0.005f ||
				m_rot.y > (D3DX_PI * 0.5f) + 0.005f)
			{
				m_rotTarget.y = D3DX_PI * 0.5f;
			}
			else if (m_rot.y <= (D3DX_PI * 0.5f) + 0.005f &&
				m_rot.y > 0.0f + 0.005f)
			{
				m_rotTarget.y = 0.0f;
			}
		}
		else
		{
			m_bRotTarget = false;
			m_rot.y -= 0.05f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
		}
	}
	else if (pKey->GetRepeat(DIK_Q) &&
		m_bRotTarget == false)
	{
		m_rot.y -= 0.05f;
		if (m_rot.y <= -D3DX_PI)
		{
			m_rot.y += TAU;
		}
	}
	else if (pKey->GetTrigger(DIK_E))
	{
		if (pKey->GetRepeat(DIK_LSHIFT))
		{
			m_bRotTarget = true;
			if (m_rot.y >= 0.0f - 0.005f &&
				m_rot.y < (D3DX_PI * 0.5f) - 0.005f)
			{
				m_rotTarget.y = D3DX_PI * 0.5f;
			}
			else if (m_rot.y >= D3DX_PI * 0.5f - 0.005f &&
				m_rot.y < D3DX_PI - 0.005f)
			{
				m_rotTarget.y = D3DX_PI;
			}
			else if (m_rot.y >= D3DX_PI - 0.005f ||
				m_rot.y < -( D3DX_PI * 0.5f) - 0.005f)
			{
				m_rotTarget.y = -D3DX_PI * 0.5f;
			}
			else if (m_rot.y >= -(D3DX_PI * 0.5f) - 0.005f &&
				m_rot.y < 0.0f - 0.005f)
			{
				m_rotTarget.y = 0.0f;
			}
		}
		else
		{
			m_bRotTarget = false;
			m_rot.y -= 0.05f;
			if (m_rot.y <= -D3DX_PI)
			{
				m_rot.y += TAU;
			}
		}
	}
	else if (pKey->GetRepeat(DIK_E) &&
		m_bRotTarget == false)
	{
		m_rot.y += 0.05f;
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y -= TAU;
		}
	}
	if (pKey->GetRepeat(DIK_R))
	{
		if (m_rot.x > -D3DX_PI)
		{
			m_rot.x -= 0.05f;
		}
		else
		{
			int a = 0;
		}
	}
	else if (pKey->GetRepeat(DIK_F))
	{
		if (m_rot.x < 0)
		{
			m_rot.x += 0.05f;
		}
				else
		{
			int a = 0;
		}
	}
	// 移動
	if(pKey->GetRepeat(DIK_LSHIFT))
	{
		if (pKey->GetRepeat(DIK_W))
		{// 前方移動
			if (pKey->GetRepeat(DIK_A))
			{// 左前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveFastSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// 右前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveFastSpeed);
			}
			else
			{// 前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveFastSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_S))
		{// 後方移動
			if (pKey->GetRepeat(DIK_A))
			{// 左後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveFastSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// 右後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveFastSpeed);
			}
			else
			{// 後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveFastSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_A))
		{// 左移動
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveFastSpeed, 0.0f,
				cosf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveFastSpeed);
		}
		else if (pKey->GetRepeat(DIK_D))
		{// 右移動
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveFastSpeed, 0.0f,
				cosf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveFastSpeed);
		}
		// 上下
		if (pKey->GetRepeat(DIK_SPACE))
		{// 上昇
			m_posV.y += m_fMoveFastSpeed;
		}
		else if (pKey->GetRepeat(DIK_LCONTROL))
		{// 下降
			m_posV.y -= m_fMoveFastSpeed;
		}
	}
	else
	{
		if (pKey->GetRepeat(DIK_W))
		{// 前方移動
			if (pKey->GetRepeat(DIK_A))
			{// 左前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// 右前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveSpeed);
			}
			else
			{// 前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_S))
		{// 後方移動
			if (pKey->GetRepeat(DIK_A))
			{// 左後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// 右後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveSpeed);
			}
			else
			{// 後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_A))
		{// 左移動
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveSpeed, 0.0f,
				cosf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveSpeed);
		}
		else if (pKey->GetRepeat(DIK_D))
		{// 右移動
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveSpeed, 0.0f,
				cosf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveSpeed);
		}
	}

	// 上下
	if (pKey->GetRepeat(DIK_SPACE))
	{// 上昇
		m_posV.y += 10.0f;
	}
	else if (pKey->GetRepeat(DIK_LCONTROL))
	{// 下降
		m_posV.y -= 10.0f;
	}
}