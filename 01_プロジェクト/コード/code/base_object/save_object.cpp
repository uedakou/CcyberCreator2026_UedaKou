//============================================
//
// シーン保持オブジェクト[scene_save.cpp]
// Author:Uedakou
// 
//============================================
#include "save_object.h"
//============================================
// コンスト
//============================================
CSaveObject::CSaveObject(CObject* object) :
	m_pObject(object)
{
	m_pNext = nullptr;
	m_pPrev = nullptr;
}
//============================================
// デストラ
//============================================
CSaveObject::~CSaveObject()
{
}
//============================================
// 生成
//============================================
CSaveObject* CSaveObject::SetList(CSaveObject* pTop, CSaveObject* pCor)
{

	this->m_pPrev = pCor;
	pCor->m_pNext = this;
	pCor = this;

	return this;
}
//============================================
// 削除
//============================================
void CSaveObject::FlagDeath()
{
	if (m_pNext != nullptr)
	{
		CSaveObject* p = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
		m_pPrev->m_pNext = p;
	}
}
