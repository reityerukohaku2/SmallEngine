#include "pch.h"
#include "VertexIndex.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="indices">頂点インデックス</param>
VertexIndex::VertexIndex (vector<DWORD> indices) {
	m_indices = indices;
}

/// <summary>
/// デストラクタ
/// </summary>
VertexIndex::~VertexIndex (){}

/// <summary>
/// 頂点インデックスのバイト数を返す
/// </summary>
/// <returns>頂点インデックスのバイト数</returns>
UINT VertexIndex::GetIndicesSize () 
{
	return m_indices.size () * sizeof (DWORD);
}

/// <summary>
/// 配列の末尾に要素を追加する
/// </summary>
/// <param name="index">追加する要素</param>
void VertexIndex::push_back (DWORD index)
{
    m_indices.push_back (index);
}

/// <summary>
/// 配列の先頭ポインタを返す
/// </summary>
/// <returns>配列の先頭ポインタ</returns>
DWORD* VertexIndex::data () {
    return m_indices.data ();
}

/// <summary>
/// 配列の終了地点を示すイテレーターを返す
/// </summary>
/// <returns></returns>
typename vector<DWORD>::const_iterator VertexIndex::end () {
    return m_indices.end ();
}

typename vector<DWORD>::const_iterator VertexIndex::begin ()
{
    return m_indices.begin ();
}

/// <summary>
/// targetPosの位置に配列を挿入する
/// </summary>
/// <param name="targetPos">挿入先</param>
/// <param name="begin">挿入する配列の開始地点</param>
/// <param name="end">挿入する配列の終了地点</param>
/// <returns></returns>
typename vector<DWORD>::const_iterator VertexIndex::insert
(
    typename vector<DWORD>::const_iterator targetPos,
    typename vector<DWORD>::const_iterator begin,
    typename vector<DWORD>::const_iterator end
) {
    return m_indices.insert (targetPos, begin, end);
}

/// <summary>
/// 配列の要素数を返す
/// </summary>
/// <returns></returns>
size_t VertexIndex::size ()
{
    return m_indices.size ();
}

/// <summary>
/// 配列要素を全て削除
/// </summary>
void VertexIndex::clear ()
{
    m_indices.clear ();
}

