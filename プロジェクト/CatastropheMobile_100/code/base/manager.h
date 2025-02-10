//===========================================
// 
// 全体マネージャー[managerer.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "renderer.h"			// レンダラー
#include "light.h"				// ライト
#include "camera.h"				// カメラ
#include "fog.h"				// フォグ
#include "input.h"				// 入力

#include "sound.h"	// サウンド

#include "../scene/scene_maneger.h"		// シーンマネージャー

#include "../collision/collision_manager.h"	// コリジョンマネージャー


#define MAX_TXT	(0x400)


class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND nWnd, BOOL bWindow);	// 初期化
	void Uninit();		// 終了
	void Update();		// 更新
	void Draw();		// 描画

	static CManager* GetInstance()
	{
		static CManager instance;	// 静的インスタンス
		return &instance;
	}

	CRenderer* GetRenderer(){ return m_pRenderer; };	// レンダラー取得
	CLight* GetLight() { return m_pLight; }				// ライト取得
	CCamera* GetCamera() { return m_pCamera; }			// カメラ取得
	CFog* GetFog() { return m_pFog; }					// フォグ
	CSound* GetSound() { return m_pSound; }				// サウンド
	
	CInputKeyboard* GetInKey() { return m_pInkey; }	// キーボード取得
	CInputMouse* GetMouse() { return m_pInMouse; }	// マウス取得
	CInputJoypad* GetJoyKey() { return m_pJoiKey; }	// マウス取得

	Scene::CBase* GetSceneManager() { return m_pSceneManager; }					// シーンマネージャー
	CCollisionManager* GetCollisionManager() { return m_pCollisionManager; }	// コリジョンマネージャー

	static void SetEnd(bool bEnd) { m_bEnd = bEnd; }
	static bool GetEnd() { return m_bEnd; }
private:
	CRenderer* m_pRenderer;	// レンダラー
	CLight* m_pLight;		// ライト
	CCamera* m_pCamera;		// カメラ
	CFog* m_pFog;			// フォグ
	CSound* m_pSound;		// サウンド

	CInputKeyboard* m_pInkey;				// キーボード
	CInputMouse* m_pInMouse;				// マウス
	CInputJoypad* m_pJoiKey;				// ジョイパッド

	Scene::CBase* m_pSceneManager;			// シーンマネージャー
	CCollisionManager* m_pCollisionManager;	// コリジョンマネージャー

	static bool m_bEnd;	// 終了
};



#endif // !_MANAGER_H_