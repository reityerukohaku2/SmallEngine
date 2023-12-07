#include "pch.h"
#include "VertexIndex.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="index">頂点インデックス</param>
VertexIndex::VertexIndex (DWORD index) {
	this->m_index = index;
}

/// <summary>
/// デストラクタ
/// </summary>
VertexIndex::~VertexIndex (){}

/// <summary>
/// DWORDの配列から頂点インデックスを作成する
/// </summary>
/// <param name="indicesData"></param>
/// <returns></returns>
VertexIndexCollection VertexIndex::CreateIndicesFromDWORDArray (vector<DWORD> indicesData)
{
	VertexIndexCollection indices;

	for (auto index : indicesData) {
		indices.push_back (VertexIndex(index));
	}

	return indices;
}
