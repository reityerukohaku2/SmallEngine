#pragma once
#include "pch.h"
#include "Geometry.h"
#include "VertexCollection.h"
#include "ICollection.h"

/// <summary>
/// Geometryの配列
/// </summary>
class GeometryCollection : public ICollection<Geometry>
{
public:
	GeometryCollection () {};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="geometries">Geometryの配列</param>
	GeometryCollection (vector<Geometry> geometries);

	/// <summary>
	/// 配列の末尾に要素を追加する
	/// </summary>
	/// <param name="geometry">追加する要素</param>
	void push_back (Geometry geometry);

	/// <summary>
	/// 配列の先頭ポインタを返す
	/// </summary>
	/// <returns>配列の先頭ポインタ</returns>
	Geometry* data ();

	/// <summary>
	/// 配列の開始地点を示すイテレーターを返す
	/// </summary>
	/// <returns></returns>
	typename vector<Geometry>::const_iterator begin ();

	/// <summary>
	/// 配列の終了地点を示すイテレーターを返す
	/// </summary>
	/// <returns></returns>
	typename vector<Geometry>::const_iterator end ();

	/// <summary>
	/// 配列の要素数を返す
	/// </summary>
	/// <returns></returns>
	size_t size ();

	/// <summary>
	/// 配列要素を全て削除
	/// </summary>
	void clear ();

	/// <summary>
	/// 形状内に存在する全ての頂点数を返す
	/// </summary>
	/// <returns>形状内に存在する全ての頂点数</returns>
	UINT GetVertexNum ();

	/// <summary>
	/// 形状のバイト数を返す
	/// </summary>
	/// <returns></returns>
	UINT GetGeometriesSize ();

	/// <summary>
	/// 全ての頂点情報を取得する
	/// </summary>
	VertexCollection GetVertices ();

private:
	vector<Geometry> m_geometries;
};

