//===========================================
// 
// ステージ000[stage_000.cpp]
// Auther:UedaKou
// 
//===========================================
#include "stage_load.h"
#include "../object/enemy000.h"
// ファイルを開くのに必要
#include <fstream>
#include <iostream>
#include "../object/enemy100.h"
namespace Scene {
	namespace Game {
		//============================================
		// コンスト
		//============================================
		CStageLode::CStageLode(CBase* scene, CGameData* gameData) :
			CBase(scene, gameData)
		{
			m_pPlayer = nullptr;
			m_pCrateObjectTop = nullptr;
			m_pCrateObjectCor = nullptr;
		}
		//============================================
		// デストラクタ
		//============================================
		CStageLode::~CStageLode()
		{

		}
		//============================================
		// 更新
		//============================================
		nsPrev::CBase* CStageLode::Update()
		{

			if (m_pPlayer != nullptr)
			{
				if (m_pPlayer->GetType() == CObject::TYPE::PLAYER)
				{
					// 条件を満たしたらオブジェクト生成
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
		// 描画
		//============================================
		void CStageLode::Draw() const
		{

		}

		//============================================
		// ポーズ中取得
		//============================================
		bool CStageLode::GetPose()
		{
			return false;
		}
		//============================================
		// 作成
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
		// 作成
		//============================================
		bool CStageLode::LodeMap(const char* aFileName)
		{
			LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

			ifstream file(aFileName);  // 読み込むファイルのパスを指定
			if (file.fail()) {
				cerr << "ファイルを開けませんでした\n";
				return false;
			}
			string str0, str1, str2, str3;	// 文字列格納用
			string skip;			// スキップ用格納
			string aTextureFile[MAX_TEXTURE];	// テクスチャファイルファイルパス
			string aModelFile[MAX_MODEL];	// モデルファイルファイルパス
			int nCntTexture = 0;
			int nMaxTexture = 0;
			int nCntModel = 0;
			int nMaxModel = 0;



			// 抽出演算子>>を使ってデリミタで区切られた単語，値を読み込む
			while (file >> str0)
			{
				// コメントアウト
				if (str0[0] == '#')
				{
					getline(file, skip);	// 一行スキップ
				}
				// テクスチャ数
				else if (str0.compare("NUM_TEXTURE") == 0)
				{
					file >> skip;	// = をスキップ
					file >> str1;	// テクスチャ数を取得
					nMaxTexture = atoi(str1.c_str());
					getline(file, skip);	// 一行スキップ
				}
				// テクスチャパス
				else if (str0.compare("TEXTURE_FILENAME") == 0 &&
					nCntTexture < nMaxTexture &&
					nMaxTexture > 0)
				{
					file >> skip;	// = をスキップ
					file >> str1;	// テクスチャパスを取得
					aTextureFile[nCntTexture] = str1;
					getline(file, skip);	// 一行スキップ
					nCntTexture++;
				}
				// モデル数
				else if (str0.compare("NUM_MODEL") == 0)
				{
					file >> skip;	// = をスキップ
					file >> str1;	// モデル数を取得
					nMaxModel = atoi(str1.c_str());
					getline(file, skip);	// 一行スキップ
				}
				// モデルパス
				else if (str0.compare("TEXTURE_FILENAME") == 0 &&
					nCntModel < nMaxModel &&
					nMaxModel > 0)
				{
					file >> skip;	// = をスキップ
					file >> str1;	// モデルパスを取得
					aModelFile[nCntModel] = str1;
					getline(file, skip);	// 一行スキップ
				}
				// カメラ(未使用)
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
				// ライト(未使用)
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
				// 空 (未使用)
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
				// 山(未使用)
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
				// 地面
				else if (str0.compare("FIELDSET") == 0)
				{
					CCreatField* pField = (CCreatField*)crate(CCreat::TYPE::FIELD, 5000.0f);
					while (file >> str1)
					{
						if (str1.compare("TEXTYPE") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// テクスチャ
								// テクスチャ
							D3DXCreateTextureFromFile(
								pDevice,
								aTextureFile[atoi(str2.c_str())].c_str(),
								&pField->m_tex);
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("POS") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 位置を取得
							pField->m_pos.x = stof(str2.c_str());
							file >> str2;	// 位置を取得
							pField->m_pos.y = stof(str2.c_str());
							file >> str2;	// 位置を取得
							pField->m_pos.z = stof(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("ROT") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 向きを取得
							pField->m_rot.x = stof(str2.c_str());
							file >> str2;	// 向きを取得
							pField->m_rot.y = stof(str2.c_str());
							file >> str2;	// 向きを取得
							pField->m_rot.z = stof(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("BLOCK") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 分割数取得
							pField->m_nBlockX = atoi(str2.c_str());
							file >> str2;	// 分割数を取得
							pField->m_nBlockY = atoi(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("SIZE") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 大きさを取得
							pField->m_siz.x = stof(str2.c_str());
							file >> str2;	// 大きさを取得
							pField->m_siz.y = stof(str2.c_str());
							file >> str1;	// 大きさを取得
							pField->m_siz.z = stof(str1.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("END_FIELDSET") == 0)
						{
							continue;
						}
					}
				}
				// 壁
				else if (str0.compare("WALLSET") == 0)
				{
					CCreatWall* pWall = (CCreatWall*)crate(CCreat::TYPE::WALL, 5000.0f);
					while (file >> str1)
					{
						if (str1.compare("TEXTYPE") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// テクスチャを取得
							D3DXCreateTextureFromFile(
								pDevice,
								aTextureFile[atoi(str2.c_str())].c_str(),
								&pWall->m_tex);
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("POS") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 位置を取得
							pWall->m_pos.x = stof(str2.c_str());
							file >> str2;	// 位置を取得
							pWall->m_pos.y = stof(str2.c_str());
							file >> str2;	// 位置を取得
							pWall->m_pos.z = stof(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("ROT") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 向きを取得
							pWall->m_rot.x = stof(str2.c_str());
							file >> str2;	// 向きを取得
							pWall->m_rot.y = stof(str2.c_str());
							file >> str2;	// 向きを取得
							pWall->m_rot.z = stof(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("BLOCK") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 分割数を取得
							pWall->m_nBlockX = atoi(str2.c_str());
							file >> str2;	// 分割数を取得
							pWall->m_nBlockY = atoi(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("SIZE") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 大きさ取得
							pWall->m_siz.x = stof(str2.c_str());
							file >> str2;	// 大きさを取得
							pWall->m_siz.y = stof(str2.c_str());
							file >> str2;	// 大きさを取得
							pWall->m_siz.z = stof(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("END_WALLSET") == 0)
						{
							continue;
						}
					}
				}
				// ビルボード
				else if (str0.compare("BILLBOARDSET") == 0)
				{
					CCreatBillboard* pBillboard = (CCreatBillboard*)crate(CCreat::TYPE::BILLBOARD, 5000.0f);
					while (file >> str1)
					{
						if (str1.compare("TEXTYPE") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// テクスチャ
							D3DXCreateTextureFromFile(
								pDevice,
								aTextureFile[atoi(str2.c_str())].c_str(),
								&pBillboard->m_tex);
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("POS") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 位置を取得
							pBillboard->m_pos.x = stof(str2.c_str());
							file >> str2;	// 位置を取得
							pBillboard->m_pos.y = stof(str2.c_str());
							file >> str2;	// 位置を取得
							pBillboard->m_pos.z = stof(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("SIZE") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 位置を取得
							pBillboard->m_siz.x = stof(str2.c_str());
							file >> str2;	// 大きさを取得
							pBillboard->m_siz.y = stof(str2.c_str());
							file >> str2;	// 大きさを取得
							pBillboard->m_siz.z = stof(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("ORIGIN") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// オリジンを取得
							pBillboard->m_nOriginX = atoi(str2.c_str());
							file >> str2;	// オリジンを取得
							pBillboard->m_nOriginY = atoi(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						else if (str1.compare("END_BILLBOARDSET") == 0)
						{
							continue;
						}
					}
				}
				// 敵
				else if (str0.compare("ENEMYSET") == 0)
				{
					CCreatEnemy* pEnemy = (CCreatEnemy*)crate(CCreat::TYPE::ENEMY, 5000.0f);
					while (file >> str1)
					{
						if (str1.compare("TYPE") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 位置を取得
							pEnemy->m_enemytype = (CCreatEnemy::ENEMY_TYPE)atoi(str2.c_str());
							file >> str2;	// 位置を取得
							getline(file, skip);	// 一行スキップ
						}
						if (str1.compare("POS") == 0)
						{
							file >> skip;	// = をスキップ
							file >> str2;	// 位置を取得
							pEnemy->m_pos.x = stof(str2.c_str());
							file >> str2;	// 位置を取得
							pEnemy->m_pos.y = stof(str2.c_str());
							file >> str2;	// 位置を取得
							pEnemy->m_pos.z = stof(str2.c_str());
							getline(file, skip);	// 一行スキップ
						}
						if (str1.compare("END_ENEMYSET") == 0)
						{
							continue;
						}
					}
				}
			}
			// ファイルを閉じる
			file.close();
			return true;
		}
		bool CStageLode::LodeMap(string aFileName)
		{
			return LodeMap(aFileName.c_str());
		}
	}
}