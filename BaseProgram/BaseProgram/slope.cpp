//=============================================================================
//
// 坂道クラス [slope.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "slope.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "collisionModel_OBB.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS        (D3DXVECTOR3(-10040.0f, 514.8f, -15282.6f))
#define TEST_ROT        (D3DXVECTOR3(0.0f, D3DXToRadian(-75.0f), 0.0f))

//=============================================================================
// コンストラクタ
//=============================================================================
CSlope::CSlope(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CSlope::~CSlope()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CSlope * CSlope::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // メモリ確保
    CSlope *pTestModel = new CSlope(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pTestModel)
    {
        // 初期化処理
        pTestModel->Init(pos, rot);
        return pTestModel;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSlope::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_SLOOP);
    GetModelInfo()->SetModelStatus(pos, rot, model);

    // 当たり判定モデル(直方体)の生成
    CCollisionModelOBB::Create(pos, D3DXVECTOR3(1500.0f, 1500.0f, 4000.0f), rot);

    return S_OK;
}