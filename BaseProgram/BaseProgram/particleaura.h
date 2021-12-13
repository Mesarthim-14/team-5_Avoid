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

    static CParticleAura * Create(const D3DXVECTOR3 &pos);
    HRESULT Init();
    void Update();
    void Uninit();
    void Draw();

private:
    void SetParticle();        // �p�[�e�B�N�����o������
    void Move();               // �ړ�����
    void Rise();               // �㏸
    void Attack();
    //==================
    // �����o�ϐ�
    //==================
    static D3DXVECTOR3 m_pos;
    float m_fAngle;         // �p�x
    float m_fSpeed;         // ���x
    int m_nLife;            // �̗�
    int m_nEndCount;
    int m_nCautionCounter;
    bool m_bFollow;
    bool m_bEnd;
    bool m_bCaution;
};

#endif
