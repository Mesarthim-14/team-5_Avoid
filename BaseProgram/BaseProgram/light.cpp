//=============================================================================
//
// ライト処理 [light.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LIGHT_POS   (D3DXVECTOR3(100000.0f, 100000.0f, 0.0f))        // ライトの座標

//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{
    //メモリの0クリア
    SecureZeroMemory(&m_Light, sizeof(D3DLIGHT9));
}

//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CLight * CLight::Create()
{
    // メモリ確保
    CLight *pLight = new CLight;

    if (pLight)
    {
        // 初期化処理
        pLight->Init();
        return pLight;
    }

    return nullptr;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLight::Init()
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //ライトをクリアする
    SecureZeroMemory(&m_Light, sizeof(D3DLIGHT9));

    // 座標設定
    m_Light.Position = LIGHT_POS;
    //ライトタイプの指定
    m_Light.Type = D3DLIGHT_DIRECTIONAL;
    //光の拡散の指定
    m_Light.Diffuse = WhiteColor;
    m_Light.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
    m_Light.Specular = WhiteColor;

    //ライト方向の指定
    m_vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

    //正規化する（大きさ1のベクトルにする必要がある）
    D3DXVec3Normalize(&m_vecDir, &m_vecDir);

    // ベクトルの設定
    m_Light.Direction = m_vecDir;
    //ライトを設定する
    pDevice->SetLight(0, &m_Light);
    //ライトを有効にする
    pDevice->LightEnable(0, TRUE);

    return S_OK;
}

//=============================================================================
// ライトクラスの終了処理
//=============================================================================
void CLight::Uninit()
{
}

//=============================================================================
// ライトクラスの更新処理
//=============================================================================
void CLight::Update()
{
}

//=============================================================================
// imgui ライトの情報
//=============================================================================
void CLight::ShowLightInfo()
{
    if (ImGui::CollapsingHeader("LightInfo"))
    {
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();    // デバイスの取得

        if (ImGui::TreeNode("Light0"))
        {
            ImGui::SliderFloat3("direction", m_vecDir, -1.0f, 1.0f);

            D3DXVec3Normalize(&m_vecDir, &m_vecDir);        //正規化
            m_Light.Direction = m_vecDir;

            pDevice->SetLight(0, &m_Light);
            ImGui::TreePop();
        }
    }
}

//=============================================================================
// ライトの方向
//=============================================================================
void CLight::SetVecDir(const D3DXVECTOR3 &Dir)
{
        //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

     m_vecDir = Dir; 

     //正規化する（大きさ1のベクトルにする必要がある）
     D3DXVec3Normalize(&m_vecDir, &m_vecDir);

     // ベクトルの設定
     m_Light.Direction = m_vecDir;

     //ライトを設定する
     pDevice->SetLight(0, &m_Light);
}
