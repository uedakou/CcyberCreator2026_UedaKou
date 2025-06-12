//============================================
//
// オブジェクト[object.cpp]
// Author:Uedakou
// 
//============================================
#include "object.h"	// オブジェクト
#include "object_billboard.h"	// ビルボード

//============================================
// コンストラクタ
//============================================
CObject* CObject::m_pTop[MAX_PRIORITY] = {};	// オブジェクトデータ
CObject* CObject::m_pCur[MAX_PRIORITY] = {};	// オブジェクトデータ
int CObject::m_nNumObject[MAX_PRIORITY] = {};	// 階層ごとオブジェクト数
CObject::CObject()
{
	m_pNext = nullptr;		// 次オブジェクト
	m_pPrev = nullptr;		// 前オブジェクト
	m_nNumObject[MAX_PRIORITY]++;	// オブジェクト数加算
	m_ID = m_nNumObject[MAX_PRIORITY];	// IDを記録

	m_nPriority = MAX_PRIORITY;		// オブジェクトプライオリティ

	// トランスフォーム
	m_x = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_fDistance = 0.0f;

	m_bAllUpdate = true;	// 全体で更新するか
	m_bPoseUpdate = false;	// ポーズ中更新するか
	m_bAllDraw = true;		// 全体で描画するか
	m_bPoseDraw = true;		// ポーズ中描画するか
	m_bReleaseScene = true;	// シーンでリリースするか

	m_bDeath = false;		// デスフラグ

	// 先頭がなかったら先頭設定
	if (m_pTop[DEFALT_PRIORITY] != nullptr)
	{
		m_pCur[DEFALT_PRIORITY]->m_pNext = this;
		m_pPrev = m_pCur[DEFALT_PRIORITY];
		m_pCur[DEFALT_PRIORITY] = this;
	}
	else
	{
		m_pTop[DEFALT_PRIORITY] = this;
		m_pCur[DEFALT_PRIORITY] = this;
	}
}
CObject::CObject(const int nPriority)
{
	m_pNext = nullptr;		// 次オブジェクト
	m_pPrev = nullptr;		// 前オブジェクト
	m_nNumObject[nPriority]++;	// オブジェクト数加算
	m_ID = m_nNumObject[MAX_PRIORITY];	// IDを記録

	m_nPriority = nPriority;	// オブジェクトプライオリティ

	// トランスフォーム
	m_x = X(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_fDistance = 0.0f;

	m_bAllUpdate = true;		// 全体で更新するか
	m_bPoseUpdate = false;	// ポーズ中更新するか
	m_bAllDraw = true;			// 全体で描画するか
	m_bPoseDraw = true;		// ポーズ中描画するか
	m_bReleaseScene = true;	// シーンでリリースするか

	m_bDeath = false;		// デスフラグ

	// 先頭がなかったら先頭設定
	if (m_pTop[nPriority] != nullptr)
	{
		m_pCur[nPriority]->m_pNext = this;
		m_pPrev = m_pCur[nPriority];
		m_pCur[nPriority] = this;
	}
	else
	{
		m_pTop[nPriority] = this;
		m_pCur[nPriority] = this;
	}
}
//============================================
// デストラクタ
//============================================
CObject::~CObject()
{

	m_nNumObject[m_nPriority]--;
}
//============================================
// オブジェクト解放
//============================================
void CObject::Release()
{
	m_bDeath = true;
}
/// <summary>
/// シーンチェンジ時に解放
/// </summary>
void CObject::ReleaseScene()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->GetNext();	//	次保管
			if (pObjact->m_bReleaseScene)
			{
				CObject* pNext = pObjact->m_pNext;	// 次保管
				CObject* pPrev = pObjact->m_pPrev;	// 前保管
				if (pNext != nullptr)
				{// 次に前を入れる
					pNext->SetPrev(pPrev);
				}
				if (pPrev != nullptr)
				{// 前に次を入れる
					pPrev->SetNext(pNext);
				}

				if (m_pTop[nCntPriority] == pObjact)
				{
					m_pTop[nCntPriority] = pNext;
				}
				if (m_pCur[nCntPriority] == pObjact)
				{
					m_pCur[nCntPriority] = pPrev;
				}
				pObjact->Uninit();
				delete pObjact;
			}

			pObjact = pNext;

		}
	}
}
//============================================
// 全オブジェクト解放
//============================================
void CObject::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext;	// 次保管
			CObject* pPrev = pObjact->m_pPrev;	// 前保管
			if (pNext != nullptr)
			{// 次に前を入れる
				pNext->SetPrev(pPrev);
			}
			if (pPrev != nullptr)
			{// 前に次を入れる
				pPrev->SetNext(pNext);
			}

			if (m_pTop[nCntPriority] == pObjact)
			{
				m_pTop[nCntPriority] = pNext;
			}
			if (m_pCur[nCntPriority] == pObjact)
			{
				m_pCur[nCntPriority] = pPrev;
			}
			pObjact->Uninit();
			delete pObjact;

			pObjact = pNext;
		}
	}
}
/// <summary>
/// 死亡フラグが立っていたら解放
/// </summary>
void CObject::ReleaseDeathFlag()
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext;	//	次保管
			if (pObjact->m_bDeath == true)
			{// 死亡フラグが立っていたら
				CObject* pNext = pObjact->m_pNext;	// 次保管
				CObject* pPrev = pObjact->m_pPrev;	// 前保管
				if (pNext != nullptr)
				{// 次に前を入れる
					pNext->SetPrev(pPrev);
				}
				if (pPrev != nullptr)
				{// 前に次を入れる
					pPrev->SetNext(pNext);
				}

				if (m_pTop[nCntPriority] == pObjact)
				{
					m_pTop[nCntPriority] = pNext;
				}
				if (m_pCur[nCntPriority] == pObjact)
				{
					m_pCur[nCntPriority] = pPrev;
				}

				pObjact->Uninit();
				delete pObjact;
			}
			pObjact = pNext;
		}
	}

	//for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
	//{
	//	CObject* pObjact = m_pTop[nCntPriority];
	//	while (pObjact != nullptr)
	//	{
	//		CObject* pNext = pObjact->m_pNext;	//	次保管
	//		if (pObjact->m_bDeath == true)
	//		{// 死亡フラグが立っていたら
	//			pObjact->Release();
	//		}
	//		pObjact = pNext;
	//	}
	//}
}
//============================================
// 全オブジェクト更新
//============================================
void CObject::UpdateAll()
{
	const bool bPose = CManager::GetInstance()->GetSceneManager()->GetPose();
	// 未更新フラグを立てる
	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{// プライオリティ分繰り返す
		// 更新済みフラグを降ろす
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	次保管

#if 1
			if (bPose)
			{
				if (pObjact->IsPoseUpdate())
				{
					pObjact->Update();
				}
			}
			else
			{
				if (pObjact->IsAllUpdate())
				{
					pObjact->Update();
				}
			}

#else
			std::thread th_a(&CObject::Update, pObjact);
			th_a.detach();
#endif
			pObjact = pNext;
		}
	}
	
}
//============================================
// 全オブジェクト描画
//============================================
void CObject::DrawAll()
{
	const bool bPose = CManager::GetInstance()->GetSceneManager()->GetPose();
	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	次保管
			if (bPose)
			{
				if (pObjact->IsPoseDraw())
				{
					pObjact->Draw();
				}
			}
			else
			{
				if (pObjact->IsAllDraw())
				{
					pObjact->Draw();
				}
			}



			pObjact = pNext;
		}
	}

}
//============================================
// オブジェクト取得
//============================================
void CObject::GetAllObject(CObject* object[MAX_PRIORITY])
{
#if 1
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		object[nCnt] = m_pTop[nCnt];
	}
