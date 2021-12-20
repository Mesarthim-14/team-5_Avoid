//=====================================================================
//
//    �p�[�e�B�N������[particlepop.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
// Author : toshiki
//=====================================================================
#include "particle_water.h"
#include "manager.h"
#include "renderer.h"
#include "library.h"
#include "texture.h"
#include "resource_manager.h"

float CParticleWater::m_fSize = 0.0f;
//=====================================================================
// �}�N����`
// Author : toshiki
//=====================================================================
#define SIZE		(D3DXVECTOR3(m_fSize, m_fSize, m_fSize))
#define ANGLE		(70.0f)
#define SPEED		(80.0f)
#define RANDOM		(3.14f)
#define LIFE		(90)
#define COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))

//=====================================================================
// �R���X�g���N�^
// Author : toshiki
//=====================================================================
CParticleWater::CParticleWater()
{
    m_fAngle = 0.0f;
    m_nLife = 0;
}

//=====================================================================
// �f�X�g���N�^
// Author : toshiki
//=====================================================================
CParticleWater::~CParticleWater()
{

}

//=====================================================================
// ��������
// Author : toshiki
//=====================================================================
CParticleWater * CParticleWater::Create(const D3DXVECTOR3 &pos)
{
    CParticleWater * pParticleWater = new CParticleWater;

    if (pParticleWater)
    {
        m_fSize = CLibrary::Random(50.0f, 100.0f);
        pParticleWater->SetSceneInfo(pos, SIZE);

        pParticleWater->Init();
        return pParticleWater;
    }
    return nullptr;
}

//=====================================================================
// ����������
// Author : toshiki
//=====================================================================
HRESULT CParticleWater::Init()
{
    CParticleInfo::Init();
    SetParticle();
    return S_OK;
}

//=====================================================================
// �X�V����
// Author : toshiki
//=====================================================================
void CParticleWater::Update()
{
    CParticleInfo::Update();
}

//=====================================================================
// �I������
// Author : toshiki
//=====================================================================
void CParticleWater::Uninit()
{
    CParticleInfo::Uninit();
}

//=====================================================================
// �`�揈��
// Author : toshiki
//=====================================================================
void CParticleWater::Draw()
{
    CParticleInfo::Draw();
}

//=====================================================================
// �p�[�e�B�N���̐ݒ�
// Author : toshiki
//=====================================================================
void CParticleWater::SetParticle()
{
    // �e�N�X�`���̐ݒ�
    CTexture *pTexture = GET_TEXTURE_PTR;
    BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_WATER));
    // �X�s�[�h�̒l��ݒ�
    m_fSpeed = SPEED;
    // �p�[�e�B�N���̏o��p�x�̐ݒ�
    m_fAngle = CLibrary::Random(RANDOM);
    // �d�͂�����
    CParticleInfo::SetGravity(true);
    // �ړ������邽�߂̏���
    D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fAngle) * m_fSpeed, ANGLE, cosf(m_fAngle) * m_fSpeed);
    // �ړ�����ݒ�
    SetMove(move);
    // �F�̐ݒ�
    SetColor(COLOR);
    // �p�[�e�B�N���������鎞�Ԃ̐ݒ�
    SetLife(LIFE);
}