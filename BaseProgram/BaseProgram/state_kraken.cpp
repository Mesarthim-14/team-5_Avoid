//=====================================================================
//
// �N���[�P���̏�ԊǗ��N���X [state_kraken.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h
//=====================================================================
#include "state_kraken.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "kraken.h"

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CKrakenState::CKrakenState()
{
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CKrakenState::~CKrakenState()
{
}

//=====================================================================
// �A�j���[�V�����ݒ�
//=====================================================================
void CKrakenState::SetAnimation(const UINT &animID, const FLOAT &time)
{
    CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
    if (!pKraken)
    {
        return;
    }
    CSkinmeshModel* pSkinMeshModel = pKraken->GetSkinMesh();
    if (!pSkinMeshModel)
    {
        return;
    }

    pSkinMeshModel->GetHLcontroller()->ChangeAnimation(animID);
    pSkinMeshModel->GetHLcontroller()->SetLoopTime(animID, time);
}

//=====================================================================
// �N���[�P���̃|�C���^
//=====================================================================
CKraken * CKrakenState::GetKrakenPtr() const
{
    return CManager::GetInstance()->GetGame()->GetKraken();
}
