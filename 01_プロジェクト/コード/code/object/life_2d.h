//===========================================
// 
// 2D•\¦ƒ‰ƒCƒt[life_2d.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _LIFE_2D_
#define _LIFE_2D_
#include "../base_object/object_2D.h"
#include "../base_object/text.h"

class CLife_2D : public CObject2D
{
public:
	CLife_2D();
	CLife_2D(int nPriorith);
	~CLife_2D();
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
	void SetLifeOld(int nLifeOld) { m_nLifeOld = nLifeOld; }	// ‘Ì—Íİ’è
	void SetLife(int nLife) { m_nLife = nLife; }	// ‘Ì—Íİ’è
	void SetMaxLife(int nMaxLife) { m_nMaxLife = nMaxLife; }	// Å‘å‘Ì—Íİ’è
	static CLife_2D* creat(D3DXVECTOR3 pos, int nLife);
	static CLife_2D* creat(int nPriorith, D3DXVECTOR3 pos, int nLife);
private:
	CObject2D* lifeBG;
	int m_nLifeOld;
	int m_nLife;
	int m_nMaxLife;
	CText* m_pText;
};





#endif // _LIFE_2D_