#ifndef _SOUND_H_
#define _SOUND_H_
//================================================
//
// サウンド処理 [sound.h]
// Author : Konishi Yuuto
//
//================================================

//================================================
// インクルード
//================================================
#include "main.h"
#include "xaudio2.h"

//================================================
// クラス宣言
//================================================
class CSound
{
public:
    enum SOUND_LABEL
    {
        SOUND_BGM_NONE = -1,            // 初期値
        SOUND_BGM_TITLE,                // タイトル
        SOUND_BGM_GAME,                 // ゲーム
        SOUND_BGM_RESULT,               // リザルト
        SOUND_BGM_BOSS,                 // ボス
        SOUND_SE_SELECT,                // 選択
        SOUND_SE_ANNOUNCEMENT,          // 結果発表
        SOUND_SE_TEXT,                  // テキスト進む
        SOUND_SE_JUMP,                  // ジャンプ
        SOUND_SE_SUPER_JUMP,            // スーパージャンプ
        SOUND_SE_AVOID,                 // 回避
        SOUND_SE_HIT_CANNON,            // 大砲
        SOUND_SE_CAVEAT,                // 警告音
        SOUND_SE_WALK,                  // 歩く
        SOUND_SE_CHECKPOINT,            // チェックポイント
        SOUND_SE_ENEMY_NOTICED,         // 敵に気づかれた
        SOUND_SE_CANNON_FIRING,         // 大砲発射
        SOUND_SE_DAMAGE,                // ダメージ
        SOUND_SE_SCREAM,                // 叫び
        SOUND_SE_WATER_FELL,            // 着水
        SOUND_SE_HEEL,                  // ヒール
        SOUND_SE_JUMP_CHARGE,           // ジャンプチャージ
        SOUND_SE_KRAKEN_BULLET_MITING,  // 叫び
        SOUND_SE_MARLIN_DAMAGE,         // かじきダメージ
        SOUND_LABEL_MAX,
    };

    enum SOUND_LOOP
    {
        SOUND_LOOP_ON = -1,             //ループする
        SOUND_LOOP_OFF,                 //ループしない
    };

    CSound();   // コンストラクタ
    ~CSound();  // デストラクタ

    static CSound *Create();                // インスタンス生成
    HRESULT Init();                         // 初期化処理
    void Uninit();                          // 終了処理
    HRESULT Play(const SOUND_LABEL &label); // サウンド再生
    void Stop(const SOUND_LABEL &label);    // サウンドストップ
    void StopAll();                         // 全てのサウンドを停止

private:
    struct PARAM
    {
        char *m_pFilename;  // ファイル名
        SOUND_LOOP isLoop;  // ループするかどうか
    };

    HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
    HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
    IXAudio2 *m_pXAudio2 = nullptr;                                                                    // XAudio2オブジェクトへのインターフェイス
    IXAudio2MasteringVoice *m_pMasteringVoice = nullptr;                                               // マスターボイス
    IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};                                     // ソースボイス
    BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};                                                      // オーディオデータ
    DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};                                                       // オーディオデータサイズ

    // 各音素材のパラメータ
    static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif