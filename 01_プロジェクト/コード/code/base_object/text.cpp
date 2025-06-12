//===========================================
// 
// �e�L�X�g[text.cop]
// Auther:UedaKou
// 
//===========================================
#include "text.h"
#include "../base/manager.h"	// �}�l�[�W���[

string CText::m_aFontList[Max] = {
	{"Terminal"},
 };
//============================================
// �R���X�g���N�^
//============================================
CText::CText()
{
	m_pFont = nullptr;

	m_nHyde = 18;	// ��������
	m_nWide = 0;	// ������
	m_nBold = 0;	// ��������
	m_nMip = 0;		// �~�b�v���x��
	m_bItalic = FALSE;				// �������Α̂�
	m_nFont = SHIFTJIS_CHARSET;		// �t�H���g
	m_nSize = OUT_DEFAULT_PRECIS;	// �����T�C�Y(�ύX�s��)
	m_nPitch = DEFAULT_PITCH;		// �s�b�`
	m_type = FontType::Terminal;		// ���̖����܂ޕ�����
	m_pCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// �����F
	m_nSpaceSW = 0;
	m_nSpaceSH = 0;
	m_nSpaceBW = SCREEN_H;
	m_nSpaceBH = SCREEN_W;
	CObject::SetType(CObject::TEXT);
}
CText::CText(int nPriorithi):
	CObject(nPriorithi)
{
	m_pFont = nullptr;

	m_nHyde = 18;					// ��������
	m_nWide = 0;					// ������
	m_nBold = 0;					// ��������
	m_nMip = 0;						// �~�b�v���x��
	m_bItalic = FALSE;				// �������Α̂�
	m_nFont = SHIFTJIS_CHARSET;		// �t�H���g
	m_nSize = OUT_DEFAULT_PRECIS;	// �����T�C�Y(�ύX�s��)
	m_nPitch = DEFAULT_PITCH;		// �s�b�`
	m_type = FontType::Terminal;		// ���̖����܂ޕ�����
	m_pCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// �����F
	m_nSpaceSW = 0;
	m_nSpaceSH = 0;
	m_nSpaceBW = SCREEN_W;
	m_nSpaceBH = SCREEN_H;
	CObject::SetType(CObject::TEXT);
}
//============================================
// �f�X�g���N�^
//============================================
CText::~CText()
{
	if (m_pFont != nullptr) {
		m_pFont->Release();
		m_pFont = nullptr;
	}
}
//============================================
// ������
//============================================
void CText::Init()
{
	CreateFont();
}
//============================================
// �I��
//============================================
void CText::Uninit()
{
}
//============================================
// �X�V
//============================================
void CText::Update()
{
	int a = 0;
}
void CText::Draw()
{
	RECT rect = { m_nSpaceSW , m_nSpaceSH, m_nSpaceBW, m_nSpaceBH };

	// �e�L�X�g�̕`��
	if (m_pFont != nullptr)
	{
		m_pFont->DrawText(nullptr, m_aText.c_str(), -1, &rect, DT_LEFT, m_pCol);
	}
}
//============================================
// �`��
//============================================
void CText::Print(const char* aText)
{
	RECT rect = { m_nSpaceSW , m_nSpaceSH, m_nSpaceBW, m_nSpaceBH };

	// �e�L�X�g�̕`��
	if (m_pFont != nullptr)
	{
		m_pFont->DrawText(nullptr, aText, -1, &rect, DT_LEFT, m_pCol);
	}
}
void CText::Print(string aText)
{
	RECT rect = { m_nSpaceSW , m_nSpaceSH, m_nSpaceBW, m_nSpaceBH };

	// �e�L�X�g�̕`��
	m_pFont->DrawText(nullptr, aText.c_str(), -1, &rect, DT_LEFT, m_pCol);
}
//============================================
// �t�H���g����
//============================================
void CText::CreateFont()
{
	CManager* instance = CManager::GetInstance();	// �C���X�^���X
	LPDIRECT3DDEVICE9 pDevice = instance->GetRenderer()->GetDevice();	// �f�o�C�X
	if (m_pFont != nullptr)
	{
		delete m_pFont;
		m_pFont = nullptr;
	}
	// �f�o�b�O�\���p�t�H���g�̐���
	HRESULT hr = D3DXCreateFont(pDevice,	// �f�o�C�X
		m_nHyde,						// �^(int)	�_���P�ʂł̕����̍����B
		m_nWide,						// �^(UINT)	�_���P�ʂł̕����̕��B
		m_nBold,						// �^(UINT)	���̂̑����B 1 �̗�͑����ł��B
		m_nMip,							// �^(UInt)	�~�b�v�}�b�v ���x���̐��B
		m_bItalic,						// �^(BOOL)	�Α̃t�H���g�̏ꍇ�� True�A����ȊO�̏ꍇ�� false�B
		m_nFont,						// �^(DWORD)	�t�H���g�̕����Z�b�g�B
		m_nSize,						// �^(DWORD)	Windows ���ړI�̃t�H���g �T�C�Y�Ɠ��������ۂ̃t�H���g�Əƍ�������@���w�肵�܂��B ���Ƃ��΁AOUT_TT_ONLY_PRECIS���g�p���āA��� TrueType �t�H���g���擾�ł���悤�ɂ��܂��B
		DEFAULT_QUALITY,				// �^(DWORD)	Windows ���ړI�̃t�H���g�Ǝ��ۂ̃t�H���g����v��������@���w�肵�܂��B ���X�^�[ �t�H���g�ɂ̂ݓK�p����ATrueType �t�H���g�ɂ͉e�����܂���B
		m_nPitch,						// �^(DWORD)	�s�b�`�ƃt�@�~�� �C���f�b�N�X�B
		m_aFontList[m_type].c_str(),	// ���(LPCTSTR)	���̖����܂ޕ�����B �R���p�C���ݒ�� Unicode ���K�v�ȏꍇ�A�f�[�^�^ LPCTSTR �� LPCWSTR �ɉ�������܂��B ����ȊO�̏ꍇ�A������f�[�^�^�� LPCSTR �ɉ�������܂��B
		&m_pFont);						// ���(LPD3DXFONT*)	�쐬���ꂽ�t�H���g �I�u�W�F�N�g��\�� ID3DXFont �C���^�[�t�F�C�X�ւ̃|�C���^�[��Ԃ��܂��B


	if (FAILED(hr)) {
		// �G���[�����i���O�o�͂��O�����Ȃǁj
		Beep(1200, 300);
		//std::cerr << "Failed to create font! HRESULT: " << hr << std::endl;
		m_pFont = nullptr;
	}
}
//============================================
// �f�[�^�ݒ�
//============================================
void CText::SetAll(int nH, UINT nW, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, FontType type)
{
	m_nHyde = nH;
	m_nWide = nW;
	m_nBold = nBold;
	m_nMip = nMip;
	m_bItalic = bItalic;
	m_nFont = nFont;
	m_nSize = nSize;
	m_nPitch = nPitch;
	m_type = type;
	CreateFont();
}
//============================================
// �ݒ�
//============================================
LPD3DXFONT CText::GetFont()
{
	return m_pFont;
}
//============================================
// ����
//============================================
CText* CText::creat()
{
	CText* pTex = new CText();

	pTex->Init();

	return pTex;
}
CText* CText::creat(int nH, UINT nW, UINT nBold, UINT nMip, bool bItalic, FontType type)
{
	CText* pTex = new CText(5);

	pTex->m_nHyde = nH;				// ��������
	pTex->m_nWide = nW;				// ������
	pTex->m_nBold = nBold;			// ��������
	pTex->m_nMip = nMip;			// �~�b�v���x��
	pTex->m_bItalic = bItalic;		// �������Α̂�
	pTex->m_type = type;			// ���̖����܂ޕ�����
									
	pTex->Init();					

	return pTex;
}
CText* CText::creat(int nH, UINT nW, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, FontType type)
{
	CText* pTex = new CText(4);

	pTex->m_nHyde = nH;				// ��������
	pTex->m_nWide = nW;				// ������
	pTex->m_nBold = nBold;			// ��������
	pTex->m_nMip = nMip;			// �~�b�v���x��
	pTex->m_bItalic = bItalic;		// �������Α̂�
	pTex->m_nFont = nFont;			// �t�H���g
	pTex->m_nSize = nSize;			// �����T�C�Y(�ύX�s��)
	pTex->m_nPitch = nPitch;		// �s�b�`
	pTex->m_type = type;			// ���̖����܂ޕ�����
									
	pTex->Init();					

	return pTex;
}