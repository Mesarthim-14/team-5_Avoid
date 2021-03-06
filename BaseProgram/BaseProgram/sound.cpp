//================================================
//
// サウンド処理 [sound.h]
// Author : Konishi Yuuto
//
//================================================

//================================================
// インクルード
//================================================
#include "sound.h"

//====================================================
//静的メンバ変数宣言
//====================================================
CSound::PARAM CSound::m_aParam[SOUND_LABEL_MAX] =
{
    { "data/Sound/BGM/01_Title.wav", SOUND_LOOP_ON },           // タイトル 
    { "data/Sound/BGM/02_Play.wav", SOUND_LOOP_ON },            // ゲーム 
    { "data/Sound/BGM/03_Result.wav", SOUND_LOOP_ON },          // リザルト 
    { "data/Sound/BGM/04_Boss.wav", SOUND_LOOP_ON },            // ボス 
    { "data/Sound/SE/01_Select.wav", SOUND_LOOP_OFF },         // 選択 
    { "data/Sound/SE/02_Announcement.wav", SOUND_LOOP_OFF },   // 結果発表 
    { "data/Sound/SE/03_Text.wav", SOUND_LOOP_OFF },           // テキスト進む 
    { "data/Sound/SE/04_Jump.wav", SOUND_LOOP_OFF },           // ジャンプ 
    { "data/Sound/SE/05_Superjump.wav", SOUND_LOOP_OFF },      // スーパージャンプ
    { "data/Sound/SE/06_Diving.wav", SOUND_LOOP_OFF },         // 回避  
    { "data/Sound/SE/07_Cannonhit.wav", SOUND_LOOP_OFF },      // 大砲 
    { "data/Sound/SE/08_Caveat.wav", SOUND_LOOP_OFF },         // 警告音 
    { "data/Sound/SE/09_Walk1.wav", SOUND_LOOP_OFF },          // 歩く 
    { "data/Sound/SE/10_Checkpoint.wav", SOUND_LOOP_OFF },     // チェックポイント
    { "data/Sound/SE/11_Enemynoticed.wav", SOUND_LOOP_OFF },   // 敵に気づかれた  
    { "data/Sound/SE/12_Cannonfiring.wav", SOUND_LOOP_OFF },   // 大砲発射 
    { "data/Sound/SE/13_Playerdamage.wav", SOUND_LOOP_OFF },   // ダメージ 
    { "data/Sound/SE/14_Bossscream.wav", SOUND_LOOP_OFF },     // 叫び 
    { "data/Sound/SE/15_Waterfell2.wav", SOUND_LOOP_OFF },      // 着水 
    { "data/Sound/SE/16_Recovery.wav", SOUND_LOOP_OFF },       // ヒール 
    { "data/Sound/SE/17_Jumpcharge.wav", SOUND_LOOP_OFF },     // ジャンプチャージ
    { "data/Sound/SE/18_Bulletvomiting.wav", SOUND_LOOP_OFF }, // 叫び  
    { "data/Sound/SE/19_Marlindamage.wav", SOUND_LOOP_OFF },   // かじきダメージ 
};

//================================================
//コンストラクタ
//================================================
CSound::CSound()
{
    m_pXAudio2 = nullptr;                                   // XAudio2オブジェクトへのインターフェイス
    m_pMasteringVoice = nullptr;                            // マスターボイス
    memset(m_apSourceVoice, 0, sizeof(m_apSourceVoice));    // ソースボイス
    memset(m_apDataAudio, 0, sizeof(m_apDataAudio));        // オーディオデータ
    memset(m_aSizeAudio, 0, sizeof(m_aSizeAudio));
}

//================================================
//デストラクタ
//================================================
CSound::~CSound()
{

}

//================================================
// インスタンス生成
//================================================
CSound * CSound::Create()
{
    // メモリ確保
    CSound *pSound = new CSound;
    if (pSound)
    {
        // 初期化処理
        pSound->Init();
    }

    return pSound;
}

//================================================
//初期化処理
//================================================
HRESULT CSound::Init()
{
    HRESULT hr;

    // COMライブラリの初期化
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    // XAudio2オブジェクトの作成
    hr = XAudio2Create(&m_pXAudio2, 0);
    if (FAILED(hr))
    {
        // COMライブラリの終了処理
        CoUninitialize();

        return E_FAIL;
    }

    // マスターボイスの生成
    hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
    if (FAILED(hr))
    {
        if (m_pXAudio2)
        {
            // XAudio2オブジェクトの開放
            m_pXAudio2->Release();
            m_pXAudio2 = nullptr;
        }

        // COMライブラリの終了処理
        CoUninitialize();

        return E_FAIL;
    }

    // サウンドデータの初期化
    for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
    {
        HANDLE hFile;
        DWORD dwChunkSize = 0;
        DWORD dwChunkPosition = 0;
        DWORD dwFiletype;
        WAVEFORMATEXTENSIBLE wfx;
        XAUDIO2_BUFFER buffer;

        // バッファのクリア
        memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
        memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

        // サウンドデータファイルの生成
        hFile = CreateFile(m_aParam[nCntSound].m_pFilename, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return HRESULT_FROM_WIN32(GetLastError());
        }
        if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        {// ファイルポインタを先頭に移動
            return HRESULT_FROM_WIN32(GetLastError());
        }

        // WAVEファイルのチェック
        hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }
        hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }
        if (dwFiletype != 'EVAW')
        {
            return S_FALSE;
        }

        // フォーマットチェック
        hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }
        hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }

        // オーディオデータ読み込み
        hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }
        m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
        hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
        if (FAILED(hr))
        {
            return S_FALSE;
        }

        // ソースボイスの生成
        hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
        if (FAILED(hr))
        {
            return S_FALSE;
        }

        // バッファの値設定
        memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
        buffer.AudioBytes = m_aSizeAudio[nCntSound];
        buffer.pAudioData = m_apDataAudio[nCntSound];
        buffer.Flags = XAUDIO2_END_OF_STREAM;
        buffer.LoopCount = m_aParam[nCntSound].isLoop;

        // オーディオバッファの登録
        m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

        // オーディオバッファの登録
        m_apSourceVoice[nCntSound]->SetVolume(0.2f);
        //m_apSourceVoice[nCntSound]->SetVolume(0.01f);

        // ファイルをクローズ
        CloseHandle(hFile);
    }

    return S_OK;
}

