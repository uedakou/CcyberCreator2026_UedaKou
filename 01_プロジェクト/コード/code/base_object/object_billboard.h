//============================================
//
// �r���{�[�h[billbord.h]
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
		Null = 0,	// �w��Ȃ�
		TREE,	// ��
		MAX
	}TYPE;
	CObjectBillbord();
	CObjectBillbord(const int nPriority);
	~CObjectBillbord();
	virtual void Init()		override;	
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	void SetPos(D3DXVECTOR3 pos) { CObject::SetPos(pos); }	// �ʒu�ݒ�
	void SetSiz(D3DXVECTOR3 siz) { m_siz = siz; }	// �傫���ݒ�

	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtx) { m_pVtxBuff = pVtx; }	// �o�[�e�b�N�X�o�b�t�@�ݒ�
	void SetTexture(const char aFileName[MAX_TXT]);	// �e�N�X�`���ݒ�
	void SetTexture(const LPDIRECT3DTEXTURE9 pTex);// �e�N�X�`���ݒ�
	void SetTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1);// �e�N�X�`��UV�ݒ�(����E��)
	void SetColor(D3DXCOLOR col);	// �J���[�ݒ�

	void SetType(TYPE type) { m_type = type; }	// ��ސݒ�

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return m_pVtxBuff; }// �o�[�e�b�N�X�o�b�t�@�擾
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }	// �e�N�X�`���擾
	D3DXMATRIX GetMaxWorld() { return m_mtxWorld; }	// ���[���h�}�g���N�X�擾
	D3DXCOLOR GetColor() { return m_col; }	// �F�擾
	TYPE GetType() { return m_type; }	// ��ގ擾
	D3DXVECTOR3 GetSiz() { return m_siz; }	// �傫���擾

	void AddTexUV(D3DXVECTOR2 tex0, D3DXVECTOR2 tex1);// �e�N�X�`��UV�ݒ�(����E��)
	static CObjectBillbord* creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz);
	static CObjectBillbord* creat(int nPriorith, D3DXVECTOR3 pos, D3DXVECTOR3 siz);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �o�[�e�b�N�X�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`��
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���N�X
	D3DXCOLOR m_col;	// �J���[
	TYPE m_type;	// ���
	D3DXVECTOR3 m_siz;	// �傫��
};




#endif // !_OBJECT_BILLBORD_H_