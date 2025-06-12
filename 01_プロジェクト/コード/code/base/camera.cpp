//============================================
//
// カメラ[camera.cpp]
// Author:Uedakou
// 
//============================================
#include "camera.h"	// カメラ
#include "manager.h"	// マネージャー
#include <strsafe.h>	// StringCbPrintfを使用するにのに必要
#include "../object/Base/object.h"	// オブジェクト
#include "../object/base/text.h"

// 透視投影
const float CCamera::ProjectionPerspectiveStrategy::PERSPECTIVE_FOV = 45.0f;
const float CCamera::ProjectionPerspectiveStrategy::PERSPECTIVE_NEAR = 50.0f;
const float CCamera::ProjectionPerspectiveStrategy::PERSPECTIVE_FAR = 10000.0f;

// 並行投影
const float CCamera::ProjectionOrthographicStrategy::PERSPECTIVE_NEAR = 50.0f;
const float CCamera::ProjectionOrthographicStrategy::PERSPECTIVE_FAR = 10000.0f;


// カメラ定数
const float CCamera::POS_CAMERA = 100.0f;	// 視点と注視点の距離
const CCamera::ProjectionType CCamera::CAMERA_TYPE = CCamera::ProjectionType::Perspective;	// 投影方式
const bool CCamera::CAMERA_CONTROLLER = false;	// カメラでコントローラーをするか
const D3DXVECTOR3 CCamera::CAMERA_V = D3DXVECTOR3(0.0f, 40.0f, -POS_CAMERA);	// カメラ位置取得
const D3DXVECTOR3 CCamera::CAMERA_ROT = D3DXVECTOR3(1.5f, 0.0f, 0.0f);	// カメラ向き取得
const D3DXVECTOR3 CCamera::CAMERA_U = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// 上方向
const float CCamera::MOVE_SPEED = 10.0f;	// 移動速度
const float CCamera::MOVE_SPEED_FAST = 50.0f;// シフト移動速度

//============================================
// コンスト
//============================================
CCamera::CCamera()
{
	m_CameraType = CAMERA_TYPE;				// カメラ遠近投影
	m_bCumeraController = CAMERA_CONTROLLER;			// プレイヤー追従

	m_posV = CAMERA_V;	// 視点
	m_vecU = CAMERA_U;	// 上方向
	m_rot = CAMERA_ROT;	// 向き
	m_fLeng = POS_CAMERA;	// 視点と注視点の距離

	m_posR.x = cos(m_rot.x) + sin(m_rot.y) * m_fLeng;	// 注視点
	m_posR.z = cos(m_rot.x) + cos(m_rot.y) * m_fLeng;	// 注視点
	m_posR.y = sin(m_rot.x) * m_fLeng;	// 注視点


	m_rotTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き(目標)
	m_bRotTarget = false;						// 補正回転中可動か

	m_fMoveSpeed = MOVE_SPEED;
	m_fMoveFastSpeed = MOVE_SPEED_FAST;

	m_pText = nullptr;

	m_pCameraStrategy = new ProjectionPerspectiveStrategy();
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
#if _DEBUG
	m_pText = CText::creat();
	m_pText->SetReleaseScene(false);
#endif //! _DEBUG
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
	}
	CameraSetR();
	// カメラ情報テキスト表示
#if _DEBUG

#if s_bCumeraDataDraw
	DrawCamera();
#endif // s_bCumeraDataDraw
#endif // _DEBUG
}
//============================================
// 描画処理
//============================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();// デバイスへのポインタ

	// プロジェクションマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
#if 1
	// プロジェクションマトリクスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	// 視野角（FOV）
		(float)SCREEN_W / (float)SCREEN_H,	// アスペクト比（横 / 縦）
		10,		// 近クリップ面
		10000);	// 遠クリップ面
#else
	m_pCameraStrategy->Projection(&m_mtxProjection);
#endif // 0


	//switch (m_CameraType)
	//{
	//case ProjectionType::Perspective:
	//	// 遠近投影
	//	Projection()
	//	break;
	//case ProjectionType::Orthographic:
	//	// 正投影
	//	break;
	//default:
	//	break;
	//}
