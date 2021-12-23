//=============================================================================
//
// 渦の足場クラス [swirl_scaffold.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "swirl_scaffold.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "swirl_scaffold_object.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEST_ROT            (D3DXVECTOR3(0.0f, D3DXToRadian(0.0f), 0.0f))   // 角度
#define ROTATE_NUM          (D3DXToRadian(1.0f))                            // 回転の値
#define OBJECT_INTER_POS    (3000.0f)                                       // オブジェクトの間隔
#define OBJECT_ROT_NUM      (D3DXToRadian(1))                               // オブジェクトの回転

//=============================================================================
// コンストラクタ
//=============================================================================
CSwirlScaffold::CSwirlScaffold(PRIORITY Priority) : CScene(Priority)
{
    m_pos = ZeroVector3;
    m_fAngle = D3DXToRadian(CLibrary::Random(180));
 //   m_fAngle = 0.0f;
    memset(m_pObject, 0, sizeof(m_pObject));
}

//=============================================================================
// デストラクタ
//=============================================================================
CSwirlScaffold::~CSwirlScaffold()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CSwirlScaffold * CSwirlScaffold::Create(const D3DXVECTOR3 &pos)
{
    // メモリ確保
    CSwirlScaffold *pRotatebody = new CSwirlScaffold(PRIORITY_GIMMICK);

    // !nullcheck
    if (pRotatebody)
    {
        // 初期化処理
        pRotatebody->m_pos = pos;
        pRotatebody->Init();
        return pRotatebody;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSwirlScaffold::Init()
{
    CreateObject();

    return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSwirlScaffold::Uninit()
{
    for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
    {
        if (m_pObject[nCount])
        {
            m_pObject[nCount]->Uninit();
            m_pObject[nCount] = nullptr;
        }
    }
}

//=============================================================================
// 更新処理
//=============================================================================
void CSwirlScaffold::Update()
{
    RotateObject();
}

//=============================================================================
// 描画処理
//=============================================================================
void CSwirlScaffold::Draw()
{

}

//=============================================================================
// 回転
//=============================================================================
void CSwirlScaffold::RotateObject()
{
    m_fAngle += OBJECT_ROT_NUM;
    CLibrary::RotFix(m_fAngle);
    D3DXVECTOR3 rot = ZeroVector3;
    float fAngle = D3DXToRadian(90.0f);

    for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
    {
        if (m_pObject[nCount])
        {
            m_pObject[nCount]->SetPos(D3DXVECTOR3(
                m_pos.x + sinf(m_fAngle + fAngle)*OBJECT_INTER_POS,
                m_pos.y,
                m_pos.z + cosf(m_fAngle + fAngle)*OBJECT_INTER_POS));
            rot = m_pObject[nCount]->GetRot();
            rot.y = m_fAngle + fAngle;
            //m_pObject[nCount]->SetRot(rot);
        }

        // 角度反転
        fAngle *= -1;
    }
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
void CSwirlScaffold::CreateObject()
{
    float fAngle = D3DXToRadian(90.0f);
    for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
    {
        if (!m_pObject[nCount])
        {
            m_pObject[nCount] = CSwirlScaffoldObject::Create(D3DXVECTOR3(
                m_pos.x + sinf(m_fAngle + fAngle)*OBJECT_INTER_POS,
                m_pos.y,
                m_pos.z + cosf(m_fAngle + fAngle)*OBJECT_INTER_POS));
        }
    }
}
