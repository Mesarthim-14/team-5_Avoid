//=====================================================================
//
//　セレクトカメラ通常状態管理クラス [state_camera_select.cpp]
//　Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera_select.h"
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
#define DISTANCE        (150000.0f)  // 距離
#define HEIGHT          (30000.0f)      // 高さ
#define ANGLE_POS       (40000.0f)   // 視点の高さ

//=====================================================================
// コンストラクタ
//=====================================================================
CCameraStateSelect::CCameraStateSelect()
{

}

//=====================================================================
// デストラクタ
//=====================================================================
CCameraStateSelect::~CCameraStateSelect()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CCameraStateSelect * CCameraStateSelect::Create()
{
    // メモリ確保
    CCameraStateSelect *pState = new CCameraStateSelect;
    if (pState)
    {
        pState->Init();
        return pState;
    }

    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
void CCameraStateSelect::Init()
{

}

//=====================================================================
// 更新処理
//=====================================================================
void CCameraStateSelect::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // カメラ座標
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = pCamera->GetposRDest();  // 目的の角度
    D3DXVECTOR3 pos = ZeroVector3;                  // 位置
    D3DXVECTOR3 rot = ZeroVector3;                  // 角度
    rot.y += D3DXToRadian(90.0f);

    // 回転
    float fHorizontal = pCamera->GetHorizontal();
    fHorizontal += D3DXToRadian(0.2f);
    CLibrary::RotFix(fHorizontal);
    pCamera->SetHorizontal(fHorizontal);

    float fDistance = DISTANCE;                 // 距離
    float fVartical = pCamera->GetVartical();   // 角度

    posRDest = D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z);    //注視点設定

    // カメラの位置設定
    VDest.x = pos.x + fDistance * sinf(fVartical) * sinf(rot.y + fHorizontal);  // カメラ位置X設定
    VDest.y = pos.y + ANGLE_POS * cosf(fVartical);                              // カメラ位置Y設定
    VDest.z = pos.z + fDistance * sinf(fVartical) * cosf(rot.y + fHorizontal);  // カメラ位置Z設定

    //設定値の反映
    pCamera->GetposV() += (VDest - pCamera->GetposV());
}