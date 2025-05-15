//===========================================
// 
// �Q�[���f�[�^�ێ�[game_data.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _GAME_DATA_H_
#include "../base_object/save_object.h"


class CPlayer;	// �v���C���[
namespace Scene {
	namespace Game {
		class CGameObjectSave : public CSaveObject
		{
		public:
			typedef enum {
				Null = 0,
				PLAYER,	// �v���C���[
				FIELD,	// �t�B�[���h
				BILLBOAD,	// �r���{�[�h
				SCORE,	// �X�R�A
				TREE, // ��
				STAGE_MANEGER,	// �X�e�[�W�}�l�[�W���[
				// �G
				ENEMY000,
				ENEMY100,
				MAX,
			}TYPE;

			CGameObjectSave() = delete;
			CGameObjectSave(CObject* object);
			~CGameObjectSave() override;
			TYPE GetType() { return m_type; }

			CGameObjectSave* GetPrev()override { return (CGameObjectSave*)CSaveObject::GetPrev(); }
			CGameObjectSave* GetNext()override { return (CGameObjectSave*)CSaveObject::GetNext(); }
			static CGameObjectSave* crate(CObject* object, TYPE type);	//�@����
			TYPE m_type;
		private:
		};


		class CGameData
		{
		public:
			CGameObjectSave* SaveObject(CGameObjectSave::TYPE type, CObject* object);	// �I�u�W�F�N�g�ۑ�
			CGameObjectSave* GetTop();	// �I�u�W�F�N�g�擾
			void FlagDeath(CGameObjectSave* pSave);				// �I�u�W�F�N�g�j��
			void AllFlagDeath();				// �I�u�W�F�N�g�j��
			// �ݒ�
			void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }	// �v���C���[�ݒ�
			void SetScore(int nScore) { m_nScore = nScore; }	// �X�R�A�ݒ�
			// ���Z
			void AddScore(int nScore) { m_nScore += nScore; }	// �X�R�A�ݒ�
			// �擾
			CPlayer* GetPlayer() { return m_pPlayer; }		// �v���C���[�擾
			int GetScore() { return m_nScore; }	// �X�R�A�擾
		private:
			CGameObjectSave* m_pTop;
			CGameObjectSave* m_pCur;
			CPlayer* m_pPlayer;		// �v���C���[
			int m_nScore;	// �X�R�A
		};
	}
}



#endif //_GAME_DATA_H_