//=============================================================================
//
// �����蔻�胂�f��(�~��)�̏��� [collisionModel_Cylinder.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel_Cylinder.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ROT (D3DXVECTOR3(D3DXToRadian(90), 0.0f, 0.0f))

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCollisionModelCylinder::CCollisionModelCylinder(PRIORITY Priority) :CCollisionModel(Priority)
{
    float m_radius = 0.0f;
    float m_length = 0.0f;
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCollisionModelCylinder::~CCollisionModelCylinder()
{
}

//*****************************************************************************
// �����蔻�胂�f���̐���
//*****************************************************************************
CCollisionModelCylinder * CCollisionModelCylinder::Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot)
{
    CCollisionModelCylinder *pColModelCylinder = new CCollisionModelCylinder(PRIORITY_COLLISION);

    if (pColModelCylinder)
    {
        //�����蔻�胂�f�����̐ݒ�
        pColModelCylinder->m_radius = radius;
        pColModelCylinder->m_length = length;
        pColModelCylinder->SetInfo(pos, D3DXVECTOR3(radius * 2, radius * 2, length), ROT + rot);
        pColModelCylinder->SetType(TYPE_CYLINDER);

        //�����蔻�胂�f���̏���������
        pColModelCylinder->Init();

        return pColModelCylinder;
    }

    return nullptr;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CCollisionModelCylinder::Init()
{
    CCollisionModel::Init();

    return E_NOTIMPL;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CCollisionModelCylinder::Uninit()
{
    CCollisionModel::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CCollisionModelCylinder::Update()
{
    CCollisionModel::Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CCollisionModelCylinder::Draw()
{
#ifdef _DEBUG
    CCollisionModel::Draw();
#endif
}