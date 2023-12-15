#include "pch.h"
#include "GeometryCollection.h"

/// <summary>
/// 形状に含まれる全ての頂点数を返す
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetVertexNum ()
{
    UINT vertexNum = 0;

    for (auto geometry: *this) {
        vertexNum += geometry.GetVertexNum ();
    }

    return vertexNum;
}

/// <summary>
/// 形状に含まれる全ての頂点インデックス数を返す
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetIndexNum ()
{
    UINT indexNum = 0;

    for (auto geometry: *this) {
        indexNum += geometry.GetIndexNum ();
    }

    return indexNum;
}

/// <summary>
/// 形状のバイト数を返す
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetGeometriesSize ()
{
    return GetVertexNum () * sizeof (Vertex);
}

/// <summary>
/// 頂点インデックスのバイト数を返す
/// </summary>
/// <returns>頂点インデックスのバイト数</returns>
UINT GeometryCollection::GetIndicesSize ()
{
    return GetIndexNum () * sizeof (DWORD);
}

/// <summary>
/// 全ての頂点情報を取得する
/// </summary>
vector<Vertex> GeometryCollection::GetVertices ()
{
    vector<Vertex> allVertices;

    // 自身の要素を1つずつ取り出して処理する
    for (auto& geometry : *this) {
        auto vertices = geometry.GetVertices();
        allVertices.reserve(allVertices.size() + vertices.size());
        allVertices.insert(allVertices.end(), vertices.begin(), vertices.end());
    }

    return allVertices;
}

UINT GeometryCollection::GetVerticesSize ()
{
    return GetVertices().size() * sizeof(XMVECTOR);
}

/// <summary>
/// 頂点インデックスを取得する
/// </summary>
/// <returns></returns>
VertexIndex GeometryCollection::GetIndices ()
{
    VertexIndex allIndices;

    for (auto& geometry : *this) {
        auto indices = geometry.GetIndices ();
        allIndices.reserve (allIndices.size () + indices.size());
        allIndices.insert (allIndices.end (), indices.begin (), indices.end ());
    }

    return allIndices;
}

/// <summary>
/// 頂点数を再計算する
/// </summary>
/// <returns>全頂点数</returns>
UINT GeometryCollection::CountVertexNum ()
{
    UINT vertexNum = 0;
    for (auto& geometry : *this) {
        vertexNum += geometry.GetVertexNum ();
    }

    return vertexNum;
}

/// <summary>
/// 頂点インデックス数を再計算する
/// </summary>
/// <returns>全頂点インデックス数</returns>
UINT GeometryCollection::CountIndexNum ()
{
    UINT indexNum = 0;
    for (auto& geometry : *this) {
        indexNum += geometry.GetIndexNum ();
    }

    return indexNum;
}
