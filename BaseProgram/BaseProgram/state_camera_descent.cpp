//=====================================================================
//
// 降下カメラ通常状態管理クラス [state_camera_descent.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera_descent.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "keyboard.h"
#include "renderer.h"
#include "kraken.h"
#include "state_kraken_normal.h"
#include "state_camera_normal.h"
#include "state_player_normal.h"
#include "camera_game.h"
#include "boss_hp.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define PLAYER_HEIGHT           (0.0f)                  // 注視点の高さ
#define CAMERA_MIN_HIGHT        (2.0f)                  // カメラの最低高度
#define STOP_LIMIT              (180)                   // 終了の時間

//=====================================================================
// コンストラクタ
//=====================================================================
CCameraStateDescent::CCameraStateDescent()
{
    m_nCount = 0;
}

//=====================================================================
// デストラクタ
//=====================================================================
CCameraStateDescent::~CCameraStateDescent()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CCameraStateDescent * CCameraStateDescent::Create()
{
    // メモリ確保
    CCameraStateDescent *pState = new CCameraStateDescent;
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
void CCameraStateDescent::Init()
{

}

//=====================================================================
// 更新処理
//=====================================================================
void CCameraStateDescent::Update()
{
    CCameraGame* pCamera = (CCameraGame*)CManager::GetInstance()->GetCamera();  // カメラ
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();                    // プレイヤー
    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();         // クラーケン

    if (!pCamera || !pPlayer || !pKraken)
    {
        return;
    }

    D3DXVECTOR3 PlayerPos = pPlayer->GetPos();    //プレイヤー位置
    D3DXVECTOR3 PlayerRot = pPlayer->GetRot();    //プレイヤー位置

    // カメラ座標
    float fDistance = pCamera->GetDistance();
    float fVartical = pCamera->GetVartical();
    float fHorizontal = pCamera->GetHorizontal();   // カメラの角度

    //キーボードクラス情報の取得
    CInputKeyboard *pKeyInput = CManager::GetInstance()->GetKeyboard();
    D3DXVECTOR3 VDest = ZeroVector3;
    // 角度の修正
    CLibrary::RotFix(fHorizontal);

    // 角度の設定
    pCamera->SetVartical(fVartical);
    pCamera->SetHorizontal(fHorizontal);

    // カメラの位置設定
    VDest.x = PlayerPos.x + fDistance * sinf(fVartical) * sinf(PlayerRot.y);    // カメラ位置X設定
    VDest.y = PlayerPos.y + fDistance * cosf(fVartical);                        // カメラ位置Y設定
    VDest.z = PlayerPos.z + fDistance * sinf(fVartical) * cosf(PlayerRot.y);    // カメラ位置Z設定

    D3DXVECTOR3 posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + PLAYER_HEIGHT, PlayerPos.z);    //注視点設定

    //設定値の反映
    pCamera->GetposV() += (VDest - pCamera->GetposV())*0.1f;
    pCamera->GetposR() += (posRDest - pCamera->GetposR())*0.1f;

    m_nCount++;
    if (m_nCount >= STOP_LIMIT)
    {
        pPlayer->ChangeState(CPlayerStateNormal::Create());
        pCamera->ChangeState(CCameraStateNormal::Create());
        pKraken->ChangeState(CKrakenStateNormal::Create());
        CGame *pGame = CManager::GetInstance()->GetGame();
        if (pGame)
        {
            pGame->CreateUi();
            CBossHp* pUi = pKraken->GetHpUi();
            if (pUi)
            {
                pUi->SetDraw(true);
            }
        }
    }
}