#if _DEBUG


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
// カメラ情報描画
//============================================
void CCamera::DrawCamera()
{
	char aStr[MAX_TXT];
	sprintf_s(aStr, sizeof(aStr), "CameraV Pos:X%f Y%f Z%f\nCameraR Pos:X%f Y%f Z%f\nCamera Rot:X%f Y%f Z%f\n", m_posV.x, m_posV.y, m_posV.z, m_posR.x, m_posR.y, m_posR.z, m_rot.x, m_rot.y, m_rot.z);
	if (m_pText != nullptr)
	{
		m_pText->SetText(aStr);
	}
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
				m_rot.y > -(D3DX_PI * 0.5f) + 0.005f)
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
				m_rot.y < -(D3DX_PI * 0.5f) - 0.005f)
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
		if (m_rot.x < D3DX_PI)
		{
			m_rot.x -= 0.05f;
		}
	}
	else if (pKey->GetRepeat(DIK_F))
	{
		if (m_rot.x > 0)
		{
			m_rot.x += 0.05f;
		}
	}
	// 移動
	if (pKey->GetRepeat(DIK_LSHIFT))
	{
		if (pKey->GetRepeat(DIK_W))
		{// 前方移動
			if (pKey->GetRepeat(DIK_A))
			{// 左後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveFastSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// 右後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveFastSpeed);
			}
			else
			{// 後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveFastSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_S))
		{// 後方移動
			if (pKey->GetRepeat(DIK_A))
			{// 左前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveFastSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// 右前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveFastSpeed);
			}
			else
			{// 前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveFastSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveFastSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_A))
		{// 左移動
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveFastSpeed, 0.0f,
				cosf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveFastSpeed);
		}
		else if (pKey->GetRepeat(DIK_D))
		{// 右移動
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveFastSpeed, 0.0f,
				cosf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveFastSpeed);
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
			{// 左後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.25f)) * m_fMoveSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// 右後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.25f)) * m_fMoveSpeed);
			}
			else
			{// 後移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.0f)) * m_fMoveSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_S))
		{// 後方移動
			if (pKey->GetRepeat(DIK_A))
			{// 左前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (-D3DX_PI * 0.75f)) * m_fMoveSpeed);
			}
			else if (pKey->GetRepeat(DIK_D))
			{// 右前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 0.75f)) * m_fMoveSpeed);
			}
			else
			{// 前移動
				m_posV += D3DXVECTOR3(
					sinf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveSpeed, 0.0f,
					cosf(m_rot.y + (D3DX_PI * 1.0f)) * m_fMoveSpeed);
			}
		}
		else if (pKey->GetRepeat(DIK_A))
		{// 左移動
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveSpeed, 0.0f,
				cosf(m_rot.y + (-D3DX_PI * 0.5f)) * m_fMoveSpeed);
		}
		else if (pKey->GetRepeat(DIK_D))
		{// 右移動
			m_posV += D3DXVECTOR3(
				sinf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveSpeed, 0.0f,
				cosf(m_rot.y + (D3DX_PI * 0.5f)) * m_fMoveSpeed);
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
void CCamera::CameraSetR()
{
	m_posR.x = m_posV.x + cosf(m_rot.x - (D3DX_PI * 0.5f)) * sinf(m_rot.y) * POS_CAMERA;
	m_posR.y = m_posV.y + sinf(m_rot.x - (D3DX_PI * 0.5f)) * POS_CAMERA;
	m_posR.z = m_posV.z + cosf(m_rot.x - (D3DX_PI * 0.5f)) * cosf(m_rot.y) * POS_CAMERA;
}
//============================================
// 投資投影
//============================================
CCamera::ProjectionPerspectiveStrategy::ProjectionPerspectiveStrategy()
{
	m_fFov = PERSPECTIVE_FOV;
	m_fNear = PERSPECTIVE_NEAR;
	m_fFar = PERSPECTIVE_FAR;
}
void CCamera::ProjectionPerspectiveStrategy::Projection(D3DXMATRIX* mtx)
{
	// プロジェクションマトリクスを作成
	D3DXMatrixPerspectiveFovLH(mtx,
		D3DXToRadian(m_fFov),	// 視野角（FOV）
		(float)SCREEN_W / (float)SCREEN_H,	// アスペクト比（横 / 縦）
		m_fNear,		// 近クリップ面
		m_fFar);	// 遠クリップ面
}

CCamera::ProjectionOrthographicStrategy::ProjectionOrthographicStrategy()
{
	m_fNear = PERSPECTIVE_NEAR;
	m_fFar = PERSPECTIVE_FAR;
}

void CCamera::ProjectionOrthographicStrategy::Projection(D3DXMATRIX* mtx)
{
	D3DXMatrixOrthoLH(
		mtx,
		(float)SCREEN_W,
		(float)SCREEN_H,
		m_fNear,
		m_fFar);
}
