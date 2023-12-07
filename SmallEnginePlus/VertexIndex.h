#pragma once
#include "pch.h"
#include "VertexIndexCollection.h"

/// <summary>
/// 頂点インデックス
/// </summary>
class VertexIndex
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="index">頂点インデックス</param>
	VertexIndex (DWORD index);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~VertexIndex ();

	/// <summary>
	/// DWORDの配列から頂点インデックス配列を生成する
	/// </summary>
	/// <param name="indices">頂点インデックス情報</param>
	/// <returns>頂点インデックス配列</returns>
	static class VertexIndexCollection CreateIndicesFromDWORDArray (vector<DWORD> indices);
private:
	/// <summary>
	/// 頂点インデックス
	/// </summary>
	DWORD m_index;
};
