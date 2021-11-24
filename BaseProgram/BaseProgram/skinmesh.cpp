//=============================================================================
//
// スキンメッシュ処理 [skinmesh.cpp]
// Author : Takahashi Naoyuki
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "skinmesh.h"

//フレーム名コピー関数
char * SkinMesh::AllocateHierarchy::copyName(const char * name)
{
    char *cName = 0;

    // 偽か\0なら
    if (!name || name[0] == '\0')
    {
        cName = new char[1];
        cName[0] = '\0';
    }
    else
    {
        size_t len = strlen(name);
        cName = new char[strlen(name) + 1];
        strcpy_s(cName, strlen(name) + 1, name);
    }

    return cName;
}

//フレーム生成関数
HRESULT SkinMesh::AllocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
    SMD3DXFRAME *newFrame = new SMD3DXFRAME;
    newFrame->Name = copyName(Name);    // フレームの名前初期化
    newFrame->pFrameFirstChild = 0;        // 子フレームへのポインタ初期化
    newFrame->pFrameSibling = 0;        // 兄弟フレームへのポインタ初期化
    newFrame->pMeshContainer = 0;        // メッシュコンテナへのポインタ初期化
    D3DXMatrixIdentity(&newFrame->TransformationMatrix);// 初期化
    *ppNewFrame = newFrame;

    return D3D_OK;
}

//フレーム削除関数
HRESULT SkinMesh::AllocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
    // 子フレームを持っているなら
    if (pFrameToFree->pFrameFirstChild)
    {
        //子フレームを消す
        DestroyFrame(pFrameToFree->pFrameFirstChild);
    }

    // 兄弟フレームを持っているなら
    if (pFrameToFree->pFrameSibling)
    {
        // 兄弟フレームを消す
        DestroyFrame(pFrameToFree->pFrameSibling);
    }

    // メッシュコンテナを持っているなら
    if (pFrameToFree->pMeshContainer)
    {
        // メッシュコンテナを消す
        DestroyMeshContainer(pFrameToFree->pMeshContainer);
    }

    // フレーム名削除
    delete[] pFrameToFree->Name;

    // フレーム削除
    delete pFrameToFree;

    return D3D_OK;
}

//メッシュコンテナー生成関数
HRESULT SkinMesh::AllocateHierarchy::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
    SMD3DXMESHCONTAINER *newCont = new SMD3DXMESHCONTAINER;
    newCont->Name = copyName(Name);// フレームの名前初期化

    newCont->pAdjacency = new DWORD[pMeshData->pMesh->GetNumFaces() * TRIANGLE];    // メッシュを構成する三角ポリゴンの数を取得及び配列の確保
    memset(newCont->pAdjacency, 0, pMeshData->pMesh->GetNumFaces() * TRIANGLE * sizeof(DWORD));    // 隣接する(3つ)ポリゴンインデックスのコピー

    newCont->MeshData.Type = pMeshData->Type;    // メッシュタイプのコピー

                                                // 読み込んだメッシュをスキンメッシュ用に最適化するヘルパー関数
    pSkinInfo->ConvertToBlendedMesh
    (
        pMeshData->pMesh,// ID3DAllocateHierarchyで読み込んだ最適化される前のメッシュ
        0,
        pAdjacency,
        newCont->pAdjacency,
        0,
        0,
        &newCont->maxFaceInfl,            // 1つの頂点に影響するボーンの最大数が返る
        &newCont->numBoneCombinations,    // ボーンコンビネーションの数
        &newCont->boneCombinationTable,    // ボーンと頂点の対応表が配列として格納されている
        &newCont->MeshData.pMesh        // 最適化されたメッシュが返る
    );

    newCont->NumMaterials = NumMaterials;    // マテリアルの数コピー
    newCont->pMaterials = new D3DXMATERIAL[NumMaterials];    // 配列の確保
    memcpy(newCont->pMaterials, pMaterials, NumMaterials * sizeof(D3DXMATERIAL)); //D3DXMATERIAL構造体の配列の先頭ポインタコピー

    newCont->pEffects = 0;// 初期化

    // pEffectInstancesが真なら
    if (pEffectInstances)
    {
        newCont->pEffects = new D3DXEFFECTINSTANCE;// メモリ確保
        newCont->pEffects->pEffectFilename = copyName(pEffectInstances->pEffectFilename);    // エフェクトファイルの名前コピー
        newCont->pEffects->NumDefaults = pEffectInstances->NumDefaults;                        // pDefaults(D3DXEFFECTDEFAULT構造体)の配列の要素数コピー
        newCont->pEffects->pDefaults = new D3DXEFFECTDEFAULT[pEffectInstances->NumDefaults];// メモリ確保（pDefaultsは配列の先頭ポインタ）
        for (DWORD i = 0; i < pEffectInstances->NumDefaults; i++)
        {
            D3DXEFFECTDEFAULT *src = pEffectInstances->pDefaults + i;    // コピー元
            D3DXEFFECTDEFAULT *dest = newCont->pEffects->pDefaults + i;    // コピー先
            dest->NumBytes = src->NumBytes;                        // パラメータの情報大きさコピー
            dest->Type = src->Type;                                // パラメータの型情報コピー
            dest->pParamName = copyName(src->pParamName);        // パラメータに付けられた名前コピー
            dest->pValue = new char[src->NumBytes];                // パラメータの値を指すポインタのメモリ確保
            memcpy(dest->pValue, src->pValue, src->NumBytes);    // パラメータの値を指すポインタのコピー
        }
    }

    newCont->pSkinInfo = pSkinInfo;// スキニング情報コピー
    pSkinInfo->AddRef();//参照カウンタを加算

    *ppNewMeshContainer = newCont;// 作成したメッシュコンテナ（D3DXMESHCONTAINER構造体）を引数に渡す

    return D3D_OK;
}

