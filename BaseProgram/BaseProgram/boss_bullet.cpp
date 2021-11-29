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

//=============================================================================
// �}�N����`
//=============================================================================
#define TEST_POS        (ZeroVector3)
#define TEST_ROT        (ZeroVector3)
#define COLLISION_SIZE  (D3DXVECTOR3(90.0f, 90.0f, 90.0f))
#define SPEED           (150.0f)

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
    SetSize(COLLISION_SIZE);

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
    //CPlayer* pPlayer = nullptr;
    //pPlayer = (CPlayer*)GetTop(PRIORITY_CHARACTER);

    //if (pPlayer != nullptr)
    //{
    //    D3DXVECTOR3 RayDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
    //    BOOL bHit = FALSE;
    //    FLOAT fDistance = 0.0f;

    //    for (int nCount = 0; nCount < (int)GetModelInfo()->GetMesh()->GetNumFaces(); nCount++)
    //    {
    //        //������
    //        D3DXIntersect(
    //            GetModelInfo()->GetMesh(),
    //            &pPlayer->GetPos(),
    //            &RayDir,
    //            &bHit,
    //            nullptr,
    //            nullptr,
    //            nullptr,
    //            &fDistance,
    //            nullptr,
    //            nullptr);

    //        if (bHit && fDistance < 80.0f)
    //        {
    //            // ���n�̏���
    //            pPlayer->Landing(pPlayer->GetPos().y + fDistance);

    //            break;
    //        }
    //        else if (!bHit)
    //        {
    //            pPlayer->SetLanding(false);
    //        }
    //    }
    //}
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