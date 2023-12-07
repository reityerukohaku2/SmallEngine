#pragma once
#include "pch.h"
#include "ICollection.h"
#include "VertexIndex.h"

class VertexIndexCollection : public ICollection<class VertexIndex>
{
public:
	VertexIndexCollection () {};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="geometries">VertexIndexの配列</param>
	VertexIndexCollection (vector<VertexIndex> indices);

	/// <summary>
	/// 配列の末尾に要素を追加する
	/// </summary>
	/// <param name="geometry">追加する要素</param>
	void push_back (VertexIndex index);

	/// <summary>
	/// 配列の先頭ポインタを返す
	/// </summary>
	/// <returns>配列の先頭ポインタ</returns>
	VertexIndex* data ();

	/// <summary>
	/// 配列の開始地点を示すイテレーターを返す
	/// </summary>
	/// <returns></returns>
	typename vector<VertexIndex>::const_iterator begin ();

	/// <summary>
	/// 配列の終了地点を示すイテレーターを返す
	/// </summary>
	/// <returns></returns>
	typename vector<VertexIndex>::const_iterator end ();

	/// <summary>
	/// targetPosの位置に配列を挿入する
	/// </summary>
	/// <param name="targetPos">挿入先</param>
	/// <param name="begin">挿入する配列の開始地点</param>
	/// <param name="end">挿入する配列の終了地点</param>
	/// <returns></returns>
	typename vector<VertexIndex>::const_iterator insert
	(
		typename vector<VertexIndex>::const_iterator targetPos,
		typename vector<VertexIndex>::const_iterator begin,
		typename vector<VertexIndex>::const_iterator end
	);

	/// <summary>
	/// 配列の要素数を返す
	/// </summary>
	/// <returns></returns>
	size_t size ();

	/// <summary>
	/// 配列要素を全て削除
	/// </summary>
	void clear ();

private:
	/// <summary>
	/// 形状の配列
	/// </summary>
	vector<VertexIndex> m_indices;
};

