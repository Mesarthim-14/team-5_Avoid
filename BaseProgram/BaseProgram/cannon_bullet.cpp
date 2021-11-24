//=============================================================================
//
// ��C�̒e�N���X [cannon_bullet.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "cannon_bullet.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "model_info.h"
#include "player.h"
#include "kraken.h"
#include "library.h"
#include "collisionModel_OBB.h"
#include "kraken.h"
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SPEED       (100.0f)
#define SPEED_Y     (50.0f)
#define POS_FIX     (1000.0f)
#define POS_FIX_Y   (700.0f)
#define GRAVITY_NUM (0.65f)

#define SIZE (D3DXVECTOR3(200.0f, 200.0f, 200.0f))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCannonBullet::CCannonBullet(PRIORITY Priority) : CModel(Priority)
{
    m_fDistanceToKraken = 0.0f;
    m_KrakenPos = ZeroVector3;
    m_pCollision = nullptr;
    m_bHit = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCannonBullet::~CCannonBullet()
{
    if (m_pCollision)
    {
        m_pCollision->Uninit();
        m_pCollision = nullptr;
    }
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCannonBullet * CCannonBullet::Create(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot)
{
    // �������m��
    CCannonBullet *pCannonBullet = new CCannonBullet(PRIORITY_TEST_MODEL);

    // !nullcheck
    if (pCannonBullet)
    {
        // ����������
        pCannonBullet->Init(CannonPos, CannonRot);
        return pCannonBullet;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCannonBullet::Init(const D3DXVECTOR3 &CannonPos, const D3DXVECTOR3 &CannonRot)
{
    D3DXVECTOR3 pos = CannonPos;

    // �o���b�g�̏��ݒ�
    SetBulletInfo(pos, CannonRot);

    // ����������
    CModel::Init();

    CXfile *pXfile = GET_XFILE_PTR;
    CXfile::MODEL model = pXfile->GetXfile(CXfile::XFILE_NUM_CANNON_BULLET);
    GetModelInfo()->SetModelStatus(pos, ZeroVector3, model);
    
    if (!m_pCollision)
    {
        m_pCollision = CCollisionModelOBB::Create(pos, SIZE, ZeroVector3);
    }
    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CCannonBullet::Update()
{
    CModel::Update();
    
    // �����v�Z
    CalDistance();

    if (m_pCollision)
    {
        m_pCollision->SetInfo(GetPos(), m_pCollision->GetInfo().size, GetRot());
    }

    Collision();
}

//=============================================================================
// �����̌v�Z
//=============================================================================
void CCannonBullet::CalDistance()
{
    float fCurDistance = CLibrary::CalDistance(GetPos(), m_KrakenPos);
    if (fCurDistance * 0.5f <= m_fDistanceToKraken)
    {
        GetMove().y -= GRAVITY_NUM;
    }
}

//=============================================================================
// �e�̏��
//=============================================================================
void CCannonBullet::SetBulletInfo(D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // ��C�̒��S���Ⴄ�̂ŁA���W�����炷
    pos = D3DXVECTOR3(
        pos.x + (sinf(rot.y)*POS_FIX),
        pos.y + POS_FIX_Y,
        pos.z + (cos(rot.y)*POS_FIX));

    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken(); // �{�X�̃|�C���^
    m_KrakenPos = pKraken->GetPos();                                    // ���W�擾
    m_fDistanceToKraken = CLibrary::CalDistance(pos, m_KrakenPos);      // �����̎擾
    D3DXVECTOR3 move = CLibrary::FollowMoveXZ(pos, m_KrakenPos, SPEED); // XZ�̈ړ���
    move.y = SPEED_Y;                                                   // �����ǉ�
    SetMove(move);                                                      // �ړ��ʐݒ�
}

//=============================================================================
// �X�V����
//=============================================================================
void CCannonBullet::Collision()
{
    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    if (!pKraken)
    {
        return;
    }

    if (!m_bHit)
    {
        if (CCollision::ColOBBs(m_pCollision->GetOBB(), pKraken->GetCollosion()->GetOBB()))
        {
            pKraken->SubLife();
            m_bHit = true;
            Uninit();
        }
    }
}