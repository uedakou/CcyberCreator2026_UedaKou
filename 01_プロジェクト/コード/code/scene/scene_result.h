//============================================
//
// ���U���g�V�[��[scene_result.h]
// Author:Uedakou
// 
//============================================
#ifndef _SCENE_RESULT_H_
#define _SCENE_RESULT_H_
#include "scene_base.h"
class CText;		// �e�L�X�g
class CObject;		// �I�u�W�F�N�g
class CObject3D;	// �RD�I�u�W�F�N�g
class CObjectMotion;// ���[�V�����I�u�W�F�N�g
namespace Scene {
	class CResult : public CBase
	{
	public:
		CResult(CBase* scene);
		~CResult() override;
		virtual CBase* Update()	override;
		virtual void Draw() const override;
		void SetScore(int nScore);
		bool GetPose()override;	// �|�[�Y��Ԏ擾
		void LoadRanc();		// �����L���O�ǂݍ���
		void SaveRanc();		// �����L���O�ǂݍ���

	private:
		// �w�i
		CObjectMotion* m_pCor;;		// �v���C���[
		CObject3D* m_pField[2];	// �n��
		unsigned int m_nCntField;
		// �����L���O
		CText* m_Ranc[5];	// �����L���O�\���p�e�L�X�g
		int m_nRanc[5];		// �����L���O�X�R�A
		CText* m_Score;		// ���݃X�R�A�\���p�e�L�X�g
		int m_nScore;		// ���݃X�R�A

		int m_nCntFlashing;	// �_�ŃJ�E���g
		const int m_nMAXCntFlashing;	// �ő�_�ŃJ�E���g
		bool bFlashing;		// �ϐF�����Ă��邩
	};
}

#endif // !_SCENE_RESULT_H_