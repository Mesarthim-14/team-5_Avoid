//=============================================================================
//
// ���U�C�N���� [gauss_filter.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "gauss_filter.h"
#include "manager.h"
#include "resource_manager.h"
#include "camera.h"
#include "texture.h"
#include "library.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAP_WIDTH	(512)
#define MAP_HEIGHT	(512)
#define FADE_NUM    (0.02f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGaussFilter::CGaussFilter(LPDIRECT3DDEVICE9 pd3dDevice)
{
    m_pd3dDevice = pd3dDevice;
    m_pEffect = nullptr;
    m_hTechnique = nullptr;
    m_hafWeight = nullptr;
    m_htSrcMap = nullptr;
    m_AlphaNum = nullptr;

    // �ʏ�̍��W�ϊ��s��
    D3DXMatrixIdentity(&m_mWorld);
    D3DXMatrixIdentity(&m_mView);
    D3DXMatrixIdentity(&m_mProj);

    m_pMapZ = nullptr;             // �[�x�o�b�t�@
    m_pOriginalMap = nullptr;      // �e�N�X�`��
    m_pOriginalMapSurf = nullptr;  // �T�[�t�F�X
    m_pXMap = nullptr;             // �e�N�X�`��
    m_pXMapSurf = nullptr;	        // �T�[�t�F�X
    m_pXYMap = nullptr;            // �e�N�X�`��
    m_pXYMapSurf = nullptr;        // �T�[�t�F�X
    m_pAllMap = nullptr;            // �e�N�X�`��
    m_pAllMapSurf = nullptr;        // �T�[�t�F�X
    m_pOldBackBuffer = nullptr;
    m_pOldZBuffer = nullptr;
    memset(&m_oldViewport, 0, sizeof(m_oldViewport));

    m_dispersion_sq = 5.0f;
    m_fAlphaNum = 1.0f;
    m_bFade = false;
    m_bUse = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGaussFilter::~CGaussFilter()
{
    if (m_pEffect)
    {
        m_pEffect->Release();
        m_pEffect = nullptr;
    }
}

//=============================================================================
// �I������
//=============================================================================
void CGaussFilter::Uninit()
{
    if (m_pMapZ)
    {
        m_pMapZ->Release();
        m_pMapZ = nullptr;
    }
    if (m_pOriginalMap)
    {
        m_pOriginalMap->Release();
        m_pOriginalMap = nullptr;
    }
    if (m_pOriginalMapSurf)
    {
        m_pOriginalMapSurf->Release();
        m_pOriginalMapSurf = nullptr;
    }
    if (m_pXMap)
    {
        m_pXMap->Release();
        m_pXMap = nullptr;
    }
    if (m_pXMapSurf)
    {
        m_pXMapSurf->Release();
        m_pXMapSurf = nullptr;
    }
    if (m_pXYMap)
    {
        m_pXYMap->Release();
        m_pXYMap = nullptr;
    }
    if (m_pXYMapSurf)
    {
        m_pXYMapSurf->Release();
        m_pXYMapSurf = nullptr;
    }
    if (m_pAllMap)
    {
        m_pAllMap->Release();
        m_pAllMap = nullptr;
    }
    if (m_pAllMapSurf)
    {
        m_pAllMapSurf->Release();
        m_pAllMapSurf = nullptr;
    }
    if (m_pEffect)
        m_pEffect->OnLostDevice();
    delete this;
}

//=============================================================================
// �f�o�C�X�ݒ�
//=============================================================================
void CGaussFilter::Restore()
{
    m_pd3dDevice->CreateDepthStencilSurface(
        SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D16,
        D3DMULTISAMPLE_NONE, 0, TRUE, &m_pMapZ, NULL);

    m_pd3dDevice->CreateTexture(
        SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pOriginalMap, NULL);
    m_pOriginalMap->GetSurfaceLevel(0, &m_pOriginalMapSurf);

    m_pd3dDevice->CreateTexture(
        SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pXMap, NULL);
    m_pXMap->GetSurfaceLevel(0, &m_pXMapSurf);

    m_pd3dDevice->CreateTexture(
        SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pXYMap, NULL);
    m_pXYMap->GetSurfaceLevel(0, &m_pXYMapSurf);

    m_pd3dDevice->CreateTexture(
        SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pAllMap, NULL);
    m_pAllMap->GetSurfaceLevel(0, &m_pAllMapSurf);

    m_pd3dDevice->CreateTexture(
        SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET,
        D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pScreenMap, NULL);

    if (m_pEffect)
    {
        m_pEffect->OnResetDevice();
    }
}

//=============================================================================
// �V�F�[�_���[�h
//=============================================================================
HRESULT CGaussFilter::Load()
{
    D3DCAPS9 caps;
    HRESULT hr;

    m_pd3dDevice->GetDeviceCaps(&caps);
    if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1) && caps.PixelShaderVersion >= D3DPS_VERSION(2, 0))
    {
        //�V�F�[�_�[�̏�����
        LPD3DXBUFFER pErr = nullptr;
        hr = D3DXCreateEffectFromFile(m_pd3dDevice, "data/Text/Shader/gauss_filter.fx", nullptr, nullptr, 0, nullptr, &m_pEffect, &pErr);
        if (FAILED(hr))
            return -2;

        m_hTechnique = m_pEffect->GetTechniqueByName("TShader");
        m_hafWeight = m_pEffect->GetParameterByName(NULL, "weight");
        m_htSrcMap = m_pEffect->GetParameterByName(NULL, "SrcMap");
        m_pEffect->SetFloat("MAP_WIDTH", SCREEN_WIDTH);             // ���̐ݒ�
        m_pEffect->SetFloat("MAP_HEIGHT", SCREEN_HEIGHT);           // �����̐ݒ�
        m_AlphaNum = m_pEffect->GetParameterByName(NULL, "fAlphaNum");

        D3DXVECTOR4 offset;
        // �V�F�[�_���Ŏg��2�e�N�Z������w�肷��萔
        offset.x = 16.0f / SCREEN_WIDTH;
        offset.y = 0.0f / SCREEN_HEIGHT;
        m_pEffect->SetVector("offsetX", &offset);
        offset.x = 0.0f / SCREEN_WIDTH;
        offset.y = 16.0f / SCREEN_HEIGHT;
        m_pEffect->SetVector("offsetY", &offset);
        // �d�݂�ݒ�
        UpdateWeight();

        m_pEffect->SetTechnique(m_hTechnique);
    }

    else
    {
        return -3;
    }

    return S_OK;
}

