#ifndef _STATE_CAMERA_TALK_H_
#define _STATE_CAMERA_TALK_H_
//=====================================================================
//
// 会話カメラ状態管理クラス [state_camera_talk.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera.h"

//=====================================================================
// 前方宣言
//=====================================================================
class CCamera;

//=====================================================================
// クラス定義
//=====================================================================
class CCameraStateTalk : public CCameraState
{
public:
    CCameraStateTalk();                 // コンストラクタ
    ~CCameraStateTalk();                // デストラクタ

    static CCameraStateTalk* Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot);    // インスタンス生成
    void Init();            // 初期化処理
    void Update()override;  // 更新処理

private:
    void TrackingTalker(CCamera* &pCamera); // 大砲の方へ向く

    // メンバ変数
    D3DXVECTOR3 m_pos;  // 座標
    D3DXVECTOR3 m_rot;  // 角度

};
#endif