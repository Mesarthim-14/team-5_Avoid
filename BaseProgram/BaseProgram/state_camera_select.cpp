//=====================================================================
//
//　セレクトカメラ通常状態管理クラス [state_camera_select.h]
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
#define DISTANCE        (30000.0f)  // 距離
#define HEIGHT          (30000.0f)  // 高さ
#define ANGLE_POS       (15000.0f)   // 視点の高さ

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

    //    D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, PLAYER_HEIGHT, 0.0f);
    //    D3DXVECTOR3 posV = ZeroVector3;
    //    float fDistance = GAME_CAMERA_DISTANCE;
    //    float fVartical = GAME_CAMERA_DEFAULT_Fθ;
    //    float fHorizontal = GAME_CAMERA_DEFAULT_Hθ;
    //
    //    SetDistance(fDistance);
    //    SetVartical(fVartical);
    //    SetHorizontal(fHorizontal);					// 初期値敵のほう向ける
    //    GetposR() = posR;
    //    GetposU() = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向ベクトル
    //
    //    posV.x = posR.x + fDistance * sinf(fVartical) * sinf(fHorizontal);	// カメラ位置X
    //    posV.y = posR.z + fDistance * cosf(fVartical);						// カメラ位置Y
    //    posV.z = posR.y + fDistance * sinf(fVartical) * cosf(fHorizontal);	// カメラ位置Z
    //
    //    GetposV() = posV;

    // カメラ座標
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = pCamera->GetposRDest();  // 目的の角度
    D3DXVECTOR3 pos = ZeroVector3;                  // 位置
    D3DXVECTOR3 rot = ZeroVector3;                  // 角度
    rot.y += D3DXToRadian(90.0f);

    float fDistance = DISTANCE;                     // 距離
    float fVartical = pCamera->GetVartical();       // 角度
    float fHorizontal = pCamera->GetHorizontal();   // 角度

    posRDest = D3DXVECTOR3(pos.x, pos.y + HEIGHT, pos.z);    //注視点設定

    // カメラの位置設定
    VDest.x = pos.x + fDistance * sinf(fVartical) * sinf(rot.y + fHorizontal);  // カメラ位置X設定
    VDest.y = pos.y + ANGLE_POS * cosf(fVartical);                              // カメラ位置Y設定
    VDest.z = pos.z + fDistance * sinf(fVartical) * cosf(rot.y + fHorizontal);  // カメラ位置Z設定

    //設定値の反映
    pCamera->GetposV() += (VDest - pCamera->GetposV());
    //    pCamera->GetposR() += (posRDest - pCamera->GetposR());

}