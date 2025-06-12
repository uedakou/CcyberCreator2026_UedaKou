//============================================
//
// リザルトシーン[scene_result.h]
// Author:Uedakou
// 
//============================================
#ifndef _SCENE_RESULT_H_
#define _SCENE_RESULT_H_
#include "scene_base.h"
class CText;		// テキスト
class CObject;		// オブジェクト
class CObject3D;	// ３Dオブジェクト
class CObjectMotion;// モーションオブジェクト
namespace Scene {
	class CResult : public CBase
	{
	public:
		CResult(CBase* scene);
		~CResult() override;
		virtual CBase* Update()	override;
		virtual void Draw() const override;
		void SetScore(int nScore);
		bool GetPose()override;	// ポーズ状態取得
		void LoadRanc();		// ランキング読み込み
		void SaveRanc();		// ランキング読み込み

	private:
		// 背景
		CObjectMotion* m_pCor;;		// プレイヤー
		CObject3D* m_pField[2];	// 地面
		unsigned int m_nCntField;
		// ランキング
		CText* m_Ranc[5];	// ランキング表示用テキスト
		int m_nRanc[5];		// ランキングスコア
		CText* m_Score;		// 現在スコア表示用テキスト
		int m_nScore;		// 現在スコア

		int m_nCntFlashing;	// 点滅カウント
		const int m_nMAXCntFlashing;	// 最大点滅カウント
		bool bFlashing;		// 変色させているか
	};
}

#endif // !_SCENE_RESULT_H_