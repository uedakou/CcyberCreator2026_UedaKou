//===========================================
// 
// 2D•\¦ƒ‰ƒCƒt[life_3d.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _LIFE_3D_
#define _LIFE_3D_
#include "../base_object/object_billboard.h"
#include "../base_object/text.h"

class CLife_3D : public CObjectBillbord
{
public:
	CLife_3D();
	~CLife_3D();
	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
	void SetX(X pos) { CObjectBillbord::SetX(pos); }
	void SetPos(D3DXVECTOR3 pos) { CObjectBillbord::SetPos(pos); }

	void SetLifeOld(int nLifeOld) { m_nLifeOld = nLifeOld; }	// ‘Ì—Íİ’è
	void SetLife(int nLife) { m_nLife = nLife; }	// ‘Ì—Íİ’è
	void SetMaxLife(int nMaxLife) { m_nMaxLife = nMaxLife; }	// Å‘å‘Ì—Íİ’è
	static CLife_3D* creat(D3DXVECTOR3 pos, int nLife);
private:
	CObjectBillbord* m_lifeBG;
	int m_nLifeOld;
	int m_nLife;
	int m_nMaxLife;
	CText* m_pText;
	D3DXVECTOR3 posOld;
};





#endif // _LIFE_3D_