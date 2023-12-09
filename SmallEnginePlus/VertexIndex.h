#pragma once
#include "pch.h"
#include "ICollection.h"

/// <summary>
/// 頂点インデックス
/// </summary>
class VertexIndex: public ICollection<DWORD>
{
public:
	VertexIndex () {};
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="indices">頂点インデックス</param>
	VertexIndex (vector<DWORD> indices);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~VertexIndex ();

	/// <summary>
	/// 頂点インデックスのバイト数を返す
	/// </summary>
	/// <returns>頂点インデックスのバイト数</returns>
	UINT GetIndicesSize ();

	//***************************/
	// ICollectionの純粋仮想関数
	//***************************/

	/// <summary>
	/// 配列の末尾に要素を追加する
	/// </summary>
	/// <param name="geometry">追加する要素</param>
	void push_back (DWORD geometry);

	/// <summary>
	/// 配列の先頭ポインタを返す
	/// </summary>
	/// <returns>配列の先頭ポインタ</returns>
	DWORD* data ();

	/// <summary>
	/// 配列の開始地点を示すイテレーターを返す
	/// </summary>
	/// <returns></returns>
	typename vector<DWORD>::const_iterator begin ();

	/// <summary>
	/// 配列の終了地点を示すイテレーターを返す
	/// </summary>
	/// <returns></returns>
	typename vector<DWORD>::const_iterator end ();

	/// <summary>
	/// targetPosの位置に配列を挿入する
	/// </summary>
	/// <param name="targetPos">挿入先</param>
	/// <param name="begin">挿入する配列の開始地点</param>
	/// <param name="end">挿入する配列の終了地点</param>
	/// <returns></returns>
	typename vector<DWORD>::const_iterator insert
	(
		typename vector<DWORD>::const_iterator targetPos,
		typename vector<DWORD>::const_iterator begin,
		typename vector<DWORD>::const_iterator end
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
	/// 頂点インデックス
	/// </summary>
	vector<DWORD> m_indices;
};
