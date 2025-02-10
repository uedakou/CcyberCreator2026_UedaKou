//===========================================
// 
// ゲームデータ保持[game_data.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _GAME_DATA_H_
#include "../base_object/save_object.h"



namespace Scene {
	namespace Game {
		class CGameObjectSave : public CSaveObject
		{
		public:
			typedef enum {
				Null = 0,
				PLAYER,	// プレイヤー
				FIELD,	// フィールド
				BILLBOAD,	// ビルボード
				TREE, // 木
				STAGE_MANEGER,	// ステージマネージャー
				// 敵
				ENEMY000,
				ENEMY100,
				MAX,
			}TYPE;

			CGameObjectSave() = delete;
			CGameObjectSave(CObject* object);
			~CGameObjectSave() override;
			CGameObjectSave* GetPrev()override { return (CGameObjectSave*)CSaveObject::GetPrev(); }
			CGameObjectSave* GetNext()override { return (CGameObjectSave*)CSaveObject::GetNext(); }
			static CGameObjectSave* crate(CObject* object, TYPE type);	//　生成
			TYPE m_type;
		private:
		};


		class CGameData
		{
		public:
			CGameObjectSave* SaveObject(CGameObjectSave::TYPE type, CObject* object);	// オブジェクト保存
			CGameObjectSave* GetTop();	// オブジェクト取得
			void FlagDeath(CGameObjectSave* pSave);				// オブジェクト破壊
			void AllFlagDeath();				// オブジェクト破壊
		private:
			CGameObjectSave* m_pTop;
			CGameObjectSave* m_pCur;
		};
	}
}



#endif //_GAME_DATA_H_