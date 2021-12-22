//=============================================================================
//
// �����蔻�胂�f��(�|���S��)�̏��� [collisionModel_Polygon.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel_Polygon.h"
#include "library.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCollisionModelPolygon::CCollisionModelPolygon(PRIORITY Priority) :CCollisionModel(Priority)
{
    m_norVec = ZeroVector3;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCollisionModelPolygon::~CCollisionModelPolygon()
{
}

//*****************************************************************************
// �����蔻�胂�f���̐���
//*****************************************************************************
CCollisionModelPolygon * CCollisionModelPolygon::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR2 &size, const D3DXVECTOR3 &rot)
{
    CCollisionModelPolygon *pColModelPolygon = new CCollisionModelPolygon(PRIORITY_COLLISION);

    if (pColModelPolygon)
    {
        //�����蔻�胂�f�����̐ݒ�
        pColModelPolygon->SetInfo(pos, D3DXVECTOR3(size.x, 0.0f, size.y), rot);
        pColModelPolygon->SetType(TYPE_POLYGON);

        //�����蔻�胂�f���̏���������
        pColModelPolygon->Init();

        return pColModelPolygon;
    }

    return nullptr;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CCollisionModelPolygon::Init()
{
    CCollisionModel::Init();

    // �@���x�N�g���̐ݒ�
    m_norVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    CLibrary::Rotate3D(m_norVec, GetInfo().rot);

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
void CCollisionModelPolygon::Uninit()
{
    CCollisionModel::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CCollisionModelPolygon::Update()
{
    CCollisionModel::Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CCollisionModelPolygon::Draw()
{
#ifdef _DEBUG
    CCollisionModel::Draw();
#endif
}