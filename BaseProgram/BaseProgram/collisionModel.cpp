//=============================================================================
//
// �����蔻�胂�f���̐e�N���X���� [collisionModel.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCollisionModel::CCollisionModel(PRIORITY Priority) :CScene(Priority)
{
    m_pMesh = nullptr;
    m_pBuffMat = nullptr;
    memset(&m_info, 0, sizeof(m_info));
    m_type = TYPE_NONE;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCollisionModel::~CCollisionModel()
{
}

//*****************************************************************************
// ���[�h
//*****************************************************************************
void CCollisionModel::Load(void)
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    switch (m_type)
    {
    case TYPE_POLYGON:

        // �|���S���̍쐬
        D3DXCreatePolygon(
            pDevice,        // �f�o�C�X���
            10.0f,          // �ӂ̒���
            4,              // �ӂ̐�
            &m_pMesh,       // ���b�V�����
            &m_pBuffMat);   // �o�b�t�@���

        break;

    case TYPE_OBB:

        // �����̂̍쐬
        D3DXCreateBox(
            pDevice,        // �f�o�C�X���
            1.0f,           // ����
            1.0f,           // ����
            1.0f,           // ����
            &m_pMesh,       // ���b�V�����
            &m_pBuffMat);   // �o�b�t�@���

        break;

    case TYPE_SPHERE:

        // ���̍쐬
        D3DXCreateSphere(
            pDevice,        // �f�o�C�X���
            0.5f,           // ���a
            10,             // �X���C�X�̐�
            10,             // �X�^�b�N��
            &m_pMesh,       // ���b�V�����
            &m_pBuffMat);   // �o�b�t�@���

        break;

    case TYPE_CYLINDER:

        // �~���̍쐬
        D3DXCreateCylinder(
            pDevice,        // �f�o�C�X���
            0.5f,           // ��O�̉~�̔��a
            0.5f,           // ���̉~�̔��a
            1.0f,           // �~���̒���
            10,             // �X���C�X(�~�̒��_��)
            1,              // �X�^�b�N(�~���̕�����)
            &m_pMesh,       // ���b�V�����
            &m_pBuffMat);   // �o�b�t�@���

        break;

    default:

        break;
    }
}

//*****************************************************************************
// �A�����[�h
//*****************************************************************************
void CCollisionModel::Unload()
{
    if (m_pMesh)
    {
        //���b�V���̔j��
        m_pMesh->Release();
        m_pMesh = nullptr;
    }

    if (m_pBuffMat)
    {
        //�o�b�t�@�̔j��
        m_pBuffMat->Release();
        m_pBuffMat = nullptr;
    }
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CCollisionModel::Init()
{
    //���[�h����
    Load();

    return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CCollisionModel::Uninit()
{
    //�A�����[�h����
    Unload();

    //���[���h�}�g���b�N�X�̏�����
    memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));

    //�P�������[�X
    Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CCollisionModel::Update()
{
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CCollisionModel::Draw()
{
#ifdef _DEBUG
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // �F�̐ݒ�
    D3DXMATERIAL* mat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
    mat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
    mat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
    mat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
    mat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

    // ���C���[�t���[���ŕ`��
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    D3DXMATRIX mtxRot, mtxTrans, mtxScale;
    D3DMATERIAL9 matDef;    // ���݂̃}�e���A���ێ��p

    // ���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxWorld);

    // �g�嗦�𔽉f
    D3DXMatrixScaling(&mtxScale, m_info.size.x, m_info.size.y, m_info.size.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

    // �����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_info.rot.y, m_info.rot.x, m_info.rot.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

    // �ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, m_info.pos.x, m_info.pos.y, m_info.pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

    // ���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

    // ���݂̃}�e���A�����擾����
    pDevice->GetMaterial(&matDef);

    // �}�e���A���f�[�^�ւ̃|�C���^
    D3DXMATERIAL*pMat;

    // �}�e���A���f�[�^�ւ̃|�C���^���擾
    pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

    // �}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
    pMat->MatD3D.Ambient = pMat->MatD3D.Diffuse;

    // �}�e���A���̐ݒ�
    pDevice->SetMaterial(&pMat->MatD3D);

    if (m_pMesh)
    {
        // ���f���p�[�c�̕`��
        m_pMesh->DrawSubset(0);
    }

    pDevice->SetTexture(0, nullptr);

    // �ێ����Ă����}�e���A����߂�
    pDevice->SetMaterial(&matDef);
    pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

    // ���C���[�t���[�������ǂ�
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif
}