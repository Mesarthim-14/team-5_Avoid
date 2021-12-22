//=============================================================================
//
// 回転本体クラス [rotate_body.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "rotate_body.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_POS            (D3DXVECTOR3(-34328.4f, 200.0f, -6081.8f))
#define TEST_ROT            (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))
#define ROTATE_NUM          (D3DXToRadian(2.0f))                            // 回転の値

//=============================================================================
// コンストラクタ
//=============================================================================
CRotateBody::CRotateBody(PRIORITY Priority) : CModel(Priority)
{
    m_fRotateNum = ROTATE_NUM;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRotateBody::~CRotateBody()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CRotateBody * CRotateBody::Create(const D3DXVECTOR3 &pos)
{
    // メモリ確保
    CRotateBody *pRotatebody = new CRotateBody(PRIORITY_GIMMICK);

    // !nullcheck
    if (pRotatebody)
    {
        // 初期化処理
        pRotatebody->Init(pos);
        return pRotatebody;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRotateBody::Init(const D3DXVECTOR3 &pos)
{
    // 初期化処理
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_GIMMICK_SPINSHIP_MAST);
    GetModelInfo()->SetModelStatus(pos, TEST_ROT, model);

    return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CRotateBody::Update()
{
    // 回転させる
    Rotate();

    // 更新処理
    CModel::Update();
}

//=============================================================================
// 回転
//=============================================================================
void CRotateBody::Rotate()
{
    D3DXVECTOR3 rot = GetModelInfo()->GetRot();
    rot.y += m_fRotateNum;
    CLibrary::RotFix(rot.y);
    GetModelInfo()->SetRot(rot);
}