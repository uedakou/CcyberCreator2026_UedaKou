//===========================================
// 
// �e�L�X�g[text.h]
// Auther:UedaKou
// 
//===========================================
#ifndef _TEXT_H_
#define _TEXT_H_
#include "object.h"
#include "../base/pch.h"

class CText :public CObject
{
public:
	typedef enum {
		Terminal = 0,// �^�[�~�i��
		Max,
	}FontType;	// �t�H���g�^�C�v
	enum class Type : int
	{
		TYPE_NULL= 0,	// �w�薳��
		SCORE,	// �X�R�A
		MAX,
	};

	CText();
	CText(int nPriorithi);
	~CText()	override;
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;
	virtual void Draw() override;
	virtual void Print(const char* aText) ;
	virtual void Print(string aText) ;
	void CreateFont();
	void SetAll(int nH, UINT nW, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, FontType type);
	void SetHyde(int nHyde) { m_nHyde = nHyde; CreateFont(); }		// ����
	void SetWide(int nWide) { m_nWide = nWide; CreateFont(); }		// ��
	void SetBold(int nBold) { m_nBold = nBold; CreateFont(); }		// �Α�
	void SetMip(int nMip) { m_nMip = nMip; CreateFont(); }			// �~�b�v�}�b�v
	void SetItalic(bool bItalic) { m_bItalic = bItalic; CreateFont(); }// �Α̃t�H���g
	void SetFont(UINT nFont) { m_nFont = nFont; CreateFont(); }	// �t�H���g
	void SetSize(UINT nSize) { m_nSize = nSize; CreateFont(); }	// �傫��
	void SetPitch(UINT nPitch) { m_nPitch = nPitch; CreateFont(); }// �s�b�`
	void SetFontType(FontType Type) { m_type = Type; CreateFont(); }		// ���
	void SetSpace(int nSpaceSW, int nSpaceSH, int nSpaceBW, int nSpaceBH) {
		m_nSpaceSW = nSpaceSW;	//�̈捶
		m_nSpaceSH = nSpaceSH;	//�̈��
		m_nSpaceBW = nSpaceBW;	//�̈�E
		m_nSpaceBH = nSpaceBH;	//�̈扺
	}
	void SetCol(D3DXCOLOR pCol) { m_pCol = pCol; }				// �F
	void SetText(const char* aText) { m_aText = aText; }
	void SetText(string aText) { m_aText = aText;
	}

	LPD3DXFONT GetFont();
	static CText* creat();
	static CText* creat(int nHyde, UINT nWide, UINT nBold, UINT nMip, bool bItalic, FontType type);
	static CText* creat(int nHyde, UINT nWide, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, FontType type);
protected:
	static string m_aFontList[Max];	// �t�H���g��

	int		m_nHyde;	// ��������	
	UINT	m_nWide;	// ������
	UINT	m_nBold;	// ��������
	UINT	m_nMip;		// �~�b�v���x��	
	bool	m_bItalic;	// �������Α̂�
	DWORD	m_nFont;	// �t�H���g
	DWORD	m_nSize;	// �����T�C�Y(�ύX�s��)
	DWORD	m_nPitch;	// �s�b�`
	FontType	m_type;		// ���̂��܂ޕ�����

	int m_nSpaceSW;	//�̈捶
	int m_nSpaceSH;	//�̈��
	int m_nSpaceBW;	//�̈�E
	int m_nSpaceBH;	//�̈扺

	D3DXCOLOR m_pCol;	// �F

	string m_aText;		// �`�敶��
	LPD3DXFONT m_pFont;// �t�H���g�̃|�C���^
};
#endif // !_TEXT_H_