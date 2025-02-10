//===========================================
// 
// ゲームデータ保持[game_data.cpp]
// Auther:UedaKou
// 
//===========================================
#include "game_data.h"
// オブジェクト保存
namespace Scene
{
	namespace Game
	{
		//============================================
		// コンストラクタ
		//============================================
		CGameObjectSave::CGameObjectSave(CObject* object):
			CSaveObject(object)
		{
			m_type = TYPE::Null;
		};
		//============================================
		// デストラクタ
		//============================================
		CGameObjectSave::~CGameObjectSave()
		{

		}
		//============================================
		//　生成
		//============================================
		CGameObjectSave* CGameObjectSave::crate(CObject* object, TYPE type)
		{
			CGameObjectSave* p = new CGameObjectSave(object);


			p->m_type = type;

			return p;
		}
		//============================================
		// 保存
		//============================================
		CGameObjectSave* CGameData::SaveObject(CGameObjectSave::TYPE type, CObject* object)
		{
			CGameObjectSave* p = CGameObjectSave::crate(object, type);

			p->SetList(m_pTop, m_pCur);

			return p;
		}
		//============================================
		// 取得
		//============================================
		CGameObjectSave* CGameData::GetTop()
		{
			return m_pTop;
		}
		//============================================
		// 死亡フラグを立てる
		//============================================
		void CGameData::FlagDeath(CGameObjectSave* pSave)
		{
			pSave->FlagDeath();
			if (m_pTop == pSave)
			{
				m_pTop = pSave->GetNext();
			}
			if (m_pCur == pSave)
			{
				m_pCur = pSave->GetPrev();
			}

		}
		//============================================
		// 全ての死亡フラグを立てる
		//============================================
		void CGameData::AllFlagDeath()
		{
			CGameObjectSave* pObject = m_pTop;
			CGameObjectSave* pNext = nullptr;
			while (pObject != nullptr)
			{
				pNext = pObject->GetNext();

				FlagDeath(pObject);


				pObject = pNext;
			}
			m_pTop = nullptr;
			m_pCur = nullptr;

		}
	}
}