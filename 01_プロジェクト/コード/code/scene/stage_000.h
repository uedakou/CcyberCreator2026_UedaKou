//===========================================
// 
// �X�e�[�W000[stage_000.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _STAGE_000_
#define _STAGE_000_
#include "scene_game.h"
#include "stage_load.h"
#include "../object/player.h"

namespace Scene {
	namespace Game {
		class CStage_000 : public CStageLode
		{
		public:
			CStage_000(CBase* game, CGameData* gameData);
			~CStage_000();
			virtual nsPrev::CBase* Update()	override;
			void Draw() const override;
			virtual bool GetPose()override;
		private:
			int m_nCntMakeFilde;
			CObject2D* m_pPU;	// �|�b�v�A�b�v
			static const D3DXVECTOR3 s_pPUpos;	// �|�b�v�A�b�v�ʒu
			static const D3DXVECTOR3 s_pPUsiz;	// �|�b�v�A�b�v�傫��
			static const string s_PUTextyure;	// �|�b�v�A�b�v�傫��
		};
	}
}
#endif // !_STAGE_000_
