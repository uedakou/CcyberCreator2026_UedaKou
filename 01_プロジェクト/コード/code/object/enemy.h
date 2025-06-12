//============================================
//
// 敵[enemy.h]
// Author:Uedakou
// 
//============================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "../object/base/character.h"

class CEnemy : public CCharacter
{
public:
	CEnemy();
	virtual ~CEnemy()		override;
	virtual void Init()		override;	// 初期化
	virtual void Uninit()	override;	// 終了
	virtual void Update()	override;	// 更新
	virtual void Draw()		override;	// 描画
	virtual int GetNextMotion() override { return 0; }	// 次モーション
	virtual void Hit(int nCntInvincible, int nDamage);	// ヒット
protected:
	void SetSearch(bool bSearch) { m_bSearch = bSearch; }	// 発見済みかを設定
	void SetTarget(CObject* pTarget) { m_pTarget = pTarget; }// ターゲットを設定

	CObject* GetTarget() { return m_pTarget; }	// ターゲットを取得

private:
	bool m_bSearch;	// 発見済みか
	CObject* m_pTarget;
};







#endif // _ENEMY_H_