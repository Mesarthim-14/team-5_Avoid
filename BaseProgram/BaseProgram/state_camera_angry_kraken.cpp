//=====================================================================
//
// クラーケン怒り演出カメラ [state_camera_angry_kraken.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera_angry_kraken.h"
#include "library.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "keyboard.h"
#include "renderer.h"
#include "kraken.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define KRAKEN_HEIGHT   (800.0f)    // クラーケンの高さ
#define DISTANCE        (8000.0f)   // 距離
#define ANGLE_POS       (1200.0f)   // 視点の高さ

//=====================================================================
// コンストラクタ
//=====================================================================
CCameraStateAngryKraken::CCameraStateAngryKraken()
{

}

//=====================================================================
// デストラクタ
//=====================================================================
CCameraStateAngryKraken::~CCameraStateAngryKraken()
{

}

//=====================================================================
// インスタンス生成
//=====================================================================
CCameraStateAngryKraken * CCameraStateAngryKraken::Create()
{
    // メモリ確保
    CCameraStateAngryKraken *pStateNormal = new CCameraStateAngryKraken;
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
void CCameraStateAngryKraken::Init()
{

}

//=====================================================================
// 更新処理
//=====================================================================
void CCameraStateAngryKraken::Update()
{
    CCamera *pCamera = CManager::GetInstance()->GetCamera();
    if (!pCamera)
    {
        return;
    }

    // クラーケンを見る
    ViewKraken(pCamera);
}

//=====================================================================
// クラーケンを見る処理
//=====================================================================
void CCameraStateAngryKraken::ViewKraken(CCamera* &pCamera)
{
    // ポインタ取得
    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    if (!pKraken)
    {
        return;
    }

    // カメラ座標
    D3DXVECTOR3 VDest = ZeroVector3;
    D3DXVECTOR3 posRDest = pCamera->GetposRDest();  // 目的の角度
    D3DXVECTOR3 pos = pKraken->GetPos();            // 位置
    D3DXVECTOR3 rot = pKraken->GetRot();            // 角度
    float fDistance = DISTANCE;                     // 距離
    float fVartical = pCamera->GetVartical();       // 角度
    float fHorizontal = pCamera->GetHorizontal();   // 角度

    posRDest = D3DXVECTOR3(pos.x, pos.y + KRAKEN_HEIGHT, pos.z);    //注視点設定

    // カメラの位置設定
    VDest.x = pos.x + fDistance * sinf(fVartical) * sinf(rot.y + fHorizontal);  // カメラ位置X設定
    VDest.y = pos.y + ANGLE_POS * cosf(fVartical);                              // カメラ位置Y設定
    VDest.z = pos.z + fDistance * sinf(fVartical) * cosf(rot.y + fHorizontal);  // カメラ位置Z設定

    //設定値の反映
    pCamera->GetposV() += (VDest - pCamera->GetposV());
    pCamera->GetposR() += (posRDest - pCamera->GetposR());

}