//メッシュコンテナー削除関数
HRESULT SkinMesh::AllocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
    {
        // メッシュコンテナをコピー(長いから短く)
        SMD3DXMESHCONTAINER *pMCont = (SMD3DXMESHCONTAINER*)pMeshContainerToFree;

        // メッシュの解放
        pMCont->MeshData.pMesh->Release();

        // 名前の解放
        delete[] pMCont->Name;

        // メッシュを構成する三角ポリゴン数の解放
        delete[] pMCont->pAdjacency;

        // pEffectが真なら
        if (pMCont->pEffects)
        {
            for (DWORD i = 0; i < pMCont->pEffects->NumDefaults; i++)
            {
                D3DXEFFECTDEFAULT *pDefaults = pMCont->pEffects->pDefaults + i;// コピー(長いから短く)

                delete[] pDefaults->pParamName;    // パラメータの名前解放
                delete[] pDefaults->pValue;        // パラメータの値を指すポインタの解放
            }

            delete[] pMCont->pEffects->pDefaults;        // pEffects配列の先頭ポインタ解放
            delete[] pMCont->pEffects->pEffectFilename;    // エフェクトファイルの名前解放
            delete pMCont->pEffects;                    // pEffectInstances解放
        }

        // マテリアル情報の解放
        delete[] pMCont->pMaterials;

        // スキン情報が真なら
        if (pMCont->pSkinInfo)
        {
            pMCont->pSkinInfo->Release();    // スキン情報解放
        }

        // ボーンコンビネーション構造体配列へのポインタが真なら
        if (pMCont->boneCombinationTable)
        {
            pMCont->boneCombinationTable->Release();    // ボーンコンビネーション構造体配列へのポインタ解放
        }

        //メッシュコンテナを削除
        delete pMCont;

        return D3D_OK;
    }
}

//メッシュコンテナ取得関数
void SkinMesh::getMeshContainer(D3DXFRAME * frame, std::vector<SkinMesh::SMD3DXMESHCONTAINER*>* cont)
{
    // メッシュコンテナを保有している
    if (frame->pMeshContainer)
    {
        // メッシュコンテナを返す
        cont->push_back((SkinMesh::SMD3DXMESHCONTAINER*)frame->pMeshContainer);
    }

    // メッシュコンテナを保有していない

    // 子フレームを保有している
    if (frame->pFrameFirstChild)
    {
        // 子フレームのメッシュコンテナを返す
        return getMeshContainer(frame->pFrameFirstChild, cont);
    }

    // メッシュコンテナ、子フレームを保有していない
    // 兄弟フレームを保有している
    if (frame->pFrameSibling)
    {
        // 兄弟フレームのメッシュコンテナを返す
        return getMeshContainer(frame->pFrameSibling, cont);
    }
}

