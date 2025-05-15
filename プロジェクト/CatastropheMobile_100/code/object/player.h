//============================================
//
// プレイヤー[player.cpp]
// Author:Uedakou
// 
//============================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "../base_object/character.h"	// キャラクター
#include "life_2d.h"
#include "../base_object/effect_generator_particle.h"

#define PLAYER_MOTIONFILE_A "data\\CHARACTER\\motion_Player.txt"	// プレイヤーモーションファイルパス
#define PLAYER_MOTIONFILE_B "data\\CHARACTER\\motion.txt"			// プレイヤーモーションファイルパス
#define PLAYER_RESISTANCE 0.01f		// 移動減衰
#define PLAYER_ROT_RESISTANCE 0.2f	// 回転減衰

#define PLAYER_SIZE X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3 (10.0f, 10.0f, 70.0f))	// サイズ
#define PLAYER_MOVE (0.5f)	// 移動
#define PLAYER_ROLL (0.01f)	// 回転

//#define PLAYER_JANP (50.0f)	// ジャンプ量
#define PLAYER_SPEED 0.25f	// 初期スピード(常時)
#define PLAYER_BRAKE 0.1f	// 初期ブレーキ
#define PLAYER_BOOST 10.0f	// 初期ブースト速度
#define PLAYER_BEND 0.75f	// サイド移動

#define PLAYER_LIFE 10	// 体力
#define PLAYER_ATTACK 1	// 攻撃

#define PLAYER_ATTACSLEEP 60	// 行動不能時間
#define PLAYER_ATTAC 40	// 行動不能時間

class CPlayer:public CCharacter
{
public:
	typedef enum {
		ACTIVITY_NEUTRAL = 0,//	ニュートラル
		ACTIVITY_MOVE,		// 動き
		ACTIVITY_ATTACK,	// 攻撃
		ACTIVITY_DETHI,		// 死亡
		ACTIVITY_DETHILoop,	// 死亡ループ
		ACTIVITY_MAX,
	}ACTIVITY;

	// 基本処理
	CPlayer();
	virtual ~CPlayer()		override;
	void Init()	override;	// 初期化
	void Uninit()	override;	// 終了
	void Update()	override;	// 更新
	void Draw()		override;	// 描画

	// 処理関数
	void Hit(int nDamage)override;
	void Hit(int nCntInvincible, int nDamage) override;
	void Hit(D3DXVECTOR3 ShockRot,int nCntInvincible, int nDamage)override;
	//void OBB();

	// 設定
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }// 速度設定
	float GetSpeed() { return m_fSpeed; }// 速度設定

	virtual int GetNextMotion() override;


	static CPlayer* creat();	// 生成

private:
	// 関数
	void Controller();
	void MoveAttenuation();

private:
	float m_fSpeed;	// スピード
	float m_fBrake;	// ブレーキ抵抗
	float m_fBoost;	// ブースト速度
	CLife_2D* m_pLife;	// 体力
	CEffectGeneratorPaeticle* m_pEffect;	// ブースターエフェクト

protected:
	// プレイヤー基底
	class PlayerActivity :public CActivity
	{
	public:
		PlayerActivity(CPlayer* player): m_pPrimary(player) {}
		~PlayerActivity() {}
		virtual PlayerActivity* update()override = 0;
		CPlayer* m_pPrimary;
	};
	// 通常
	class PlayerActivityUsually :public PlayerActivity
	{
	public:
		PlayerActivityUsually(CPlayer* player);
		~PlayerActivityUsually() {}
		virtual PlayerActivity* update()override;
	};
	// 攻撃
	class PlayerActivityAttack :public PlayerActivity
	{
	public:
		PlayerActivityAttack(CPlayer* player);
		~PlayerActivityAttack() {}
		virtual PlayerActivity* update()override;
		int nAttackCnt;
		CEffectGeneratorPaeticle* m_pEffect;
	};
	// ヒット
	class PlayerActivityHit :public PlayerActivity
	{
	public:
		PlayerActivityHit(CPlayer* player);
		~PlayerActivityHit() {}
		virtual PlayerActivity* update()override;
		int nDeathCnt;
	};
	// 死亡
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