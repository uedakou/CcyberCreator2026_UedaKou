//===========================================
// 
// デバックシーン[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_DEBUG_H_
#define _SCENE_DEBUG_H_
#include "stage_base.h"	// シーンゲームベース

class CObject3D;	// オブジェクト３Ｄ
class CText;	// テキスト

namespace Scene {
	namespace Game {
		class CSceneDebug : public CStage_Base
		{
		public:
			CSceneDebug(CBase* scene, CGameData* gameData);
			virtual ~CSceneDebug()		override;
			virtual nsPrev::CBase* Update()	override;	// 更新
			virtual void Draw() const override;	// 描画
			virtual bool GetPose()override;
		private:
			bool m_bPose;	// ポーズ状態
			bool m_bCameraFollowPlayer;	// カメラがプレイヤーを追従するかどうか
			float m_fCameraRot;		// プレイヤーからのカメラの角度


			static const bool s_bCameraFollowPlayer;
			static const float s_fCameraRot;
			static const float s_fGool;
		};
	}
}



#endif // !_SCENE_DEBUG_H_
