//===========================================
// 
// タイトルシーン[scene_title.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_
#include "scene_base.h"
#include "../object/base/object_3D.h"	// ３D

class CObject;
class CObject2D;
namespace Scene{
	enum class SELECT_TYPE {
		STATE = 0,
		END,
		MAX
	};
	class CTitle : public CBase
	{
	private:
	public:
		CTitle(CBase* scene);
		virtual ~CTitle();
		virtual CBase* Update()	override;	// 更新
		virtual void Draw() const override;	// 描画
		bool GetPose()override;		// ポーズ状態取得
	private:
		CObject2D* m_pTitle;	// タイトル
		CObject2D* m_pBG;			// 背景
		CObject2D* m_pOptions[static_cast<unsigned int>(SELECT_TYPE::MAX)];	// 選択肢
		CObject2D* m_pSelectedOption;		// 選択中の

		int m_nSelect;	// 現在セレクト
		bool m_bNext;	// 
		const int m_nCntMax;	// 
		int m_nCnt;

		static const D3DXCOLOR m_Selected;		// 選択中
		static const D3DXCOLOR m_NotSelected;	// 非選択中
	};
}



#endif // _SCENE_TITLE_H_