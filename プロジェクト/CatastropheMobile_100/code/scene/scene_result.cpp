//============================================
//
// リザルトシーン[scene_result.cpp]
// Author:Uedakou
// 
//============================================
#include "scene_result.h"	// リザルト
#include "../base/manager.h"	// マネージャー
#include "../base_object/object_2D.h"	// オブジェクト2D
#include "../base/pch.h"	// プリコンパイル
#include "../base_object/text.h"	// テキスト
#include "../base_object/object_3D.h"	// オブジェクト３D
#include "../base_object/motion.h"

#include <fstream>
#include "../base_object/object_billboard.h"


namespace Scene {
	class CTitle;

	//============================================
	// 生成オブジェクト更新
	//============================================
	CResult::CResult(CBase* scene) :
		CBase(*scene),
		m_nMAXCntFlashing(30)
	{
		CManager* pManager = CManager::GetInstance();
		CSound* pSound = pManager->GetSound();
		CCamera* pCamera = pManager->GetCamera();

		CObject::ReleaseAll();
		pSound->PlaySoundA(CSound::SOUND_LABEL::SOUND_REZULT000);

		// 背景
		m_pField[0] = CObject3D::creat(
			D3DXVECTOR3(0.0f, 0.0f, 4500.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[0]->SetBlock(1, 10);
		m_pField[0]->SetTexture("data\\TEXTURE\\AsphaltLoad000.png");
		m_pField[0]->SetType(CObject::TYPE::FIELD);
		m_pField[1] = CObject3D::creat(
			D3DXVECTOR3(-2000.0f, 0.0f, 4500.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[1]->SetBlock(3, 10);
		m_pField[1]->SetTexture("data\\TEXTURE\\Glass000.png");
		m_pField[1]->SetType(CObject::TYPE::FIELD);
		m_nCntField = 0;

		float fRand;
		CObjectBillbord* pBillbord = nullptr;
		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			fRand = (float)(rand() % 100 / 10);
			pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);
		}

		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			if (m_Ranc[nCnt] != nullptr)
			{
				Beep(900, 300);
				delete m_Ranc[nCnt];
				m_Ranc[nCnt] = nullptr;
			}
			m_Ranc[nCnt] = CText::creat(100, 0, 0, 3, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_PITCH, CText::Type::Terminal);
			m_Ranc[nCnt]->SetSpace(100, 200 + 100* nCnt, SCREEN_W, SCREEN_H);
			m_nRanc[nCnt] = 0;
		}
		// 受け取るスコア
		m_Score = nullptr;
		m_nScore = -1;
		// 点滅
		m_nCntFlashing = 0;
		bFlashing = false;

		D3DXVECTOR3 CorPos = D3DXVECTOR3(-200.0f, 0.0f,2000.0f);
		m_pCor = nullptr;
		m_pCor = CObjectMotion::creat("data/CHARACTER/motion_Player.txt");
		m_pCor->SetPos(CorPos);
		m_pCor->SetRotY(AngleToRadian(180.0f));
		m_pCor->SetMotion(1);

		// カメラ
		D3DXVECTOR3 CameraRPos = D3DXVECTOR3(CorPos.x + 50.0f, CorPos.y, CorPos.z + 80.0f);
		pCamera->SetCameraPosR(CameraRPos);	// 注視点をプレイヤーにする
		D3DXVECTOR3 rotCumera = pCamera->GetCameraRot();	// カメラの向きを取得
		D3DXVECTOR3 posV;	// カメラの視点計算用
		rotCumera.y = AngleToRadian(30.0f);
		pCamera->SetCameraRot(CCamera::CENTER::R, rotCumera);
		float Leng = 300.0f;
		posV.x = CameraRPos.x - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * sinf(rotCumera.y) * Leng;
		posV.y = CameraRPos.y - sinf(rotCumera.x - (D3DX_PI * 0.5f)) * Leng;
		posV.z = CameraRPos.z - cosf(rotCumera.x - (D3DX_PI * 0.5f)) * cosf(rotCumera.y) * Leng;
		pCamera->SetCameraPosV(D3DXVECTOR3(posV));	// 注視点をプレイヤーにする

		pCamera->SetCameraPosV(D3DXVECTOR3(posV));	// 注視点をプレイヤーにする
		LoadRanc();
	}
	//============================================
	// 生成オブジェクト更新
	//============================================
	CResult::~CResult()
	{
		CManager* pManager = CManager::GetInstance();
		CSound* pSound = pManager->GetSound();
		pSound->StopSound(CSound::SOUND_LABEL::SOUND_REZULT000);

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_pField[nCnt] != nullptr)
			{
				m_pField[nCnt]->DeathFlag();
				m_pField[nCnt] = nullptr;
			}
		}
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			if (m_Ranc[nCnt] != nullptr)
			{
				m_Ranc[nCnt]->DeathFlag();
				m_Ranc[nCnt] = nullptr;
			}
		}
		if (m_Score != nullptr)
		{
			m_Score->DeathFlag();
			m_Score = nullptr;
		}

	}
	//============================================
	// 生成オブジェクト更新
	//============================================
	CBase* CResult::Update()
	{
		CInputKeyboard* pKey = CManager::GetInstance()->GetInKey();
		if (pKey->GetTrigger(DIK_RETURN))
		{
			return makeScene<CTitle>();
		}
		// 背景
		CObject* object[MAX_PRIORITY];
		CObject::GetAllObject(object);
		CObject* Next = nullptr;
		// 地面の動き
		if (m_nCntField % 20 == 0)
		{
			float fRand = (float)(rand() % 100 / 10);
			CObjectBillbord* pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 2750), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);
		}
		m_nCntField++;

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (m_pField[nCnt] != nullptr)
			{
				m_pField[nCnt]->AddTexUV(D3DXVECTOR2(0.0f, -0.01f), D3DXVECTOR2(0.0f, -0.01f));
			}
		}
		for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
		{
			while (object[nCnt] != nullptr)
			{
				Next = object[nCnt]->GetNext();
				if (object[nCnt]->GetType() == CObject::TYPE::BILLBOARD)
				{

					CObjectBillbord* pTree = (CObjectBillbord*)object[nCnt];
					pTree->AddPos(D3DXVECTOR3(0.0f, 0.0f, -10.0f));


					D3DXVECTOR3 pos = pTree->GetPos();
					if (pos.z <= -500.0f)
					{
						pTree->DeathFlag();
					}

				}
				object[nCnt] = Next;
			}
		}
		// ランキング強調表示
		if (bFlashing)
		{
			m_nCntFlashing++;
			if (m_nCntFlashing >= m_nMAXCntFlashing)
			{
				bFlashing = false;
			}
		}
		else
		{
			m_nCntFlashing--;
			if (m_nCntFlashing <= 0)
			{
				bFlashing = true;
			}
		}
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			if (m_nRanc[nCnt] == m_nScore)
			{
				m_Ranc[nCnt]->SetCol(D3DXCOLOR(1.0f / m_nMAXCntFlashing * m_nCntFlashing, 1.0f / m_nMAXCntFlashing * m_nCntFlashing, 0.0f, 1.0f));
			}
		}

		return this;
	}
	//============================================
	// 生成オブジェクト更新
	//============================================
	void CResult::Draw()const
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			if (m_Ranc[nCnt] != nullptr)
			{
				string Score = to_string(m_nRanc[nCnt]);
				Score.insert(0, 4 - Score.length(), '0');

				string Text = to_string(nCnt + 1) + "位 : " + Score;
				m_Ranc[nCnt]->Print(Text);
			}
		}

		if (m_Score != nullptr)
		{
			string Score = to_string(m_nScore);
			Score.insert(0, 4 - Score.length(), '0');

			string Text = "You : " + Score;
			m_Score->Print(Text);
		}
	}

	void CResult::SetScore(int nScore)
	{
		bool nNowScoreRancIn(false);	// 今のスコアがランク入りしたか
		m_nScore = nScore;
		if (nScore > m_nRanc[4])
		{
			nNowScoreRancIn = true;
			m_nRanc[4] = nScore;
			//m_nScore = nScore;
		}
		else
		{
			m_Score = CText::creat(100, 0, 0, 3, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_PITCH, CText::Type::Terminal);
			m_Score->SetSpace(800, 600, SCREEN_W, SCREEN_H);
		}
		int nMax = 0;
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			nMax = nCnt;
			for (int nCnt1 = nCnt; nCnt1 < 5; nCnt1++)
			{
				if (m_nRanc[nCnt1] > m_nRanc[nCnt])
				{
					nMax = nCnt1;
				}
			}
			if (nCnt != nMax)
			{
				int a = m_nRanc[nCnt];
				m_nRanc[nCnt] = m_nRanc[nMax];
				m_nRanc[nMax] = a;
			}
		}
		
		ofstream file("data/Ranking.txt");

		if (!file) {
			std::cerr << "ファイルを開けませんでした！" << std::endl;
			return ;
		}

		for (int i = 0; i < 5; i++) {
			file << "RANKING " << m_nRanc[i] << std::endl;
		}

		file.close();
	}

	//============================================
	// ポーズ中取得
	//============================================
	bool CResult::GetPose()
	{
		return false;
	}
	//============================================
	// ランキング読み込み
	//============================================
	void CResult::LoadRanc()
	{
		ifstream file("data\\Ranking.txt");  // 読み込むファイルのパスを指定
		if (file.fail()) {
			cerr << "ファイルを開けませんでした\n";
			Beep(1200, 300);
			return;
		}
		string str0, str1, str2, str3;	// 文字列格納用
		string skip;			// スキップ用格納
		int nCntRank = 0;

		// 抽出演算子>>を使ってデリミタで区切られた単語，値を読み込む
		while (file >> str0)
		{
			if (str0[0] == '#')
			{
				getline(file, skip);	// 一行スキップ
			}
			// モデル数
			else if (str0.compare("RANKING") == 0)
			{
				if (nCntRank <= 5)
				{
					file >> str1;	// ランクスコア数を取得
					m_nRanc[nCntRank] = atoi(str1.c_str());
					getline(file, skip);	// 一行スキップ
					nCntRank++;
				}
			}
		}
		file.close();
	}

	void CResult::SaveRanc()
	{

	}

	template<>
	CBase* CBase::makeScene<CResult>() {
		return new CResult(this);
	}
}