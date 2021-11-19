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

//=============================================================================
// �}�N����`
//=============================================================================
#define SPEED	(100.0f)
#define POS_FIX (1000.0f)
#define POS_FIX_Y (700.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCannonBullet::CCannonBullet(PRIORITY Priority) : CModel(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCannonBullet::~CCannonBullet()
{
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

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CCannonBullet::Update()
{
	CModel::Update();
}

//=============================================================================
// �e�̏��
//=============================================================================
void CCannonBullet::SetBulletInfo(D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
	pos = D3DXVECTOR3(
		pos.x + (sinf(rot.y)*POS_FIX),
		pos.y + POS_FIX_Y,
		pos.z + (cos(rot.y)*POS_FIX));

	// Follow
	// �{�X�̃|�C���^
	CKraken *pKraken = CManager::GetInstance()->GetGame()->GetKraken();
	D3DXVECTOR3 Ppos = pKraken->GetPos();	// ���W�擾
	SetMove(CLibrary::FollowMoveXZ(pos, Ppos, SPEED));
}