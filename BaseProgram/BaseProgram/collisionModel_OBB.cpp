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
    CCollisionModelOBB *pCollisionModelOBB = new CCollisionModelOBB;

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

    //�e���̉�]�O���W�̐ݒ�(��]���Ă��Ȃ�XYZ���ɑ傫��������K��)
    m_DirVect[0] = D3DXVECTOR3(GetInfo().size.x / 2, 0.0f, 0.0f);
    m_DirVect[1] = D3DXVECTOR3(0.0f, GetInfo().size.y / 2, 0.0f);
    m_DirVect[2] = D3DXVECTOR3(0.0f, 0.0f, GetInfo().size.z / 2);

    //�e���̕����x�N�g���̌v�Z
    for (int nCount = 0; nCount < AXIS_NUM_OBB; nCount++)
    {
        CLibrary::Rotate3D(m_DirVect[nCount], GetInfo().rot);
    }

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
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CCollisionModelOBB::Draw()
{
    CCollisionModel::Draw();
}