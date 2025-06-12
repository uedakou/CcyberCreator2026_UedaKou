//===========================================
// 
// ポリゴン2[object_2D.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "object.h"	// オブジェクト
#include "../base/pch.h"	// プリコンパイル
#include <stdio.h>


class CObject2D : public CObject
{
public:
	CObject2D();
	CObject2D(int nPriority);
	virtual ~CObject2D()	override;
	virtual void Init()		override;	// 初期化
	virtual void Uninit()	override;	// 終了
	virtual void Update()	override;	// 更新
	virtual void Draw()		override;	// 描画
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtx) { m_pVtxBuff = pVtx; }	// バッファ設定
	void SetTexture(const LPDIRECT3DTEXTURE9 ptex);	// テクスチャ設定
	void SetTexture(const char aName[MAX_TXT]);	// テクスチャ設定
	void SetTexture(std::string aName);	// テクスチャ設定
	void SetColor(D3DXCOLOR col);	// カラー設定
	void SetSiz(D3DXVECTOR3 siz) { m_siz = siz; }	// サイズ設定
		

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return m_pVtxBuff; }	// バッファ取得
	D3DXCOLOR GetColor() { return m_col; }	// カラー取得
	D3DXVECTOR3 GetSiz() { return m_siz; }	// サイズ取得


	static CObject2D* creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz);
	static CObject2D* creat(int nPriority, D3DXVECTOR3 pos, D3DXVECTOR3 siz);
private:
	// 変数宣言
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャ
	D3DXCOLOR m_col;	// カラー設定
	D3DXVECTOR3 m_siz;	// 大きさ設定
};

#endif // !_OBJECT_H_