//=============================================================================
// �d�݂̌v�Z
//=============================================================================
void CGaussFilter::UpdateWeight()
{
//    ShowInfo();
    DWORD nCount;
    FLOAT total = 0;
    for (nCount = 0; nCount<WEIGHT_MUN; nCount++) 
    {
        FLOAT pos = 1.0f + 2.0f*(FLOAT)nCount;
        m_tbl[nCount] = expf(-0.5f*(FLOAT)(pos*pos) / m_dispersion_sq*m_dispersion_sq);
        total += 2.0f*m_tbl[nCount];
    }

    // �K�i��
    for (nCount = 0; nCount < WEIGHT_MUN; nCount++)
    {
        m_tbl[nCount] /= total;
    }

    if (m_pEffect)
    {
        m_pEffect->SetFloatArray(m_hafWeight, m_tbl, WEIGHT_MUN);
    }
}

//=============================================================================
// �T�[�t�F�X����ւ�
//=============================================================================
void CGaussFilter::BeginSurface()
{
    //-------------------------------------------------
    // �����_�����O�^�[�Q�b�g�̕ۑ�
    //-------------------------------------------------
    m_pd3dDevice->GetRenderTarget(0, &m_pOldBackBuffer);
    m_pd3dDevice->GetDepthStencilSurface(&m_pOldZBuffer);

    m_pd3dDevice->SetRenderTarget(0, m_pOriginalMapSurf);
    m_pd3dDevice->SetDepthStencilSurface(m_pMapZ);

    m_pd3dDevice->GetViewport(&m_oldViewport);

    // �r���[�|�[�g�̕ύX
    D3DVIEWPORT9 viewport = { 0,0   // ����̍��W
        , SCREEN_WIDTH              // ��
        , SCREEN_HEIGHT             // ����
        , 0.0f,1.0f };              // �O�ʁA���
    m_pd3dDevice->SetViewport(&viewport);

    // �����_�����O�^�[�Q�b�g�̃N���A
    m_pd3dDevice->Clear(0L, NULL
        , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
        , 0xffffffff, 1.0f, 0L);

    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

    ShowInfo();
    UpdateWeight();
    SetAlphaNum();
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CGaussFilter::DrawPolygon()
{   

    // ��s���f���̕`��
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

    m_pd3dDevice->LightEnable(0, TRUE);

    // �K�E�X�t�B���^
    GaussShader();

    // �T�[�t�F�X��߂�
    EndSurface();

    //-----------------------------------------------------
    // ���̂܂ܒ���
    //-----------------------------------------------------
    FLOAT w = (FLOAT)m_oldViewport.Width;
    FLOAT h = (FLOAT)m_oldViewport.Height;
    TVERTEX Vertex1[4] =
    {
        //x  y   z    rhw  tu tv
        { 0, 0, 0.1f, 1.0f, 0 + 0.5f / SCREEN_WIDTH, 0 + 0.5f / SCREEN_HEIGHT, },
        { w, 0, 0.1f, 1.0f, 1 + 0.5f / SCREEN_WIDTH, 0 + 0.5f / SCREEN_HEIGHT, },
        { w, h, 0.1f, 1.0f, 1 + 0.5f / SCREEN_WIDTH, 1 + 0.5f / SCREEN_HEIGHT, },
        { 0, h, 0.1f, 1.0f, 0 + 0.5f / SCREEN_WIDTH, 1 + 0.5f / SCREEN_HEIGHT, },
    };
    m_pd3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
    m_pd3dDevice->SetTexture(0, m_pOriginalMap);
    m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN
        , 2, Vertex1, sizeof(TVERTEX));

    //-----------------------------------------------------
    // �u���[�������̂𒣂�
    //-----------------------------------------------------
    m_pd3dDevice->SetTexture(0, m_pAllMap);
    m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN
        , 2, Vertex1, sizeof(TVERTEX));

    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

    FadeOut();
}

