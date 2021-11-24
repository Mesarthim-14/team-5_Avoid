#ifndef _STATE_CAMERA_ANGRY_KRAKEN_H_
#define _STATE_CAMERA_ANGRY_KRAKEN_H_
//=====================================================================
//
// クラーケン怒り演出カメラ [state_camera_angry_kraken.h]
// Author : Konishi Yuuto
//
//=====================================================================

//=====================================================================
// インクルードファイル
//=====================================================================
#include "state_camera.h"

//=====================================================================
// 前方宣言
//=====================================================================
class CCamera;

//=====================================================================
// クラス定義
//=====================================================================
class CCameraStateAngryKraken : public CCameraState
{
public:
    CCameraStateAngryKraken();                  // コンストラクタ
    ~CCameraStateAngryKraken();                 // デストラクタ
    static CCameraStateAngryKraken* Create();   // インスタンス生成

    void Init();            // 初期化処理
    void Update()override;  // 更新処理
private:
    void ViewKraken(CCamera* &pCamera); // クラーケンを見る処理
};
#endif