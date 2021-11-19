//=====================================================================
//
//    カメラ通常状態管理クラス [state_camera_cannon.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera_cannon.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "keyboard.h"
#include "renderer.h"
#include "cannon.h"
#include "gimmick_factory.h"
#include "cannon_manager.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define DISTANCE        (3000.0f)               // 距離
#define CANNON_HEIGHT   (1000.0f)               // 大砲の高さ
#define SHIFT_ANGLE     (D3DXToRadian(20.0f))   // ずらす角度
#define ANGLE_POS       (800.0f)                // 視点の高さ

//=====================================================================
// コンストラクタ
//=====================================================================
CCameraStateCannon::CCameraStateCannon()
{

}

//=====================================================================
// デストラクタ
//=====================================================================
CCameraStateCannon::~CCameraStateCannon()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CCameraStateCannon * CCameraStateCannon::Create()
{
    // メモリ確保
    CCameraStateCannon *pStateNormal = new CCameraStateCannon;
    if (pStateNormal)
    {
        // 初期化処理
        pStateNormal->Init();
        return pStateNormal;
    }

    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CCameraStateCannon::Init()
{

}

//=====================================================================
// 更新処理
//=====================================================================
void CCameraStateCannon::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // 大砲へ追従
    TrackingCannon(pCamera);
}

//=====================================================================
// 大砲の向き
//=====================================================================
void CCameraStateCannon::TrackingCannon(CCamera* &pCamera)
{
    CCannon* pCannon = CManager::GetInstance()->GetGame()->GetGimmickFactory()->GetCannonManager()->GetCurrentCannon();
    D3DXVECTOR3 CannonPos = pCannon->GetPos();
    D3DXVECTOR3 CannonRot = pCannon->GetRot();
    float fDistance = DISTANCE;
    float fVartical = pCamera->GetVartical();
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = ZeroVector3;

    // カメラの位置設定
    VDest.x = CannonPos.x + fDistance * sinf(fVartical) * -sinf(CannonRot.y- SHIFT_ANGLE);        // カメラ位置X設定
    VDest.y = CannonPos.y /*+ CANNON_HEIGHT*/ + ANGLE_POS * cosf(fVartical);            // カメラ位置Y設定
    VDest.z = CannonPos.z + fDistance * sinf(fVartical) * -cosf(CannonRot.y- SHIFT_ANGLE);        // カメラ位置Z設定

    posRDest = D3DXVECTOR3(CannonPos.x, CannonPos.y + CANNON_HEIGHT, CannonPos.z);    //注視点設定

    //設定値の反映
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.9f;
}