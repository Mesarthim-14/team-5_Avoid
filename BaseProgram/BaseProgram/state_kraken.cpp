//=====================================================================
//
// クラーケンの状態管理クラス [state_kraken.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルード
//=====================================================================
#include "state_kraken.h"
#include "manager.h"
#include "game.h"
#include "library.h"
#include "skinmesh_model.h"
#include "animation_skinmesh.h"
#include "kraken.h"

//=====================================================================
// コンストラクタ
//=====================================================================
CKrakenState::CKrakenState()
{
}

//=====================================================================
// デストラクタ
//=====================================================================
CKrakenState::~CKrakenState()
{
}

//=====================================================================
// アニメーション設定
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
// クラーケンのポインタ
//=====================================================================
CKraken * CKrakenState::GetKrakenPtr() const
{
    return CManager::GetInstance()->GetGame()->GetKraken();
}
