//=====================================================================
//
//    �p�[�e�B�N����b����[particle_info.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
// Author : toshiki
//=====================================================================
#include "particle_info.h"
#include "scene3D.h"
#include "manager.h"
#include "player.h"
#include "library.h"

#define MOVE    (D3DXVECTOR3(0.0f,0.0f,0.0f))
//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleInfo::CParticleInfo()
{
    m_move = ZeroVector3;
    m_nLife = 0;
    m_bGravitySet = false;
    m_bGravityMiniSet = false;
    m_LifeSet = true;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleInfo::~CParticleInfo()
{

}

//=====================================================================
// ����������
// Author : toshiki
//=====================================================================
HRESULT CParticleInfo::Init()
{
    CBillboard::Init();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleInfo::Update()
{
    // ���W�����擾
    D3DXVECTOR3 pos = GetPos();
    // �̗͏����擾
    m_nLife = GetLife();
    // �ړ��ʂ����Z
    pos += m_move;
    // �d�͂����邩���Ȃ����̔���
    if (m_bGravitySet)
    {
        Gravity();
    }
    else if (m_bGravityMiniSet)
    {
        Gravitymini();
    }

    if (m_LifeSet)
    {
        //    ���C�t���O�ɂȂ��������
        m_nLife--;
        if (m_nLife <= 0)
        {
            Erase();
        }
    }
    // ���Z��������ݒ�
    SetPos(pos);
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleInfo::Uninit()
{
    CBillboard::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleInfo::Draw()
{
    CBillboard::Draw();
}

//=====================================================================
// �d��
// Author : toshiki
//=====================================================================
void CParticleInfo::Gravity()
{
    // ���W�����擾
    D3DXVECTOR3 pos = GetPos();
    m_move.y -= 2.0f;
    // �ړ��ʂ����Z
    pos.y += m_move.y;
}

//=====================================================================
// �d��
// Author : toshiki
//=====================================================================
void CParticleInfo::Gravitymini()
{
    // ���W�����擾
    D3DXVECTOR3 pos = GetPos();
    m_move.y += 0.09f;
    // �ړ��ʂ����Z
    pos.y += m_move.y;
}

//=====================================================================
// �w���������
// Author : toshiki
//=====================================================================
void CParticleInfo::Erase()
{
    Uninit();
}

//=============================================================================
// �v���C���[��T������
//=============================================================================
bool CParticleInfo::Search()
{
    // �������擾
    D3DXVECTOR3 pos = CManager::GetInstance()->GetPlayer()->GetPos();

    float fDistance = CLibrary::CalDistance(pos, GetPos());
    if (fDistance <= 23000.0f)
    {
        return true;
    }

    return false;
}

//=====================================================================
// �p�[�e�B�N���̒Ǐ]
// Author : toshiki
//=====================================================================
bool CParticleInfo::Follow()
{
    // �������擾
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (pPlayer)
    {
        D3DXVECTOR3 Ppos = pPlayer->GetPos();
        Ppos.y += 500.0f;
        float fSpeed = 50.0f;
        // 2�_�Ԃ̃x�N�g�������߂�i�I�_[�ڕW�n�_] - �n�_[���g�̈ʒu]�j
        D3DXVECTOR3 Vector = Ppos - GetPos();
        Vector = *D3DXVec3Normalize(&Vector, &Vector);
        Vector *= fSpeed;

        // �ړ��ʂ̐ݒ�
        SetMove(Vector);
        return true;
    }

    return false;
}