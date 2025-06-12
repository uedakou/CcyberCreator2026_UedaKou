//===========================================
// 
// 2D�\�����C�t[life_3d.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _LIFE_3D_
#define _LIFE_3D_
#include "../base_object/object_billboard.h"
#include "../base_object/text.h"

class CLife_3D : public CObjectBillbord
{
public:
	CLife_3D();
	~CLife_3D();
	void Init()		override;	// ������
	void Uninit()	override;	// �I��
	void Update()	override;	// �X�V
	void Draw()		override;	// �`��
	void SetX(X pos) { CObjectBillbord::SetX(pos); }				// �ʒu�ݒ�
	void SetPos(D3DXVECTOR3 pos) { CObjectBillbord::SetPos(pos); }	// �ʒu�ݒ�

	void SetLifeOld(int nLifeOld) { m_nLifeOld = nLifeOld; }	// 1f�O�̗͐ݒ�
	void SetLife(int nLife) { m_nLife = nLife; }				// �̗͐ݒ�
	void SetMaxLife(int nMaxLife) { m_nMaxLife = nMaxLife; }	// �ő�̗͐ݒ�

	static CLife_3D* creat(D3DXVECTOR3 pos, int nLife);		// ����
private:
	CObjectBillbord* m_lifeBG;	// �w�i
	int m_nLifeOld;		// 1f�O�̗̑�
	int m_nLife;		// ���ݑ̗�
	int m_nMaxLife;		// �ő�̗�
	CText* m_pText;		// �e�L�X�g
	D3DXVECTOR3 posOld;	// 1f�O�̈ʒu
};





#endif // _LIFE_3D_