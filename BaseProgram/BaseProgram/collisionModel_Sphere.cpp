//=============================================================================
//
// �����蔻�胂�f��(����)�̏��� [collisionModel_Sphere.cpp]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "collisionModel_Sphere.h"
#include "library.h"

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CCollisionModelSphere::CCollisionModelSphere(PRIORITY Priority) :CCollisionModel(Priority)
{
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CCollisionModelSphere::~CCollisionModelSphere()
{
}

//*****************************************************************************
// �����蔻�胂�f���̐���
//*****************************************************************************
CCollisionModelSphere * CCollisionModelSphere::Create(const D3DXVECTOR3 &pos, const float &radius, const D3DXVECTOR3 &rot)
{
    CCollisionModelSphere *pCollisionModelSphere = new CCollisionModelSphere;

    if (pCollisionModelSphere)
    {
        //�����蔻�胂�f�����̐ݒ�
        pCollisionModelSphere->SetInfo(pos, D3DXVECTOR3(radius, radius, radius), rot);
        pCollisionModelSphere->SetType(TYPE_SPHERE);

        //�����蔻�胂�f���̏���������
        pCollisionModelSphere->Init();

        return pCollisionModelSphere;
    }

    return nullptr;
}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CCollisionModelSphere::Init()
{
    CCollisionModel::Init();

    return E_NOTIMPL;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CCollisionModelSphere::Uninit()
{
    CCollisionModel::Uninit();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CCollisionModelSphere::Update()
{
    CCollisionModel::Update();
}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CCollisionModelSphere::Draw()
{
    CCollisionModel::Draw();
}