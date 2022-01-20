#include "main.h"
#include "skinmesh.h"
#include "animation_skinmesh.h"
#include <vector>

//アニメーションコントローラーのポインタ取得
bool IHighLevelAnimController::SetAnimationController(ID3DXAnimationController * pAnimCont)
{
    //NULLチェック
    if (pAnimCont)
    {
        //コンテナコピー
        m_AnimCont = pAnimCont;
        //サイズ確保
        m_Anim.resize(pAnimCont->GetMaxNumAnimationSets());
        //アニメーションセット取得
        for (unsigned int size = 0; size < m_Anim.size(); size++)
        {
            pAnimCont->GetAnimationSet(size, &m_Anim[size].pAnimSet);
			m_Anim[size].bLoop = true;
        }

        m_CurAnimID = 0;
        m_PreAnimID = 0;
        return true;
    }
    else
    {
        return false;
    }
}

//アニメーションコントローラーのポインタを譲渡
bool IHighLevelAnimController::GetAnimationController(ID3DXAnimationController ** ppAnimCont)
{
    //NULLチェック
    if (m_AnimCont)
    {
        ppAnimCont = &m_AnimCont;

        return true;
    }
    else
    {
        return false;
    }
}

bool IHighLevelAnimController::SetAnimationLoop(UINT animID, BOOL loop)
{
	// 指定のアニメーションIDの存在をチェック
	if (m_Anim.size() <= animID)
	{
		return false;
	}

	m_Anim[animID].bLoop = loop;

	return true;
}

//アニメーションが一回のアニメーションがループするまでの時間
bool IHighLevelAnimController::SetLoopTime(UINT animID, FLOAT time)
{
    // 指定のアニメーションIDの存在をチェック
    if (m_Anim.size() <= animID)
    {
        return false;
    }

    // トラックスピード調節値を算出
    FLOAT DefTime = float(m_Anim[animID].pAnimSet->GetPeriod());
    m_Anim[animID].fLoopTime = time;
    m_Anim[animID].fTrackSpeed = DefTime / time;

    return true;
}

//アニメーションが完全に次に移る回るまでの時間
bool IHighLevelAnimController::SetShiftTime(UINT animID, FLOAT interval)
{
    // 指定のアニメーションIDの存在をチェック
    if (m_Anim.size() <= animID)
    {
        return false;
    }

    // シフト時間を登録
    m_Anim[animID].fShiftTime = interval;

    return true;
}

//アニメーション変更
bool IHighLevelAnimController::ChangeAnimation(UINT animID)
{
	int n = m_Anim.size();

    // 指定のアニメーションIDの存在をチェック
    if (m_Anim.size() <= animID)
    {
        return false;
    }

    // 異なるアニメーションであるかをチェック
    if (m_CurAnimID == animID)
    {
        return false;
    }

    // 現在のアニメーションセットの設定値を取得
    D3DXTRACK_DESC TD;   // トラックの能力

    m_AnimCont->GetTrackDesc(0, &TD);

    // 今のアニメーションをトラック1に移行し
    // トラックの設定値も移行
    m_AnimCont->SetTrackAnimationSet(1, m_Anim[m_CurAnimID].pAnimSet);
    m_AnimCont->SetTrackDesc(1, &TD);

    // 新しいアニメーションセットをトラック0に設定
    m_AnimCont->SetTrackAnimationSet(0, m_Anim[animID].pAnimSet);

    // トラック0のスピードの設定
    m_AnimCont->SetTrackSpeed(0, m_Anim[animID].fTrackSpeed);

    // トラックの合成を許可
    m_AnimCont->SetTrackEnable(0, true);
    m_AnimCont->SetTrackEnable(1, true);

    // ウェイト時間を初期化
    m_Anim[m_CurAnimID].fCurWeightTime = 0.0f;
    m_Anim[m_PreAnimID].fCurWeightTime = 0.0f;
    m_Anim[animID].fCurWeightTime = 0.0f;
    m_AnimCont->AdvanceTime(0, NULL);

    // 現在のアニメーション番号を切り替え
    m_PreAnimID = m_CurAnimID;
    m_CurAnimID = animID;

    return true;
}

//アニメーション合成及び更新
bool IHighLevelAnimController::AdvanceTime(FLOAT time)
{
    m_Anim[m_CurAnimID].fCurWeightTime += time;

    // 合成中か否かを判定
    if (m_Anim[m_CurAnimID].fCurWeightTime <= m_Anim[m_CurAnimID].fShiftTime)
    {
        // 合成中。ウェイトを算出
        FLOAT Weight = m_Anim[m_CurAnimID].fCurWeightTime / m_Anim[m_CurAnimID].fShiftTime;
        // ウェイトを登録
        m_AnimCont->SetTrackWeight(0, Weight);       // 現在のアニメーション
        m_AnimCont->SetTrackWeight(1, 1 - Weight);   // 前のアニメーション

        // 時間を更新
        m_AnimCont->AdvanceTime(time, NULL);
    }
    else
    {
        // 合成終了中。通常アニメーションをするTrack0のウェイトを最大値に
        m_AnimCont->SetTrackWeight(0, 1);       // 現在のアニメーション
        m_AnimCont->SetTrackEnable(1, false);      // 前のアニメーションを無効にする

		if (m_Anim[m_CurAnimID].bLoop)
		{
            // 時間を更新
            m_AnimCont->AdvanceTime(time, NULL);
		}
		else
		{
            if (m_Anim[m_CurAnimID].fCurWeightTime < m_Anim[m_CurAnimID].fLoopTime)
            {
                // 時間を更新
                m_AnimCont->AdvanceTime(time, NULL);
            }
            else
            {
                m_Anim[m_CurAnimID].fCurWeightTime = m_Anim[m_CurAnimID].fLoopTime;
            }
			//ChangeAnimation(m_Anim.size() -1);
		}
    }

    return true;
}