//=====================================================================
//
// �G���G�̍U���x�� [caution_wimp_attack.cpp]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "caution_wimp_attack.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "keyboard.h"
#include "camera.h"
#include "library.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define POS             (D3DXVECTOR3(SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 ,0.0f))    // ���W
#define SIZE            (D3DXVECTOR3(800.0f, 800.0f, 0.0f))                         // �T�C�Y
#define FIX_POS_Y       (400.0f)                                                    // Y���W�̏C���l

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCautionWimpAttack::CCautionWimpAttack(PRIORITY priority) : CBillboard(priority)
{
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCautionWimpAttack::~CCautionWimpAttack()
{

}

//=====================================================================
// ��������
//=====================================================================
CCautionWimpAttack * CCautionWimpAttack::Create(const D3DXVECTOR3& pos)
{
    CCautionWimpAttack * pCaution = new CCautionWimpAttack(PRIORITY_EFFECT);

    if (pCaution)
    {
        pCaution->SetSceneInfo(pCaution->FixPos(pos), SIZE);
        pCaution->Init();

        return pCaution;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
HRESULT CCautionWimpAttack::Init()
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_WARNING2));

    CBillboard::Init();

    return S_OK;
}

//=====================================================================
// �I������
//=====================================================================
void CCautionWimpAttack::Uninit()
{
    CBillboard::Uninit();
}

//=====================================================================
// �X�V����
//=====================================================================
void CCautionWimpAttack::Update()
{
    CBillboard::Update();
}

//=====================================================================
// �`�揈��
//=====================================================================
void CCautionWimpAttack::Draw()
{
    CBillboard::Draw();
}

//=====================================================================
// ���W�C��
//=====================================================================
D3DXVECTOR3 CCautionWimpAttack::FixPos(const D3DXVECTOR3& pos)
{
    return D3DXVECTOR3(pos.x, pos.y + FIX_POS_Y, pos.z);
}