//=====================================================================
//
// ��C��ԊǗ��N���X [state_player_cannon.h]
//    Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "state_player_cannon.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "state_player_normal.h"
#include "gimmick_factory.h"
#include "cannon_manager.h"
#include "cannon.h"
#include "kraken.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define DISTANCE    (10.0f)     // ����
#define SPEED       (15.0f)     // ���x
#define POS_FIX     (-800.0f)   // ���W�̏C��

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CPlayerStateCannon::CPlayerStateCannon()
{

}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CPlayerStateCannon::~CPlayerStateCannon()
{

}

//=====================================================================
// �C���X�^���X����
//=====================================================================
CPlayerStateCannon * CPlayerStateCannon::Create()
{
    // �������m��
    CPlayerStateCannon *pStateJump = new CPlayerStateCannon;
    if (pStateJump)
    {
        // ����������
        pStateJump->Init();
        return pStateJump;
    }
    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
void CPlayerStateCannon::Init()
{
    // �������m��
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }
    pPlayer->SetCollision(false);
    // �A�j���[�V�����ݒ�
    SetAnimation(UINT((CPlayer::ACTION_MAX - 1) - CPlayer::ACTION_IDOL), 60);
    TrackingCannon(pPlayer);

    // ��Ԃ̐ݒ�
    pPlayer->SetState(CPlayer::CANNON);
}

//=====================================================================
// �X�V����
//=====================================================================
void CPlayerStateCannon::Update()
{
    // �������m��
    CPlayer *pPlayer = CManager::GetInstance()->GetPlayer();
    if (!pPlayer)
    {
        return;
    }

}

//=====================================================================
// ��C�̌��֒Ǐ]
//=====================================================================
void CPlayerStateCannon::TrackingCannon(CPlayer* &pPlayer)
{
    CCannon* pCannon = CManager::GetInstance()->GetGame()->GetGimmickFactory()->GetCannonManager()->GetCurrentCannon();
    D3DXVECTOR3 CannonPos = pCannon->GetPos();
    D3DXVECTOR3 CannonRot = pCannon->GetRot();
    float fDistance = DISTANCE;

    D3DXVECTOR3 pos = D3DXVECTOR3(
        CannonPos.x + (sinf(CannonRot.y))*POS_FIX,
        pPlayer->GetPos().y,
        CannonPos.z + (cos(CannonRot.y))*POS_FIX);

    pPlayer->SetPos(pos);
    pPlayer->SetMove(ZeroVector3);

    CKraken* pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    D3DXVECTOR3 rot = pPlayer->GetRot();

    // �p�x�ݒ�
    if (pKraken)
    {
        rot.y = CLibrary::LookTarget(pos, pKraken->GetPos());
    }
    CLibrary::RotFix(rot.y);
    pPlayer->SetRotDest(rot);
}