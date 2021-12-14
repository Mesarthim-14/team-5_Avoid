//=====================================================================
//
//	�p�[�e�B�N������[particle.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
// Author : toshiki
//=====================================================================
#include "particlenormal.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

D3DXVECTOR3 CParticleNormal::m_Rot = ZeroVector3;
//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define POS         (ZeroVector3)
#define SIZE        (D3DXVECTOR3(650.0f, 400.0f, 400.0f))
#define SPEED       (7.0f)
#define RANDOM      (3.14f)
#define LIFE        (200)
#define COLOR       (D3DXCOLOR(1.0f,1.0f,1.0f,m_fColor))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleNormal::CParticleNormal()
{
    m_fAngle = 0.0f;
    m_fSpeed = 0.0f;
    m_fColor = 0.5f;
    m_nCnt = 0;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleNormal::~CParticleNormal()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticleNormal * CParticleNormal::Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot)
{
    CParticleNormal * pParticle = new CParticleNormal;

    if (pParticle != nullptr)
    {
        pParticle->SetSceneInfo(D3DXVECTOR3(pos.x, pos.y - 100.0f, pos.z), SIZE);
        m_Rot = rot;
        pParticle->Init();
        return pParticle;
    }
    return nullptr;
}

//=====================================================================
// ����������
// Author : toshiki
//=====================================================================
HRESULT CParticleNormal::Init(void)
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleNormal::Update(void)
{
    CParticleInfo::Update();
    SetParticleColor();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleNormal::Uninit(void)
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleNormal::Draw(void)
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N�����o������
// Author : toshiki
//=====================================================================
void CParticleNormal::SetParticle(void)
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_SMOKE));
    // �X�s�[�h�̒l��ݒ�
    m_fSpeed = SPEED;
    // �p�[�e�B�N���̏o��p�x�̐ݒ�
    m_fAngle = CLibrary::Random(RANDOM);
    // �ړ������邽�߂̏���
    D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
    // �ړ�����ݒ�
    SetMove(move);
    // �p�[�e�B�N���������鎞�Ԃ̐ݒ�
    SetLife(LIFE);
}

//=====================================================================
// �p�[�e�B�N�������X�ɏ�������
// Author : toshiki
//=====================================================================
void CParticleNormal::SetParticleColor(void)
{
    m_nCnt++;
    // ���X�ɏ����Ă�������
    if (m_nCnt >= 5)
    {
        m_fColor -= 0.01f;
        m_nCnt = 0;
    }
    SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));
}
