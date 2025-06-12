//============================================
//
// �G100[enemy100.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY100_H_
#define _ENEMY100_H_
#include "enemy.h"
#define Enemy100_RESISTANCE 0.01f	// �ړ�����
#define Enemy100_RESISTANCE_SIDE 0.005f	// �ړ�����


#define Enemy100_SIZE X(D3DXVECTOR3(0.0f, 0.0f, -80.0f), D3DXVECTOR3(0.0f, 0.0f ,0.0f), D3DXVECTOR3(10.0f, 10.0f, 120.0f))

#define Enemy100_MOVE (0.1f)	// �ړ�
//#define Enemy000_JANP (50.0f)	// �W�����v��
#define Enemy100_SPEED 0.25f	// �����X�s�[�h(�펞)
#define Enemy100_BRAKE 0.1f	// �����u���[�L
#define Enemy100_BOOST 0.5f	// �����u�[�X�g���x
#define Eneny100_COUNT_SURVIVAL 1800	// ��������

#define Enemy100_BEND 0.1f	// �T�C�h�ړ�

class CEffectGeneratorPaeticle;
class CLife_3D;
class CEnemy100 : public CEnemy
{
public:
	CEnemy100();
	virtual ~CEnemy100();
	virtual void Init()		override;	// ������
	virtual void Uninit()	override;	// �I��
	virtual void Update()	override;	// �X�V
	virtual void Draw()		override;	// �`��
	virtual int GetNextMotion() override;	// �����[�V����
	void Hit(int nCntInvincible, int nDamage) override;
	static CEnemy100* creat(D3DXVECTOR3 pos);

private:
	float m_fSpeed;	// �X�s�[�h
	float m_fBrake;	// �u���[�L��R
	float m_fBoost;	// �u�[�X�g���x
	int m_nCntSurvival;	// ��������
	CLife_3D* m_pLife3D;

private:
	CEffectGeneratorPaeticle* m_pEffect;	// �G�t�F�N�g
	// ���
	class CActivity_Enemy100 : public CActivity
	{
	public:
		CActivity_Enemy100(CEnemy100* p);
		virtual CActivity_Enemy100* update()override = 0;
		CEnemy100* m_pPrimary;	// ������Ă�ł�|�C���^
	};
	// ���G
	class CActivity_Enemy100_Search : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Search(CEnemy100* p);
		CActivity_Enemy100* update()override;
	};
	// �ǐ�
	class CActivity_Enemy100_Following : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Following(CEnemy100* p);
		CActivity_Enemy100* update()override;
		const int m_MaxCnt;
		int m_nCnt;	// �U�����s���܂ł̎���
		typedef enum {
			TACKL = 0,	// �^�b�N��
			SUMMON,		// ����
			MAX
		}ATTACE_TYPE;
	};
	// �^�b�N��
	class CActivity_Enemy100_Tackle_000 : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Tackle_000(CEnemy100* p);
		CActivity_Enemy100* update()override;
		const int m_MaxCnt;
		int m_nCnt;
	};
	class CActivity_Enemy100_Tackle_001 : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Tackle_001(CEnemy100* p);
		CActivity_Enemy100* update()override;
		const int m_MaxCnt;
		int m_nCnt;
	};
	// ����
	class CActivity_Enemy100_Summon : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Summon(CEnemy100* p);
		CActivity_Enemy100* update()override;
		const int m_MaxCnt;
		int m_nCnt;
	};
	// ���S
	class CActivity_Enemy100_Dethe : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Dethe(CEnemy100* p);
		CActivity_Enemy100* update()override;
		const int m_MaxCnt;
		int m_nCnt;
	};
};
#endif // !_ENEMY100_H_