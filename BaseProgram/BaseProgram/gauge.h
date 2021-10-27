#ifndef _GAUGE_H_
#define _GAUGE_H_
//=====================================================================
//
//	�Q�[�W����[gauge.h]
//	Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "scene2d.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CGauge : public CScene2D
{
public:
	CGauge();
	~CGauge();
	//========================
	// �����o�֐�
	//========================
	static CGauge * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetDown(float down) { m_fDown = down; }
	float GetDown(void) { return m_fDown; }

private:
	void SetVertexGauge(void);		// �Q�[�W���Z����
	void SetDownUp(void);			// �e�X�g���鏈��

	//========================
	// �����o�ϐ�
	//========================
	float m_fDown;		// �Q�[�W��
	float m_fSave;		// �����
};


#endif // !_GAUGE_H_