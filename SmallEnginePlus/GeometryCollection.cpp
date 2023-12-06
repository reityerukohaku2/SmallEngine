#include "pch.h"
#include "GeometryCollection.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="geometries">Geometryの配列</param>
GeometryCollection::GeometryCollection (vector<Geometry> geometries)
{
    m_geometries = geometries;
    m_vertexNum = CountVertexNum ();
    m_indexNum = CountIndexNum ();
}

/// <summary>
/// 配列の末尾に要素を追加する
/// </summary>
/// <param name="geometry">追加する要素</param>
void GeometryCollection::push_back (Geometry geometry)
{
    m_geometries.push_back (geometry);
    m_vertexNum++;
    m_indexNum++;
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
    return m_vertexNum;
}

/// <summary>
/// 形状に含まれる全ての頂点インデックス数を返す
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetIndexNum ()
{
    return m_indexNum;
}

/// <summary>
/// 形状のバイト数を返す
/// </summary>
/// <returns></returns>
UINT GeometryCollection::GetGeometriesSize ()
{
    return GetVertexNum () * sizeof(Vertex);
}

/// <summary>
/// 頂点インデックスのバイト数を返す
/// </summary>
/// <returns>頂点インデックスのバイト数</returns>
UINT GeometryCollection::GetIndiceSize () 
{
    return GetIndexNum () * sizeof (VertexIndex);
}

/// <summary>
/// 全ての頂点情報を取得する
/// </summary>
VertexCollection GeometryCollection::GetVertices ()
{
    VertexCollection allVertices;
    vector<Vertex> hoge, hoge2;

    for (auto geometry : m_geometries) {
        auto vertices = geometry.GetVertices ();

        // 末尾に配列を追加
        allVertices.insert (allVertices.end(), vertices.begin(), vertices.end());
    }

    return allVertices;
}

/// <summary>
/// 頂点数を再計算する
/// </summary>
/// <returns>全頂点数</returns>
UINT GeometryCollection::CountVertexNum ()
{
    UINT vertexNum = 0;
    for (auto geometry : m_geometries) {
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
    for (auto geometry : m_geometries) {
        indexNum += geometry.GetIndexNum ();
    }

    return indexNum;
}

/// <summary>
/// targetPosの位置に配列を挿入する
/// </summary>
/// <param name="targetPos">挿入先</param>
/// <param name="begin">挿入する配列の開始地点</param>
/// <param name="end">挿入する配列の終了地点</param>
/// <returns></returns>
typename vector<Geometry>::const_iterator GeometryCollection::insert 
(
    typename vector<Geometry>::const_iterator targetPos, 
    typename vector<Geometry>::const_iterator begin, 
    typename vector<Geometry>::const_iterator end
){
    return m_geometries.insert (targetPos, begin, end);
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
    m_vertexNum = 0;
}