//================================================
//終了処理
//================================================
void CSound::Uninit()
{
    // 一時停止
    for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
    {
        if (m_apSourceVoice[nCntSound])
        {
            // 一時停止
            m_apSourceVoice[nCntSound]->Stop(0);

            // ソースボイスの破棄
            m_apSourceVoice[nCntSound]->DestroyVoice();
            m_apSourceVoice[nCntSound] = nullptr;

            // オーディオデータの開放
            free(m_apDataAudio[nCntSound]);
            m_apDataAudio[nCntSound] = nullptr;
        }
    }

    // マスターボイスの破棄
    m_pMasteringVoice->DestroyVoice();
    m_pMasteringVoice = nullptr;

    if (m_pXAudio2)
    {
        // XAudio2オブジェクトの開放
        m_pXAudio2->Release();
        m_pXAudio2 = nullptr;
    }

    // COMライブラリの終了処理
    CoUninitialize();
}

//================================================
//セグメント再生(再生中なら停止)
//================================================
HRESULT CSound::Play(const SOUND_LABEL &label)
{
    XAUDIO2_VOICE_STATE xa2state;
    XAUDIO2_BUFFER buffer;

    // バッファの値設定
    memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
    buffer.AudioBytes = m_aSizeAudio[label];
    buffer.pAudioData = m_apDataAudio[label];
    buffer.Flags = XAUDIO2_END_OF_STREAM;
    buffer.LoopCount = m_aParam[label].isLoop;

    // 状態取得
    m_apSourceVoice[label]->GetState(&xa2state);
    if (xa2state.BuffersQueued != 0)
    {// 再生中
     // 一時停止
        m_apSourceVoice[label]->Stop(0);

        // オーディオバッファの削除
        m_apSourceVoice[label]->FlushSourceBuffers();
    }

    // オーディオバッファの登録
    m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

    // 再生
    m_apSourceVoice[label]->Start(0);

    return S_OK;
}

//================================================
//セグメント停止(ラベル指定)
//================================================
void CSound::Stop(const SOUND_LABEL &label)
{
    XAUDIO2_VOICE_STATE xa2state;

    // 状態取得
    m_apSourceVoice[label]->GetState(&xa2state);
    if (xa2state.BuffersQueued != 0)
    {// 再生中
     // 一時停止
        m_apSourceVoice[label]->Stop(0);

        // オーディオバッファの削除
        m_apSourceVoice[label]->FlushSourceBuffers();
    }
}
//=============================================================================
// セグメント停止(全て)
//=============================================================================
void CSound::StopAll()
{
    // 一時停止
    for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
    {
        if (m_apSourceVoice[nCntSound])
        {
            // 一時停止
            m_apSourceVoice[nCntSound]->Stop(0);
        }
    }
}

//================================================
// チャンクのチェック
//================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
    HRESULT hr = S_OK;
    DWORD dwRead;
    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD dwBytesRead = 0;
    DWORD dwOffset = 0;

    if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {// ファイルポインタを先頭に移動
        return HRESULT_FROM_WIN32(GetLastError());
    }

    while (hr == S_OK)
    {
        if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr) == 0)
        {// チャンクの読み込み
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr) == 0)
        {// チャンクデータの読み込み
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

        switch (dwChunkType)
        {
        case 'FFIR':
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr) == 0)
            {// ファイルタイプの読み込み
                hr = HRESULT_FROM_WIN32(GetLastError());
            }
            break;

        default:
            if (SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
            {// ファイルポインタをチャンクデータ分移動
                return HRESULT_FROM_WIN32(GetLastError());
            }
        }

        dwOffset += sizeof(DWORD) * 2;
        if (dwChunkType == format)
        {
            *pChunkSize = dwChunkDataSize;
            *pChunkDataPosition = dwOffset;

            return S_OK;
        }

        dwOffset += dwChunkDataSize;
        if (dwBytesRead >= dwRIFFDataSize)
        {
            return S_FALSE;
        }
    }

    return S_OK;
}

//================================================
// チャンクデータの読み込み
//================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
    DWORD dwRead;

    if (SetFilePointer(hFile, dwBufferoffset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {// ファイルポインタを指定位置まで移動
        return HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, nullptr) == 0)
    {// データの読み込み
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}