//============================================
//
// ビルボード[billbord.h]
// Author:Uedakou
// 
//============================================
#ifndef _OBJECT_BILLBORD_H_
#define _OBJECT_BILLBORD_H_
#include "object.h"

class CObjectBillbord : public CObject
{
public:
	typedef enum {
		Null = 0,	// 指定なし
		TREE,	// 木
		MAX
	}TYPE;
	CObjectBillbord();
	CObjectBillbord(const int nPriority);
	~CObjectBillbord();
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	void SetPos(D3DXVECTOR3 pos) { CObject::SetPos(pos); }


	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtx) { m_pVtxBuff = pVtx; }
	void SetTexture(const char aFileName[MAX_TXT]);
	void SetTexture(const LPDIRECT3DTEXTURE9 pTex);
	void SetTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1);// テクスチャUV設定(左上右下)
	void SetColor(D3DXCOLOR col);

	void SetType(TYPE type) { m_type = type; }	// 種類設定

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return m_pVtxBuff; }// バーテックスバッファ取得
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }	// テクスチャ取得
	D3DXMATRIX GetMaxWorld() { return m_mtxWorld; }	// ワールドマトリクス取得
	D3DXCOLOR GetColor() { return m_col; }	// 色取得
	TYPE GetType() { return m_type; }	// 種類取得

	void AddTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1);// テクスチャUV設定(左上右下)
	static CObjectBillbord* creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz);
	static CObjectBillbord* creat(int nPriorith, D3DXVECTOR3 pos, D3DXVECTOR3 siz);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// バーテックスバッファ
	LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャ
	D3DXMATRIX m_mtxWorld;		// ワールドマトリクス
	D3DXCOLOR m_col;
	TYPE m_type;
};




#endif // !_OBJECT_BILLBORD_H_