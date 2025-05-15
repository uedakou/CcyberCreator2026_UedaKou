//===========================================
// 
// テキスト[text.cop]
// Auther:UedaKou
// 
//===========================================
#include "text.h"
#include "../base/manager.h"	// マネージャー

string CText::m_aFontList[Max] = {
	{"Terminal"},
 };
//============================================
// コンストラクタ
//============================================
CText::CText()
{
	m_pFont = nullptr;

	m_nHyde = 18;	// 文字高さ
	m_nWide = 0;	// 文字幅
	m_nBold = 0;	// 文字太さ
	m_nMip = 0;		// ミップレベル
	m_bItalic = FALSE;				// 文字が斜体か
	m_nFont = SHIFTJIS_CHARSET;		// フォント
	m_nSize = OUT_DEFAULT_PRECIS;	// 文字サイズ(変更不可)
	m_nPitch = DEFAULT_PITCH;		// ピッチ
	m_type = FontType::Terminal;		// 書体名を含む文字列
	m_pCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// 文字色
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

	m_nHyde = 18;					// 文字高さ
	m_nWide = 0;					// 文字幅
	m_nBold = 0;					// 文字太さ
	m_nMip = 0;						// ミップレベル
	m_bItalic = FALSE;				// 文字が斜体か
	m_nFont = SHIFTJIS_CHARSET;		// フォント
	m_nSize = OUT_DEFAULT_PRECIS;	// 文字サイズ(変更不可)
	m_nPitch = DEFAULT_PITCH;		// ピッチ
	m_type = FontType::Terminal;		// 書体名を含む文字列
	m_pCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// 文字色
	m_nSpaceSW = 0;
	m_nSpaceSH = 0;
	m_nSpaceBW = SCREEN_W;
	m_nSpaceBH = SCREEN_H;
	CObject::SetType(CObject::TEXT);
}
//============================================
// デストラクタ
//============================================
CText::~CText()
{
	if (m_pFont != nullptr) {
		m_pFont->Release();
		m_pFont = nullptr;
	}
}
//============================================
// 初期化
//============================================
void CText::Init()
{
	CreateFont();
}
//============================================
// 終了
//============================================
void CText::Uninit()
{
}
//============================================
// 更新
//============================================
void CText::Update()
{
	int a = 0;
}
void CText::Draw()
{
	RECT rect = { m_nSpaceSW , m_nSpaceSH, m_nSpaceBW, m_nSpaceBH };

	// テキストの描画
	if (m_pFont != nullptr)
	{
		m_pFont->DrawText(nullptr, m_aText.c_str(), -1, &rect, DT_LEFT, m_pCol);
	}
}
//============================================
// 描画
//============================================
void CText::Print(const char* aText)
{
	RECT rect = { m_nSpaceSW , m_nSpaceSH, m_nSpaceBW, m_nSpaceBH };

	// テキストの描画
	if (m_pFont != nullptr)
	{
		m_pFont->DrawText(nullptr, aText, -1, &rect, DT_LEFT, m_pCol);
	}
}
void CText::Print(string aText)
{
	RECT rect = { m_nSpaceSW , m_nSpaceSH, m_nSpaceBW, m_nSpaceBH };

	// テキストの描画
	m_pFont->DrawText(nullptr, aText.c_str(), -1, &rect, DT_LEFT, m_pCol);
}
//============================================
// フォント生成
//============================================
void CText::CreateFont()
{
	CManager* instance = CManager::GetInstance();	// インスタンス
	LPDIRECT3DDEVICE9 pDevice = instance->GetRenderer()->GetDevice();	// デバイス
	if (m_pFont != nullptr)
	{
		delete m_pFont;
		m_pFont = nullptr;
	}
	// デバッグ表示用フォントの生成
	HRESULT hr = D3DXCreateFont(pDevice,	// デバイス
		m_nHyde,						// 型(int)	論理単位での文字の高さ。
		m_nWide,						// 型(UINT)	論理単位での文字の幅。
		m_nBold,						// 型(UINT)	書体の太さ。 1 つの例は太字です。
		m_nMip,							// 型(UInt)	ミップマップ レベルの数。
		m_bItalic,						// 型(BOOL)	斜体フォントの場合は True、それ以外の場合は false。
		m_nFont,						// 型(DWORD)	フォントの文字セット。
		m_nSize,						// 型(DWORD)	Windows が目的のフォント サイズと特性を実際のフォントと照合する方法を指定します。 たとえば、OUT_TT_ONLY_PRECISを使用して、常に TrueType フォントを取得できるようにします。
		DEFAULT_QUALITY,				// 型(DWORD)	Windows が目的のフォントと実際のフォントを一致させる方法を指定します。 ラスター フォントにのみ適用され、TrueType フォントには影響しません。
		m_nPitch,						// 型(DWORD)	ピッチとファミリ インデックス。
		m_aFontList[m_type].c_str(),	// 種類(LPCTSTR)	書体名を含む文字列。 コンパイラ設定で Unicode が必要な場合、データ型 LPCTSTR は LPCWSTR に解決されます。 それ以外の場合、文字列データ型は LPCSTR に解決されます。
		&m_pFont);						// 種類(LPD3DXFONT*)	作成されたフォント オブジェクトを表す ID3DXFont インターフェイスへのポインターを返します。


	if (FAILED(hr)) {
		// エラー処理（ログ出力や例外処理など）
		Beep(1200, 300);
		//std::cerr << "Failed to create font! HRESULT: " << hr << std::endl;
		m_pFont = nullptr;
	}
}
//============================================
// データ設定
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
// 設定
//============================================
LPD3DXFONT CText::GetFont()
{
	return m_pFont;
}
//============================================
// 生成
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

	pTex->m_nHyde = nH;				// 文字高さ
	pTex->m_nWide = nW;				// 文字幅
	pTex->m_nBold = nBold;			// 文字太さ
	pTex->m_nMip = nMip;			// ミップレベル
	pTex->m_bItalic = bItalic;		// 文字が斜体か
	pTex->m_type = type;			// 書体名を含む文字列
									
	pTex->Init();					

	return pTex;
}
CText* CText::creat(int nH, UINT nW, UINT nBold, UINT nMip, bool bItalic, DWORD nFont, DWORD nSize, DWORD nPitch, FontType type)
{
	CText* pTex = new CText(4);

	pTex->m_nHyde = nH;				// 文字高さ
	pTex->m_nWide = nW;				// 文字幅
	pTex->m_nBold = nBold;			// 文字太さ
	pTex->m_nMip = nMip;			// ミップレベル
	pTex->m_bItalic = bItalic;		// 文字が斜体か
	pTex->m_nFont = nFont;			// フォント
	pTex->m_nSize = nSize;			// 文字サイズ(変更不可)
	pTex->m_nPitch = nPitch;		// ピッチ
	pTex->m_type = type;			// 書体名を含む文字列
									
	pTex->Init();					

	return pTex;
}