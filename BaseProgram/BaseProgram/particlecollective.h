#ifndef _PARTICLECOLLECTIVE_H_
#define _PARTICLECOLLECTIVE_H_
//=====================================================================
//
//  �W���p�[�e�B�N������[particlefire.h]
//  Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "particle_info.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CParticleCollective : public CParticleInfo
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticleCollective();
    ~CParticleCollective();

    static CParticleCollective * Create(const D3DXVECTOR3 &pos);
    HRESULT Init(void);
    void Update(void);
    void Uninit(void);
    void Draw(void);

private:
    void SetParticle(void);     // �p�[�e�B�N�����o������
    //==================
    // �����o�ϐ�
    //==================
    float m_fAngle;             // �p�x
    float m_fSpeed;             // ���x
    int m_nLife;                // �̗�
};

#endif