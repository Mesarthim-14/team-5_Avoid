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
#include "state_player_knockback.h"
#include "caution_boss_bullet_ui.h"
#include "gauge.h"
#include "particlepop.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS            (ZeroVector3)
#define TEST_ROT            (ZeroVector3)
#define COLLISION_RADIUS    (1800.0f)
#define SPEED               (150.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBossBullet::CBossBullet(PRIORITY Priority) : CBullet(Priority)
{
    m_pModel = nullptr;
    m_pCaution = nullptr;
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
    SetColRadius(COLLISION_RADIUS);

    // ����������
    CBullet::Init();

    m_pModel = CModel::Create(pos, rot);
    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_KRAKEN_BULLET);
    m_pModel->GetModelInfo()->SetModelStatus(pos, rot, model);
    FollowPlayer();
    SetLife(200);
    if (!m_pCaution)
    {
        m_pCaution = CCautionBossBulletUi::Create();
        m_pCaution->SetBulletPos(pos);
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
    D3DXVECTOR3 pos = GetPos();
    if (m_pModel)
    {
        m_pModel->GetModelInfo()->SetPos(GetPos());
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
// �Փ˔���
//=============================================================================
void CBossBullet::Hit()
{
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    CGauge * pGauge = CManager::GetInstance()->GetGame()->GetGauge();
    D3DXVECTOR3 pos = pPlayer->GetPos();
    if (!pPlayer)
    {
        return;
    }

    if (pPlayer->GetCollision())
    {
        if (GetColSpherePtr() && pPlayer->GetColCapsulePtr())
        {
            if (CCollision::ColSphereAndCapsule(GetColSpherePtr()->GetSphere(), pPlayer->GetColCapsulePtr()->GetInfo()))
            {
                // ������Ԓl
                D3DXVECTOR3 move = GetMove();
                move.x *= 0.5f;
                move.z *= 0.5f;
                move.y += 50.0f;
                pPlayer->ChangeState(CPlayerStateKnockback::Create(move));  // �v���C���[���m�b�N�o�b�N
                pPlayer->SubLife(20);                                       // �̗͂����炷
                // ���g�̏I������
                pGauge->SetHitDown(true);
                pGauge->SetDown(20);
                // �p�[�e�B�N���̐���
                for (int nCntParticle = 0; nCntParticle <= 20; nCntParticle++)
                {
                    CParticlePop::Create(pos);
                }
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