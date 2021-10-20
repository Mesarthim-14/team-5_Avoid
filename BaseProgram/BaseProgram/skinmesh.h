#ifndef SKINMESH_H
#define SKINMESH_H

#include "main.h"

#define TRIANGLE 3

namespace SkinMesh
{
	// D3DXFRAME(ボーン)関連の情報を保持
	// D3DXFRAMEの派生クラス(SMD3DXFRAME)作成idとoffsetMatrixを追加
	struct SMD3DXFRAME : public D3DXFRAME
	{
		DWORD id;						// ボーンID
		D3DXMATRIX offsetMatrix;		// ボーンオフセット行列

		SMD3DXFRAME() : id(0xffffffff)	// 初期化
		{
			D3DXMatrixIdentity(&offsetMatrix);
		}
	};

	// SMD3DXMESHCONTAINER(メッシュ)関連の情報を保持
	struct SMD3DXMESHCONTAINER : public D3DXMESHCONTAINER
	{
		DWORD maxFaceInfl;					// ボーン最大影響数
		DWORD numBoneCombinations;			// ボーンコンビネーション数
		ID3DXBuffer *boneCombinationTable;	// ボーンコンビネーション構造体配列へのポインタ
		SMD3DXMESHCONTAINER() : maxFaceInfl(1), numBoneCombinations(0), boneCombinationTable(0) {}	// 初期化
	};

	// ボーンの構成であるフレームツリー（D3DXFRAME）、FKアニメーション（ID3DXAnimationController）という2つのオブジェクトを返す。
	class AllocateHierarchy : public ID3DXAllocateHierarchy
	{
	public:
		// フレームオブジェクト（D3DXFRAME構造体）作成関数
		STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
		// 指定されたフレームを削除する関数
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
		// メッシュコンテナ（D3DXMESHCONTAINER構造体）作成関数
		STDMETHOD(CreateMeshContainer)(THIS_
			LPCSTR Name,								// フレームの名前
			CONST D3DXMESHDATA *pMeshData,				// D3DXMESHDATA構造体へのポインタ
			CONST D3DXMATERIAL *pMaterials,				// マテリアル情報
			CONST D3DXEFFECTINSTANCE *pEffectInstances,	// エフェクト情報（レンダリングをカスタマイズする専用のプログラムのようなもの）
			DWORD NumMaterials,							// マテリアルの数
			CONST DWORD *pAdjacency,					// メッシュを構成する三角ポリゴンの数
			LPD3DXSKININFO pSkinInfo,					// スキニング(メッシュを変形)情報
			LPD3DXMESHCONTAINER *ppNewMeshContainer);	// メッシュコンテナ構造体へのポインタ

														//指定されたメッシュコンテナを削除
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);
	private:
		char *copyName(const char* name);//名前
	};
	void updateCombMatrix(std::map<DWORD, D3DXMATRIX> &combMatrixMap, SkinMesh::SMD3DXFRAME *frame);
	void getMeshContainer(D3DXFRAME *frame, std::vector<SkinMesh::SMD3DXMESHCONTAINER*> *cont);
	void setFrameId(SkinMesh::SMD3DXFRAME * frame, ID3DXSkinInfo * info);
}

#endif