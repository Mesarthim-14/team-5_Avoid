#ifndef _SWIRL_SCAFFOLD_H_
#define _SWIRL_SCAFFOLD_H_
//=============================================================================
//
// 渦の足場クラス [swirl_scaffold.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CSwirlScaffoldObject;

//=========================================================================
// クラス定義
//=========================================================================
class CSwirlScaffold : public CScene
{
public:

    CSwirlScaffold(PRIORITY = PRIORITY_MAP); // コンストラクタ
    ~CSwirlScaffold();                              // デストラクタ

    static CSwirlScaffold *Create(const D3DXVECTOR3 &pos);  // インスタンス生成
    HRESULT Init();                                         // 初期化処理
    void Uninit();                                          // 終了処理
    void Update();                                          // 更新処理
    void Draw();                                            // 描画処理

private:
    enum
    {
        MAX_OBJECT = 2,    // 出すオブジェクトの最大数
    };

    // private関数
    void RotateObject();                        // 回転
    void CreateObject();  // オブジェクトの生成

    // メンバ変数
    CSwirlScaffoldObject* m_pObject[MAX_OBJECT];
    D3DXVECTOR3 m_pos;
    float m_fAngle;
};

#endif