#else
	object = m_pTop;
#endif // 0

}
//============================================
// ソート
//============================================
void CObject::Sort()
{
	for (int nCnt = 0; nCnt < MAX_PRIORITY; nCnt++)
	{
		CObject* headUnsorted;	// 前
		CObject* headSorted;	// 先頭
		CObject* max;			// 次に大きい
		CObject* prevMax;
		CObject* prevComp;
		//printf("リストを昇順ソートします\n");
		headUnsorted = m_pTop[nCnt];    /* 未ソートリスト */
		headSorted = NULL;      /* ソート済リスト */
		while (headUnsorted != NULL) {
			max = headUnsorted;         /* 最大値要素を初期化 */
			prevMax = NULL;     /* 最大値要素の前の要素を初期化 */
			prevComp = headUnsorted;
			// 未ソートリストから条件を満たす最大値を探す
			while (prevComp->m_pNext != NULL) {
				// 条件を満たす場合のみ比較
				if (dynamic_cast<CObjectBillbord*>(prevComp->m_pNext)) {
					// ソート条件
					if ((prevComp->m_pNext)->m_fDistance < max->m_fDistance) {
						max = prevComp->m_pNext;         // 最大値を更新
						prevMax = prevComp;         // 最大値の前の要素を記録
					}
				}
				prevComp = prevComp->m_pNext;   // 次の要素に進む
			}
			// 最大値が見つからない場合、残りのリストはソート対象外
			if (max == NULL) {//maxがNULLにならない
				break;
			}

			// 最大値を未ソートリストから削除
			if (prevMax == NULL) {
				// 最大値がリストの先頭の場合
				headUnsorted = max->m_pNext;
			}
			else {
				// 最大値をリストから除外
				prevMax->m_pNext = max->m_pNext;
			}

			// 最大値要素をソート済リストの先頭に追加
			if (headSorted == NULL) {
				// ソート済リストが空の場合
				headSorted = max;
				m_pCur[nCnt] = max;
				max->m_pNext = NULL;
				max->m_pPrev = NULL;
			}
			else {
				// ソート済リストの先頭に追加
				max->m_pNext = headSorted;
				headSorted->m_pPrev = max;
				max->m_pPrev = NULL;
				headSorted = max;

			}
		}
		m_pTop[nCnt] = headSorted;
	}
}
void CObject::CalculateDistanceToCamera()
{
	CManager* instance = CManager::GetInstance();
	CCamera* pCamera = instance->GetCamera();
	D3DXVECTOR3 pos = pCamera->GetPosR();

	for (int nCntPriority = MIN_PRIORITY; nCntPriority < MAX_PRIORITY; nCntPriority++)
	{
		CObject* pObjact = m_pTop[nCntPriority];
		while (pObjact != nullptr)
		{
			CObject* pNext = pObjact->m_pNext; //	次保管

			pObjact->CalculateDistance(pos);

			pObjact = pNext;
		}
	}
}
void CObject::CalculateDistance(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 diff = m_x.pos - pos;
	m_fDistance = D3DXVec3LengthSq(&diff); // 距離の二乗を計算
}