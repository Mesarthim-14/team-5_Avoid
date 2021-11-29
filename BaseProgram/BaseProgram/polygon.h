#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// �|���S�������N���X���� [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �|���S���N���X
//=============================================================================
class CPolygon
{
public:
    CPolygon();     // �R���X�g���N�^
    ~CPolygon();    // �f�X�g���N�^

    HRESULT Init(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);  // ����������
    void Uninit();                                                  // �I������
    void Update();                                                  // �X�V����
    void Draw();                                                    // �`�揈��
    void SetColor(const D3DXCOLOR &color);                          // �F�̐ݒ�

    static CPolygon *Create(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);   // �C���X�^���X����
    inline void BindTexture(const LPDIRECT3DTEXTURE9 &pTexture) { m_pTexture = pTexture; }

private:
    LPDIRECT3DTEXTURE9 m_pTexture;      // �e�N�X�`���̃|�C���^
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; // ���_�o�b�t�@�ւ̃|�C���^
    D3DXVECTOR3 m_size;                 // �|���S���̃T�C�Y
    D3DXVECTOR3 m_pos;                  // ���C�t�̈ʒu

};
#endif 