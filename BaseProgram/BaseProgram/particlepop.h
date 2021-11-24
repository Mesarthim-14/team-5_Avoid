#ifndef _PARTICLEPOP_H_
#define _PARTICLEPOP_H_
//=====================================================================
//
//    �p�[�e�B�N������[particlepop.h]
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
class CParticlePop : public CParticleInfo
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticlePop();
    ~CParticlePop();

    static CParticlePop * Create(const D3DXVECTOR3 &pos);
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