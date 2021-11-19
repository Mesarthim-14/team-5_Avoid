#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//=============================================================================
//
// リソースマネージャー処理 [resource_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CTexture;
class CXfile;
class CSound;

//=============================================================================
// リソースマネージャークラス
//=============================================================================
class CResourceManager
{
public:
    ~CResourceManager();                        // デストラクタ

    HRESULT Init();                             // 初期化処理
    void LoadAll();                             // 全てのロード処理
    void UnLoadAll();                           // 全てのアンロード

    static CResourceManager *GetInstance();     // インスタンス取得関数

    // Get関数
    inline CTexture *GetTextureClass()const     { return m_pTexture; }  // テクスチャの情報
    inline CXfile *GetXfileClass()const         { return m_pXFile; }    // テクスチャの情報
    inline CSound *GetSoundClass()const         { return m_pSound; }    // サウンドの情報

private:
    CResourceManager();                             // コンストラクタ
    static CResourceManager *m_pResourceManager;    // 自身のポインタ

    CTexture *m_pTexture;   // テクスチャのポインタ
    CXfile *m_pXFile;       // Xファイルのポインタ
    CSound *m_pSound;       // サウンドのポインタ
};

#endif