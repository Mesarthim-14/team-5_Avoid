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

	static CGauge * Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetDown(float down) { m_fDown = down; }
	float GetDown(void) { return m_fDown; }

private:
	void SetVertexGauge(void);
	void SetDownUp(void);
	float m_fDown;
};


#endif // !_GAUGE_H_
