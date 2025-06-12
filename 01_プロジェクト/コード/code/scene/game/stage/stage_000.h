//===========================================
// 
// チュートリアルステージ[stage_000.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_000_H_
#define _STAGE_000_H_
#include "stage_base.h"	// シーンゲームベース
#include "./../../../base/pch.h"	// プリコンパイル
class CObject2D;
class CText;

namespace Scene {
	namespace Game {
		class CStage_000 : public CStage_Base
		{
		public:
			// チュートリアルイベント
			enum class TUTORIAL {
				Tutorial_000 = 0,	// 左右避け
				Tutorial_001,		// 飛び越え
				Tutorial_002,		// 潜り抜け
				Tutorial_003,		// アイテム
				MAX,
			};
			CStage_000(CBase* game, CGameData* gameData);
			virtual ~CStage_000();
			virtual nsPrev::CBase* Update()	override;
			virtual void Draw() const override;

			virtual bool GetPose()override;
		private:
			// メンバ変数設定
			float m_fTutorialRange;	// チュートリアルイベント発生の範囲
			// チュートリアル
			bool m_bCanShownTutorial_000;	// イベントフラグ
			bool m_bCanShownTutorial_001;	// イベントフラグ
			bool m_bCanShownTutorial_002;	// イベントフラグ
			bool m_bCanShownTutorial_003;	// イベントフラグ

			bool m_bHasShownTutorial_000;	// イベントを行ったかどうか
			bool m_bHasShownTutorial_001;	// イベントを行ったかどうか
			bool m_bHasShownTutorial_002;	// イベントを行ったかどうか
			bool m_bHasShownTutorial_003;	// イベントを行ったかどうか

			CObject2D* m_pTutorealPopup[static_cast<int>(TUTORIAL::MAX)];	// チュートリアルポップアップ

			// メンバ変数の初期値
			static const float s_fGool;			// ゴール距離
			static const string s_aStage;	// 初期チュートリアルのポップアップの大きさ

			static const float s_fTutorialRange;	// チュートリアルイベント発生の範囲
			// チュートリアル
			static const float s_fTutorial_000;	// 初期チュートリアルのイベント発生位置
			static const float s_fTutorial_001;	// 初期チュートリアルのイベント発生位置
			static const float s_fTutorial_002;	// 初期チュートリアルのイベント発生位置
			static const float s_fTutorial_003;	// 初期チュートリアルのイベント発生位置

			static const bool s_bCanShownTutorial_000;	// 初期チュートリアルのイベントフラグ
			static const bool s_bCanShownTutorial_001;	// 初期チュートリアルのイベントフラグ
			static const bool s_bCanShownTutorial_002;	// 初期チュートリアルのイベントフラグ
			static const bool s_bCanShownTutorial_003;	// 初期チュートリアルのイベントフラグ

			static const D3DXVECTOR3 s_TutorialPopupPos;	// 初期チュートリアルのポップアップの位置
			static const D3DXVECTOR3 s_TutorialPopupSiz;	// 初期チュートリアルのポップアップの大きさ


		};
	}
}
#endif // !_STAGE_000_H_
