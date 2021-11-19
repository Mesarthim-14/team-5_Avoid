//=============================================================================
//
// �T���N���X [wimp_enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "wimp_enemy.h"
#include "manager.h"
#include "player.h"
#include "library.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PERCEPTION_DISTANCE (6000.0f)    // ���m�ł��鋗��
#define FOLLOW_TIME         (50)         // �d�͂�������Ȃ�����
#define PLAYER_ADD_HEIGHT   (500.0f)       // �v���C���[��K���ɗʑ���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWimpEnemy::CWimpEnemy(PRIORITY Priority) : CEnemy(Priority)
{
    isRush = false;
    m_nRushCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWimpEnemy::~CWimpEnemy()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWimpEnemy::Init()
{
    CEnemy::Init();
    SetGravityFlag(false);

    return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CWimpEnemy::Update()
{
    CEnemy::Update();
    if (isRush)
    {
        // �d�͂̐؂�ւ�
        GravitySwitch();
    }
}


//=============================================================================
// �ːi
//=============================================================================
void CWimpEnemy::Rush()
{
    // �ːi
    if (Follow())
    {
        isRush = true;
    }
}

//=============================================================================
// �d�͂�������
//=============================================================================
void CWimpEnemy::GravitySwitch()
{
    m_nRushCount++;
    if (m_nRushCount >= FOLLOW_TIME)
    {
        m_nRushCount = 0;
        SetGravityFlag(true);
    }
}

//=============================================================================
// �Ǐ]
//=============================================================================
bool CWimpEnemy::Follow()
{
    // �������擾
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        D3DXVECTOR3 Ppos = pPlayer->GetPos();
        Ppos.y += PLAYER_ADD_HEIGHT;
        D3DXVECTOR3 Epos = GetPos();
        float fSpeed = GetSpeed();

        // 2�_�Ԃ̃x�N�g�������߂�i�I�_[�ڕW�n�_] - �n�_[���g�̈ʒu]�j
        D3DXVECTOR3 Vector = Ppos - Epos;
        Vector = *D3DXVec3Normalize(&Vector, &Vector);
        Vector *= fSpeed;
        //���@���擾����
        float fAngle = atan2f((Epos.x - Ppos.x), (Epos.z - Ppos.z));    // �p�x
        float fDistance = CLibrary::CalDistance(Ppos, Epos);
        if (fDistance <= PERCEPTION_DISTANCE)
        {
            // �����ȓG�̈ړ�
            D3DXVECTOR3 FollowMove = D3DXVECTOR3(
                (sinf(fAngle)*-fSpeed),
                0.0f, cosf(fAngle)*-fSpeed);

            // �ړ��ʂ̐ݒ�
            SetMove(Vector);

            return true;
        }
    }

    return false;
}
