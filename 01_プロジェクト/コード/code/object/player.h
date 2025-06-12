//============================================
//
// プレイヤー[player.cpp]
// Author:Uedakou
// 
//============================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "base/character.h"	// キャラクター
#include "base/effect_generator_particle.h"	// エフェクトジェネレーターパーティクル

#define PLAYER_MOTIONFILE_A "data\\CHARACTER\\motion_Humimaru.txt"	// プレイヤーモーションファイルパス
#define PLAYER_RESISTANCE 0.01f		// 移動減衰

class CPlayer:public CCharacter
{
public:
	class ActivityStrategy;
	// モーション
	enum class Motion{
		ACTIVITY_NEUTRAL = 0,//	ニュートラル
		ACTIVITY_MOVE,		// 動き
		ACTIVITY_SLIDING,	// スライディング
		ACTIVITY_JANP,		// ジャンプ
		ACTIVITY_DEATH,		// 死亡
		ACTIVITY_MAX,
	};


	// パブリック関数
	// 基本処理
	CPlayer();
	virtual ~CPlayer()		override;

	// 基本処理
	void Init()		override;	// 初期化
	void Uninit()	override;	// 終了
	void Update()	override;	// 更新
	void Draw()		override;	// 描画

	// 取得
	float GetSpeed() { return m_fSpeed; }	// 速度取得
	bool IsMove() { return m_bMove; }		// 自動で移動するかどうかを取得
	float GetLaneSiz() { return m_fLane; }	// 現在の1レーンの幅の取得
	bool IsJanp() { return m_bJanp; }		// ジャンプ中かどうか設定
	bool IsSliding() { return m_bSliding; }	// スライディング中かそうか

	ActivityStrategy* GetActivity() { return m_pActivityStrategy; }	// ストラテジー取得

	// 設定
	void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }	// 速度設定
	void SetSpeedNomal() { m_fSpeed = s_fSpeed; }		// 速度設定
	void SetMove(bool bMove) { m_bMove = bMove; }		// 自動で移動するかどうかを設定
	void SetLaneSiz(float fLane) { m_fLane = fLane; }	// 現在の1レーンの幅の設定

	void SetActivity(ActivityStrategy* pActivityStrategy) { m_pActivityStrategy = pActivityStrategy; }	// ストラテジー設定

	virtual int GetNextMotion() override;	// モーションを取得

	// 処理関数
	void Hit(int nDamage)override;
	void Hit(int nCntInvincible, int nDamage) override;
	void Hit(D3DXVECTOR3 ShockRot,int nCntInvincible, int nDamage)override;

	// 生成
	static CPlayer* creat();

	// ストラテジー
	// プロテクテッドストラテジー
	class ActivityStrategy
	{
	public:
		enum class Type {
			Null = 0,	// 変更しない
			Ran,		// 走り
			LaneChangeL,	// レーンチェンジ
			LaneChangeR,	// レーンチェンジ
			Janp,		// ジャンプ
			Sliding,	// スライディング
		}m_type;	//　次ストラテジー

		ActivityStrategy() = delete;
		ActivityStrategy(CPlayer* player) : m_pPrimary(player), m_type(Type::Null),
			m_bInUP(true), m_bInDown(true), m_bInLeft(true), m_bInRight(true) {}
		virtual ~ActivityStrategy() {}

		virtual ActivityStrategy* Update(); // 更新

		// 入力
		virtual void InputUP() {}		// 上入力
		virtual void InputDown() {}		// 下入力
		virtual void InputLeft() {}		// 左入力
		virtual void InputRight() {}	// 右入力

		// 取得
		bool GetInUP() { return m_bInUP; }	// 上入力
		bool GetInDown() { return m_bInDown; }// 下入力
		bool GetInLeft() { return m_bInLeft; }// 左入力
		bool GetInRight() { return m_bInRight; }// 右入力

		// 設定
		void SetInUP(bool bIn) { m_bInUP = bIn; }// 上入力
		void SetInDown(bool bIn) { m_bInDown = bIn; }// 下入力
		void SetInLeft(bool bIn) { m_bInLeft = bIn; }// 左入力
		void SetInRight(bool bIn) { m_bInRight = bIn; }// 右入力

		virtual void Hit() {};

	protected:
		CPlayer* m_pPrimary;	// プレイヤー

		bool m_bInUP;		// 上入力
		bool m_bInDown;		// 下入力
		bool m_bInLeft;		// 左入力
		bool m_bInRight;	// 右入力
	};
	// 通常状態
	class PlayerNomarActivity :public ActivityStrategy
	{
	public:
		PlayerNomarActivity() = delete;
		PlayerNomarActivity(CPlayer* player);
		~PlayerNomarActivity();
		void InputUP()		override;	// 上入力
		void InputDown()	override;	// 下入力
		void InputLeft()	override;	// 左入力
		void InputRight()	override;	// 右入力
	};
	// ラインチェンジ状態
	class PlayerLaneChangeActivity :public ActivityStrategy
	{
	public:
			enum class LR {
			L = 0,
			R,
		} m_LR;
		PlayerLaneChangeActivity() = delete;
		PlayerLaneChangeActivity(CPlayer* player, LR lr);
		~PlayerLaneChangeActivity();
		virtual ActivityStrategy* Update();	// 更新
		void InputUP()		override;	// 上入力
		void InputDown()	override;	// 下入力
		void InputLeft()	override;	// 左入力
		void InputRight()	override;	// 右入力
		int m_nCnt;					// 移動カウント
		static const int s_nCnt = 5;	// カウント最大
	};
	// ジャンプ状態
	class PlayerJanpActivity :public ActivityStrategy
	{
	public:
		PlayerJanpActivity() = delete;
		PlayerJanpActivity(CPlayer* player);
		~PlayerJanpActivity();
		virtual ActivityStrategy* Update();	// 更新
		void InputUP()		override;	// 上入力
		void InputDown()	override;	// 下入力
		void InputLeft()	override;	// 左入力
		void InputRight()	override;	// 右入力
	};
	// スライディング状態
	class PlayerSlidingActivity :public ActivityStrategy
	{
	public:
		PlayerSlidingActivity() = delete;
		PlayerSlidingActivity(CPlayer* player);
		~PlayerSlidingActivity();
		virtual ActivityStrategy* Update();	// 更新
		void InputUP()		override;	// 上入力
		void InputDown()	override;	// 下入力
		void InputLeft()	override;	// 左入力
		void InputRight()	override;	// 右入力
		int m_nCnt;						// スライディングカウント
		static const int s_nCnt = 30;	// スライディングカウント最大
	};

private:
	// プライベート関数
	void MoveAttenuation();	// 移動減衰

private:
	// プライベート変数
	float m_fSpeed;	// スピード
	bool m_bMove;	// 自動で動くかどうか
	float m_fLane;	// 1レーンの幅
	bool m_bSliding;	// スライディングしているかどうか
	bool m_bJanp;	// ジャンプしているかどうか

	ActivityStrategy* m_pActivityStrategy;	// 行動ストラテジ
	CEffectGeneratorPaeticle* m_pEffect;	// エフェクト

	// 定数
	static const int s_nLife = 1;		// 体力初期値
	static const float s_fSpeed;	// 速度初期値
	static const bool s_bMove;		// 自動移動するかどうか
	static const float s_fLane;		// 基本の1レーンの幅
	static const X s_Collision;	// 当たり判定初期値
};

#endif // !_PLAYER_H_