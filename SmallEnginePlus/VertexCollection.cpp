#include "pch.h"
#include "VertexCollection.h"

VertexCollection::VertexCollection (vector<Vertex> vertices) {
    m_vertices = vertices;
}

/// <summary>
/// 配列の末尾に要素を追加する
/// </summary>
void VertexCollection::push_back (Vertex vertex)
{
    m_vertices.push_back (vertex);
}

/// <summary>
/// 配列要素の先頭ポインタを返す
/// </summary>
/// <returns>配列の先頭ポインタ</returns>
Vertex* VertexCollection::data ()
{
    return m_vertices.data();
}

/// <summary>
/// 配列の開始地点を示すイテレーターを返す
/// </summary>
/// <returns></returns>
vector<Vertex>::const_iterator VertexCollection::begin ()
{
    return m_vertices.begin();
}

/// <summary>
/// 配列の終了地点を示すイテレーターを返す
/// </summary>
/// <returns></returns>
vector<Vertex>::const_iterator VertexCollection::end ()
{
    return m_vertices.end ();
}

/// <summary>
/// 配列要素を全て削除
/// </summary>
void VertexCollection::clear () {
    m_vertices.clear ();
}

/// <summary>
/// 配列の要素数を返す
/// </summary>
/// <returns></returns>
size_t VertexCollection::size () {
    return m_vertices.size ();
}

/// <summary>
/// プリミティブ型配列にした頂点配列を返す
/// </summary>
/// <returns>プリミティブ型配列にした頂点配列</returns>
vector<XMFLOAT3> VertexCollection::GetArrayOfXMFLOAT3Position ()
{
    vector<XMFLOAT3> positions;

    for (auto vertex:m_vertices) {
        auto vectorPos = vertex.GetXMVECTORPosition();
        shared_ptr<XMFLOAT3> float3Pos = make_shared<XMFLOAT3>();
        XMStoreFloat3(float3Pos.get(), vectorPos);
        positions.push_back (*float3Pos);
    }

    return positions;
}

/// <summary>
/// targetPosの位置に配列を挿入する
/// </summary>
/// <param name="targetPos">挿入先</param>
/// <param name="begin">挿入する配列の開始地点</param>
/// <param name="end">挿入する配列の終了地点</param>
/// <returns></returns>
typename vector<Vertex>::const_iterator VertexCollection::insert (
    typename vector<Vertex>::const_iterator targetPos, 
    typename vector<Vertex>::const_iterator begin, 
    typename vector<Vertex>::const_iterator end
)
{
    return m_vertices.insert (targetPos, begin, end);
}

/// <summary>
/// 配列全体のバイト数を返す
/// </summary>
/// <returns></returns>
UINT VertexCollection::GetVerticesSize ()
{
    return m_vertices.size() * sizeof(Vertex);
}
