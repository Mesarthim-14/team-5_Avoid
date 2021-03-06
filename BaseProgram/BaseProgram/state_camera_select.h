#ifndef _STATE_CAMERA_SELECT_H_
#define _STATE_CAMERA_SELECT_H_
//=====================================================================
//
// セレクトカメラ状態管理クラス [state_camera_select.h]
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
class CCameraStateSelect : public CCameraState
{
public:
    CCameraStateSelect();                 // コンストラクタ
    ~CCameraStateSelect();                // デストラクタ

    static CCameraStateSelect* Create();    // インスタンス生成
    void Init();            // 初期化処理
    void Update()override;  // 更新処理

private:

};
#endif