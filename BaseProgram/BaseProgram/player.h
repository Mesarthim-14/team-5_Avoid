#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "skinmesh_model.h"
#include "state_object.h"

//=========================================================================
// 前方宣言
//=========================================================================
class CCollisionModelOBB;
class CState;
class CGauge;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter, public CStateObject
{
public:

    enum ACTION_STATE
    {
        ACTION_NONE = -1,
        ACTION_IDOL,
        ACTION_JUMP,
        ACTION_LANDING,
        ACTION_WALK,
    //    ACTION_AVOID,
        ACTION_MAX
    };//行動状態

    enum STATE_PLAYER
    {
        STATE_PLAYER_NONE = -1,     // 初期値
        STATE_PLAYER_IDOL,          // 通常状態
        STATE_PLAYER_JUMP,          // ジャンプ状態
        STATE_PLAYER_AVOID,         // 回避状態
        STATE_PLAYER_STUN,          // 気絶
        STATE_PLAYER_KNOCK_BACK,    // ノックバック
        STATE_PLAYER_MAX,           // 最大値
    };

    enum SLIME_STATE
    {
        SLIME_LITTLESIZE = 0,
        SLIME_MIDDLESIZE,
        SLIME_LARGESIZE,
        SLIME_STATE_MAX
    };//スライムの状態（大きさ）

    CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);    // コンストラクタ
    ~CPlayer();                                         // デストラクタ

    static CPlayer*Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);    // クリエイト

    HRESULT Init();                                 // 初期化処理
    void Uninit();                                  // 終了処理
    void Update();                                  // 更新処理
    void Draw();                                    // 描画処理
    void ShowInfo();                                // 情報
    HRESULT LoadInfo();                             // データロード
    void SaveInfo();                                // データセーブ
    void SubLife(const int &nDamage);               // ダメージ
    CSkinmeshModel* GetCurrentSkinMeshPtr();        // 現在のスキンメッシュポインタ
    void ChangeState(CState* pPlayerState);         // 状態チェンジ

    // Set関数
    inline void SetAction(const int &nCount, const int &nMaxAction) { m_nMaxAction[nCount] = nMaxAction; }  // アクションの設定
    inline void SetMove(const D3DXVECTOR3 &move)                    { CCharacter::SetMove(move); }          // 移動量設定
    inline void SetRotDest(const D3DXVECTOR3& rotDest)              { m_rotDest = rotDest; }                // 目的の角度
    inline void SetAngle(const float& fAngle)                       { m_fAngle = fAngle; }                  // アングル

    // Get関数
    inline int GetLife()const                           { return m_nHP; }                   // HPの情報
    inline float GetAngle()const                        { return m_fAngle; }                // アングル
    inline D3DXVECTOR3 GetRotDest()const                { return m_rotDest; }               // 目的
    inline D3DXVECTOR3 GetInertia()const                { return m_Inertia; }               // 慣性の情報
    inline float GetInertiaNum()const                   { return m_fInertiaNum; }           // 慣性の値
    inline SLIME_STATE GetSlimeState()const             { return m_SlimeState; }            // スライムの状態
    inline CCollisionModelOBB* GetCollisionPtr()const   { return m_pCollisionModelOBB; }    //当たり判定ポインタ

private:
    // private関数
    void UpdateState(); // プレイヤーの状態
    void UpdateRot();   // 角度の更新処理
    void ChangeModel(); // モデルチェンジ
    void ReSporn();     // リスポーン
    void CreateModel(); // モデル生成

    // メンバ変数
    D3DXVECTOR3 m_rotDest;                              // 回転(目標値)
    D3DXVECTOR3 m_Inertia;                              // 慣性
    float m_fInertiaNum;                                // 慣性の値
    float m_fRotationSpeed;                             // 回転の速度
    bool m_bMove;                                       // 移動のフラグ
    int m_nHP;                                          // スライムHP ~100まで（パーセント）
    SLIME_STATE    m_SlimeState;                        // スライムの状態
    float m_fAngle;                                     // カメラ向きアングル
    float m_fAngleSpeed;                                // 目標向きまで向かうスピード
    ACTION_STATE m_ActionState;                         // 行動状態
    CSkinmeshModel *m_pSkinmeshModel[SLIME_STATE_MAX];  // スキンメッシュモデルポインタ
    int m_nMaxAction[SLIME_STATE_MAX];                  // アクションの最大数
    CState* m_pCurrentState;                            // 現在の状態ポインタ
    CState* m_pNextState;                               // 次の状態ポインタ
    CCollisionModelOBB* m_pCollisionModelOBB;           // 当たり判定モデルのポインタ
};
#endif