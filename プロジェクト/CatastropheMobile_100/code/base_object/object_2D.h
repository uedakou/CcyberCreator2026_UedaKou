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
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtx) { m_pVtxBuff = pVtx; }
	void SetTexture(const LPDIRECT3DTEXTURE9 ptex);
	void SetTexture(const char aName[MAX_TXT]);
	void SetTexture(std::string aName);
	void SetColor(D3DXCOLOR col);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return m_pVtxBuff; }
	D3DXCOLOR GetColor() { return m_col; }



	static CObject2D* creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz);
	static CObject2D* creat(int nPriority, D3DXVECTOR3 pos, D3DXVECTOR3 siz);
private:
	// 変数宣言
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャ
	D3DXCOLOR m_col;
};

#endif // !_OBJECT_H_