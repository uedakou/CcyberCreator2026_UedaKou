//===========================================
// 
// デバックシーン[scene_debug.cpp]
// Auther:UedaKou
// 
//===========================================
#include "scene_debug.h"	// デバックシーン
#include "../base/manager.h"		// マネージャー
#include "../object/field.h"		// フィールド


namespace Scene {
	namespace Game {
		//============================================
		// コンストラクタ
		//============================================
		CSceneDebug::CSceneDebug(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			m_pField = CField::creat(CField::TYPE::Road, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		}
		//============================================
		// デストラクタ
		//============================================
		CSceneDebug::~CSceneDebug()
		{
			m_pField->DeathFlag();
		}
		//============================================
		// 更新
		//============================================
		CBase* CSceneDebug::Update()
		{
			m_pField->Update();

			return this;
		}
		//============================================
		// 描画
		//============================================
		void CSceneDebug::Draw() const
		{
		}

		//============================================
		// ポーズ中取得
		//============================================
		bool CSceneDebug::GetPose()
		{
			return false;
		}

		template<>
		nsPrev::CBase* CBase::makeScene<CSceneDebug>(CGameData* gamaData) {
			return new CSceneDebug(this, gamaData);
		}
	}
}