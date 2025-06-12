//============================================
//
// �G000[enemy000.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY000_H_
#define _ENEMY000_H_
#include "enemy.h"
#include "life_3d.h"
#define Enemy000_RESISTANCE 0.01f	// �ړ�����
#define Enemy000_RESISTANCE_SIDE 0.005f	// �ړ�����

#define Enemy000_XSIZE X(D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 70.0f))
#define Enemy000_SIZE D3DXVECTOR3()

#define Enemy000_MOVE (0.1f)	// �ړ�
//#define Enemy000_JANP (50.0f)	// �W�����v��
#define Enemy000_SPEED 0.25f	// �����X�s�[�h(�펞)
#define Enemy000_BRAKE 0.5f	// �����u���[�L
#define Enemy000_BOOST 0.5f		// �����u�[�X�g���x
#define Eneny000_COUNT_SURVIVAL 600	// ��������

#define Enemy000_BEND 0.2f	// �T�C�h�ړ�

#define Enemy000_ATTAC 30			// �U��������܂ł̎���
#define Enemy000_ATTAC_COOL_DOWN 60	// �U���̃N�[���_�E������

#define Enemy000_DEATHCNT 60		// ���S���烊���[�X�܂ł̎���

#define Enemy000_MotionFilename "data\\CHARACTER\\motion_Enemy000.txt"	// �G000 �t�@�C���p�X

#define Enemy000_LIFE 5
class CEffectGeneratorPaeticle;
class CEnemy000 : public CEnemy
{
public:
	CEnemy000();
	virtual ~CEnemy000();
	virtual void Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��
	virtual int GetNextMotion() override;	// �����[�V����
	void Hit(int nCntInvincible, int nDamage);	// �q�b�g����(���G����, �_���[�W) 
	static CEnemy000* creat(D3DXVECTOR3 pos);
private:
	float m_fSpeed;	// �X�s�[�h
	float m_fBrake;	// �u���[�L��R
	float m_fBoost;	// �u�[�X�g���x
	CLife_3D* m_pLife3D;
	CEffectGeneratorPaeticle* m_pEffect;
protected:
	// 000 ���
	class CActivity_Enemy000 : public CActivity
	{
	public:
		CActivity_Enemy000(CEnemy000* p,int nS);
		virtual CActivity_Enemy000* update()override = 0;
		CActivity_Enemy000* DeathCnt();
		CEnemy000* m_pPrimary;	// ������Ă�ł�|�C���^
		int m_nCntSurvival;	// ��������
	};
	// ���G
	class CActivity_Enemy000_Search : public CActivity_Enemy000
	{
	public:
		CActivity_Enemy000_Search(CEnemy000* p, int nS);
		virtual CActivity_Enemy000* update()override;
	};
	//�Ǐ]
	class CActivity_Enemy000_Following : public CActivity_Enemy000
	{
	public:
		CActivity_Enemy000_Following(CEnemy000* p, int nS);
		virtual CActivity_Enemy000* update()override;
		int m_nCntAttac;	// �U�����s���܂ł̎���
	};
	//�U��
	class CActivity_Enemy000_Tackle : public CActivity_Enemy000
	{
	public:
		CActivity_Enemy000_Tackle(CEnemy000* p, int nS);
		virtual CActivity_Enemy000* update()override;
		int m_nCnt;
		D3DXVECTOR3 m_Move;
		CEffectGeneratorPaeticle* m_pEffect;
	};
	// ���S
	class CActivity_Enemy000_Death : public CActivity_Enemy000
	{
	public:
		CActivity_Enemy000_Death(CEnemy000* p);
		virtual CActivity_Enemy000* update()override;
		int m_nCntDeath;
	};
};
#endif // !_ENEMY000_H_