//============================================
//
// 敵100[enemy100.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY100_H_
#define _ENEMY100_H_
#include "enemy.h"
#define Enemy100_RESISTANCE 0.01f	// 移動減衰
#define Enemy100_RESISTANCE_SIDE 0.005f	// 移動減衰


#define Enemy100_SIZE X(D3DXVECTOR3(0.0f, 0.0f, -80.0f), D3DXVECTOR3(0.0f, 0.0f ,0.0f), D3DXVECTOR3(10.0f, 10.0f, 120.0f))

#define Enemy100_MOVE (0.1f)	// 移動
//#define Enemy000_JANP (50.0f)	// ジャンプ量
#define Enemy100_SPEED 0.25f	// 初期スピード(常時)
#define Enemy100_BRAKE 0.1f	// 初期ブレーキ
#define Enemy100_BOOST 0.5f	// 初期ブースト速度
#define Eneny100_COUNT_SURVIVAL 1800	// 生存時間

#define Enemy100_BEND 0.1f	// サイド移動

class CEffectGeneratorPaeticle;
class CLife_3D;
class CEnemy100 : public CEnemy
{
public:
	CEnemy100();
	virtual ~CEnemy100();
	virtual void Init()		override;	// 初期化
	virtual void Uninit()	override;	// 終了
	virtual void Update()	override;	// 更新
	virtual void Draw()		override;	// 描画
	virtual int GetNextMotion() override;	// 次モーション
	void Hit(int nCntInvincible, int nDamage) override;
	static CEnemy100* creat(D3DXVECTOR3 pos);

private:
	float m_fSpeed;	// スピード
	float m_fBrake;	// ブレーキ抵抗
	float m_fBoost;	// ブースト速度
	int m_nCntSurvival;	// 生存時間
	CLife_3D* m_pLife3D;

private:
	CEffectGeneratorPaeticle* m_pEffect;	// エフェクト
	// 基底
	class CActivity_Enemy100 : public CActivity
	{
	public:
		CActivity_Enemy100(CEnemy100* p);
		virtual CActivity_Enemy100* update()override = 0;
		CEnemy100* m_pPrimary;	// これを呼んでるポインタ
	};
	// 索敵
	class CActivity_Enemy100_Search : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Search(CEnemy100* p);
		CActivity_Enemy100* update()override;
	};
	// 追跡
	class CActivity_Enemy100_Following : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Following(CEnemy100* p);
		CActivity_Enemy100* update()override;
		const int m_MaxCnt;
		int m_nCnt;	// 攻撃を行うまでの時間
		typedef enum {
			TACKL = 0,	// タックル
			SUMMON,		// 召喚
			MAX
		}ATTACE_TYPE;
	};
	// タックル
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
	// 召喚
	class CActivity_Enemy100_Summon : public CActivity_Enemy100
	{
	public:
		CActivity_Enemy100_Summon(CEnemy100* p);
		CActivity_Enemy100* update()override;
		const int m_MaxCnt;
		int m_nCnt;
	};
	// 死亡
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