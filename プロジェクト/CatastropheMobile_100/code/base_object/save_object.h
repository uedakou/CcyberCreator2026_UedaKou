//===========================================
// 
// セレクト[title_select.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _SAVE_OBJECT_H_
#define _SAVE_OBJECT_H_
#include "object.h"

class CSaveObject
{
public:
	CSaveObject() = delete;
	CSaveObject(CObject* object);
	virtual ~CSaveObject();
	virtual CSaveObject* GetPrev() { return m_pPrev; }
	virtual CSaveObject* GetNext() { return m_pNext; }

	CSaveObject* SetList(CSaveObject* pTop, CSaveObject* pCor);	//　生成
	void FlagDeath();
private:
	CSaveObject* m_pPrev;	// 前
	CSaveObject* m_pNext;	// 次

	CObject* m_pObject;	// オブジェクト
};


#endif // !_SAVE_OBJECT_H_