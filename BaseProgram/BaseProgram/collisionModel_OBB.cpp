//=============================================================================
//
// �����蔻�胂�f��(������)�̏��� [collisionModelOBB.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel_OBB.h"
#include "library.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCollisionModelOBB::CCollisionModelOBB(PRIORITY Priority) :CCollisionModel(Priority)
{
    memset(&m_DirVect, 0, sizeof(m_DirVect));
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCollisionModelOBB::~CCollisionModelOBB()
{
}

//*****************************************************************************
// �����蔻�胂�f���̐���
//*****************************************************************************
CCollisionModelOBB * CCollisionModelOBB::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot)
{
    CCollisionModelOBB *pCollisionModelOBB = new CCollisionModelOBB(PRIORITY_COLLISION);

    if (pCollisionModelOBB)
    {
        //�����蔻�胂�f�����̐ݒ�
        pCollisionModelOBB->SetInfo(pos, size, rot);
        pCollisionModelOBB->SetType(TYPE_OBB);

        //�����蔻�胂�f���̏���������
        pCollisionModelOBB->Init();

        return pCollisionModelOBB;
    }

    return nullptr;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CCollisionModelOBB::Init()
{
    CCollisionModel::Init();

    // �@���x�N�g���̐ݒ�
    SetDirVect();

    return E_NOTIMPL;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CCollisionModelOBB::Uninit()
{
    CCollisionModel::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CCollisionModelOBB::Update()
{
    CCollisionModel::Update();

    // �@���x�N�g���̐ݒ�
    SetDirVect();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CCollisionModelOBB::Draw()
{
#ifdef _DEBUG
    CCollisionModel::Draw();
#endif
}

//*****************************************************************************
// �@���x�N�g���̐ݒ�
//*****************************************************************************
void CCollisionModelOBB::SetDirVect()
{
    D3DXVECTOR3 InitDirVect[AXIS_MAX];  // ���������x�N�g��
    D3DXVECTOR3 size = GetInfo().size;  // �傫��

    //�e���̉�]�O���W�̐ݒ�(��]���Ă��Ȃ�XYZ���ɑ傫��������K��)
    InitDirVect[AXIS_X] = D3DXVECTOR3(size.x / 2, 0.0f, 0.0f);
    InitDirVect[AXIS_Y] = D3DXVECTOR3(0.0f, size.y / 2, 0.0f);
    InitDirVect[AXIS_Z] = D3DXVECTOR3(0.0f, 0.0f, size.z / 2);

    //�e���̕����x�N�g���̌v�Z
    for (int nCount = 0; nCount < AXIS_MAX; nCount++)
    {
        CLibrary::Rotate3D(InitDirVect[nCount], GetInfo().rot);
        m_DirVect[nCount] = InitDirVect[nCount];
    }
}