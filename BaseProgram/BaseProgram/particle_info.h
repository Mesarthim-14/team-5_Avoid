#ifndef _PARTICLE_INFO_H_
#define _PARTICLE_INFO_H_
//=====================================================================
//
//    �p�[�e�B�N����b����[particle_info.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "billboard.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CParticleInfo : public CBillboard
{
public:
    //==================
    // �����o�֐�
    //==================
    CParticleInfo();
    virtual ~CParticleInfo();

    virtual HRESULT Init() = 0;
    virtual void Update() = 0;
    virtual void Uninit() = 0;
    virtual void Draw() = 0;

    // get�֐�
    inline D3DXVECTOR3 GetMove()const  { return m_move; }
    inline int GetLife()const          { return m_nLife; }
    // set�֐�
    inline void SetMove(const D3DXVECTOR3 &move)    { m_move = move; }
    inline void SetLife(const int &life)            { m_nLife = life; }
    inline void SetGravity(const bool &set)         { m_bGravitySet = set; }
    inline void SetLife(const bool &set)            { m_LifeSet = set; }

private:
    void Gravity();
    void Erase();
    //==================
    // �����o�ϐ�
    //==================
    D3DXVECTOR3 m_move;         // �p�[�e�B�N���̈ړ���
    int m_nLife;                // �p�[�e�B�N���̃��C�t
    bool m_bGravitySet;
    bool m_LifeSet;
};

#endif