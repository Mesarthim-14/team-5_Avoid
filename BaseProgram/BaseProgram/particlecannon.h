#ifndef _PARTICLECANNON_H_
#define _PARTICLECANNON_H_
//=====================================================================
//
//	�p�[�e�B�N������[particlenormal.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "particle_info.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CParticleCannon : public CParticleInfo
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticleCannon();
    ~CParticleCannon();

    static CParticleCannon * Create(const D3DXVECTOR3 &pos);
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