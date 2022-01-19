//=====================================================================
//
// �{�X�̒e�̌x������ [caution_boss_bullet_ui.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "caution_boss_bullet_ui.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "keyboard.h"
#include "camera.h"
#include "library.h"
#include "player.h"

//=====================================================================
// �}�N����`
//=====================================================================
#define POS             (D3DXVECTOR3(SCREEN_WIDTH / 2 ,SCREEN_HEIGHT / 2 ,0.0f))    // ���W
#define SIZE            (D3DXVECTOR3(150.0f, 150.0f, 0.0f))                         // �T�C�Y
#define DISTANCE        (200.0f)                                                    // ����
#define BLINK_DISTANCE  (25000.0f)                                                  // �_�ŋ���
#define VIEWING_ANGLE   (0.5f)                                                      // ����p

//=====================================================================
// �R���X�g���N�^
//=====================================================================
CCautionBossBulletUi::CCautionBossBulletUi(PRIORITY priority) : CScene2D(priority)
{
    m_fAngle = 0.0f;
    m_bDraw = true;
    m_bBlinking = false;
}

//=====================================================================
// �f�X�g���N�^
//=====================================================================
CCautionBossBulletUi::~CCautionBossBulletUi()
{

}

//=====================================================================
// ��������
//=====================================================================
CCautionBossBulletUi * CCautionBossBulletUi::Create()
{
    CCautionBossBulletUi * pCaution = new CCautionBossBulletUi(PRIORITY_UI);

    if (pCaution)
    {
        pCaution->SetSceneInfo(POS, SIZE);
        pCaution->Init();

        return pCaution;
    }

    return nullptr;
}

//=====================================================================
// ����������
//=====================================================================
HRESULT CCautionBossBulletUi::Init()
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_WARNING));

    CScene2D::Init();

    return S_OK;
}

//=====================================================================
// �I������
//=====================================================================
void CCautionBossBulletUi::Uninit()
{
    CScene2D::Uninit();
}

//=====================================================================
// �X�V����
//=====================================================================
void CCautionBossBulletUi::Update()
{
    Rotate();
    CalDistance();

    CScene2D::Update();
}

//=====================================================================
// �`�揈��
//=====================================================================
void CCautionBossBulletUi::Draw()
{
    if (m_bDraw)
    {
        CScene2D::Draw();
    }
}

//=====================================================================
// ��]
//=====================================================================
void CCautionBossBulletUi::Rotate()
{
    // �v���C���[�̍��W�擾
    D3DXVECTOR3 PlayerPos = CManager::GetInstance()->GetPlayer()->GetPos();
    float fAngle = CLibrary::CalAngleXZ(PlayerPos, m_BulletPos);
    CLibrary::RotFix(fAngle);

    float fRot = D3DXToRadian( CManager::GetInstance()->GetCamera()->GetRot().y );
    CLibrary::RotFix(fRot);

    D3DXVECTOR3 center = HALF_SCREEN_POS;
    D3DXVECTOR3 pos =
        D3DXVECTOR3(
            center.x + cosf(fRot + D3DXToRadian(-90.0f) + fAngle)*DISTANCE,
            center.y + sinf(fRot + D3DXToRadian(-90.0f) + fAngle)*DISTANCE,
            0.0f);

    // �ʒu�Ɗp�x�̐ݒ�
    SetPos(pos);
    SetRotation(fRot + fAngle);

    // �p�x�̔���
    JudgeAngle(fRot, fAngle);
}

//=====================================================================
// �����̌v�Z
//=====================================================================
void CCautionBossBulletUi::CalDistance()
{
    if (m_bDraw)
    {
        float fDistance = CLibrary::CalDistance(m_BulletPos, CManager::GetInstance()->GetPlayer()->GetPos());
        
        // �v���C���[�ƒe�̋����𑪂�
        if (fDistance < BLINK_DISTANCE)
        {
            // �_��
            Blinking();
        }
        else
        {
            if (m_bBlinking)
            {
                SetColor(WhiteColor);
            }
        }
    }
}

//=====================================================================
// ����p
//=====================================================================
void CCautionBossBulletUi::JudgeAngle(const float& fCamera, const float& fAngle)
{
    if (-fCamera <= fAngle + VIEWING_ANGLE
        && -fCamera >= fAngle - VIEWING_ANGLE)
    {
        m_bDraw = true;
    }
    else
    {
        m_bDraw = true;
    }
}

//=====================================================================
// �_��
//=====================================================================
void CCautionBossBulletUi::Blinking()
{
    // �_��
    FlashPolygon(0.2f);
    if (!m_bBlinking)
    {
        m_bBlinking = true;
    }
}