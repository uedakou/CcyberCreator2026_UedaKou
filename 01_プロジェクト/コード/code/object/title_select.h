//===========================================
// 
// ÉZÉåÉNÉg[title_select.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _TITLE_SELECT_H_
#define _TITLE_SELECT_H_
#include "select.h"

class CTitleSelect : public CSelect
{
public:
	typedef enum {
		STATE = 0,
		END,
		MAX
	}TYPE;

	CTitleSelect();
	CTitleSelect(int nP);
	~CTitleSelect();
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	static CTitleSelect* creat(D3DXVECTOR3 pos, D3DXVECTOR3 siz, int type);
	static CTitleSelect* creat(int nP, D3DXVECTOR3 pos, D3DXVECTOR3 siz, int type);
private:
};

#endif // !_TITLE_SELECT_H_