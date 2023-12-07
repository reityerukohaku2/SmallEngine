#include "pch.h"
#include "VertexIndexCollection.h"

VertexIndexCollection::VertexIndexCollection (vector<VertexIndex> indices) {
    m_indices = indices;
}

/// <summary>
/// 配列の末尾に要素を追加する
/// </summary>
void VertexIndexCollection::push_back (VertexIndex vertex)
{
    m_indices.push_back (vertex);
}

/// <summary>
/// 配列要素の先頭ポインタを返す
/// </summary>
/// <returns>配列の先頭ポインタ</returns>
VertexIndex* VertexIndexCollection::data ()
{
    return m_indices.data ();
}

/// <summary>
/// 配列の開始地点を示すイテレーターを返す
/// </summary>
/// <returns></returns>
vector<VertexIndex>::const_iterator VertexIndexCollection::begin ()
{
    return m_indices.begin ();
}

/// <summary>
/// 配列の終了地点を示すイテレーターを返す
/// </summary>
/// <returns></returns>
vector<VertexIndex>::const_iterator VertexIndexCollection::end ()
{
    return m_indices.end ();
}

/// <summary>
/// 配列要素を全て削除
/// </summary>
void VertexIndexCollection::clear () {
    m_indices.clear ();
}

/// <summary>
/// 配列の要素数を返す
/// </summary>
/// <returns></returns>
size_t VertexIndexCollection::size () {
    return m_indices.size ();
}

/// <summary>
/// targetPosの位置に配列を挿入する
/// </summary>
/// <param name="targetPos">挿入先</param>
/// <param name="begin">挿入する配列の開始地点</param>
/// <param name="end">挿入する配列の終了地点</param>
/// <returns></returns>
typename vector<VertexIndex>::const_iterator VertexIndexCollection::insert (
    typename vector<VertexIndex>::const_iterator targetPos,
    typename vector<VertexIndex>::const_iterator begin,
    typename vector<VertexIndex>::const_iterator end
)
{
    return m_indices.insert (targetPos, begin, end);
}
