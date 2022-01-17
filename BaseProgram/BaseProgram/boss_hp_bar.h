#ifndef _BOSS_HP_BAR_H_
#define _BOSS_HP_BAR_H_
//=========================================================
//
// �{�X�̗̓o�[�N���X�w�b�_�[    [boss_hp_bar.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// �C���N���[�h
//=========================================================
#include "scene_base.h"

//=========================================================
// �Q�[�W�o�[�N���X
//=========================================================
class CBossHpBar : public CSceneBase
{
public:
    CBossHpBar(PRIORITY Priority);  // �R���X�g���N�^
    ~CBossHpBar();                  // �f�X�g���N�^

    static CBossHpBar* Create(const int& nLife);    // �C���X�^���X����
   HRESULT Init();                                  // ����������
   void Uninit();                                   // �I������
   void Update();                                   // �X�V����
   void Draw();                                     // �`�揈��
   void SetGageVertex();                            // �Q�[�W�̒��_�ݒ�
   void SubHp(const int& nNum);                     // HP�̌��Z
   void Render();                                   // �`��

    // Get�֐�
    inline int GetGage()const       { return m_nGage; }                        // �̗͂̏��
    inline int GetMaxGage()const    { return m_nMaxGage; }                    // �̗͂̍ő吔���

private:
    int m_nMaxGage;     // �̗͂̍ő�l
    int m_nGage;        // �̗�

    void CreateVertex(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);    // ���_�̐���
    void InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop) {}  // �A�j���[�V������񏉊���
    void UpdateAnimation() {}                                                           // �A�j���[�V�����X�V


};
#endif