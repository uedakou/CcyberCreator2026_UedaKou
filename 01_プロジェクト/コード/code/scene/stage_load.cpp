//===========================================
// 
// �X�e�[�W000[stage_000.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_load.h"
#include "../object/enemy000.h"
// �t�@�C�����J���̂ɕK�v
#include <fstream>
#include <iostream>
#include "../object/enemy100.h"
namespace Scene {
	namespace Game {
		//============================================
		// �R���X�g
		//============================================
		CStageLode::CStageLode(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			m_pPlayer = nullptr;
			m_pCrateObjectTop = nullptr;
			m_pCrateObjectCor = nullptr;
		}
		//============================================
		// �f�X�g���N�^
		//============================================
		CStageLode::~CStageLode()
		{

		}
		//============================================
		// �X�V
		//============================================
		nsPrev::CBase* CStageLode::Update()
		{

			if (m_pPlayer != nullptr)
			{
				if (m_pPlayer->GetType() == CObject::TYPE::PLAYER)
				{
					// �����𖞂�������I�u�W�F�N�g����
					CCreat* object = m_pCrateObjectTop;
					CCreat* pNext = nullptr;
					while (object != nullptr)
					{
						pNext = object->m_pNext;

						D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
						D3DXVECTOR3 Objectpos = object->m_pos;
						float fObjectLeng = object->m_fLeng;
						float fLeng = hypot(PlayerPos.x - Objectpos.x, PlayerPos.z - Objectpos.z);
						if (fLeng <= fObjectLeng)
						{
							switch (object->m_type)
							{
							case CCreat::FIELD:


								break;
							case CCreat::WALL:


								break;
							case CCreat::MODEL:
								break;
							case CCreat::BILLBOARD:


								break; 
							case CCreat::ENEMY:
								CCreatEnemy* pEnemy = (CCreatEnemy*)object;
								switch (pEnemy->m_enemytype)
								{
								case CCreatEnemy::ENEMY_TYPE::Enemy000:
								{
									CEnemy000* pEnenmy = CEnemy000::creat(Objectpos);
									m_gameData->SaveObject(CGameObjectSave::TYPE::ENEMY000, pEnenmy);
								}

									break;
								case CCreatEnemy::ENEMY_TYPE::Enemy100:
								{
									CEnemy100* pEnenmy = CEnemy100::creat(Objectpos);
									m_gameData->SaveObject(CGameObjectSave::TYPE::ENEMY100, pEnenmy);
								}
									break;
								}
								break; 
							}


							if (object == m_pCrateObjectTop)
							{
								m_pCrateObjectTop = pNext;
							}

							if (object == m_pCrateObjectCor)
							{
								m_pCrateObjectCor = nullptr;
							}
							delete object;
						}
						object = pNext;
					}
				}
			}
			else
			{
				CObject* object[MAX_PRIORITY] = {};
				CObject::GetAllObject(object);
				CObject* next = nullptr;
				for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
				{
					while (object[nCnt] != nullptr)
					{
						next = object[nCnt]->GetNext();

						if (object[nCnt]->GetType() == CObject::TYPE::PLAYER)
						{
							m_pPlayer = (CPlayer*)object[nCnt];
							break;
						}
						object[nCnt] = next;
					}
				}
			}
			return this;
		}
		//============================================
		// �`��
		//============================================
		void CStageLode::Draw() const
		{

		}

