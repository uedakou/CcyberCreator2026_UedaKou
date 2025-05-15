//===========================================
// 
// タイトルシーン[scene_title.h]
// Auther:UedaKou
// 
//===========================================
#include "scene_title.h"	// タイトルシーン
//#include "common_data.h"	// 共有データ
#include "../base/manager.h"		// 全体マネージャー
#include "../base_object/object_2D.h"		// オブジェクト２D
#include "../base_object/object_fade.h"
#include "../base_object/object_billboard.h"

namespace Scene {
	namespace Game 
	{
		class CGameManager;
	}
	class CSceneDebug;
	//============================================
	// コンストラクタ
	//============================================
	CTitle::CTitle(CBase* scene) :
		CBase(*scene),
		m_nCntMax(30)
	{
		CObject::ReleaseScene();
		CManager* manager = CManager::GetInstance();	// マネージャー
		CCamera* pCamera = manager->GetCamera();
		pCamera->SetCameraPosNomal();

		srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

		CManager* pManager = CManager::GetInstance();
		CSound* pSound = pManager->GetSound();

		pSound->PlaySoundA(CSound::SOUND_LABEL::SOUND_TITLE000);

		m_nCnt = 0;

		// タイトル
		m_pTitle = CObject2D::creat(4, D3DXVECTOR3(300.0f, 150.0f, 0), D3DXVECTOR3(500.0f, 200.0f, 0));
		m_pTitle->SetTexture("data\\TEXTURE\\Title000.png");	// テクスチャ
		m_pTitle->SetType(CObject::TYPE::POPUP);

		// セレクト
		m_nSelect = 0;
		for (int nCnt = 0; nCnt < CTitleSelect::MAX; nCnt++)
		{
			m_pSelect[nCnt] = CTitleSelect::creat(4,
				D3DXVECTOR3(SCREEN_W * 0.5f, 500.0f + (nCnt * 100.0f), 0),
				D3DXVECTOR3(200.0f, 90.0f, 0),
				nCnt);
			m_pSelect[nCnt]->SetType(CObject::TYPE::POPUP);

		}
		m_pSelect[0]->SetColor(D3DXCOLOR(1.0f, 0.5f,0.5f, 1.0f));

		m_nCntField = 0;
		// アスファルト
		m_pField[0] = CObject3D::creat(
				D3DXVECTOR3(0.0f, 0.0f, 4500.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[0]->SetBlock(1, 10);
		m_pField[0]->SetTexture("data\\TEXTURE\\AsphaltLoad000.png");
		m_pField[0]->SetType(CObject::TYPE::FIELD);

		// ダート
		m_pField[1] = CObject3D::creat(
			D3DXVECTOR3(2000.0f, 0.0f, 4500.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[1]->SetBlock(3, 10);
		m_pField[1]->SetTexture("data\\TEXTURE\\Glass000.png");
		m_pField[1]->SetType(CObject::TYPE::FIELD);

		m_pField[2] = CObject3D::creat(
			D3DXVECTOR3(-2000.0f, 0.0f, 4500.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
		m_pField[2]->SetBlock(3, 10);
		m_pField[2]->SetTexture("data\\TEXTURE\\Glass000.png");
		m_pField[2]->SetType(CObject::TYPE::FIELD);

		m_bNext = false;




		float fRand;
		CObjectBillbord* pBillbord = nullptr;
		for (int nCnt = 0; nCnt < 39; nCnt++)
		{
			fRand = (float)(rand() % 100 / 10);
			pBillbord = CObjectBillbord::creat(D3DXVECTOR3(700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);


			fRand = (float)(rand() % 100 / 10);
			pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 250.0f * nCnt), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);
		}
#if B_SORT
		//CObject::CalculateDistanceToCamera();
		//CObject::Sort();
#endif // B_SORT


		CFade::creat(CFade::FADE_TYPE::WHITE_IN, m_nCntMax);

	}
	//============================================
	// デストラ
	//============================================
	CTitle::~CTitle()
	{
		CManager* pManager = CManager::GetInstance();	// マネージャー
		CSound* pSound = pManager->GetSound();	// サウンド
		pSound->StopSound(CSound::SOUND_LABEL::SOUND_TITLE000);	// BGMを止める
	}
	//============================================
	// 更新
	//============================================
	CBase* CTitle::Update()
	{
		CManager* pManager = CManager::GetInstance();
		CInputKeyboard* pKye = pManager->GetInKey();
		CSound* pSound = pManager->GetSound();

		int nSelectOld = m_nSelect;
		// エンターをまだ押してなかったら
		if (m_bNext == false)
		{
			// エンターを押したら
			if (pKye->GetTrigger(DIK_RETURN))
			{
				// フェードと次シーンへのフラグを立てる
				CFade::creat(CFade::FADE_TYPE::WHITE_OUT, m_nCntMax);
				m_bNext = true;
			}
			// Wを押したら
			if (pKye->GetTrigger(DIK_W))
			{
				// セレクトを一つ上げる
				m_nSelect--;
				// 一番上なら最下段にする
				if (m_nSelect < 0)
				{
					m_nSelect = CTitleSelect::MAX - 1;
				}
			}
			// Sを押したら
			else if (pKye->GetTrigger(DIK_S))
			{
				// セレクトを一つ下げる
				m_nSelect++;
				// 一番下なら最上段にする
				if (m_nSelect >= CTitleSelect::MAX)
				{
					m_nSelect = 0;
				}
			}
			// セレクトを変更していたら色を変更する
			if (nSelectOld != m_nSelect)
			{
				if (m_pSelect[nSelectOld] != nullptr)
				{
					m_pSelect[nSelectOld]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				if (m_pSelect[m_nSelect] != nullptr)
				{
					m_pSelect[m_nSelect]->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
				}
			}
		}
		// 次シーンへのフラグが立っていたら
		else
		{
			// チーン変更のカウントをする
			m_nCnt++;
			// カウントが最大まで進んだら
			if (m_nCnt > m_nCntMax)
			{
				// 選択している処理をする
				switch (m_nSelect)
				{
				case CTitleSelect::TYPE::STATE:
					// ゲームスタート
					return makeScene<Game::CGameManager>();
					break;
				case CTitleSelect::TYPE::END:
					// 終了
					return nullptr;
					break;
				default:
					break;
				}
			}
		}
		// 地面の動き
		m_nCntField++;
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			if (m_pField[nCnt] != nullptr)
			{
				m_pField[nCnt]->SetTexUV(D3DXVECTOR2(0.0f, 0.0f - 0.01f * m_nCntField), D3DXVECTOR2(1.0f, 10.0f - 0.01f * m_nCntField));
			}
		}
		if (m_nCntField % 30 == 0)
		{
			float fRand = 0.0f;
			CObjectBillbord* pBillbord = nullptr;
			fRand = (float)(rand() % 100 / 10);
			pBillbord = CObjectBillbord::creat(D3DXVECTOR3(700.0f, 0.0f, 9500.0f), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);


			fRand = (float)(rand() % 100 / 10);
			pBillbord = CObjectBillbord::creat(D3DXVECTOR3(-700.0f, 0.0f, 9500.0f), D3DXVECTOR3(150.0f, 200.0f + 15.0f * fRand, 0.0f));
			pBillbord->SetTexture("data\\TEXTURE\\tree000.png");
			pBillbord->SetType(CObjectBillbord::TYPE::TREE);
#if B_SORT
			//CObject::CalculateDistanceToCamera();
			//CObject::Sort();
#endif // B_SORT

		}

		CObject* Top[MAX_PRIORITY];
		CObject::GetAllObject(Top);
		for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
		{
			CObject* pObject = Top[nCnt];
			CObject* pNext = nullptr;
			while (pObject != nullptr)
			{
				pNext = pObject->GetNext();

				if (pObject->GetType() == CObject::TYPE::BILLBOARD)
				{

					CObjectBillbord* pTree = (CObjectBillbord*)pObject;
					pTree->AddPos(D3DXVECTOR3(0.0f, 0.0f, -10.0f));


					D3DXVECTOR3 pos = pTree->GetPos();
					if (pos.z <= -500.0f)
					{
						pTree->Release();
					}

				}
				pObject = pNext;
			}
		}


		return this;
	}
	//============================================
	// 描画
	//============================================
	void CTitle::Draw() const
	{

	}
	//============================================
	// ポーズ中取得
	//============================================
	bool CTitle::GetPose()
	{
		return false;
	}
	//============================================
	// シーン生成
	//============================================
	template<>
	CBase* CBase::makeScene<CTitle>() {
		return new CTitle(this);
	}
}