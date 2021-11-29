#ifndef _COLLISION_MODEL_H_
#define _COLLISION_MODEL_H_
//=============================================================================
//
// �����蔻�胂�f���̐e�N���X���� [collisionModel.h]
// Author : Suzuki Mahiro
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CCollisionModel :public CScene
{
public:
    // �����蔻��^�C�v�̗񋓌^
    enum TYPE
    {
        TYPE_NONE = -1,
        TYPE_POLYGON,   // �|���S��
        TYPE_OBB,       // ������
        TYPE_SPHERE,    // ����
        TYPE_CAPSULE,   // �J�v�Z��
        TYPE_CYLINDER,  // �~��
        TYPE_MAX
    };

    // �ʒu/�傫��/�p�x���̍\����
    struct INFO
    {
        D3DXVECTOR3 pos;    // �ʒu
        D3DXVECTOR3 size;   // �傫��
        D3DXVECTOR3 rot;    // �p�x
    };

    CCollisionModel(PRIORITY = PRIORITY_COLLISION); // �R���X�g���N�^
    ~CCollisionModel();                             // �f�X�g���N�^

    void Load();    // ���[�h����
    void Unload();  // �A�����[�h����

    HRESULT Init(); // ����������
    void Uninit();  // �I������
    void Update();  // �X�V����
    void Draw();    // �`�揈��

    inline void SetInfo(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot)
    { m_info.pos = pos; m_info.size = size; m_info.rot = rot; }     // �ʒu/�傫��/�p�x�̐ݒ�

    INFO GetInfo()const { return m_info; }  // �ʒu/�傫��/�p�x���

protected:
    inline void SetType(const TYPE &type) { m_type = type; }    // �����蔻��^�C�v�̐ݒ�

private:
    LPD3DXMESH m_pMesh;         // ���b�V�����̃|�C���^
    LPD3DXBUFFER m_pBuffMat;    // �}�e���A�����̃|�C���^
    D3DXMATRIX m_mtxWorld;      // �s��v�Z�p
    INFO m_info;                // �ʒu/�傫��/�p�x���
    TYPE m_type;                // �����蔻��^�C�v
};
#endif