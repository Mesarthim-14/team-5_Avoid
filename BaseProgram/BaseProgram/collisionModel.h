//=============================================================================
//
// �����蔻�胂�f���̏��� [collisionModel.h]
// Author : Suzuki Mahiro
//
//=============================================================================
#ifndef _COLLISION_MODEL_H_
#define _COLLISION_MODEL_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define AXIS_NUM_OBB (3) //OBB�̎���

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CCollisionModel :public CScene
{
public:
    // �����蔻��^�C�v�̗񋓌^
    enum TYPE
    {
        TYPE_NONE = 0,
        TYPE_POLYGON,   // �|���S��
        TYPE_BOX,       // ��
        TYPE_SPHERE,    // ��
        TYPE_CYLINDER,  // �~��
        TYPE_MAX
    };

    //OBB���̍\����
    struct OBB
    {
        D3DXVECTOR3 pos;                    // �ʒu
        D3DXVECTOR3 size;                   // �傫��
        D3DXVECTOR3 rot;                    // �p�x
        D3DXVECTOR3 DirVect[AXIS_NUM_OBB];  // �����x�N�g��
        TYPE CollisionType;                 // �����蔻��̃^�C�v
    };

    CCollisionModel(PRIORITY = PRIORITY_COLLISION); // �R���X�g���N�^
    ~CCollisionModel();                             // �f�X�g���N�^

    void Load();        //���[�h����
    void Unload();      //�A�����[�h����

    static CCollisionModel *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXVECTOR3 &rot, const TYPE &type);    // ��������

    HRESULT Init();        // ����������
    void Uninit(void);    // �I������
    void Update(void);    // �X�V����
    void Draw(void);    // �`�揈��

    // �e��ݒ�
    inline void SetPos(const D3DXVECTOR3 &pos)     { m_obb.pos = pos; }            // �ʒu
    inline void SetSize(const D3DXVECTOR3 &size)   { m_obb.size = size; }          // �傫��
    inline void SetRot(const D3DXVECTOR3 &rot)     { m_obb.rot = rot; }            // �p�x
    inline void SetCollisionType(const TYPE &type) { m_obb.CollisionType = type; } // ���

    inline OBB GetOBB()const { return m_obb; }    // OBB�̎擾

private:
    LPD3DXMESH m_pMesh;         // ���b�V�����̃|�C���^
    LPD3DXBUFFER m_pBuffMat;    // �}�e���A�����̃|�C���^
    D3DXMATRIX m_mtxWorld;      // �s��v�Z�p
    OBB m_obb;                  // OBB���ϐ�
};
#endif