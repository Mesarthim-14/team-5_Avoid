#ifndef _LIGHT_H_
#define _LIGHT_H_
//=============================================================================
//
// ライト処理 [light.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CLight
{
public:
    CLight();   // コンストラクタ
    ~CLight();  // デストラクタ

    static CLight *Create();    // インスタンス生成処理
    HRESULT Init();             // 初期化処理
    void Uninit();              // 終了処理
    void Update();              // 更新処理
    void ShowLightInfo();       //imgui ライト情報表示

    // Set関数
    inline void SetPos(const D3DXVECTOR3 &pos)  { m_Light.Position = pos; }
    void SetVecDir(const D3DXVECTOR3 &Dir);

    // Get関数
    inline D3DXVECTOR3 GetPos()const        { return m_Light.Position; }    // 座標
    inline D3DXVECTOR3 GetLightDir()const   { return m_vecDir; }            // ライトの向き

private:
    D3DLIGHT9 m_Light;      // ライトの変数
    D3DXVECTOR3 m_vecDir;   // ライトの向き
};
#endif