#ifndef _PARTICLESHRINK_HEEL_H_
#define _PARTICLESHRINK_HEEL_H_
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
class CParticleHeel : public CParticleInfo
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticleHeel();
    ~CParticleHeel();

    static CParticleHeel * Create(const D3DXVECTOR3 &pos);
    HRESULT Init(void);
    void Update(void);
    void Uninit(void);
    void Draw(void);

private:
    void SetParticle(void);		// �p�[�e�B�N�����o������
    //==================
    // �����o�ϐ�
    //==================
    static float m_fAngleX;     // �p�x
    static float m_fAngleZ;     // �p�x
    static float m_fSize;       // �傫��
    float m_fSpeed;             // ���x
    int m_nLife;                // �̗�

    D3DXVECTOR3 ShrinkPos;
};

#endif