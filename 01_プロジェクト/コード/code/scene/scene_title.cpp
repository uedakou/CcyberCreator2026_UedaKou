//===========================================
// 
// タイトルシーン[scene_title.h]
// Auther:UedaKou
// 
//===========================================
#include "scene_title.h"	// タイトルシーン
//#include "common_data.h"	// 共有データ
#include "../base/manager.h"		// 全体マネージャー
#include "../object/base/object_2D.h"		// オブジェクト２D
#include "../object/base/object_fade.h"
#include "../object/base/object_billboard.h"

namespace Scene {
	namespace Game {
		class CGameManager;
	}
	class CSceneDebug;

	const D3DXCOLOR CTitle::m_Selected = {1.0f, 0.0f, 0.0f, 1.0f};		// 選択中
	const D3DXCOLOR CTitle::m_NotSelected = { 1.0f, 1.0f, 1.0f, 1.0f};	// 非選択中

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
		//pCamera->SetNomal();

		srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

		CManager* pManager = CManager::GetInstance();
		CSound* pSound = pManager->GetSound();

		pSound->PlaySoundA(CSound::SOUND_LABEL::SOUND_TITLE000);

		m_nCnt = 0;

		// 背景
		m_pBG = CObject2D::creat(D3DXVECTOR3(SCREEN_W * 0.5f, SCREEN_H * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_W, SCREEN_H, 0));	// 生成
		m_pBG->SetTexture("data/TEXTURE/Provisional/BG_000.png");	// テクスチャ

		// タイトル
		m_pTitle = CObject2D::creat(4, D3DXVECTOR3(300.0f, 150.0f, 0.0f), D3DXVECTOR3(500.0f, 200.0f, 0));	// 生成
		m_pTitle->SetTexture("data/TEXTURE/Title_001.png");	// テクスチャ

		// セレクト
		m_nSelect = 0;	// 現在の選択
		for (int nCnt = 0; nCnt < static_cast<int>(SELECT_TYPE::MAX); nCnt++)
		{
			m_pOptions[nCnt] = CObject2D::creat(5,
				D3DXVECTOR3(SCREEN_W * 0.5f, 500.0f + (nCnt * 100.0f), 0),
				D3DXVECTOR3(200.0f, 90.0f, 0));
			switch (static_cast<SELECT_TYPE>(nCnt))
			{
			case SELECT_TYPE::STATE:
				m_pOptions[nCnt]->SetTexture("data/TEXTURE/Provisional/Start_000.png");
				break;
			case SELECT_TYPE::END:
				m_pOptions[nCnt]->SetTexture("data/TEXTURE/Provisional/End_000.png");
				break;
			default:
				break;
			}

		}

		m_pSelectedOption = CObject2D::creat(4, D3DXVECTOR3(SCREEN_W * 0.5f, 500.0f , 0),D3DXVECTOR3(210.0f, 100.0f, 0));
		m_pSelectedOption->SetColor(m_Selected);	// 選択中の色設定
		//m_pSelectedOption->SetTexture("d+ata/TEXTURE/Provisional/End_000.png");

		m_bNext = false;

		CFade::creat(CFade::TYPE::WHITE_IN, m_nCntMax);

	}
	//============================================
	// デストラ
	//============================================
	CTitle::~CTitle()
	{
		CManager* pManager = CManager::GetInstance();	// マネージャー
		CSound* pSound = pManager->GetSound();	// サウンド
		pSound->StopSound(CSound::SOUND_LABEL::SOUND_TITLE000);	// BGMを止める
		// タイトル
		if (m_pTitle != nullptr)
		{
			m_pTitle = nullptr;
		}
		// セレクト
		for (int nCnt = 0; nCnt < static_cast<int>(SELECT_TYPE::MAX); nCnt++ )
		{
			if (m_pOptions[nCnt] != nullptr)
			{
				m_pOptions[nCnt] = nullptr;
			}
		}
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
					m_nSelect = static_cast<int>(SELECT_TYPE::MAX) - 1;
				}
			}
			// Sを押したら
			else if (pKye->GetTrigger(DIK_S))
			{
				// セレクトを一つ下げる
				m_nSelect++;
				// 一番下なら最上段にする
				if (m_nSelect >= static_cast<int>(SELECT_TYPE::MAX))
				{
					m_nSelect = 0;
				}
			}
			// セレクトを変更していたら色を変更する
			if (nSelectOld != m_nSelect)
			{
				D3DXVECTOR3 pos = m_pOptions[m_nSelect]->GetPos();
				m_pSelectedOption->SetPos(pos);
				if (m_pOptions[nSelectOld] != nullptr)
				{
					m_pOptions[nSelectOld]->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
				}
				if (m_pOptions[m_nSelect] != nullptr)
				{
					m_pOptions[m_nSelect]->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
				}
			}
		}
		// 次シーンへのフラグが立っていたら
		else
		{
			// カウント開始なら
			if (m_nCnt == 0)
			{
				// フェード開始
				CFade::creat(10, CFade::TYPE::WHITE_OUT, m_nCntMax);
			}
			// カウントが最大まで進んだら
			if (m_nCnt >= m_nCntMax)
			{
				// 選択している処理をする
				switch (static_cast<SELECT_TYPE>(m_nSelect))
				{
				case SELECT_TYPE::STATE:
					// ゲームスタート
					return makeScene<Game::CGameManager>();
					break;
				case SELECT_TYPE::END:
					// 終了
					return nullptr;
					break;
				default:
					break;
				}
			}
			// シーン変更のカウントをする
			m_nCnt++;
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