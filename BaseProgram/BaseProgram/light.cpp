//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LIGHT_POS   (D3DXVECTOR3(100000.0f, 100000.0f, 0.0f))        // ���C�g�̍��W

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{
    //��������0�N���A
    SecureZeroMemory(&m_Light, sizeof(D3DLIGHT9));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CLight * CLight::Create()
{
    // �������m��
    CLight *pLight = new CLight;

    if (pLight)
    {
        // ����������
        pLight->Init();
        return pLight;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLight::Init()
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    //���C�g���N���A����
    SecureZeroMemory(&m_Light, sizeof(D3DLIGHT9));

    // ���W�ݒ�
    m_Light.Position = LIGHT_POS;
    //���C�g�^�C�v�̎w��
    m_Light.Type = D3DLIGHT_DIRECTIONAL;
    //���̊g�U�̎w��
    m_Light.Diffuse = WhiteColor;
    m_Light.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
    m_Light.Specular = WhiteColor;

    //���C�g�����̎w��
    m_vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

    //���K������i�傫��1�̃x�N�g���ɂ���K�v������j
    D3DXVec3Normalize(&m_vecDir, &m_vecDir);

    // �x�N�g���̐ݒ�
    m_Light.Direction = m_vecDir;
    //���C�g��ݒ肷��
    pDevice->SetLight(0, &m_Light);
    //���C�g��L���ɂ���
    pDevice->LightEnable(0, TRUE);

    return S_OK;
}

//=============================================================================
// ���C�g�N���X�̏I������
//=============================================================================
void CLight::Uninit()
{
}

//=============================================================================
// ���C�g�N���X�̍X�V����
//=============================================================================
void CLight::Update()
{
}

//=============================================================================
// imgui ���C�g�̏��
//=============================================================================
void CLight::ShowLightInfo()
{
    if (ImGui::CollapsingHeader("LightInfo"))
    {
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();    // �f�o�C�X�̎擾

        if (ImGui::TreeNode("Light0"))
        {
            ImGui::SliderFloat3("direction", m_vecDir, -1.0f, 1.0f);

            D3DXVec3Normalize(&m_vecDir, &m_vecDir);        //���K��
            m_Light.Direction = m_vecDir;

            pDevice->SetLight(0, &m_Light);
            ImGui::TreePop();
        }
    }
}

//=============================================================================
// ���C�g�̕���
//=============================================================================
void CLight::SetVecDir(const D3DXVECTOR3 &Dir)
{
        //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

     m_vecDir = Dir; 

     //���K������i�傫��1�̃x�N�g���ɂ���K�v������j
     D3DXVec3Normalize(&m_vecDir, &m_vecDir);

     // �x�N�g���̐ݒ�
     m_Light.Direction = m_vecDir;

     //���C�g��ݒ肷��
     pDevice->SetLight(0, &m_Light);
}
