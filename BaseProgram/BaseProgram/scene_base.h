#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_
//=============================================================================
//
// �V�[���x�[�X�N���X�w�b�_�[ [scene_base.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CTextureAnimation;

//=============================================================================
// �V�[���x�[�X�N���X
//=============================================================================
class CSceneBase : public CScene
{
public:
	CSceneBase(PRIORITY Priority = PRIORITY_0);										// �R���X�g���N�^
	virtual ~CSceneBase();															// �f�X�g���N�^

	virtual void Uninit(void);														// �I������
	virtual void Update(void);														// �X�V����
	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }	// �e�N�X�`���̐ݒ�

	// �������z�֐�
	virtual HRESULT Init(void) = 0;												// ����������
	virtual void Draw(void) = 0;												// �`�揈��
	virtual void InitAnimation(int nPatternNum, int nSpeed, int nLoop) = 0;		// �A�j���[�V�����̐ݒ�
	virtual void UpdateAnimation(void) = 0;										// �A�j���[�V�����̍X�V

protected:
	void SetSceneInfo(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// �V�[�����̐ݒ�

	// Set�֐�
	virtual void SetPos(const D3DXVECTOR3 &pos)					{ m_pos = pos; }				// ���W
	virtual void SetSize(const D3DXVECTOR3 &size)				{ m_size = size; }				// �T�C�Y
	virtual void SetRot(const D3DXVECTOR3 &rot)					{ m_rot = rot; }				// �p�x		
	virtual void SetColor(const D3DXCOLOR &col)					{ m_col = col; }				// �F
	void BindVtxBuff(const LPDIRECT3DVERTEXBUFFER9 pVtxBuff)	{ m_pVtxBuff = pVtxBuff; }		// ���_�o�b�t�@
	void SetTextureAnimationPtr(CTextureAnimation* pPtr)		{ m_pTextureAnimation = pPtr; }	// �|�C���^�擾

	// Get�֐�
	D3DXVECTOR3 GetPos(void)const					{ return m_pos; }				// ���W
	D3DXVECTOR3 GetSize(void)const					{ return m_size; }				// �T�C�Y
	D3DXVECTOR3 GetRot(void)const					{ return m_rot; }				// ��]��
	D3DXCOLOR &GetColor(void)						{ return m_col; }				// �F
	LPDIRECT3DTEXTURE9 GetTexture(void)				{ return m_pTexture; }			// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void)		{ return m_pVtxBuff; }			// �o�b�t�@���
	CTextureAnimation*GetTextureAnimationPtr(void)	{ return m_pTextureAnimation; }	// �e�N�X�`���|�C���^

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// �o�b�t�@
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXCOLOR m_col;						// �F
	D3DXVECTOR3 m_rot;						// ��]��
	CTextureAnimation* m_pTextureAnimation;	// �e�N�X�`���A�j���[�V�����̏��
};

#endif