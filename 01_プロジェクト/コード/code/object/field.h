//===========================================
// 
// �n��[field.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "../base_object/object_3D.h"	// �I�u�W�F�N�g3D
class CPlayer;
class CField : public CObject3D
{
public:
	typedef enum {
		Null = 0,	// ����
		Road,		// ��
		Grass,		// ����
		MAX,
	}TYPE;		// �n�ʎ��
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