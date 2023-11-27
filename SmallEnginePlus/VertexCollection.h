#pragma once
#include "pch.h"
#include "Vertex.h"
#include "ICollection.h"

/// <summary>
/// Vertexの配列
/// </summary>
class VertexCollection: public ICollection<Vertex>
{
public:
	VertexCollection () {};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="vertices">頂点配列</param>
	VertexCollection (vector<Vertex> vertices);

	/// <summary>
	/// 配列の末尾に要素を追加する
	/// </summary>
	void push_back (Vertex vertex);

	/// <summary>
	/// 配列要素の先頭ポインタを返す
	/// </summary>
	/// <returns>配列の先頭ポインタ</returns>
	Vertex* data ();

	/// <summary>
	/// 配列の開始地点を示すイテレーターを返す
	/// </summary>
	/// <returns></returns>
	typename vector<Vertex>::const_iterator begin ();

	/// <summary>
	/// 配列の終了地点を示すイテレーターを返す
	/// </summary>
	/// <returns></returns>
	typename vector<Vertex>::const_iterator end ();

	/// <summary>
	/// 配列要素を全て削除
	/// </summary>
	void clear ();

	/// <summary>
	/// 配列の要素数を返す
	/// </summary>
	size_t size ();

	/// <summary>
	/// プリミティブ型配列にした頂点配列を返す
	/// </summary>
	/// <returns>プリミティブ型配列にした頂点配列</returns>
	vector<XMFLOAT3> GetArrayOfXMFLOAT3Position ();

private:
	vector<Vertex> m_vertices;
};