		//============================================
		// �|�[�Y���擾
		//============================================
		bool CStageLode::GetPose()
		{
			return false;
		}
		//============================================
		// �쐬
		//============================================
		CCreat* CStageLode::crate(CCreat::TYPE type, float fLeng)
		{
			CCreat* p = nullptr;
			switch (type)
			{
			case CCreat::FIELD:
				p = new CCreatField();
				break;
			case CCreat::WALL:
				p = new CCreatWall();
				break;
			case CCreat::MODEL:
				p = new CCreatModel();
				break;
			case CCreat::BILLBOARD:
				p = new CCreatBillboard();
				break;
			case CCreat::ENEMY:
				p = new CCreatEnemy();
				break;
			default:
				p = new CCreat();
				break;
			}
			p->m_type = type;
			p->m_fLeng = fLeng;
			if (m_pCrateObjectTop == nullptr)
			{
				m_pCrateObjectTop = p;
			}
			if (m_pCrateObjectCor == nullptr)
			{
				m_pCrateObjectCor = p;
			}
			else
			{
				m_pCrateObjectCor->m_pNext = p;
				p->m_pPrev = m_pCrateObjectCor;
				m_pCrateObjectCor = p;
			}
			return p;
		}
		//============================================
		// �쐬
		//============================================
		bool CStageLode::LodeMap(const char* aFileName)
		{
			LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

			ifstream file(aFileName);  // �ǂݍ��ރt�@�C���̃p�X���w��
			if (file.fail()) {
				cerr << "�t�@�C�����J���܂���ł���\n";
				return false;
			}
			string str0, str1, str2, str3;	// ������i�[�p
			string skip;			// �X�L�b�v�p�i�[
			string aTextureFile[MAX_TEXTURE];	// �e�N�X�`���t�@�C���t�@�C���p�X
			string aModelFile[MAX_MODEL];	// ���f���t�@�C���t�@�C���p�X
			int nCntTexture = 0;
			int nMaxTexture = 0;
			int nCntModel = 0;
			int nMaxModel = 0;



			// ���o���Z�q>>���g���ăf���~�^�ŋ�؂�ꂽ�P��C�l��ǂݍ���
			while (file >> str0)
			{
				// �R�����g�A�E�g
				if (str0[0] == '#')
				{
					getline(file, skip);	// ��s�X�L�b�v
				}
				// �e�N�X�`����
				else if (str0.compare("NUM_TEXTURE") == 0)
				{
					file >> skip;	// = ���X�L�b�v
					file >> str1;	// �e�N�X�`�������擾
					nMaxTexture = atoi(str1.c_str());
					getline(file, skip);	// ��s�X�L�b�v
				}
				// �e�N�X�`���p�X
				else if (str0.compare("TEXTURE_FILENAME") == 0 &&
					nCntTexture < nMaxTexture &&
					nMaxTexture > 0)
				{
					file >> skip;	// = ���X�L�b�v
					file >> str1;	// �e�N�X�`���p�X���擾
					aTextureFile[nCntTexture] = str1;
					getline(file, skip);	// ��s�X�L�b�v
					nCntTexture++;
				}
				// ���f����
				else if (str0.compare("NUM_MODEL") == 0)
				{
					file >> skip;	// = ���X�L�b�v
					file >> str1;	// ���f�������擾
					nMaxModel = atoi(str1.c_str());
					getline(file, skip);	// ��s�X�L�b�v
				}
				// ���f���p�X
				else if (str0.compare("TEXTURE_FILENAME") == 0 &&
					nCntModel < nMaxModel &&
					nMaxModel > 0)
				{
					file >> skip;	// = ���X�L�b�v
					file >> str1;	// ���f���p�X���擾
					aModelFile[nCntModel] = str1;
					getline(file, skip);	// ��s�X�L�b�v
				}
				// �J����(���g�p)
				else if (str0.compare("CAMERASET") == 0)
				{
					while (file >> str1)
					{
						if (str1.compare("END_CAMERASET") == 0)
						{
							continue;
						}
					}
				}
				// ���C�g(���g�p)
				else if (str0.compare("LIGHTSET") == 0)
				{
					while (file >> str1)
					{
						if (str1.compare("END_LIGHTSET") == 0)
						{
							continue;
						}
					}
				}
				// �� (���g�p)
				else if (str0.compare("SKYSET") == 0)
				{
					while (file >> str1)
					{
						if (str1.compare("END_SKYSET") == 0)
						{
							continue;
						}
					}
				}
				// �R(���g�p)
				else if (str0.compare("MOUNTAINSET") == 0)
				{
					while (file >> str1)
					{
						if (str1.compare("END_MOUNTAINSET") == 0)
						{
							continue;
						}
					}
				}
				// �n��
				else if (str0.compare("FIELDSET") == 0)
				{
					CCreatField* pField = (CCreatField*)crate(CCreat::TYPE::FIELD, 5000.0f);
					while (file >> str1)
					{
						if (str1.compare("TEXTYPE") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �e�N�X�`��
								// �e�N�X�`��
							D3DXCreateTextureFromFile(
								pDevice,
								aTextureFile[atoi(str2.c_str())].c_str(),
								&pField->m_tex);
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("POS") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �ʒu���擾
							pField->m_pos.x = stof(str2.c_str());
							file >> str2;	// �ʒu���擾
							pField->m_pos.y = stof(str2.c_str());
							file >> str2;	// �ʒu���擾
							pField->m_pos.z = stof(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("ROT") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �������擾
							pField->m_rot.x = stof(str2.c_str());
							file >> str2;	// �������擾
							pField->m_rot.y = stof(str2.c_str());
							file >> str2;	// �������擾
							pField->m_rot.z = stof(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("BLOCK") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �������擾
							pField->m_nBlockX = atoi(str2.c_str());
							file >> str2;	// ���������擾
							pField->m_nBlockY = atoi(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("SIZE") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �傫�����擾
							pField->m_siz.x = stof(str2.c_str());
							file >> str2;	// �傫�����擾
							pField->m_siz.y = stof(str2.c_str());
							file >> str1;	// �傫�����擾
							pField->m_siz.z = stof(str1.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("END_FIELDSET") == 0)
						{
							continue;
						}
					}
				}
				// ��
				else if (str0.compare("WALLSET") == 0)
				{
					CCreatWall* pWall = (CCreatWall*)crate(CCreat::TYPE::WALL, 5000.0f);
					while (file >> str1)
					{
						if (str1.compare("TEXTYPE") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �e�N�X�`�����擾
							D3DXCreateTextureFromFile(
								pDevice,
								aTextureFile[atoi(str2.c_str())].c_str(),
								&pWall->m_tex);
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("POS") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �ʒu���擾
							pWall->m_pos.x = stof(str2.c_str());
							file >> str2;	// �ʒu���擾
							pWall->m_pos.y = stof(str2.c_str());
							file >> str2;	// �ʒu���擾
							pWall->m_pos.z = stof(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("ROT") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �������擾
							pWall->m_rot.x = stof(str2.c_str());
							file >> str2;	// �������擾
							pWall->m_rot.y = stof(str2.c_str());
							file >> str2;	// �������擾
							pWall->m_rot.z = stof(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("BLOCK") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// ���������擾
							pWall->m_nBlockX = atoi(str2.c_str());
							file >> str2;	// ���������擾
							pWall->m_nBlockY = atoi(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("SIZE") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �傫���擾
							pWall->m_siz.x = stof(str2.c_str());
							file >> str2;	// �傫�����擾
							pWall->m_siz.y = stof(str2.c_str());
							file >> str2;	// �傫�����擾
							pWall->m_siz.z = stof(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("END_WALLSET") == 0)
						{
							continue;
						}
					}
				}
				// �r���{�[�h
				else if (str0.compare("BILLBOARDSET") == 0)
				{
					CCreatBillboard* pBillboard = (CCreatBillboard*)crate(CCreat::TYPE::BILLBOARD, 5000.0f);
					while (file >> str1)
					{
						if (str1.compare("TEXTYPE") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �e�N�X�`��
							D3DXCreateTextureFromFile(
								pDevice,
								aTextureFile[atoi(str2.c_str())].c_str(),
								&pBillboard->m_tex);
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("POS") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �ʒu���擾
							pBillboard->m_pos.x = stof(str2.c_str());
							file >> str2;	// �ʒu���擾
							pBillboard->m_pos.y = stof(str2.c_str());
							file >> str2;	// �ʒu���擾
							pBillboard->m_pos.z = stof(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("SIZE") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �ʒu���擾
							pBillboard->m_siz.x = stof(str2.c_str());
							file >> str2;	// �傫�����擾
							pBillboard->m_siz.y = stof(str2.c_str());
							file >> str2;	// �傫�����擾
							pBillboard->m_siz.z = stof(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("ORIGIN") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �I���W�����擾
							pBillboard->m_nOriginX = atoi(str2.c_str());
							file >> str2;	// �I���W�����擾
							pBillboard->m_nOriginY = atoi(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						else if (str1.compare("END_BILLBOARDSET") == 0)
						{
							continue;
						}
					}
				}
				// �G
				else if (str0.compare("ENEMYSET") == 0)
				{
					CCreatEnemy* pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
					while (file >> str1)
					{
						if (str1.compare("TYPE") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �ʒu���擾
							pEnemy->m_enemytype = (CCreatEnemy::ENEMY_TYPE)atoi(str2.c_str());
							file >> str2;	// �ʒu���擾
							getline(file, skip);	// ��s�X�L�b�v
						}
						if (str1.compare("POS") == 0)
						{
							file >> skip;	// = ���X�L�b�v
							file >> str2;	// �ʒu���擾
							pEnemy->m_pos.x = stof(str2.c_str());
							file >> str2;	// �ʒu���擾
							pEnemy->m_pos.y = stof(str2.c_str());
							file >> str2;	// �ʒu���擾
							pEnemy->m_pos.z = stof(str2.c_str());
							getline(file, skip);	// ��s�X�L�b�v
						}
						if (str1.compare("END_ENEMYSET") == 0)
						{
							continue;
						}
					}
				}
			}
			// �t�@�C�������
			file.close();
			return true;
		}
		bool CStageLode::LodeMap(string aFileName)
		{
			return LodeMap(aFileName.c_str());
		}
	}
}