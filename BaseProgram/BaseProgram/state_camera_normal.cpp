//=====================================================================
//
//    カメラ通常状態管理クラス [state_camera_normal.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera_normal.h"
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
#define INPUT_CONVERSION        (D3DXToRadian(1.0f))    // スティック入力変化量
#define PLAYER_HEIGHT           (0.0f)                  // 注視点の高さ
#define CAMERA_MIN_HIGHT        (2.0f)                  // カメラの最低高度
#define PLAYER_CAMERA_HEIGHT    (300.0f)                // プレイヤーの高さ
#define CAMERA_DISTANCE         (2000.0f)               // プレイヤーとカメラの距離

//=====================================================================
// コンストラクタ
//=====================================================================
CCameraStateNormal::CCameraStateNormal()
{
    m_bMouseCountrol = false;
}

//=====================================================================
// デストラクタ
//=====================================================================
CCameraStateNormal::~CCameraStateNormal()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CCameraStateNormal * CCameraStateNormal::Create()
{
    // メモリ確保
    CCameraStateNormal *pStateNormal = new CCameraStateNormal;
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
void CCameraStateNormal::Init()
{

}

//=====================================================================
// 更新処理
//=====================================================================
void CCameraStateNormal::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    if (m_bMouseCountrol)
    {
        // マウスの更新
        MouseUpdate(pCamera);
    }
    else
    {
        // キーボード更新
        KeyBoardMove(pCamera);
    }

    // ImGui
    ShowInfo();
}

//=====================================================================
// マウスの更新処理
//=====================================================================
void CCameraStateNormal::MouseUpdate(CCamera* &pCamera)
{
    CInputKeyboard *pKeyboard = CManager::GetInstance()->GetKeyboard();    // キーボード更新
    D3DXVECTOR3 fRotateCenter; //カメラ回転の中心

    POINT point;
    GetCursorPos(&point);
    D3DXVECTOR3 CameraRot = pCamera->GetRot();
    if (!pKeyboard->GetPress(DIK_LCONTROL))//LCONT押しているときはカーソル開放する
    {
        SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);              //マウス位置をリセット
        CameraRot.y -= (point.x - (SCREEN_WIDTH / 2))*(0.01f*15.0f);    //マウス位置を反映
        CameraRot.x += (point.y - (SCREEN_HEIGHT / 2))*(0.01f*15.0f);
    }

    //rot補正
    if (CameraRot.x >= 50)
    {
        CameraRot.x = 50;
    }
    else if (CameraRot.x <= -50)
    {
        CameraRot.x = -50;
    }

    //反転しないように
    if (CameraRot.y < 0)
    {
        CameraRot.y += 360;
    }
    if (CameraRot.y > 360)
    {
        CameraRot.y -= 360;
    }

    pCamera->Setrot(CameraRot);

    // プレイヤー
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer != nullptr)
    {
        //カメラ回転の中心をプレイヤーの位置にする（少し上に）
        fRotateCenter = pPlayer->GetPos() + D3DXVECTOR3(0.0f, PLAYER_CAMERA_HEIGHT, 0.0f);
    }

    D3DXVECTOR3 rot = pCamera->GetRot();
    //カメラが地面を貫通してしまう場合地面に這わせるように
    if (fRotateCenter.y + sinf(D3DXToRadian(rot.x)) * CAMERA_DISTANCE > 0)
    {
        pCamera->SetposV(fRotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-rot.y)) * cosf(D3DXToRadian(rot.x)) * CAMERA_DISTANCE, sinf(D3DXToRadian(rot.x)) * CAMERA_DISTANCE, cosf(D3DXToRadian(-rot.y)) * cosf(D3DXToRadian(rot.x)) * CAMERA_DISTANCE));
    }
    else
    {
        pCamera->SetposV(fRotateCenter + D3DXVECTOR3(sinf(D3DXToRadian(-rot.y)) * cosf(D3DXToRadian(rot.x))* CAMERA_DISTANCE, -fRotateCenter.y + 1, cosf(D3DXToRadian(-rot.y)) * cosf(D3DXToRadian(rot.x))* CAMERA_DISTANCE));
    }

    //注視点を中心にあわせる
    pCamera->SetposR(fRotateCenter);
}

//=====================================================================
// キーボード処理
//=====================================================================
void CCameraStateNormal::KeyBoardMove(CCamera* &pCamera)
{
    // プレイヤー
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

    D3DXVECTOR3 PlayerPos = pPlayer->GetPos();    //プレイヤー位置
    D3DXVECTOR3 PlayerRot = pPlayer->GetRot();    //プレイヤー位置

    // カメラ座標
    float fDistance = pCamera->GetDistance();
    float fVartical = pCamera->GetVartical();
    float fHorizontal = pCamera->GetHorizontal();                            // カメラの角度
    //キーボードクラス情報の取得
    CInputKeyboard *pKeyInput = CManager::GetInstance()->GetKeyboard();
    D3DXVECTOR3 VDest = ZeroVector3;

    //視点（カメラ座標）の左旋回
    if (pKeyInput->GetPress(DIK_LEFT))
    {
        fHorizontal += INPUT_CONVERSION;
    }
    //視点（カメラ座標）の右旋回
    if (pKeyInput->GetPress(DIK_RIGHT))
    {
        fHorizontal -= INPUT_CONVERSION;
    }
    //視点（カメラ座標）の上旋回
    if (pKeyInput->GetPress(DIK_UP))
    {
        fVartical -= INPUT_CONVERSION;
    }
    //視点（カメラ座標）の下旋回
    if (pKeyInput->GetPress(DIK_DOWN))
    {
        fVartical += INPUT_CONVERSION;
    }

    // 角度の修正
    CLibrary::RotFix(fHorizontal);

    // 角度の設定
    pCamera->SetVartical(fVartical);
    pCamera->SetHorizontal(fHorizontal);

    // カメラの位置設定
    VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(fHorizontal);    // カメラ位置X設定
    VDest.y = PlayerPos.y + fDistance * cosf(fVartical);                        // カメラ位置Y設定
    VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(fHorizontal);    // カメラ位置Z設定

    D3DXVECTOR3 posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);    //注視点設定

    //カメラPOSYの下限
    if (VDest.y <= CAMERA_MIN_HIGHT)
    {
        VDest.y = CAMERA_MIN_HIGHT;    //限界値に戻す
    }

    //設定値の反映
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.9f;
}

//=====================================================================
// Imgui情報
//=====================================================================
void CCameraStateNormal::ShowInfo()
{
    ImGui::Begin("DebugInfo");

    if (ImGui::CollapsingHeader("CameraState"))
    {
    //    if (ImGui::TreeNode("Camera"))
        {
            ImGui::Checkbox("isMouseControl", &m_bMouseCountrol);
        //    ImGui::TreePop();
        }
    }
    ImGui::End();
}