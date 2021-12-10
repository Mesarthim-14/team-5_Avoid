//=====================================================================
//
// 雑魚敵の攻撃警告 [caution_wimp_attack.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "caution_wimp_attack.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "keyboard.h"
#include "camera.h"
#include "library.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define POS             (D3DXVECTOR3(SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 ,0.0f))    // 座標
#define SIZE            (D3DXVECTOR3(800.0f, 800.0f, 0.0f))                         // サイズ
#define FIX_POS_Y       (400.0f)                                                    // Y座標の修正値

//=====================================================================
// コンストラクタ
//=====================================================================
CCautionWimpAttack::CCautionWimpAttack(PRIORITY priority) : CBillboard(priority)
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CCautionWimpAttack::~CCautionWimpAttack()
{

}

//=====================================================================
// 生成処理
//=====================================================================
CCautionWimpAttack * CCautionWimpAttack::Create(const D3DXVECTOR3& pos)
{
    CCautionWimpAttack * pCaution = new CCautionWimpAttack(PRIORITY_EFFECT);

    if (pCaution)
    {
        pCaution->SetSceneInfo(pCaution->FixPos(pos), SIZE);
        pCaution->Init();

        return pCaution;
    }

    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
HRESULT CCautionWimpAttack::Init()
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_WARNING2));

    CBillboard::Init();

    return S_OK;
}

//=====================================================================
// 終了処理
//=====================================================================
void CCautionWimpAttack::Uninit()
{
    CBillboard::Uninit();
}

//=====================================================================
// 更新処理
//=====================================================================
void CCautionWimpAttack::Update()
{
    CBillboard::Update();
}

//=====================================================================
// 描画処理
//=====================================================================
void CCautionWimpAttack::Draw()
{
    CBillboard::Draw();
}

//=====================================================================
// 座標修正
//=====================================================================
D3DXVECTOR3 CCautionWimpAttack::FixPos(const D3DXVECTOR3& pos)
{
    return D3DXVECTOR3(pos.x, pos.y + FIX_POS_Y, pos.z);
}