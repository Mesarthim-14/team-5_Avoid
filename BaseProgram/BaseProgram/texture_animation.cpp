//=============================================================================
//
// テクスチャアニメーションクラス [texture_animation.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture_animation.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTextureAnimation::CTextureAnimation()
{
    memset(m_tex, 0, sizeof(m_tex));
    m_nCountAnim = 0;
    m_nCountAnimPattern = 0;
    m_nPatternNum = 0;
    m_nAnimSpeed = 0;
    m_nLoop = -1;
    m_nSpeedTexture = 0;
    m_nScrollCounter = 0;
    m_fDivisionBaseNum = 0.0f;
    m_fDivisionCounter = 0.0f;
    m_bEnd = false;
    m_bUpdate = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTextureAnimation::~CTextureAnimation()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CTextureAnimation * CTextureAnimation::Create(const D3DXVECTOR2 m_tex[NUM_VERTEX])
{
    // オブジェクトを生成
    CTextureAnimation* pTextureAnimation = new CTextureAnimation;

    if (pTextureAnimation)
    {
        // 値の設定
        memcpy(pTextureAnimation->m_tex, m_tex, NUM_VERTEX);
        return pTextureAnimation;
    }

    return nullptr;
}

//=============================================================================
// 更新処理
//=============================================================================
void CTextureAnimation::Update()
{
    // テクスチャのアニメーション
    if (m_nAnimSpeed != 0)
    {
        // アニメーションを更新する
        UpdateAnimation();
    }

    // テクスチャのスクロール
    if (m_nSpeedTexture != 0)
    {
        // アニメーションを更新する
        UpdateScroll();
    }
}

//=============================================================================
// アニメーション情報の設定
//=============================================================================
void CTextureAnimation::InitAnimationInfo(const int &nPatternNum, const int &nSpeed, const int &nLoop)
{
    m_nPatternNum = nPatternNum;
    m_nAnimSpeed = nSpeed;
    m_nLoop = nLoop;
}

//=============================================================================
// スクロール情報の設定
//=============================================================================
void CTextureAnimation::InitScroll(const int &nSpeed, const float &fDivision)
{
    m_nSpeedTexture = nSpeed;
    m_fDivisionBaseNum = fDivision;
}

//=============================================================================
// アニメーションの更新
//=============================================================================
void CTextureAnimation::UpdateAnimation()
{
    // 爆発のアニメーションカウントを進めて、パターンを切り替える
    m_nCountAnim++;

    // 頂点情報(テクスチャ座標)の更新
    if (m_nCountAnim >= m_nAnimSpeed)    // 爆発の速さ
    {
        m_nCountAnim = 0;            // アニメーションのカウントを0にする
        m_nCountAnimPattern++;        // アニメーションのパターンをカウントさせる
    }

    // アニメーションが終わったら
    if (m_nCountAnimPattern >= m_nPatternNum)
    {
        // 数値を戻しておく
        m_nCountAnimPattern = 0;

        if (m_nLoop == 0)
        {
            m_bEnd = true;
        }
    }
    else
    {
        // テクスチャ座標の更新
        m_tex[0] = D3DXVECTOR2((float)(1.0f / m_nPatternNum)*(float)m_nCountAnimPattern, 0.0f);
        m_tex[1] = D3DXVECTOR2((float)(1.0f / m_nPatternNum)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternNum), 0.0f);
        m_tex[2] = D3DXVECTOR2((float)(1.0f / m_nPatternNum)*(float)m_nCountAnimPattern, 1.0f);
        m_tex[3] = D3DXVECTOR2((float)(1.0f / m_nPatternNum)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternNum), 1.0f);

        m_bUpdate = true;
    }
}

//=============================================================================
// スクロールの更新
//=============================================================================
void CTextureAnimation::UpdateScroll()
{
    // カウンターを進める
    m_nScrollCounter++;

    // 頂点情報(テクスチャ座標)の更新
    if (m_nScrollCounter >= m_nSpeedTexture)        // 爆発の速さ
    {
        //テクスチャ座標を更新
        m_tex[0] = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
        m_tex[1] = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
        m_tex[2] = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
        m_tex[3] = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

        // アニメーションのパターンをカウントさせる
        m_fDivisionCounter += m_fDivisionBaseNum;
        m_nScrollCounter = 0;

        m_bUpdate = true;
    }
}