//=============================================================================CShadow
//
// �V���h�E�N���X [shadow.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "light.h"
#include "shadow_volume.h"
#include "shadow_polygon.h"

//=============================================================================
// static������
//=============================================================================
CShadowPolygon *CShadow::m_pPolygon = nullptr;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow()
{
    m_pShadowVolume = nullptr;
    D3DXMatrixIdentity(&m_ModelMtxWorld);
    m_bDrawUpdate = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CShadow * CShadow::Create(const LPD3DXMESH &pSrcMesh)
{
    // �������m��
    CShadow *pShadow = new CShadow;

    // !nullcheck
    if (pShadow)
    {
        // ����������
        pShadow->Init(pSrcMesh);
    }

    return pShadow;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShadow::Init(const LPD3DXMESH &pSrcMesh)
{
    // nullcheck
    if (!m_pShadowVolume)
    {
        // �e�̐���
        m_pShadowVolume = CShadowVolume::Create(pSrcMesh);
    }

    // nullcheck
    if (!m_pPolygon)
    {
        m_pPolygon = CShadowPolygon::Create();
    }

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShadow::Uninit()
{
    if (m_pShadowVolume)
    {
        // �V���h�E�{�����[���I������
        m_pShadowVolume->Uninit();
        delete m_pShadowVolume;
        m_pShadowVolume = nullptr;
    }
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CShadow::VolumeDraw()
{
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    //���[���h�}�g���N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &m_ModelMtxWorld);

    // �V���h�E�̕`��
    if (m_pShadowVolume)
    {
        // �X�e���V���ݒ�
        SetShadowStateStencil();

        // �V���h�E�{�����[���̕`��
        m_pShadowVolume->Draw();

        // ��Ԃ����ɖ߂�
        // �X�e���V���e�X�g�͏�ɍ��i�ɂ���
        pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
        // pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

        // �����_�����O�^�[�Q�b�g�ɏ������݂͂��Ȃ�
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
        pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    }
}

//=============================================================================
// �e�̐�������(��]����E�}�g���N�X�̏C��������d��)
//=============================================================================
void CShadow::CreateShadow(const D3DXVECTOR3 &rot, const D3DXVECTOR3 &ShipRot, const D3DXMATRIX &ModelMtxWorld)
{
    // ���[���h���W���󂯎��
    m_ModelMtxWorld = ModelMtxWorld;

    // �e�̐���
    if (m_pShadowVolume)
    {
        m_pShadowVolume->CreateShadow(rot, ShipRot);
    }
}

//=============================================================================
// �e�̐�������
//=============================================================================
void CShadow::CreateShadow(const D3DXVECTOR3 &rot, const D3DXMATRIX &ModelMtxWorld)
{
    if (m_bDrawUpdate)
    {
        return;
    }
    // �e�̐���
    if (m_pShadowVolume)
    {
        m_pShadowVolume->CreateShadow(rot);
    }

    // ���[���h���W���󂯎��
    m_ModelMtxWorld = ModelMtxWorld;

    m_bDrawUpdate = true;
}

//=============================================================================
// �X�e���V���̐ݒ�
// Author : Konishi Yuuto
//=============================================================================
void CShadow::SetShadowStateStencil()
{
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    //------------------------------------------------------------
    // �p�X1:�e�{�����[���̕`��
    //------------------------------------------------------------
    // �[�x�o�b�t�@�ɏ������݂͂��Ȃ�
    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

    // �����_�����O�^�[�Q�b�g�ɏ������݂͂��Ȃ�
    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, FALSE);

    // ���ʕ`��
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // ���ʃX�e���V�����g�p����
    pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, TRUE);

    // �X�e���V���e�X�g�͏�ɍ��i�ɂ���
    pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

    // �\�ʂ͐[�x�e�X�g�ɍ��i������X�e���V���o�b�t�@�̓��e��+1����
    pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

    // ���ʂ͐[�x�e�X�g�ɍ��i������X�e���V���o�b�t�@�̓��e��-1����
    pDevice->SetRenderState(D3DRS_CCW_STENCILPASS, D3DSTENCILOP_DECR);
}

//=============================================================================
// �X�e���V���e�X�g�ݒ�
// Author : Konishi Yuuto
//=============================================================================
void CShadow::SetShadowStencilTest()
{
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

    // ��Ԃ����ɖ߂�
    pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

    //--------------------------------------------------------------
    // �p�X2:�e�̕`��
    //--------------------------------------------------------------
    // �A���t�@�u�����f�B���O�͐��^�Ɋ|����
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

    // �X�e���V���o�b�t�@�̒l��1�ȏ�̎��ɏ�������
    pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
    pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);

    // ���߂���
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �X�e���V���ݒ胊�Z�b�g
// Author : Konishi Yuuto
//=============================================================================
void CShadow::ReSetShadowStateStencil()
{
    LPDIRECT3DDEVICE9 pDevice = GET_RENDERER_DEVICE;

    // ��Ԃ����ɖ߂�
    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CShadow::PolygonUninit()
{
    if (m_pPolygon)
    {
        // �|���S���I������
        m_pPolygon->Uninit();
        m_pPolygon = nullptr;
    }
}