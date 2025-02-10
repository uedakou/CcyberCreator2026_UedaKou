//============================================
//
// カメラ[camera.h]
// Author:Uedakou
// 
//============================================
#ifndef _CUMERA_H_
#define _CUMERA_H_
#include "main.h"

#define POS_CAMERA (600.0f)	// 視点と焦点の距離
// 初期設定
#define CAMERA_TYPE (true)	// 遠近投影
#define CAMERA_CONTROLLER (false)	// カメラコントローラーを使うか
#define CAMERA_V D3DXVECTOR3(0.0f, 300.0f, -POS_CAMERA)
#define CAMERA_R D3DXVECTOR3(0.0f, 10.0f, 0.0f)
#define CAMERA_U D3DXVECTOR3(0.0f, 1.0f, 0.0f)

class CText;

class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init(void);		//初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void SetCamera(void);	// 描画
	typedef enum {
		V = 0,
		R,
	}CENTER;
	void SetCameraPosV(D3DXVECTOR3 pos) { m_posV = pos;}	// カメラ位置取得
	void SetCameraPosR(D3DXVECTOR3 pos) { m_posR = pos;}	// カメラ焦点位置取得
	void SetCameraRot(CENTER centor, D3DXVECTOR3 rot);
	void SetCameraPosNomal() { 
		m_posR = CAMERA_R;
		m_posV = CAMERA_V;
	}	// カメラ焦点位置取得

	D3DXVECTOR3 GetCameraPosV() { return m_posV; }	// カメラ位置取得
	D3DXVECTOR3 GetCameraPosR() { return m_posR; }	// カメラ焦点位置取得
	D3DXVECTOR3 GetCameraRot() { return m_rot; }

	void AddCameraPosV(D3DXVECTOR3 pos) { m_posV += pos;}	// カメラ位置取得
	void AddCameraPosR(D3DXVECTOR3 pos) { m_posR += pos;}	// カメラ焦点位置取得
	void AddCameraRot(CENTER centor, D3DXVECTOR3 rot);

	bool GetCameraControllreFpllow()// 現在カメラをコントロールするか
	{return m_bCumeraController;}
	
	void DrawCamera();		// カメラ情報描画
private:
	// 関数
	void Controller();	// 操作
	// 変数
	D3DXVECTOR3 m_posV;			// カメラ
	D3DXVECTOR3 m_posR;			// 焦点
	D3DXVECTOR3 m_vecU;			// 上側
	D3DXMATRIX m_mtxProjection;	//プロジェクション行列
	D3DXMATRIX m_mtxView;		//ビューマトリックス
	D3DXVECTOR3 m_rot;			// 向き
	D3DXVECTOR3 m_rotTarget;	// 向き
	bool m_bRotTarget;			// ターゲットに向けるか

	bool m_bCameraTipe;			// カメラが遠近投影か正投影か
	bool m_bCumeraController;	// カメラのコントロールができるか
	const float m_fMoveSpeed;
	const float m_fMoveFastSpeed;

	CText* m_pTex;
};



#endif // !_CUMERA_H_