#ifndef _COLLISION_MODEL_CAPSULE_H_
#define _COLLISION_MODEL_CAPSULE_H_
//=============================================================================
//
// �����蔻�胂�f��(�J�v�Z��)�̏��� [collisionModel_Capsule.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCollisionModelCapsule :public CScene
{
public:
    // �J�v�Z�����f������邽�߂Ɏg�����b�V���ƃo�b�t�@�̗񋓌^
    enum TYPE
    {
        TYPE_NONE = -1,
        TYPE_CYLINDER,  // �~��
        TYPE_SPHERE_1,  // ���̂P
        TYPE_SPHERE_2,  // ���̂Q
        TYPE_MAX
    };

    // �~�����
    struct CYLINDER
    {
        D3DXVECTOR3 pos;    // �ʒu
        float radius;       // ���a
        float length;       // ����
        D3DXVECTOR3 rot;    // �p�x
    };
    
    // ���̏��(�Q��)
    struct SPHERE
    {
        D3DXVECTOR3 pos;    // �ʒu
        float radius;       // ���a
        D3DXVECTOR3 rot;    // �p�x
    };
    
    // �J�v�Z�����`������e�I�u�W�F�N�g�̏ڍ׏��
    struct DETAIL
    {
        CYLINDER cylinder;  // �~�����
        SPHERE sphere1;     // ���̂P���
        SPHERE sphere2;     // ���̂Q���
    };

    // �J�v�Z�����[�ʒu/���a/����/�p�x etc...]�̍\����
    struct INFO
    {
        D3DXVECTOR3 pos;    // �ʒu
        float radius;       // ���a
        float length;       // ����
        D3DXVECTOR3 rot;    // �p�x
        D3DXVECTOR3 P0;     // �����̎n�_
        D3DXVECTOR3 P1;     // �����̏I�_
        DETAIL detail;      // �J�v�Z�����`������e�I�u�W�F�N�g�̏ڍ׏��
    };

    CCollisionModelCapsule(PRIORITY = PRIORITY_COLLISION); // �R���X�g���N�^
    ~CCollisionModelCapsule();                             // �f�X�g���N�^

    void Load();    // ���[�h����
    void Unload();  // �A�����[�h����

    static CCollisionModelCapsule *Create(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot);    // ��������

    HRESULT Init(); // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����
    void Draw();    // �`�揈��

    void SetInfo(const D3DXVECTOR3 &pos, const float &radius, const float &length, const D3DXVECTOR3 &rot);  // �ʒu/���a/����/�p�x�̐ݒ�

    inline INFO GetInfo()const { return m_info; }  // �ʒu/���a/����/�p�x���̎擾

private:
    void SetPos(const int &nCount);  // �ʒu�̐ݒ�
    void SetSize(const int &nCount); // �傫���̐ݒ�
    void SetRot(const int &nCount);  // �p�x�̐ݒ�
    void SetMtx(const int &nCount);  // ���[���h�}�g���b�N�X�̐ݒ�

    LPD3DXMESH m_apMesh[TYPE_MAX];      // ���b�V�����̃|�C���^
    LPD3DXBUFFER m_apBuffMat[TYPE_MAX]; // �}�e���A�����̃|�C���^
    D3DXMATRIX m_mtxWorld;              // �s��v�Z�p
    INFO m_info;                        // �ʒu/�傫��/�p�x���
};
#endif