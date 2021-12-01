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
    D3DXVECTOR3 pos = pPlayer->GetPos();

    for (auto &HeelPoint : m_apHeelPoint)
    {
        // 当たり判定
        if (HeelPoint->Collision())
        {
            // 回復
            CManager::GetInstance()->GetPlayer()->SubLife(-HEEL_NUM);
            CGauge::SetDown((float)HEEL_NUM);
            CGauge::SetHitUp(true);
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
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-1546.4f, 100.0f, -0.0f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-4587.7f, 87.3f, -12224.9f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-19864.6f, 1030.4f, -18272.0f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-34715.7f, 981.2f, -13988.7f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-32146.7f, 1006.5f, 5995.2f)));
    m_apHeelPoint.push_back(CHeelPoint::Create(D3DXVECTOR3(-23408.0f, 107.3f, 15867.4f)));
}