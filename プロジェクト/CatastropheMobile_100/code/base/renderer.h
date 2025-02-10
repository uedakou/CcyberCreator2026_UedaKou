//===========================================
// 
// レンダラー[renderer.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _RCNDRERE_H_
#define _RCNDRERE_H_
#include "main.h"

#define B_SORT true

class CText;
// レンダラー
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND nWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	void DrawFPS(void);
	LPDIRECT3DDEVICE9 GetDevice();
private:
	LPDIRECT3D9 m_pD3D;				// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Direct3Dデバイス

	CText* m_pText;
};

#endif // !_RCNDRERE_H_
