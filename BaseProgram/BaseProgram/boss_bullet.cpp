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
#include "caution_boss_bullet_ui.h"
#include "collisionModel_Sphere.h"
#include "collisionModel_OBB.h"
#include "kraken.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS            (ZeroVector3)
#define TEST_ROT            (ZeroVector3)
#define COLLISION_RADIUS    (3750.0f)
#define COLLISION_SIZE_OBB  (D3DXVECTOR3(7500.0f, 7500.0f, 7500.0f))
#define SPEED               (400.0f)
#define LIFE                (300)
#define FIX_POS             (-15000.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBossBullet::CBossBullet(PRIORITY Priority) : CBullet(Priority)
{
    m_pModel = nullptr;
    m_pCaution = nullptr;
    m_bDeath = false;
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
    CBossBullet *pBullet = new CBossBullet(PRIORITY_BULLET);

    // !nullcheck
    if (pBullet)
    {
        // ����������
        pBullet->SetPos(pos);
        pBullet->SetRot(rot);
        pBullet->SetColRadius(COLLISION_RADIUS);
        pBullet->SetColSizeOBB(COLLISION_SIZE_OBB);
        pBullet->FixPos(pos);
        pBullet->Init();
        return pBullet;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossBullet::Init()
{
    // ����������
    CBullet::Init();

    m_pModel = CModel::Create(GetPos(), GetRot());
    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_KRAKEN_BULLET);
    m_pModel->GetModelInfo()->SetModelStatus(GetPos(), GetRot(), model);
    FollowPlayer();
    SetLife(LIFE);
    if (!m_pCaution)
    {
        m_pCaution = CCautionBossBulletUi::Create();
        m_pCaution->SetBulletPos(GetPos());
    }

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
    if (m_pCaution)
    {
        m_pCaution->Uninit();
        m_pCaution = nullptr;
    }

    CBullet::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossBullet::Update()
{
    // �j�����肪true�̂Ƃ�
    if (m_bDeath)
    {
        // �I������
        Uninit();
        return;
    }

    if (m_pModel)
    {
        m_pModel->GetModelInfo()->SetPos(GetPos());
    }

    // �����蔻�胂�f���̍X�V
    if (GetColSpherePtr())
    {
        GetColSpherePtr()->SetInfo(GetPos(), D3DXVECTOR3(COLLISION_RADIUS * 2, COLLISION_RADIUS * 2, COLLISION_RADIUS * 2), GetRot());
    }
    if (GetColOBBPtr())
    {
        GetColOBBPtr()->SetInfo(GetPos(), GetColOBBPtr()->GetOBB().info.size, GetRot());
    }

    // �x��
    if (m_pCaution)
    {
        m_pCaution->SetBulletPos(GetPos());
    }

    // �e�N���X�̍X�V����
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
// ���W�̏C��
//=============================================================================
void CBossBullet::FixPos(const D3DXVECTOR3& pos)
{
    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    if (pKraken)
    {
        D3DXVECTOR3 rot = pKraken->GetRot();
        D3DXVECTOR3 FixPos = D3DXVECTOR3(
            pos.x +(sinf(rot.y))*FIX_POS,
            pos.y,
            pos.z + (cosf(rot.y))*FIX_POS);

        SetPos(FixPos);
    }
}