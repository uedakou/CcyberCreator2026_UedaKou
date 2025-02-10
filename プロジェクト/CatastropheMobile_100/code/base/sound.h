//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"
#include "xaudio2.h"

class CSound
{
public:
	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	typedef enum
	{
		SOUND_BEEP = 0,		// ビープ
		SOUND_TITLE000,		// タイトル音楽
		SOUND_REZULT000,	// リザルト
		SOUND_STAGE000,		// ステージ000
		SOUND_BOUST000,		// ステージ000
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	//*****************************************************************************
	// サウンド情報の構造体定義
	//*****************************************************************************
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;
	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);	// 再生
	void StopSound(SOUND_LABEL label);		// 停止
	void StopSound(void);					// 停止(全て)
	bool IsPlaySound(SOUND_LABEL label);	// 再生状態取得
protected:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
	// サウンドの情報
	SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX];
};

#endif
