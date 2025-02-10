//===========================================
// 
// フォグ[fog.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _FOG_H_
#define _FOG_H_

class CFog
{
public:
	typedef enum {
		EXP = 0,	// 密度
		LINEAR,		// 範囲
	}FogType;
	CFog();
	~CFog();

	void SetFogType(FogType type);
	void SetFogLinear(float fStart, float fEnd);
	void SetFogDensity(float fDensity);

	static CFog* creat();

private:
	FogType m_type;

	float m_fFogStartPos;	// フォグ開始位置
	float m_fFogEndPos;		// フォグ終了位置

	float m_m_fFogDensity;	// フォグ密度
};

#endif // !_FOG_H_