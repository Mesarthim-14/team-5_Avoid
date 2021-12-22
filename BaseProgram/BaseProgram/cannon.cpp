//=============================================================================
//
// 大砲クラス [cannon.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "cannon.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "kraken.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CAN_PUSH_DISTANCE    (1000.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
CCannon::CCannon(PRIORITY Priority) : CModel(Priority)
{
    m_bUse = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCannon::~CCannon()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CCannon * CCannon::Create(const D3DXVECTOR3 &pos)
{
    // メモリ確保
    CCannon *pTestModel = new CCannon(PRIORITY_GIMMICK);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init(pos);
        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCannon::Init(const D3DXVECTOR3 &pos)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON);

    GetModelInfo()->SetModelStatus(pos, LookAtKraken(pos), model);

    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCannon::Update()
{
    CModel::Update();
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CCannon::Collision()
{
    if (!m_bUse)
    {
        return PlayerDisCollision(CAN_PUSH_DISTANCE);
    }
    return false;
}

//=============================================================================
// クラーケンを見る処理
//=============================================================================
D3DXVECTOR3 CCannon::LookAtKraken(const D3DXVECTOR3 &pos)
{
    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    if (pKraken)
    {
        D3DXVECTOR3 Tpos = pKraken->GetPos();
        D3DXVECTOR3 rot = GetRot();
        rot.y = CLibrary::LookTarget(Tpos, pos);
        return rot;
    }
    return ZeroVector3;
}
