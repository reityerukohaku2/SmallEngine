#include "pch.h"
#include "GeometryCollection.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="geometries">Geometryの配列</param>
GeometryCollection::GeometryCollection (vector<Geometry> geometries)
{
    m_geometries = geometries;
}

/// <summary>
/// 配列の末尾に要素を追加する
/// </summary>
/// <param name="geometry">追加する要素</param>
void GeometryCollection::push_back (Geometry geometry)
{
    m_geometries.push_back (geometry);
}

/// <summary>
/// 配列の先頭ポインタを返す
/// </summary>
/// <returns>配列の先頭ポインタ</returns>
Geometry* GeometryCollection::data () {
    return m_geometries.data ();
}

/// <summary>
/// 配列の終了地点を示すイテレーターを返す
/// </summary>
/// <returns></returns>
typename vector<Geometry>::const_iterator GeometryCollection::end () {
    return m_geometries.end ();
}

typename vector<Geometry>::const_iterator GeometryCollection::begin ()
{
    return m_geometries.begin ();
}

/// <summary>
/// 形状に含まれる全ての頂点数を返す
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetVertexNum ()
{
    UINT vertexNum = 0;
    for (auto geometry: m_geometries) {
        vertexNum += geometry.GetVertexNum ();
    }

    return vertexNum;
}

/// <summary>
/// 形状のバイト数を返す
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetGeometriesSize ()
{
    return this->GetVertexNum () * sizeof(Vertex);
}

/// <summary>
/// 全ての頂点情報を取得する
/// </summary>
VertexCollection GeometryCollection::GetVertices ()
{
    vector<Vertex> allVertices;
    for (auto geometry : m_geometries) {
        auto vertices = geometry.GetVertices ();
        copy (vertices.begin (), vertices.end (), back_inserter (allVertices));
    }

    return allVertices;
}

/// <summary>
/// 配列の要素数を返す
/// </summary>
/// <returns></returns>
size_t GeometryCollection::size ()
{
    return m_geometries.size();
}

/// <summary>
/// 配列要素を全て削除
/// </summary>
void GeometryCollection::clear ()
{
    m_geometries.clear ();
}

