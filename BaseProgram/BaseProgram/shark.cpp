//=============================================================================
//
// �T���N���X [shark.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "shark.h"
#include "shark_model.h"
#include "manager.h"
#include "pause.h"
#include "library.h"
#include "player.h"
#include "kraken.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ATTACK_INTER    (150)                                   // �U���Ԋu
#define ATTACK_STR      (20)                                    // �U����
#define ATTACK_POWER    (2.0f)                                  // ������΂���
#define SPEED           (500.0f)                                // �X�s�[�h
#define POS             (D3DXVECTOR3(-3500.0f, -200.0f, 0.0f))  // ���W
#define COLLISION_SIZE  (D3DXVECTOR3(m_fCollisionSize, m_fCollisionSize, m_fCollisionSize))

const float CShark::m_fCollisionSize = 500.0f;
constexpr float DISTANCE = -20000.0f;
constexpr float DISTANCE_Y = 4000.0f;
constexpr float PLAYER_ADD_HEIGHT = 500.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShark::CShark(PRIORITY Priority) : CWimpEnemy(Priority)
{
    m_pSharkModel = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShark::~CShark()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CShark * CShark::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    // �������m��
    CShark *pShark = new CShark;
    if (pShark)
    {
        // ����������
        pShark->Init(pos, rot);
        return pShark;
    }

    return nullptr;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShark::Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    float frotY = 0.0f;
    CPlayer* pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        frotY = CLibrary::LookTarget(pos, pPlayer->GetPos());
    }
    D3DXVECTOR3 Prot = D3DXVECTOR3(rot.x, frotY, rot.z);

    // ��C�̒��S���Ⴄ�̂ŁA���W�����炷
    D3DXVECTOR3 Ppos = D3DXVECTOR3(
        pos.x + (sinf(rot.y)*DISTANCE),
        pos.y + DISTANCE_Y,
        pos.z + (cos(rot.y)*DISTANCE));

    CWimpEnemy::Init(Ppos, COLLISION_SIZE, Prot);

    SetAttackInfo(ATTACK_INTER, ATTACK_STR, ATTACK_POWER);
    SetCharacterInfo(Ppos, Prot);
    SetSpeed(SPEED);

    // ���f������
    CreateModel();

    // �Ǐ]�U��
    Rush();

    return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShark::Uninit()
{
    // ���f���X�V����
    if (m_pSharkModel)
    {
        m_pSharkModel->Uninit();
    }
    CWimpEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CShark::Update()
{
    bool bPause = CManager::GetInstance()->GetActivePause();

    if (!bPause)
    {
        // ���f���X�V����
        if (m_pSharkModel)
        {
            m_pSharkModel->SetPos(GetPos());
            m_pSharkModel->SetRot(GetRot());
        }

        CWimpEnemy::Update();
    }
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CShark::CreateModel()
{
    // ���f������
    if (!m_pSharkModel)
    {
        m_pSharkModel = CSharkModel::Create(GetPos());
    }
}

//=============================================================================
// �U���֐�
//=============================================================================
void CShark::Attack()
{
    // �Ǐ]�U��
//    Rush();
}