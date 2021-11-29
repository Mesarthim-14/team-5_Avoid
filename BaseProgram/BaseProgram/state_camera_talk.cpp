//=====================================================================
//
//　会話カメラ通常状態管理クラス [state_camera_talk.h]
//　Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera_talk.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "keyboard.h"
#include "renderer.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define DISTANCE        (2000.0f)               // 距離
#define HEIGHT          (500.0f)                // 高さ
#define SHIFT_ANGLE     (D3DXToRadian(30.0f))   // ずらす角度
#define ANGLE_POS       (800.0f)                // 視点の高さ

//=====================================================================
// コンストラクタ
//=====================================================================
CCameraStateTalk::CCameraStateTalk()
{
    m_pos = ZeroVector3;
    m_rot = ZeroVector3;
}

//=====================================================================
// デストラクタ
//=====================================================================
CCameraStateTalk::~CCameraStateTalk()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CCameraStateTalk * CCameraStateTalk::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // メモリ確保
    CCameraStateTalk *pState = new CCameraStateTalk;
    if (pState)
    {
        // 初期化処理
        pState->m_pos = pos;
        pState->m_rot = rot;
        pState->Init();
        return pState;
    }

    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CCameraStateTalk::Init()
{

}

//=====================================================================
// 更新処理
//=====================================================================
void CCameraStateTalk::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // 大砲へ追従
    TrackingTalker(pCamera);
}

//=====================================================================
// 大砲の向き
//=====================================================================
void CCameraStateTalk::TrackingTalker(CCamera* &pCamera)
{
    float fDistance = DISTANCE;
    float fVartical = pCamera->GetVartical();
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = ZeroVector3;
    float rotY = m_rot.y-D3DXToRadian(90.0f);

    // カメラの位置設定
    VDest.x = m_pos.x + fDistance * sinf(fVartical) * -sinf(rotY - SHIFT_ANGLE); // カメラ位置X設定
    VDest.y = m_pos.y /*+ CANNON_HEIGHT*/ + ANGLE_POS * cosf(fVartical);            // カメラ位置Y設定
    VDest.z = m_pos.z + fDistance * sinf(fVartical) * -cosf(rotY - SHIFT_ANGLE); // カメラ位置Z設定

    posRDest = D3DXVECTOR3(m_pos.x, m_pos.y + HEIGHT, m_pos.z);              // 注視点設定

    //設定値の反映
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.9f;
}