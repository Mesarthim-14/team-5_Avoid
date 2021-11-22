#ifndef _PARTICLEAURA_H_
#define _PARTICLEAURA_H_
//=====================================================================
//
//    �p�[�e�B�N������[particleaura.h]
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
class CParticleAura : public CParticleInfo
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticleAura();
    ~CParticleAura();

    static CParticleAura * Create(D3DXVECTOR3 pos);
    HRESULT Init();
    void Update();
    void Uninit();
    void Draw();

private:
    void SetParticle();        // �p�[�e�B�N�����o������
    //==================
    // �����o�ϐ�
    //==================
    float m_fAngle;         // �p�x
    float m_fSpeed;         // ���x
    int m_nLife;            // �̗�
    static float m_fSize;   
};

#endif