//===========================================
// 
// 地面[field.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "../base_object/object_3D.h"	// オブジェクト3D
class CPlayer;
class CField : public CObject3D
{
public:
	typedef enum {
		Null = 0,	// 無し
		Road,		// 道
		Grass,		// 草原
		MAX,
	}TYPE;		// 地面種類
	CField();
	~CField();
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw()		override;
	void SetPlayer(CPlayer* player) { m_player = player; }

	static CField* creat(TYPE m_type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 siz);

private:
	CPlayer* m_player;
};





#endif // !_FIELD_H_