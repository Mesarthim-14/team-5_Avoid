//=============================================================================
//
// テクスチャの管理クラス [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
    memset(m_apTexture, 0, sizeof(m_apTexture));
    memset(m_pVolumeTexture, 0, sizeof(m_pVolumeTexture));
    memset(m_pCubeTexture, 0, sizeof(m_pCubeTexture));
    memset(m_aTexFileName, 0, sizeof(m_aTexFileName));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
    for (int nCount = 0; nCount < TEXTURE_TYPE_NUM_MAX; nCount++)
    {
        // 名前データのクリア
        m_aTexFileName[nCount].clear();
    }
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTexture * CTexture::Create()
{
    // メモリ確保
    CTexture *pTexture = new CTexture;

    // nullcheck
    if (pTexture)
    {
        // 初期値
        pTexture->SetTextureName();
        return pTexture;
    }

    return nullptr;
}

//=============================================================================
// テクスチャの名前を設定
//=============================================================================
HRESULT CTexture::SetTextureName()
{
    // 通常テクスチャ
    m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL] =
    {
        { "data/Texture/test.jpg" },                // テスト
        { "data/Texture/star.png" },
        { "data/Texture/effect_kaihuku.png" },
        { "data/Texture/.png" },
        { "data/Texture/cannon_smoke_tex.png" },
        { "data/Texture/uzusio_1.png" },
        { "data/Texture/uzusio_2.png" },
        { "data/Texture/tame.png" },
        { "data/Texture/water.png" },
        { "data/Texture/water_effect_tex.png" },
        { "data/Texture/cannon_attack_tex.png" },
        { "data/Texture/slime_drop.png" },
        { "data/Texture/Gauge.png" },
        { "data/Texture/Gauge_Frame.png" },
        { "data/Texture/pose_bar.png" },
        { "data/Texture/button_1clip.png" },
        { "data/Texture/button_2.png" },
        { "data/Texture/button_3.png" },
        { "data/Texture/pose_base.png" },
        { "data/Texture/E-key.png" },
        { "data/Texture/message_back.jpeg" },
        { "data/Texture/Warning.png" },
        { "data/Texture/Warning2.png" },
        { "data/Texture/NPC1_1.png" },
        { "data/Texture/white.png" },
        { "data/Texture/slime_50.png" },
        { "data/Texture/takohead_tex.png" },
        { "data/Texture/boss_hp_back.png" },
        { "data/Texture/boss_hp_bar.png" },
    };
    
    // 分割テクスチャ
    m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE] =
    {
        { "data/Texture/test_animation.png" },        // テストアニメーション
    };

    // ボリュームテクスチャ
    m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME] =
    {
//        { "data/Texture/NoiseVolume.dds" }
    };

    // キューブテクスチャ
    m_aTexFileName[TEXTURE_TYPE_NUM_CUBE] =
    {
//        { "data/Texture/suimen8.dds" }
    };

    return S_OK;
}

//=============================================================================
// 全てのテクスチャロード
//=============================================================================
void CTexture::LoadAll()
{
    // 通常テクスチャ
    NormalTexLoad();

    // 分割テクスチャ
    SeparateTexLoad();

    // ボリュームテクスチャ
//    VolumeTexLoad();

    // キューブテクスチャ
//    CubeTexLoad();
}

//=============================================================================
// 全てのテクスチャアンロード
//=============================================================================
void CTexture::UnLoadAll()
{
    // 通常テクスチャ
    NormalTexUnLoad();

    // 分割テクスチャ
    SeparateTexUnLoad();

    // ボリュームテクスチャ
//    VolumeTexUnLoad();

    // キューブテクスチャ
//    CubeTexUnLoad();
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::NormalTexLoad()
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // テクスチャの読み込み
    size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL].size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_NORMAL][nCount].data(), &m_apTexture[nCount]);
    }

    return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::NormalTexUnLoad()
{
    for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
    {
        if (m_apTexture[nCount])
        {
            m_apTexture[nCount]->Release();
            m_apTexture[nCount] = nullptr;
        }
    }
}

//=============================================================================
// 分割テクスチャのロード
//=============================================================================
HRESULT CTexture::SeparateTexLoad()
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // 分割テクスチャの読み込み
    size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE].size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        D3DXCreateTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_SEPARATE][nCount].data(), &m_apSeparateTexture[nCount].pSeparateTexture);
    }
    return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnLoad()
{
    // テクスチャの解放
    for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
    {
        if (m_apSeparateTexture[nCount].pSeparateTexture)
        {
            m_apSeparateTexture[nCount].pSeparateTexture->Release();
            m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
        }
    }
}

