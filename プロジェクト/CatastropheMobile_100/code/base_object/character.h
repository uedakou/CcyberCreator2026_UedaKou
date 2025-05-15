//===========================================
// 
// キャラクター[charactor.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "motion.h"
#include "../base/calculation.h"

#define BASE_RESISTANCE 0.01f


class CCharacter : public CObjectMotion
{
public:
	CCharacter();
	virtual ~CCharacter()	override;
	virtual void Init()		override;	// 初期化
	virtual void Uninit()	override;	// 終了
	virtual void Update()	override;	// 更新
	virtual void Draw()		override;	// 描画

	virtual int GetNextMotion() override ;	// 次モーション

		// ステータス設定
	void SetLife(int nLife)				{ m_nLife = nLife; }				// 体力設定
	void SetInvincible(int nInvincible) { m_nCntInvincible = nInvincible; }	// 無敵時間設定
	void SetAttcak(int nAttcak)			{ m_nAttcak = nAttcak; }			// 攻撃力設定
	void SetDefense(int nDefense)		{ m_nDefense = nDefense; }			// 防御力設定
	void SetSpeed(int nSpeed)			{ m_fSpeed = nSpeed; }				// 速度設定
	// ステータス取得
	int GetLife()		{ return m_nLife; }				// 体力設定
	int GetInvincible() { return m_nCntInvincible; }	// 無敵時間設定
	int GetAttcak()		{ return m_nAttcak; }			// 攻撃力設定
	int GetDefense()	{ return m_nDefense; }			// 防御力設定
	int GetSpeed()		{ return m_fSpeed; }			// 速度設定
	// ステータス加算
	void AddLife(int nLife)				{ m_nLife += nLife; }						// 体力設定
	void AddInvincible(int nInvincible)	{ m_nCntInvincible += nInvincible; }		// 無敵時間設定
	void AddAttcak(int nAttcak)			{ m_nAttcak += nAttcak; }					// 攻撃力設定
	void AddDefense(int nDefense)		{ m_nDefense += nDefense; }					// 防御力設定
	void AddSpeed(int fSpeed)			{ m_fSpeed += fSpeed; }						// 速度設定

	// 運動量設定



	void SetMoveX(X x) { m_xmove = x;}
	void SetMovePos(D3DXVECTOR3 pos) { m_xmove.pos = pos; }// 位置設定
	void SetMovePosX(float x) { m_xmove.pos.x = x; }// 位置設定
	void SetMovePosY(float y) { m_xmove.pos.y = y; }// 位置設定
	void SetMovePosZ(float z) { m_xmove.pos.z = z; }// 位置設定
	void SetMoveRot(D3DXVECTOR3 rot) { m_xmove.rot = rot; }// 向き設定
	void SetMoveRotX(float x) { m_xmove.rot.x = x; }// 向き設定
	void SetMoveRotY(float y) { m_xmove.rot.y = y; }// 向き設定
	void SetMoveRotZ(float z) { m_xmove.rot.z = z; }// 向き設定
	void SetMoveSiz(D3DXVECTOR3 siz) { m_xmove.scl = siz; }// 大きさ設定
	void SetMoveSizX(float x) { m_xmove.scl.x = x; }// 大きさ設定
	void SetMoveSizY(float y) { m_xmove.scl.y = y; }// 大きさ設定
	void SetMoveSizZ(float z) { m_xmove.scl.z = z; }// 大きさ設定

	X GetMoveX() { return m_xmove; }
	D3DXVECTOR3 GetMovePos() { return m_xmove.pos; }// 運動量設定
	D3DXVECTOR3 GetMoveRot() { return m_xmove.rot; }// 回転量設定
	D3DXVECTOR3 GetMoveSiz() { return m_xmove.scl; }// 膨張量設定

	void AddMoveX(X x) { m_xmove = x; }
	void AddMovePos(D3DXVECTOR3 pos) { m_xmove.pos += pos; }// 位置設定
	void AddMovePosX(float x) { m_xmove.pos.x += x; }// 大きさ設定
	void AddMovePosY(float y) { m_xmove.pos.y += y; }// 大きさ設定
	void AddMovePosZ(float z) { m_xmove.pos.z += z; }// 大きさ設定
	void AddMoveRot(D3DXVECTOR3 rot) { m_xmove.rot += rot; }// 向き設定
	void AddMoveRotX(float x) { m_xmove.rot.x += x; }// 大きさ設定
	void AddMoveRotY(float y) { m_xmove.rot.y += y; }// 大きさ設定
	void AddMoveRotZ(float z) { m_xmove.rot.z += z; }// 大きさ設定
	void AddMoveSiz(D3DXVECTOR3 siz) { m_xmove.scl += siz; }// 大きさ設定
	void AddMoveSizX(float x) { m_xmove.scl.x += x; }// 大きさ設定
	void AddMoveSizY(float y) { m_xmove.scl.y += y; }// 大きさ設定
	void AddMoveSizZ(float z) { m_xmove.scl.z += z; }// 大きさ設定

	// 当たり判定
	void SetCollisionX(X pX) { m_Xcollision = pX; }	//	当たり判定設定
	void SetCollisionPos(D3DXVECTOR3 pPos) { m_Xcollision.pos = pPos; }	//	当たり判定設定
	void SetCollisionRot(D3DXVECTOR3 pRot) { m_Xcollision.rot = pRot; }	//	当たり判定設定
	void SetCollisionSiz(D3DXVECTOR3 pSiz) { m_Xcollision.scl = pSiz; }	//	当たり判定設定

	X GetCollisionX() { return m_Xcollision; }	//	当たり判定取得
	D3DXVECTOR3 GetCollisionPos() { return m_Xcollision.pos; }	//	当たり判定取得
	D3DXVECTOR3 GetCollisionRot() { return m_Xcollision.rot; }	//	当たり判定取得
	D3DXVECTOR3 GetCollisionSiz() { return m_Xcollision.scl; }	//	当たり判定取得
protected:
	virtual void Hit(int nDamage);
	virtual void Hit(int nCntInvincible, int nDamage);
	virtual void Hit(D3DXVECTOR3 ShockRot, int nCntInvincible, int nDamage);
protected :
	virtual void MoveAttenuation();	// 移動減衰
	class CActivity
	{
	public:
		CActivity() {}
		virtual CActivity* update() = 0;
	};
	virtual void ActivityUpdate();
	CActivity* m_pActivity;		// 攻撃行動

private:
	int m_nLife;	// 体力
	int m_nCntInvincible;	// 無敵時間
	int m_nAttcak;	// 攻撃力
	int m_nDefense;	// 防御
	int m_fSpeed;	// 速度

	X m_Xcollision;	// 当たり判定位置
	X m_xmove;		// 変化量(運動量,回転量,膨張量)
	bool bJump;

};


#endif // !_CHARACTER_H_


