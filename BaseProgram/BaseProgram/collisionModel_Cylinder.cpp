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
#include "library.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCollisionModelCylinder::CCollisionModelCylinder(PRIORITY Priority) :CCollisionModel(Priority)
{
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
    CCollisionModelCylinder *pCollisionModelCylinder = new CCollisionModelCylinder;

    if (pCollisionModelCylinder)
    {
        //�����蔻�胂�f�����̐ݒ�
        pCollisionModelCylinder->SetInfo(pos, D3DXVECTOR3(radius * 2, radius * 2, length), rot);
        pCollisionModelCylinder->SetType(TYPE_CYLINDER);

        //�����蔻�胂�f���̏���������
        pCollisionModelCylinder->Init();

        return pCollisionModelCylinder;
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
    CCollisionModel::Draw();
}