//=============================================================================
// テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(const TEXTURE_TYPE &Tex_Num)
{
    if (Tex_Num < TEXTURE_NUM_MAX)
    {
        if (m_apTexture[Tex_Num])
        {
            return m_apTexture[Tex_Num];
        }
    }

    return nullptr;
}

//=============================================================================
// 分割テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(const SEPARATE_TEX_TYPE &SepaTex_Type)
{
    // 配列より小さかったら
    if (SepaTex_Type < SEPARATE_TEX_MAX)
    {
        // NULLcheck
        if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture)
        {
            // テクスチャ情報
            return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
        }
    }

    return nullptr;
}

//=============================================================================
// 分割テクスチャの情報
//=============================================================================
INT_VERTEX_2D CTexture::GetSparateTexInfo(const SEPARATE_TEX_TYPE &SepaTex_Type)
{
    // 配列より小さかったら
    if (SepaTex_Type < SEPARATE_TEX_MAX)
    {
        // テクスチャ情報
        return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
    }

    return { 0, 0 };
}

//=============================================================================
// 分割テクスチャのループフラグ
//=============================================================================
bool CTexture::GetSparateTexLoop(const SEPARATE_TEX_TYPE &SepaTex_Type)
{
    // 配列より小さかったら
    if (SepaTex_Type < SEPARATE_TEX_MAX)
    {
        // テクスチャ情報
        return m_apSeparateTexture[SepaTex_Type].bLoop;
    }

    return false;
}

//=============================================================================
// ボリュームテクスチャロード
//=============================================================================
HRESULT CTexture::VolumeTexLoad()
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    // テクスチャの読み込み
    size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME].size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        D3DXCreateVolumeTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_VOLUME][nCount].data(), &m_pVolumeTexture[nCount]);
    }

    return S_OK;
}

//=============================================================================
// ボリュームテクスチャアンロード
//=============================================================================
void CTexture::VolumeTexUnLoad()
{
    for (int nCount = 0; nCount < VOLUME_TEX_MAX; nCount++)
    {
        if (m_pVolumeTexture[nCount])
        {
            m_pVolumeTexture[nCount]->Release();
            m_pVolumeTexture[nCount] = nullptr;
        }
    }
}

//=============================================================================
// ボリュームテクスチャの情報
//=============================================================================
LPDIRECT3DVOLUMETEXTURE9 CTexture::GetVolumeTexture(const VOLUME_TEX_TYPE &Tex_Type)
{
    if (Tex_Type < VOLUME_TEX_MAX)
    {
        if (m_pVolumeTexture[Tex_Type])
        {
            return m_pVolumeTexture[Tex_Type];
        }
    }

    return nullptr;
}

//=============================================================================
// キューブテクスチャロード
//=============================================================================
HRESULT CTexture::CubeTexLoad()
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    // テクスチャの読み込み
    size_t size = m_aTexFileName[TEXTURE_TYPE_NUM_CUBE].size();
    for (size_t nCount = 0; nCount < size; nCount++)
    {
        D3DXCreateCubeTextureFromFile(pDevice, m_aTexFileName[TEXTURE_TYPE_NUM_CUBE][nCount].data(), &m_pCubeTexture[nCount]);
    }

    return S_OK;
}

//=============================================================================
// キューブテクスチャアンロード
//=============================================================================
void CTexture::CubeTexUnLoad()
{
    for (int nCount = 0; nCount < CUBE_TEX_MAX; nCount++)
    {
        if (m_pCubeTexture[nCount] != nullptr)
        {
            m_pCubeTexture[nCount]->Release();
            m_pCubeTexture[nCount] = nullptr;
        }
    }
}

//=============================================================================
// キューブテクスチャの情報
//=============================================================================
LPDIRECT3DCUBETEXTURE9 CTexture::GetCubeTexture(const CUBE_TEX_TYPE &Tex_Type)
{
    if (Tex_Type < CUBE_TEX_MAX)
    {
        if (m_pVolumeTexture[Tex_Type] != nullptr)
        {
            return m_pCubeTexture[Tex_Type];
        }
    }

    return nullptr;
}