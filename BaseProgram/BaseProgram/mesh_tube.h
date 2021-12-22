#ifndef _MESH_TUBE_H_
#define _MESH_TUBE_H_
//=============================================================================
//
// メッシュフィールドクラス [meshfield.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "mesh_3d.h"

//=============================================================================
// メッシュフィールドクラス
//=============================================================================
class CMeshTube : public CMesh3d
{
public:
    CMeshTube(PRIORITY = PRIORITY_0);  // コンストラクタ
    ~CMeshTube();                      // デストラクタ

    static CMeshTube*Create(const D3DXVECTOR3 &pos, const MESH_TYPE &MeshNum); // メッシュフィールド
    HRESULT Init();     // 初期化処理
    void Update();      // 更新処理
    void Uninit();
    void Draw();        // 描画処理

private:
    // private関数
    void InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop) {}  // アニメーション情報初期化
    void UpdateAnimation() {}                                                           // アニメーション更新
};

#endif