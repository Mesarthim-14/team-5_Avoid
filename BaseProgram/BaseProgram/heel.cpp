//=============================================================================
//
// 回復クラス [heel.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "heel.h"
#include "heel_point.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "gauge.h"
#include "particleshrink_heel.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define HEEL_NUM        (1)    // 回復の値

//=============================================================================
// コンストラクタ
//=============================================================================
CHeel::CHeel()
{
    m_apHeelPoint.clear();
}

//=============================================================================
// デストラクタ
//=============================================================================
CHeel::~CHeel()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CHeel * CHeel::Create()
{
    // メモリ確保
    CHeel *pCheckPoint = new CHeel;

    // !nullcheck
    if (pCheckPoint)
    {
        // 初期化処理
        pCheckPoint->Init();
        return pCheckPoint;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CHeel::Init()
{
    // 旗の生成
    CreateHeelPoint();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CHeel::Uninit()
{
    if (m_apHeelPoint.size() > 0)
    {
        // 終了処理
        for (auto &HeelPoint : m_apHeelPoint)
        {
            HeelPoint->Uninit();
        }
        m_apHeelPoint.clear();
    }
}

//=============================================================================
// 更新処理
//=============================================================================
void CHeel::Update()
{
    // プレイヤーの位置取得
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    CGauge * pGauge = CManager::GetInstance()->GetGame()->GetGauge();
    if (!pPlayer)
    {
        return;
    }
    D3DXVECTOR3 pos = pPlayer->GetPos();

    for (auto &HeelPoint : m_apHeelPoint)
    {
        // 当たり判定
        if (HeelPoint->Collision())
        {
            // 回復
            CManager::GetInstance()->GetPlayer()->SubLife(-HEEL_NUM);
            pGauge->SetDown((float)HEEL_NUM);
            pGauge->SetHitUp(true);
            // プレイヤーの位置にエフェクト生成
            CParticleHeel::Create(pos);
        }
    }
}

//=============================================================================
// 旗の生成
//=============================================================================
void CHeel::CreateHeelPoint()
{
    // 旗の生成
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(57761.4f, 1370.0f, 27879.0f)));
//    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-23408.0f, 107.3f, 15867.4f)));

    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(7223.2f, 5140.0f, -50789.8f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-28757.1f, 5310.0f, -55027.8f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-58786.7f, 5050.0f, -23108.5f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(1908.0f, 1750.0f, 67083.5f)));
}