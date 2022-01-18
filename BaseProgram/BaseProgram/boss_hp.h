#ifndef _BOSS_HP_H_
#define _BOSS_HP_H_
//=============================================================================
//
// �{�X��HP�N���X [boss_hp.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene.h"

//=========================================================================
// �O���錾
//=========================================================================
class CBossHpBack;
class CBossHpBar;

//=========================================================================
// �N���X��`
//=========================================================================
class CBossHp : CScene
{
public:
    CBossHp(PRIORITY);      // �R���X�g���N�^
    ~CBossHp();             // �f�X�g���N�^

    static CBossHp *Create(const int& nLife);   // �C���X�^���X����
    HRESULT Init() { return S_OK; }             // ����������
    HRESULT Init(const int& nLife);             // ����������

    void Uninit();                              // ����������
    void Update();                              // �X�V����
    void Draw();                                // �`��
    void SubHp();                               // HP�̌��Z

    inline void SetDraw(const bool& bDraw) { m_bDraw = bDraw; }

private:
    CBossHpBack* m_pBack;   // �w�i
    CBossHpBar* m_pBar;     // �o�[
    bool m_bDraw;
};

#endif