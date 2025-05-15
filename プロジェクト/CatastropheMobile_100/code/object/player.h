//============================================
//
// �v���C���[[player.cpp]
// Author:Uedakou
// 
//============================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "../base_object/character.h"	// �L�����N�^�[
#include "life_2d.h"
#include "../base_object/effect_generator_particle.h"

#define PLAYER_MOTIONFILE_A "data\\CHARACTER\\motion_Player.txt"	// �v���C���[���[�V�����t�@�C���p�X
#define PLAYER_MOTIONFILE_B "data\\CHARACTER\\motion.txt"			// �v���C���[���[�V�����t�@�C���p�X
#define PLAYER_RESISTANCE 0.01f		// �ړ�����
#define PLAYER_ROT_RESISTANCE 0.2f	// ��]����

#define PLAYER_SIZE X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 (10.0f, 10.0f, 70.0f))	// �T�C�Y
#define PLAYER_MOVE (0.5f)	// �ړ�
#define PLAYER_ROLL (0.01f)	// ��]

//#define PLAYER_JANP (50.0f)	// �W�����v��
#define PLAYER_SPEED 0.25f	// �����X�s�[�h(�펞)
#define PLAYER_BRAKE 0.1f	// �����u���[�L
#define PLAYER_BOOST 10.0f	// �����u�[�X�g���x
#define PLAYER_BEND 0.75f	// �T�C�h�ړ�

#define PLAYER_LIFE 10	// �̗�
#define PLAYER_ATTACK 1	// �U��

#define PLAYER_ATTACSLEEP 60	// �s���s�\����
#define PLAYER_ATTAC 40	// �s���s�\����

class CPlayer:public CCharacter
{
public:
	typedef enum {
		ACTIVITY_NEUTRAL = 0,//	�j���[�g����
		ACTIVITY_MOVE,		// ����
		ACTIVITY_ATTACK,	// �U��
		ACTIVITY_DETHI,		// ���S
		ACTIVITY_DETHILoop,	// ���S���[�v
		ACTIVITY_MAX,
	}ACTIVITY;

	// ��{����
	CPlayer();
	virtual ~CPlayer()		override;
	void Init()	override;	// ������
	void Uninit()	override;	// �I��
	void Update()	override;	// �X�V
	void Draw()		override;	// �`��

	// �����֐�
	void Hit(int nDamage)override;
	void Hit(int nCntInvincible, int nDamage) override;
	void Hit(D3DXVECTOR3 ShockRot,int nCntInvincible, int nDamage)override;
	//void OBB();

	// �ݒ�
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }// ���x�ݒ�
	float GetSpeed() { return m_fSpeed; }// ���x�ݒ�

	virtual int GetNextMotion() override;


	static CPlayer* creat();	// ����

private:
	// �֐�
	void Controller();
	void MoveAttenuation();

private:
	float m_fSpeed;	// �X�s�[�h
	float m_fBrake;	// �u���[�L��R
	float m_fBoost;	// �u�[�X�g���x
	CLife_2D* m_pLife;	// �̗�
	CEffectGeneratorPaeticle* m_pEffect;	// �u�[�X�^�[�G�t�F�N�g

protected:
	// �v���C���[���
	class PlayerActivity :public CActivity
	{
	public:
		PlayerActivity(CPlayer* player): m_pPrimary(player) {}
		~PlayerActivity() {}
		virtual PlayerActivity* update()override = 0;
		CPlayer* m_pPrimary;
	};
	// �ʏ�
	class PlayerActivityUsually :public PlayerActivity
	{
	public:
		PlayerActivityUsually(CPlayer* player);
		~PlayerActivityUsually() {}
		virtual PlayerActivity* update()override;
	};
	// �U��
	class PlayerActivityAttack :public PlayerActivity
	{
	public:
		PlayerActivityAttack(CPlayer* player);
		~PlayerActivityAttack() {}
		virtual PlayerActivity* update()override;
		int nAttackCnt;
		CEffectGeneratorPaeticle* m_pEffect;
	};
	// �q�b�g
	class PlayerActivityHit :public PlayerActivity
	{
	public:
		PlayerActivityHit(CPlayer* player);
		~PlayerActivityHit() {}
		virtual PlayerActivity* update()override;
		int nDeathCnt;
	};
	// ���S
	class PlayerActivityDeath :public PlayerActivity
	{
	public:
		PlayerActivityDeath(CPlayer* player);
		~PlayerActivityDeath() {}
		virtual PlayerActivity* update()override;
		int nDeathCnt;
	};
};




#endif // !_PLAYER_H_