#ifndef _BOSS_BULLET_H_
#define _BOSS_BULLET_H_
//=============================================================================
//
// ボスの弾クラス [boss_bullet.h]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "model.h"
#include "bullet.h"

//=========================================================================
// クラス定義
//=========================================================================
class CCautionBossBulletUi;

//=========================================================================
// クラス定義
//=========================================================================
class CBossBullet : public CBullet
{
public:
	CBossBullet(PRIORITY Priority);    // コンストラクタ
	~CBossBullet();                    // デストラクタ

	static CBossBullet *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// インスタンス生成
	HRESULT Init();					// 初期化処理
	void Uninit();					// 初期化処理
	void Update();					// 更新処理
	void Draw();					// 描画

    void Delete();  // ステージ外処理

    void SetDeath() { m_bDeath = true; }    // 次の更新で破棄するかの判定更新

    bool GetDeath()const { return m_bDeath; }   // // 次の更新で破棄するかの判定取得

private:
    void FollowPlayer();                    // 移動量の設定
    void FixPos(const D3DXVECTOR3& pos);    // 座標の修正

	// メンバ変数
	CModel * m_pModel;					// モデルポインタ
    CCautionBossBulletUi* m_pCaution;   // 警告

    bool m_bDeath;  // 次の更新で破棄するかの判定

    D3DXVECTOR3 m_InitPlayerPos;    // 生成時のプレイヤーの座標
    float m_fInitDistance;          // 生成時のプレイヤーとの距離
    D3DXVECTOR3 m_MoveXZ;           // XZ移動量
    float m_fMoveY;                 // 1ごとのY座標移動量
};

#endif