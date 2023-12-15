#include "pch.h"
#include "VertexIndex.h"

VertexIndex::VertexIndex (vector<DWORD> &&indicesData) : vector<DWORD>(move(indicesData)){}

/// <summary>
/// 頂点インデックスのバイト数を返す
/// </summary>
/// <returns>頂点インデックスのバイト数</returns>
UINT VertexIndex::GetIndicesSize () 
{
	return this->size () * sizeof (DWORD);
}
