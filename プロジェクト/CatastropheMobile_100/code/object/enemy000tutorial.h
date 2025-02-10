//============================================
//
// 敵000チュートリアル[enemy000tutoreal.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY000TUTOREAL_H_
#define _ENEMY000TUTOREAL_H_
#include "enemy000.h"	// 敵000


class CEnemy000Tutorial : public CEnemy000
{
public:
	CEnemy000Tutorial();
	virtual ~CEnemy000Tutorial();
	virtual void Init()		override;	// 初期化
	virtual void Uninit()	override;	// 終了
	virtual void Update()	override;	// 更新
	virtual void Draw()		override;	// 描画
	void Hit(int nCntInvincible, int nDamage);
	static CEnemy000Tutorial* creat(D3DXVECTOR3 pos);
protected:
	// 000 基底
	class CActivity_Enemy000Tutoriale : public CActivity
	{
	public:
		CActivity_Enemy000Tutoriale(CEnemy000Tutorial* p);
		virtual CActivity_Enemy000Tutoriale* update()override = 0;
		CEnemy000Tutorial* m_pPrimary;	// これを呼んでるポインタ
	};
	// 索敵
	class CActivity_Enemy000Tutoriale_Search : public CActivity_Enemy000Tutoriale
	{
	public:
		CActivity_Enemy000Tutoriale_Search(CEnemy000Tutorial* p);
		virtual CActivity_Enemy000Tutoriale* update()override;
	};
	//追従
	class CActivity_Enemy000Tutoriale_Following : public CActivity_Enemy000Tutoriale
	{
	public:
		CActivity_Enemy000Tutoriale_Following(CEnemy000Tutorial* p);
		virtual CActivity_Enemy000Tutoriale* update()override;
	};
	// 死亡
	class CActivity_Enemy000Tutoriale_Death : public CActivity_Enemy000Tutoriale
	{
	public:
		CActivity_Enemy000Tutoriale_Death(CEnemy000Tutorial* p);
		virtual CActivity_Enemy000Tutoriale* update()override;
		int m_nCntDeath;
	};
private:
	float m_fSpeed;	// スピード
	float m_fBrake;	// ブレーキ抵抗
	float m_fBoost;	// ブースト速度
};





#endif // _ENEMY000TUTOREAL_H_