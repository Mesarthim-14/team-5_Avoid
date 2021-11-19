#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
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
class CMeshField : public CMesh3d
{
public:
    CMeshField(PRIORITY = PRIORITY_0);  // コンストラクタ
    ~CMeshField();                      // デストラクタ

    virtual HRESULT Init();     // 初期化処理
    virtual void Update();      // 更新処理
    virtual void Draw();        // 描画処理
    static CMeshField*Create(); // メッシュフィールド

protected:
    void SetInfo(const D3DXVECTOR3 &size, const INT_VERTEX_2D &PieceNum);   // 情報の設定

private:
    // private関数
    void CreateVerterx();                                                               // 頂点の生成
    void InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop) {}  // アニメーション情報初期化
    void UpdateAnimation() {}                                                           // アニメーション更新
};

#endif