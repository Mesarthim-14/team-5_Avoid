#ifndef _NON_PLAYER_CHARACTER_H_
#define _NON_PLAYER_CHARACTER_H_
//=============================================================================
//
// NPCクラスヘッダ  [non_player_character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CSkinmeshModel;
class CKeyE;
class CNpcTextEnemy;
class CProductionNpcTalk;

//=============================================================================
// クラス定義
//=============================================================================
class CNonPlayerCharacter : public CScene
{
public:
    CNonPlayerCharacter(PRIORITY Priority = PRIORITY_CHARACTER); // コンストラクタ
    virtual ~CNonPlayerCharacter();                              // デストラクタ

    virtual HRESULT Init();             // 初期化処理
    virtual void Uninit();              // 終了処理
    virtual void Update();              // 更新処理
    virtual void Draw();                // 描画処理

    // Set関数
    inline void SetPos(const D3DXVECTOR3& pos) { m_pos = pos; }
    inline void SetRot(const D3DXVECTOR3& pos) { m_rot = pos; }

    // Get関数
    inline D3DXVECTOR3 GetPos() { return m_pos; }
    inline D3DXVECTOR3 GetRot() { return m_rot; }

private:
    // private関数
    void CreateModel();                                                     // モデル生成
    void Collision();                                                       // 当たり判定
    void Talk();                                                            // お話
    void BebinProduction(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);   // 状態の開始
    void EndProduction();                                                   // 状態の終了

    // メンバ変数
    D3DXVECTOR3 m_pos;                  // 座標
    D3DXVECTOR3 m_rot;                  // 角度
    D3DXMATRIX m_mtxWorld;              // ワールドマトリックス
    CSkinmeshModel* m_pSkinmeshModel;   // スキンメッシュモデルポインタ
    CKeyE* m_pKeyE;                     // Eキー
    CNpcTextEnemy* m_pText;             // テキストクラス
    bool m_bDead;                       // 話さなくなる
    CProductionNpcTalk* m_pProduction;  // 演出のポインタ

};
#endif
