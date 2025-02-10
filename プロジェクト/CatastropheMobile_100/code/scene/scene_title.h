//===========================================
// 
// タイトルシーン[scene_title.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_
#include "scene_base.h"
#include "../base_object/save_object.h"
#include "../object/title_select.h"	// セレクト
#include "../base_object/object_3D.h"	// ３D

class CObject;
namespace Scene{



	// 移行先クラス名
	class CTitle : public CBase
	{
	private:
	public:
		CTitle(CBase* scene);
		virtual ~CTitle();
		virtual CBase* Update()	override;
		virtual void Draw() const override;
		bool GetPose()override;
	private:
		CObject2D* m_pTitle;	// タイトル
		CTitleSelect* m_pSelect[CTitleSelect::MAX];	// セレクト
		CObject3D* m_pField[3];
		int m_nCntField;
		int m_nSelect;	// 現在選択中
		bool m_bNext;
		const int m_nCntMax;
		int m_nCnt;
	};
}



#endif // _SCENE_TITLE_H_