//=====================================================================
//
// ボスの弾の警告処理 [caution_boss_bullet_ui.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "caution_boss_bullet_ui.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "keyboard.h"
#include "camera.h"
#include "library.h"
#include "player.h"

//=====================================================================
// マクロ定義
//=====================================================================
#define POS             (D3DXVECTOR3(SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 ,0.0f))    // 座標
#define SIZE            (D3DXVECTOR3(150.0f, 150.0f, 0.0f))                         // サイズ
#define DISTANCE        (200.0f)                                                    // 距離
#define BLINK_DISTANCE  (25000.0f)                                                  // 点滅距離
#define VIEWING_ANGLE   (0.5f)                                                      // 視野角

//=====================================================================
// コンストラクタ
//=====================================================================
CCautionBossBulletUi::CCautionBossBulletUi(PRIORITY priority) : CScene2D(priority)
{
    m_fAngle = 0.0f;
    m_bDraw = true;
    m_bBlinking = false;
}

//=====================================================================
// デストラクタ
//=====================================================================
CCautionBossBulletUi::~CCautionBossBulletUi()
{

}

//=====================================================================
// 生成処理
//=====================================================================
CCautionBossBulletUi * CCautionBossBulletUi::Create()
{
    CCautionBossBulletUi * pCaution = new CCautionBossBulletUi(PRIORITY_UI);

    if (pCaution)
    {
        pCaution->SetSceneInfo(POS, SIZE);
        pCaution->Init();

        return pCaution;
    }

    return nullptr;
}

//=====================================================================
// 初期化処理
//=====================================================================
HRESULT CCautionBossBulletUi::Init()
{
    // テクスチャの設定
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_WARNING));

    CScene2D::Init();

    return S_OK;
}

//=====================================================================
// 終了処理
//=====================================================================
void CCautionBossBulletUi::Uninit()
{
    CScene2D::Uninit();
}

//=====================================================================
// 更新処理
//=====================================================================
void CCautionBossBulletUi::Update()
{
    Rotate();
    CalDistance();

    CScene2D::Update();
}

//=====================================================================
// 描画処理
//=====================================================================
void CCautionBossBulletUi::Draw()
{
    if (m_bDraw)
    {
        CScene2D::Draw();
    }
}

//=====================================================================
// 回転
//=====================================================================
void CCautionBossBulletUi::Rotate()
{
    // プレイヤーの座標取得
    D3DXVECTOR3 PlayerPos = CManager::GetInstance()->GetPlayer()->GetPos();
    float fAngle = CLibrary::CalAngleXZ(PlayerPos, m_BulletPos);
    CLibrary::RotFix(fAngle);

    float fRot = D3DXToRadian( CManager::GetInstance()->GetCamera()->GetRot().y );
    CLibrary::RotFix(fRot);

    D3DXVECTOR3 center = HALF_SCREEN_POS;
    D3DXVECTOR3 pos =
        D3DXVECTOR3(
            center.x + cosf(fRot + D3DXToRadian(-90.0f) + fAngle)*DISTANCE,
            center.y + sinf(fRot + D3DXToRadian(-90.0f) + fAngle)*DISTANCE,
            0.0f);

    // 位置と角度の設定
    SetPos(pos);
    SetRotation(fRot + fAngle);

    // 角度の判定
    JudgeAngle(fRot, fAngle);
}

//=====================================================================
// 距離の計算
//=====================================================================
void CCautionBossBulletUi::CalDistance()
{
    if (m_bDraw)
    {
        float fDistance = CLibrary::CalDistance(m_BulletPos, CManager::GetInstance()->GetPlayer()->GetPos());
        
        // プレイヤーと弾の距離を測る
        if (fDistance < BLINK_DISTANCE)
        {
            // 点滅
            Blinking();
        }
        else
        {
            if (m_bBlinking)
            {
                SetColor(WhiteColor);
            }
        }
    }
}

//=====================================================================
// 視野角
//=====================================================================
void CCautionBossBulletUi::JudgeAngle(const float& fCamera, const float& fAngle)
{
    if (-fCamera <= fAngle + VIEWING_ANGLE
        && -fCamera >= fAngle - VIEWING_ANGLE)
    {
        m_bDraw = true;
    }
    else
    {
        m_bDraw = true;
    }
}

//=====================================================================
// 点滅
//=====================================================================
void CCautionBossBulletUi::Blinking()
{
    // 点滅
    FlashPolygon(0.2f);
    if (!m_bBlinking)
    {
        m_bBlinking = true;
    }
}