//=============================================================================
// �����x�̌��Z
//=============================================================================
void CGaussFilter::FadeOut()
{
    if (m_bFade)
    {
        m_fAlphaNum -= FADE_NUM;
        if (m_fAlphaNum <= 0.0f)
        {
            m_bUse = false;
            m_fAlphaNum = 0.0f;
        }
    }
}

//=============================================================================
// �K�E�X�V�F�[�_�̐ݒ�
//=============================================================================
void CGaussFilter::GaussShader()
{
    //-------------------------------------------------
    // �V�F�[�_�̐ݒ�
    //-------------------------------------------------
    m_pEffect->Begin(nullptr, 0);

    //-------------------------------------------------
    // 2�p�X��:�ڂ���x
    //-------------------------------------------------
    m_pd3dDevice->SetRenderTarget(0, m_pXMapSurf);
    m_pEffect->BeginPass(0);
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    struct VERTEX { FLOAT p[3]; FLOAT tu, tv; };
    VERTEX Vertex0[4] =
    {
        //   x      y     z      tu tv
        { { 1.0f, -1.0f, 0.1f }, 1, 1, },
        { { -1.0f, -1.0f, 0.1f }, 0, 1, },
        { { -1.0f, 1.0f, 0.1f }, 0, 0, },
        { { 1.0f, 1.0f, 0.1f }, 1, 0, },
    };

    m_pd3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
    m_pEffect->SetTexture(m_htSrcMap, m_pOriginalMap);
    m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN
        , 2, Vertex0, sizeof(VERTEX));
    m_pEffect->EndPass();

    //-------------------------------------------------
    // 3�p�X��:�ڂ���x
    //-------------------------------------------------
    m_pd3dDevice->SetRenderTarget(0, m_pXYMapSurf);
    m_pEffect->BeginPass(0);

    m_pEffect->SetTexture(m_htSrcMap, m_pXMap);
    m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN
        , 2, Vertex0, sizeof(VERTEX));
    m_pEffect->EndPass();

    //-------------------------------------------------
    // 3�p�X��:�ڂ���y
    //-------------------------------------------------
    m_pd3dDevice->SetRenderTarget(0, m_pAllMapSurf);
    m_pEffect->BeginPass(1);

    m_pEffect->SetTexture(m_htSrcMap, m_pXYMap);
    m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN
        , 2, Vertex0, sizeof(VERTEX));
    m_pEffect->EndPass();
    m_pEffect->End();
}

//=============================================================================
// �T�[�t�F�X��߂�
//=============================================================================
void CGaussFilter::EndSurface()
{
    //-----------------------------------------------------
    // �����_�����O�^�[�Q�b�g�����ɖ߂�
    //-----------------------------------------------------
    m_pd3dDevice->SetRenderTarget(0, m_pOldBackBuffer);
    m_pd3dDevice->SetDepthStencilSurface(m_pOldZBuffer);
    m_pd3dDevice->SetViewport(&m_oldViewport);
    if (m_pOldBackBuffer)
    {
        m_pOldBackBuffer->Release();
        m_pOldBackBuffer = nullptr;
    }
    if (m_pOldZBuffer)
    {
        m_pOldZBuffer->Release();
        m_pOldZBuffer = nullptr;
    }
}

//=============================================================================
// �����x
//=============================================================================
void CGaussFilter::SetAlphaNum()
{
    m_pEffect->SetFloat(m_AlphaNum, m_fAlphaNum);
}

//=============================================================================
// imgui���
//=============================================================================
void CGaussFilter::ShowInfo()
{
#ifdef _DEBUG

    //�����_���[�ŊǗ����Ă��̏��
    ImGui::Begin("DebugInfo");

    if (ImGui::CollapsingHeader("GaussFilter"))
    {
        LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

        if (ImGui::TreeNode("Info"))
        {

            // �����̒l
            ImGui::SliderFloat("dispersion_sq", &m_dispersion_sq, 0.0f, 10.0f);
            ImGui::SliderFloat("m_fAlphaNum", &m_fAlphaNum, 0.0f, 1.0f);

            ImGui::TreePop();
        }
    }

    ImGui::End();

#endif // !_DEBUG
}
