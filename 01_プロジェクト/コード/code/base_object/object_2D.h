//===========================================
// 
// �|���S��2[object_2D.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_
#include "object.h"	// �I�u�W�F�N�g
#include "../base/pch.h"	// �v���R���p�C��
#include <stdio.h>


class CObject2D : public CObject
{
public:
	CObject2D();
	CObject2D(int nPriority);
	virtual ~CObject2D()	override;
	virtual void Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtx) { m_pVtxBuff = pVtx; }	// �o�b�t�@�ݒ�
	void SetTexture(const LPDIRECT3DTEXTURE9 ptex);	// �e�N�X�`���ݒ�
	void SetTexture(const char aName[MAX_TXT]);	// �e�N�X�`���ݒ�
	void SetTexture(std::string aName);	// �e�N�X�`���ݒ�
	void SetColor(D3DXCOLOR col);	// �J���[�ݒ�
	void SetSiz(D3DXVECTOR3 siz) { m_siz = siz; }	// �T�C�Y�ݒ�
		

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff() { return m_pVtxBuff; }	// �o�b�t�@�擾
	D3DXCOLOR GetColor() { return m_col; }	// �J���[�擾
	D3DXVECTOR3 GetSiz() { return m_siz; }	// �T�C�Y�擾


	static CObject2D* creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz);
	static CObject2D* creat(int nPriority, D3DXVECTOR3 pos, D3DXVECTOR3 siz);
private:
	// �ϐ��錾
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`��
	D3DXCOLOR m_col;	// �J���[�ݒ�
	D3DXVECTOR3 m_siz;	// �傫���ݒ�
};

#endif // !_OBJECT_H_