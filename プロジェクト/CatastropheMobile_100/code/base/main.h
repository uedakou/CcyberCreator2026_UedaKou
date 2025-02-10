//===========================================
// 
// メイン[main.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _MAIN_H_	// このマクロ定義されてないなら
#define _MAIN_H_	// 二重インクルード防止のマクロ
#include "pch.h"	// プリコンパイル

// 頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変更用係数（1.0fで固定）
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_2D;
// 頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_3D;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int GetFPS();

#endif // _MAIN_H_