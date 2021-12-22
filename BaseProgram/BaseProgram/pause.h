#ifndef _PAUSE_H_
#define _PAUSE_H_
//=====================================================================
//
//    �|�[�Y����[pause.h]
//    Author : toshiki
//
//=====================================================================

//=====================================================================
// �C���N���[�h�t�@�C��
//=====================================================================
#include "scene.h"
#include "polygon.h"

//=====================================================================
// �N���X��`
//=====================================================================
class CPause : public CPolygon
{
public:
    enum MENU
    {
        BACK = 0,
        RESUME,
        RESTART,
        EXIT,
        MAX
    };

    CPause();
    ~CPause();

    static CPause * Create();

    HRESULT Init();
    void Uninit();
    void Update();
    void Draw();

    inline bool SetPause(const bool &pause) { m_bPause = pause; }

private:
    CPolygon * m_pPolygon[MAX];
    int m_nMenu;
    bool m_bPause;
    float m_fMove;
};


#endif // !_GAUGE_H_
