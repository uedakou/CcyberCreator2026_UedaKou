//===========================================
// 
// ゲームデータ保持[game_data.cpp]
// Auther:UedaKou
// 
//===========================================
#include "game_data.h"
#include <fstream>	// ファイルの読み込みに必要
#include <iostream>	// ファイルの読み込みに必要


// オブジェクト保存
namespace Scene
{
	namespace Game
	{
		CGameData::CGameData()
		{
			m_player = nullptr;	// プレイヤー
			// ステージ評価初期化
			for (int nCnt = 0; nCnt < static_cast<int>(Stage::MAX); nCnt++)
			{
				m_nScore[nCnt] = 0;
			}
			// ステージ評価読み込み
			ifstream file("data/SaveData/StageEvaluation.txt");  // 読み込むファイルのパスを指定
			if (file.fail()) {
				MessageBoxA(nullptr, "開けませんでした", "エラー", MB_OK);
				return;
			}
			string str0, str1, str2, str3;	// 文字列格納用
			string _;	// スキップ用格納
			string aModelFile[MAX_MOTION_MODEL];	// モデルファイル

			// 抽出演算子>>を使ってデリミタで区切られた単語，値を読み込む
			while (file >> str0)
			{
				// コメントアウト
				if (str0[0] == '#')
				{
					getline(file, _);	// 一行スキップ
				}
				// 障害物TALL
				else if (str0.compare("STAGESET") == 0)
				{
					int nStage = 0;
					while (file >> str1 &&
						str1.compare("END_STAGESET") != 0)
					{
						// コメントアウト
						if (str1[0] == '#')
						{
							getline(file, _);	// 一行スキップ
						}
						else if (str1.compare("STAGE") == 0)
						{
							file >> str1;	// ステージ取得
							nStage = atoi(str1.c_str());
							getline(file, _);	// 一行スキップ
						}
						else if (str1.compare("EVALUATION") == 0)
						{
							file >> str1;	// ステージ評価取得
							m_nScore[nStage] = atoi(str1.c_str());
						}
					}
				}
			}
			// ファイルを閉じる
			file.close();

		}
		CGameData::~CGameData()
		{
			// ステージ評価読み込み
			ofstream file("data/SaveData/StageEvaluation.txt");  // 読み込むファイルのパスを指定
			if (!file) {
				MessageBoxA(nullptr, "開けませんでした", "エラー", MB_OK);
				return;
			}
			string str0, str1, str2, str3;	// 文字列格納用
			string _;	// スキップ用格納
			string aModelFile[MAX_MOTION_MODEL];	// モデルファイル

			file << "STAGESET" << endl;
			for (int nCnt = 0; nCnt < static_cast<int>(Stage::MAX); nCnt++)
			{
				file << "	STAGE " << nCnt << endl;
				file << "	EVALUATION " << m_nScore[nCnt] << endl;
				
			}
			file << "END_STAGESET" << endl;

			// ファイルを閉じる
			file.close();
		}
	}
}