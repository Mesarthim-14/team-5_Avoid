#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//=======================================================================================
// 
// 2D�|���S���N���X���� [scene2d.h]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "scene_base.h"

//=======================================================================================
// �V�[��2D�N���X��`
//=======================================================================================
class CScene2D : public CSceneBase
{
public:
    CScene2D(PRIORITY Priority = PRIORITY_0);   // �R���X�g���N�^
    ~CScene2D();                                // �f�X�g���N�^

    static CScene2D* Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);                           // �C���X�^���X����
    static CScene2D* Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const float &fFadeNum);    // �C���X�^���X����(�t�F�[�h�L��)

    HRESULT Init(); // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����
    void Draw();    // �`�揈��

protected:
    void SetVertexPos();                                                                // ���_�̐ݒ�
    void InitAnimation(const int &nPatternNum, const int &nSpeed, const int &nLoop);    // �A�j���[�V������񏉊���
    void InitScroll(const int &nSpeed, const float &fDivision);                         // �摜�X�N���[���̐ݒ�
    void ScaleUp(const float &fScaleUp);                                                // �g��֐�
    void FlashPolygon(const int &nFlashFlame);                                          // �|���S���̓_��

    // Set�֐�
    void SetColor(const D3DXCOLOR &col) override;                               // �F�̐ݒ�
    void SetRotation(float rotasion);                                           // ��]�̐ݒ�
    void SetScale(const float &fScale);                                         // �g��̒l�ݒ�
    inline void SetSubFlashNum(const float &fSubNum) { m_fSubNum = fSubNum; }   // �_�ł̒l�ݒ�

    // Get�֐�
    inline float GetScale()const { return m_fScaleNum; }    // �g��̒l���

private:
    // private�֐�
    void CreateVertex();                // ���_�̐���
    void UpdateAnimation();             // �A�j���[�V�����̍X�V
    void UpdateScroll();                // �摜�X�N���[���̍X�V
    void FadeOut(const float &fSpeed);  // �t�F�[�h�A�E�g

    // �����o�ϐ�
    int m_nFlashFlame;      // �_���p�̃J�E���^�[
    float m_fRotasion;      // ��]�p�ϐ�
    float m_fScaleNum;      // �g��p�ϐ�
    float m_fSubFlashNum;   // �|���S���̓_���p
    float m_fSubNum;        // �|���S���̓_���p
    float m_fFadeSpeedNum;  // �t�F�[�h�̃X�s�[�h
    bool m_bDisappearFlag;  // �_�ŗp�̃t���O
    bool m_bFadeOut;        // �t�F�[�h�̃t���O
};

#endif // !_SCENE2D_H_