//フレーム情報リンク関数
void frameLink(std::map<std::string, DWORD> nameToIdMap, ID3DXSkinInfo * info, SkinMesh::SMD3DXFRAME* frame)
{
    //nameToIdMapの名前を検索して、フレームの最後尾ではないなら
    if (nameToIdMap.find(frame->Name) != nameToIdMap.end())
    {
        //フレームに対応するボーンオフセット行列と名前を紐づけ
        frame->id = nameToIdMap[frame->Name];
        frame->offsetMatrix = *info->GetBoneOffsetMatrix(frame->id);
    }

    //子フレームの有無
    if (frame->pFrameFirstChild)
    {
        frameLink(nameToIdMap, info, (SkinMesh::SMD3DXFRAME*)frame->pFrameFirstChild);
    }

    //兄弟フレームの有無
    if (frame->pFrameSibling)
    {
        frameLink(nameToIdMap, info, (SkinMesh::SMD3DXFRAME*)frame->pFrameSibling);
    }
};

// ボーンID毎の情報を引き出し、フレームに対応するボーンIDを紐づけ
void SkinMesh::setFrameId(SkinMesh::SMD3DXFRAME *frame, ID3DXSkinInfo *info)
{
    std::map < std::string, DWORD > BonesMap;//ボーンネームとID保存用

                                             //ボーンの名前とIDを紐づけ
    for (DWORD nCount = 0; nCount < info->GetNumBones(); nCount++)
    {
        BonesMap[info->GetBoneName(nCount)] = nCount;
    }

    //フレーム情報紐づけ
    frameLink(BonesMap, info, frame);
}

//サブメッシュへのボーン影響度を計算格納する関数
void boneMatrixLink(std::map<DWORD, D3DXMATRIX> &combMatrixMap, D3DXMATRIX &parentBoneMatrix, SkinMesh::SMD3DXFRAME *frame)
{
    //フレームのボーン影響度を抽出
    D3DXMATRIX &localBoneMatrix = frame->TransformationMatrix;

    //ボーン影響度のワールド変換
    D3DXMATRIX boneMatrix = localBoneMatrix * parentBoneMatrix;

    //ボーンが存在している
    if (frame->id != 0xffffffff)
    {
        //ボーンのオフセット * フレームのボーン影響度 ＝ フレームのサブメッシュへのボーン影響度を計算格納
        combMatrixMap[frame->id] = frame->offsetMatrix * boneMatrix;
    }

    //子フレームが存在している
    if (frame->pFrameFirstChild)
    {
        //子フレームの計算
        boneMatrixLink(combMatrixMap, boneMatrix, (SkinMesh::SMD3DXFRAME*)frame->pFrameFirstChild);
    }

    //兄弟フレームが存在している
    if (frame->pFrameSibling)
    {
        //兄弟フレームの計算
        boneMatrixLink(combMatrixMap, parentBoneMatrix, (SkinMesh::SMD3DXFRAME*)frame->pFrameSibling);
    }
}

//現在フレーム(fps)のワールド変換行列計算(行列保存用,参照フレーム)
void SkinMesh::updateCombMatrix(std::map<DWORD, D3DXMATRIX>& combMatrixMap, D3DXMATRIX matrix, SkinMesh::SMD3DXFRAME * frame)
{
    boneMatrixLink(combMatrixMap, matrix, frame);
}

// ブレンド行列インデックス作成
void SkinMesh::createBlendIndex(BlendIndex** ppIndex, D3DXBONECOMBINATION* pBoneComb, DWORD boneCombNum)
{
	*ppIndex = new BlendIndex[boneCombNum];
	BlendIndex *bi = *ppIndex;

	for (DWORD i = 0; i < boneCombNum; ++i)
	{
		memcpy(bi[i].index, pBoneComb[i].BoneId, sizeof(DWORD) * 4);
		bi[i].boneNum = 0;
		for (int j = 0; j < 4; ++j)
		{
			if (pBoneComb[i].BoneId[j] != UINT_MAX)
			{
				bi[i].boneNum++;
			}
		}
	}
}