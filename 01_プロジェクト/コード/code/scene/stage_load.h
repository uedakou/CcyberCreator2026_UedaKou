//===========================================
// 
// �X�e�[�W�ǂݍ���[stage_load.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SCENE_LOAD_H_
#define _STAGE_000_
#include "scene_game.h"
#include "game_data.h"
#include "../object/player.h"
#define MAX_TEXTURE 64	// �e�N�X�`���ő吔
#define MAX_MODEL 64	// ���f���ő吔

namespace Scene {
	namespace Game {
		// �����\��
		class CCreat
		{
		public:
			CCreat() {
				m_pos = { 0.0f, 0.0f, 0.0f };
				m_fLeng = 0.0f;
				m_type = FIELD;

				m_pPrev = nullptr;
				m_pNext = nullptr;
			}
			typedef enum {
				FIELD = 0,	// �n��
				WALL,		// ��
				MODEL,		// ���f��
				BILLBOARD,	// �r���{�[�h
				ENEMY,		// �G
				MAX,
			}TYPE;
			D3DXVECTOR3 m_pos;	// �����ʒu
			float m_fLeng;		// �������锼�a
			TYPE m_type;		// ���

			CCreat* m_pPrev;
			CCreat* m_pNext;
		};
		// �t�B�[���h
		class CCreatField : public CCreat
		{
		public:
			CCreatField() {
				m_tex = nullptr;
				m_rot = { 0.0f, 0.0f, 0.0f };
				m_siz = { 0.0f, 0.0f, 0.0f };
				m_nBlockX = 0;
				m_nBlockY = 0;
			}
			LPDIRECT3DTEXTURE9 m_tex;
			D3DXVECTOR3 m_rot;
			D3DXVECTOR3 m_siz;
			int m_nBlockX;
			int m_nBlockY;
		};
		// ��
		class CCreatWall : public CCreat
		{
		public :
			CCreatWall() {
				m_tex = nullptr;
				m_rot = { 0.0f, 0.0f, 0.0f };
				m_siz = { 0.0f, 0.0f, 0.0f };
				m_nBlockX = 0;
				m_nBlockY = 0;
			}
			LPDIRECT3DTEXTURE9 m_tex;
			D3DXVECTOR3 m_rot;
			D3DXVECTOR3 m_siz;
			int m_nBlockX;
			int m_nBlockY;
		};
		// ���f��
		class CCreatModel : public CCreat
		{
		public:
			CCreatModel() {
				m_aFName = "";
				m_rot = { 0.0f, 0.0f, 0.0f };
			}
			string m_aFName;
			D3DXVECTOR3 m_rot;
		};
		// �r���{�[�h
		class CCreatBillboard : public CCreat
		{
		public:
			CCreatBillboard() {
				m_tex = nullptr;
				m_siz = { 0.0f, 0.0f, 0.0f };
				m_nOriginX = 0;
				m_nOriginY = 0;
			}
			LPDIRECT3DTEXTURE9 m_tex;
			D3DXVECTOR3 m_siz;
			int m_nOriginX;
			int m_nOriginY;
		};
		// �G
		class CCreatEnemy : public CCreat
		{
		public:
			CCreatEnemy() {
				m_enemytype = ENEMY_TYPE::Enemy000;
			}
			typedef enum {
				Enemy000 = 0,
				Enemy100,
				MAX
			}ENEMY_TYPE;
			ENEMY_TYPE m_enemytype;
		};


		// �X�e�[�W���[�h�N���X
		class CStageLode : public CBase
		{
		public:
			CStageLode(CBase* game, CGameData* gameData);
			virtual ~CStageLode();
			virtual nsPrev::CBase* Update()	override;
			void Draw() const override;
			virtual bool GetPose()override;
			virtual CCreat* crate(CCreat::TYPE type, float fLeng);
			bool LodeMap(const char* aFileName);
			bool LodeMap(string aFileName);
		private:
			CPlayer* m_pPlayer;	// �v���C���[
			CCreat* m_pCrateObjectTop;	// �����I�u�W�F�N�g�擪
			CCreat* m_pCrateObjectCor;	// �����I�u�W�F�N�g�Ō��
		};
	}
}
#endif // !_STAGE_000_