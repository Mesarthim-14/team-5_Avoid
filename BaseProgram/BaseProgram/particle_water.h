#ifndef _PARTICLE_WATER_H_
#define _PARTICLE_WATER_H_
//=====================================================================
//
//    ���ɗ��������̃G�t�F�N�g����[particlepop.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "particle_info.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CParticleWater : public CParticleInfo
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticleWater();
    ~CParticleWater();

    static CParticleWater * Create(const D3DXVECTOR3 &pos);
    HRESULT Init();
    void Update();
    void Uninit();
    void Draw();

private:
    void SetParticle();        // �p�[�e�B�N�����o������
    //==================
    // �����o�ϐ�
    //==================
    float m_fAngle;                // �p�x
    float m_fSpeed;                // ���x
    int m_nLife;                   // �̗�
    static float m_fSize;
};

#endif