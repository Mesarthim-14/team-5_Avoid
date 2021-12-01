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
	CBossBullet(PRIORITY = PRIORITY_TEST_MODEL);    // コンストラクタ
	~CBossBullet();                                 // デストラクタ

	static CBossBullet *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);	// インスタンス生成
	HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);					// 初期化処理
	void Uninit();					// 初期化処理
	void Update();					// 更新処理
	void Draw();					// 描画
	void Hit();						// 衝突判定

private:
    void FollowPlayer(); // 移動量の設定
	void Move();

	// メンバ変数
	CModel * m_pModel;					// モデルポインタ
    CCautionBossBulletUi* m_pCaution;   // 警告
};

#endif