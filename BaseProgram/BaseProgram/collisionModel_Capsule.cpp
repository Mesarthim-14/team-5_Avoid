//=============================================================================
//
// �����蔻�胂�f��(�J�v�Z��)�̏��� [collisionModel_Capsule.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel_Capsule.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCollisionModelCapsule::CCollisionModelCapsule(PRIORITY Priority) :CScene(Priority)
{
    memset(&m_apMesh, 0, sizeof(m_apMesh));
    memset(&m_apBuffMat, 0, sizeof(m_apBuffMat));
    memset(&m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCollisionModelCapsule::~CCollisionModelCapsule()
{
}

//*****************************************************************************
// ���[�h
//*****************************************************************************
void CCollisionModelCapsule::Load()
{
    // �f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    // �~���̍쐬
    D3DXCreateCylinder(
        pDevice,            // �f�o�C�X���
        0.5f,               // ��O�̉~�̔��a
        0.5f,               // ���̉~�̔��a
        1.0f,               // �~���̒���
        10,                 // �X���C�X(�~�̒��_��)
        1,                  // �X�^�b�N(�~���̕�����)
        &m_apMesh[0],       // ���b�V�����
        &m_apBuffMat[0]);   // �o�b�t�@���

    // ���̍쐬
    D3DXCreateSphere(
        pDevice,            // �f�o�C�X���
        0.5f,               // ���a
        10,                 // �X���C�X�̐�
        10,                 // �X�^�b�N��
        &m_apMesh[1],       // ���b�V�����
        &m_apBuffMat[1]);   // �o�b�t�@���

    // ���̍쐬
    D3DXCreateSphere(
        pDevice,            // �f�o�C�X���
        0.5f,               // ���a
        10,                 // �X���C�X�̐�
        10,                 // �X�^�b�N��
        &m_apMesh[2],       // ���b�V�����
        &m_apBuffMat[2]);   // �o�b�t�@���
}

//*****************************************************************************
// �A�����[�h����
//*****************************************************************************
void CCollisionModelCapsule::Unload()
{
    for (int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        if (m_apMesh[nCount])
        {
            //���b�V���̔j��
            m_apMesh[nCount]->Release();
            m_apMesh[nCount] = nullptr;
        }

        if (m_apBuffMat[nCount])
        {
            //�o�b�t�@�̔j��
            m_apBuffMat[nCount]->Release();
            m_apBuffMat[nCount] = nullptr;
        }
    }
}

//*****************************************************************************
// �����蔻�胂�f���̐���
//*****************************************************************************
CCollisionModelCapsule * CCollisionModelCapsule::Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot)
{
    CCollisionModelCapsule *pCollisionModelSphere = new CCollisionModelCapsule;

    if (pCollisionModelSphere)
    {
        //�����蔻�胂�f�����̐ݒ�
        pCollisionModelSphere->m_info.pos = pos;
        pCollisionModelSphere->m_info.radius = radius;
        pCollisionModelSphere->m_info.length = length;
        pCollisionModelSphere->m_info.rot = rot;

        //�����蔻�胂�f���̏���������
        pCollisionModelSphere->Init();

        return pCollisionModelSphere;
    }

    return nullptr;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CCollisionModelCapsule::Init()
{
    // ���[�h����
    Load();

    return E_NOTIMPL;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CCollisionModelCapsule::Uninit()
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
void CCollisionModelCapsule::Update()
{
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CCollisionModelCapsule::Draw()
{
#ifdef _DEBUG
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

    for (int nCount = 0; nCount < TYPE_MAX; nCount++)
    {
        //�F�̐ݒ�
        D3DXMATERIAL* mat = (D3DXMATERIAL*)m_apBuffMat[nCount]->GetBufferPointer();
        mat->MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
        mat->MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
        mat->MatD3D.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
        mat->MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

        //���C���[�t���[���ŕ`��
        pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

        //���[���h�}�g���b�N�X�̏�����
        D3DXMatrixIdentity(&m_mtxWorld);

        // �p�x�̐ݒ�
        SetRot(nCount);

        // �傫���̐ݒ�
        SetSize(nCount);

        // �ʒu�̐ݒ�
        SetPos(nCount);

        //���[���h�}�g���b�N�X�̐ݒ�
        pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

        D3DMATERIAL9 matDef;    //���݂̃}�e���A���ێ��p
        memset(&matDef, 0, sizeof(matDef));

        //���݂̃}�e���A�����擾����
        pDevice->GetMaterial(&matDef);

        //�}�e���A���f�[�^�ւ̃|�C���^
        D3DXMATERIAL*pMat = nullptr;

        //�}�e���A���f�[�^�ւ̃|�C���^���擾
        pMat = (D3DXMATERIAL*)m_apBuffMat[nCount]->GetBufferPointer();

        //�}�e���A���̃A���r�G���g�Ƀf�B�t���[�Y�J���[��ݒ�
        pMat->MatD3D.Ambient = pMat->MatD3D.Diffuse;

        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&pMat->MatD3D);

        if (m_apMesh)
        {
            //���f���p�[�c�̕`��
            m_apMesh[nCount]->DrawSubset(0);
        }

        pDevice->SetTexture(0, nullptr);

        //�ێ����Ă����}�e���A����߂�
        pDevice->SetMaterial(&matDef);
        pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
    }

    //���C���[�t���[�������ǂ�
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif
}

//*****************************************************************************
// �ʒu�̐ݒ�
//*****************************************************************************
void CCollisionModelCapsule::SetPos(const int &nCount)
{
    D3DXMATRIX mtxTrans;
    memset(&mtxTrans, 0, sizeof(mtxTrans));

    D3DXVECTOR3 pos = ZeroVector3;  // �����蔻�胂�f���̈ʒu

    switch (nCount)
    {
    case TYPE_CYLINDER:

        pos = D3DXVECTOR3(m_info.pos.x, m_info.pos.y, m_info.pos.z);

        break;

    case TYPE_SPHERE_1:

        // ��]�ʂ�0�̂Ƃ��̍��W�����_�𒆐S�ɐݒ�
        pos = D3DXVECTOR3(0.0f, ((m_info.length / 2) - m_info.radius), 0.0f);

        // �_�̎O������]����
        CLibrary::Rotate3D(pos, m_info.rot);

        // �~���̍��W�ɑ����āA���m�Ȉʒu�ɐݒ肷��
        pos += m_info.pos;

        // �����̎n�_�̐ݒ�
        m_info.P0 = pos;

        break;

    case TYPE_SPHERE_2:

        // ��]�ʂ�0�̂Ƃ��̍��W�����_�𒆐S�ɐݒ�
        pos = D3DXVECTOR3(0.0f, -((m_info.length / 2) - m_info.radius), 0.0f);

        // �_�̎O������]����
        CLibrary::Rotate3D(pos, m_info.rot);

        // �~���̍��W�ɑ����āA���m�Ȉʒu�ɐݒ肷��
        pos += m_info.pos;

        // �����̏I�_�̐ݒ�
        m_info.P1 = pos;

        break;

    default:

        break;
    }

    //�ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//*****************************************************************************
// �傫���̐ݒ�
//*****************************************************************************
void CCollisionModelCapsule::SetSize(const int &nCount)
{
    D3DXMATRIX mtxScale;
    memset(&mtxScale, 0, sizeof(mtxScale));

    D3DXVECTOR3 scale = ZeroVector3;

    switch (nCount)
    {
    case TYPE_CYLINDER:

        scale = D3DXVECTOR3(m_info.radius * 2, m_info.length - (m_info.radius * 2), m_info.radius * 2);

        break;

    case TYPE_SPHERE_1:
    case TYPE_SPHERE_2:

        scale = D3DXVECTOR3(m_info.radius * 2, m_info.radius * 2, m_info.radius * 2);

        break;

    default:

        break;
    }

    // �g�嗦�𔽉f
    D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);
}

//*****************************************************************************
// �p�x�̐ݒ�
//*****************************************************************************
void CCollisionModelCapsule::SetRot(const int &nCount)
{
    D3DXMATRIX mtxRot;
    memset(&mtxRot, 0, sizeof(mtxRot));

    D3DXVECTOR3 rot = ZeroVector3;

    switch (nCount)
    {
    case TYPE_CYLINDER:

        rot = D3DXVECTOR3(m_info.rot.x + D3DXToRadian(90.0f), m_info.rot.y, m_info.rot.z);

        break;

    case TYPE_SPHERE_1:
    case TYPE_SPHERE_2:

        rot = D3DXVECTOR3(m_info.rot.x, m_info.rot.y, m_info.rot.z);

        break;

    default:

        break;
    }

    //�����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
    D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
}