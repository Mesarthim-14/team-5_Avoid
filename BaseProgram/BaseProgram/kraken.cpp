//=============================================================================
//
// �N���[�P���N���X [kraken.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "kraken.h"
#include "animation_skinmesh.h"
#include "skinmesh_model.h"
#include "boss_bullet.h"
#include "collisionModel_OBB.h"
#include "state.h"
#include "state_kraken_normal.h"
#include "player.h"
#include "manager.h"
#include "library.h"
#include "kraken_tentacles.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define POS                 (D3DXVECTOR3(3115.0f, 0.0f, -3267.0f))
#define SIZE                (D3DXVECTOR3(27000.0f, 60000.0f, 27000.0f))
#define BULLET_INTERVAL     (500)                                      // ���ܔ��ˊԊu
#define MAX_LIFE            (5)                                        // ���C�t
#define MAX_TENTACLES       (8)                                        // �G��̐�
#define TENTACLES_DISTANCE  (30000.0f)                                 // �G��Ƃ̋���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKraken::CKraken(PRIORITY Priority) : CEnemy(Priority)
{
    m_pSkinmeshModel = nullptr;
    m_nBulletCount = 0;
    m_pCollision = nullptr;
    m_nLife = MAX_LIFE;
    m_bDead = false;
    m_pCurrentState = nullptr;
    m_pNextState = nullptr;
    m_apTentacles.clear();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKraken::~CKraken()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CKraken * CKraken::Create()
{
    CKraken *pKraken = new CKraken;
    if (pKraken)
    {
        pKraken->Init();
        return pKraken;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CKraken::Init()
{
    // ���f�����ݒ�
    SetCharacterInfo(POS, ZeroVector3);
    SetGravityFlag(false);
    CEnemy::Init();

    // ���f���̐���
    CreateModel();

    if (!m_pCollision)
    {
        // �C���X�^���X����
        m_pCollision = CCollisionModelOBB::Create(POS, SIZE, ZeroVector3);
    }

    if (!m_pCurrentState)
    {
        m_pCurrentState = CKrakenStateNormal::Create();
    }

    // �G��̐���
    CreateTentacles();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CKraken::Uninit()
{
    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->Uninit();
        m_pSkinmeshModel = nullptr;
    }
    if (m_pCollision)
    {
        m_pCollision->Uninit();
        m_pCollision = nullptr;
    }
    for (auto& pTantacles : m_apTentacles)
    {
        pTantacles->Uninit();
        pTantacles = nullptr;
    }
    m_apTentacles.clear();

    CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CKraken::Update()
{
    CEnemy::Update();
    Attack();
    LookAtPlayer();

    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 rot = GetRot();
    if (m_pCollision)
    {
        m_pCollision->SetInfo(pos, m_pCollision->GetOBB().info.size, rot);
    }

    if (m_pSkinmeshModel)
    {
        m_pSkinmeshModel->SetPos(pos);
        m_pSkinmeshModel->SetRot(rot);
    }

    // �̗͂������Ȃ�����
    if (m_nLife <= 0)
    {
        m_bDead = true;
    }
}

//=============================================================================
// ��Ԃ̕ύX
//=============================================================================
void CKraken::ChangeState(CState* pState)
{
    if (!m_pNextState)
    {
        m_pNextState = pState;
    }
    else
    {
        delete m_pNextState;
        m_pNextState = nullptr;
        m_pNextState = pState;
    }
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CKraken::CreateModel()
{
    m_pSkinmeshModel = CSkinmeshModel::Create(GetPos(), GetRot(), CSkinmeshModel::MODEL_ENEMY_KRAKEN_HEAD);
    if (m_pSkinmeshModel)
    {
        CTexture* pTexture = GET_TEXTURE_PTR;
        m_pSkinmeshModel->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_KRAKEN));
        m_pSkinmeshModel->IsDraw(true);

        // ���f���̏�񕪂���Ȃ�
        m_pSkinmeshModel->GetHLcontroller()->ChangeAnimation(0);
        m_pSkinmeshModel->GetHLcontroller()->SetLoopTime(0, 60);
        m_pSkinmeshModel->GetHLcontroller()->SetShiftTime(0, 60);
    }
}

//=============================================================================
// ��Ԃ̍X�V
//=============================================================================
void CKraken::UpdateState()
{
    if (m_pNextState)
    {
        delete m_pCurrentState;
        m_pCurrentState = nullptr;

        m_pCurrentState = m_pNextState;
        m_pNextState = nullptr;
    }

    if (m_pCurrentState)
    {
        // �X�V����
        m_pCurrentState->Update();
    }
}

//=============================================================================
// �U��
//=============================================================================
void CKraken::Attack()
{
    UpdateState();
}

//=============================================================================
// �G��̐���
//=============================================================================
void CKraken::CreateTentacles()
{
    D3DXVECTOR3 pos = GetPos();
    D3DXVECTOR3 rot = GetRot();
    float fAngle = 360.0f / MAX_TENTACLES;

    for (int nCount = 0; nCount < MAX_TENTACLES; nCount++)
    {
        m_apTentacles.push_back(CKrakenTentacles::Create(D3DXVECTOR3(
            pos.x + sinf(rot.y+D3DXToRadian(fAngle * nCount))*TENTACLES_DISTANCE,
            pos.y,
            pos.z + cosf(rot.y + D3DXToRadian(fAngle * nCount))*TENTACLES_DISTANCE),
            D3DXVECTOR3(rot.x, CLibrary::Random(180.0f), rot.z)));
    }
}
