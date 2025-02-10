//============================================
//
// 敵000[enemy000.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY000_H_
#define _ENEMY000_H_
#include "enemy.h"
#include "life_3d.h"
#define Enemy000_RESISTANCE 0.01f	// 移動減衰
#define Enemy000_RESISTANCE_SIDE 0.005f	// 移動減衰

#define Enemy000_XSIZE X(D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 70.0f))
#define Enemy000_SIZE D3DXVECTOR3()

#define Enemy000_MOVE (0.1f)	// 移動
//#define Enemy000_JANP (50.0f)	// ジャンプ量
#define Enemy000_SPEED 0.25f	// 初期スピード(常時)
#define Enemy000_BRAKE 0.5f	// 初期ブレーキ
#define Enemy000_BOOST 0.5f		// 初期ブースト速度
#define Eneny000_COUNT_SURVIVAL 600	// 生存時間

#define Enemy000_BEND 0.2f	// サイド移動

#define Enemy000_ATTAC 30			// 攻撃をするまでの時間
#define Enemy000_ATTAC_COOL_DOWN 60	// 攻撃のクールダウン時間

#define Enemy000_DEATHCNT 60		// 死亡からリリースまでの時間

#define Enemy000_MotionFilename "data\\CHARACTER\\motion_Enemy000.txt"	// 敵000 ファイルパス

#define Enemy000_LIFE 5
class CEffectGeneratorPaeticle;
class CEnemy000 : public CEnemy
{
public:
	CEnemy000();
	virtual ~CEnemy000();
	virtual void Init()		override;	// 初期化
	virtual void Uninit()	override;	// 終了
	virtual void Update()	override;	// 更新
	virtual void Draw()		override;	// 描画
	virtual int GetNextMotion() override;	// 次モーション
	void Hit(int nCntInvincible, int nDamage);	// ヒット処理(無敵時間, ダメージ) 
	static CEnemy000* creat(D3DXVECTOR3 pos);
private:
	float m_fSpeed;	// スピード
	float m_fBrake;	// ブレーキ抵抗
	float m_fBoost;	// ブースト速度
	CLife_3D* m_pLife3D;
	CEffectGeneratorPaeticle* m_pEffect;
protected:
	// 000 基底
	class CActivity_Enemy000 : public CActivity
	{
	public:
		CActivity_Enemy000(CEnemy000* p,int nS);
		virtual CActivity_Enemy000* update()override = 0;
		CActivity_Enemy000* DeathCnt();
		CEnemy000* m_pPrimary;	// これを呼んでるポインタ
		int m_nCntSurvival;	// 生存時間
	};
	// 索敵
	class CActivity_Enemy000_Search : public CActivity_Enemy000
	{
	public:
		CActivity_Enemy000_Search(CEnemy000* p, int nS);
		virtual CActivity_Enemy000* update()override;
	};
	//追従
	class CActivity_Enemy000_Following : public CActivity_Enemy000
	{
	public:
		CActivity_Enemy000_Following(CEnemy000* p, int nS);
		virtual CActivity_Enemy000* update()override;
		int m_nCntAttac;	// 攻撃を行うまでの時間
	};
	//攻撃
	class CActivity_Enemy000_Tackle : public CActivity_Enemy000
	{
	public:
		CActivity_Enemy000_Tackle(CEnemy000* p, int nS);
		virtual CActivity_Enemy000* update()override;
		int m_nCnt;
		D3DXVECTOR3 m_Move;
		CEffectGeneratorPaeticle* m_pEffect;
	};
	// 死亡
	class CActivity_Enemy000_Death : public CActivity_Enemy000
	{
	public:
		CActivity_Enemy000_Death(CEnemy000* p);
		virtual CActivity_Enemy000* update()override;
		int m_nCntDeath;
	};
};
#endif // !_ENEMY000_H_