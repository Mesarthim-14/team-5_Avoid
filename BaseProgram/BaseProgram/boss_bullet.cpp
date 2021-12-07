//=============================================================================
//
// �{�X�̔��˒e [boss_bullet.cpp]
// Author : Hayashikawa Sarina
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "boss_bullet.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "library.h"
#include "collision.h"
#include "collisionModel_Sphere.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS            (ZeroVector3)
#define TEST_ROT            (ZeroVector3)
#define COLLISION_RADIUS    (900.0f)
#define SPEED               (150.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBossBullet::CBossBullet(PRIORITY Priority) : CBullet(Priority)
{
    m_pModel = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBossBullet::~CBossBullet()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBossBullet * CBossBullet::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // �������m��
    CBossBullet *pBullet = new CBossBullet(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pBullet)
    {
        // ����������
        pBullet->Init(pos, rot);
        return pBullet;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossBullet::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    SetPos(pos);
    SetRot(rot);
    SetSize(D3DXVECTOR3(COLLISION_RADIUS * 2, COLLISION_RADIUS * 2, COLLISION_RADIUS * 2));

    // ����������
    CBullet::Init();

    m_pModel = CModel::Create(pos, rot);
    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_KRAKEN_BULLET);
    m_pModel->GetModelInfo()->SetModelStatus(pos, rot, model);
    FollowPlayer();
    SetLife(200);

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossBullet::Uninit()
{
    if (m_pModel)
    {
        m_pModel->Uninit();
        m_pModel = nullptr;
    }
    CBullet::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossBullet::Update()
{
    if (m_pModel)
    {
        m_pModel->GetModelInfo()->SetPos(GetPos());
    }
     
    CBullet::Update();

    // �Փ˔���
    Hit();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBossBullet::Draw()
{
    CBullet::Draw();
}

//=============================================================================
// �Փ˔���
//=============================================================================
void CBossBullet::Hit()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    //CPlayer* pPlayer = nullptr;
    //pPlayer = (CPlayer*)GetTop(PRIORITY_CHARACTER);

    if (pPlayer)
    {
        if (GetColSpherePtr() && pPlayer->GetColCapsulePtr())
        {
            if (CCollision::ColSphereAndCapsule(GetColSpherePtr()->GetInfo(), pPlayer->GetColCapsulePtr()->GetInfo()))
            {
                Uninit();
            }
        }
    }
}

//=============================================================================
// �ړ��ʐݒ�
//=============================================================================
void CBossBullet::FollowPlayer()
{
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        D3DXVECTOR3 This = GetPos();
        D3DXVECTOR3 Target = pPlayer->GetPos();
        // 2�_�Ԃ̃x�N�g�������߂�i�I�_[�ڕW�n�_] - �n�_[���g�̈ʒu]�j
        D3DXVECTOR3 Vector = Target - This;
        Vector = *D3DXVec3Normalize(&Vector, &Vector);
        Vector *= SPEED;

        // �ړ��ʐݒ�
        SetMove(Vector);
    }
}

//=============================================================================
// ���̃|�C���^����
//=============================================================================
void CBossBullet::Move()
{
}