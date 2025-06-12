//============================================
//
// �G000�`���[�g���A��[enemy000tutoreal.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY000TUTOREAL_H_
#define _ENEMY000TUTOREAL_H_
#include "enemy000.h"	// �G000


class CEnemy000Tutorial : public CEnemy000
{
public:
	CEnemy000Tutorial();
	virtual ~CEnemy000Tutorial();
	virtual void Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��
	void Hit(int nCntInvincible, int nDamage);
	static CEnemy000Tutorial* creat(D3DXVECTOR3 pos);
protected:
	// 000 ���
	class CActivity_Enemy000Tutoriale : public CActivity
	{
	public:
		CActivity_Enemy000Tutoriale(CEnemy000Tutorial* p);
		virtual CActivity_Enemy000Tutoriale* update()override = 0;
		CEnemy000Tutorial* m_pPrimary;	// ������Ă�ł�|�C���^
	};
	// ���G
	class CActivity_Enemy000Tutoriale_Search : public CActivity_Enemy000Tutoriale
	{
	public:
		CActivity_Enemy000Tutoriale_Search(CEnemy000Tutorial* p);
		virtual CActivity_Enemy000Tutoriale* update()override;
	};
	//�Ǐ]
	class CActivity_Enemy000Tutoriale_Following : public CActivity_Enemy000Tutoriale
	{
	public:
		CActivity_Enemy000Tutoriale_Following(CEnemy000Tutorial* p);
		virtual CActivity_Enemy000Tutoriale* update()override;
	};
	// ���S
	class CActivity_Enemy000Tutoriale_Death : public CActivity_Enemy000Tutoriale
	{
	public:
		CActivity_Enemy000Tutoriale_Death(CEnemy000Tutorial* p);
		virtual CActivity_Enemy000Tutoriale* update()override;
		int m_nCntDeath;
	};
private:
	float m_fSpeed;	// �X�s�[�h
	float m_fBrake;	// �u���[�L��R
	float m_fBoost;	// �u�[�X�g���x
};





#endif // _ENEMY000TUTOREAL_H_