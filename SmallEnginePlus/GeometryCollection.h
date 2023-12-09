#pragma once
#include "pch.h"
#include "Geometry.h"
#include "VertexIndex.h"
#include "VertexCollection.h"
#include "ICollection.h"

/// <summary>
/// Geometryの配列
/// </summary>
class GeometryCollection : public ICollection<class Geometry>
{
public:
	GeometryCollection () {};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="geometries">Geometryの配列</param>
	GeometryCollection (vector<Geometry> geometries);

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

	/// <summary>
	/// 全ての頂点インデックスを取得する
	/// </summary>
	/// <returns></returns>
	VertexIndex GetIndices ();

	/// <summary>
	/// 頂点インデックスのバイト数を返す
	/// </summary>
	/// <returns>頂点インデックスのバイト数</returns>
	UINT GetIndicesSize ();

	/// <summary>
	/// 頂点インデックスの数を返す
	/// </summary>
	/// <returns>頂点インデックスの数</returns>
	UINT GetIndexNum ();



	//***************************/
	// ICollectionの純粋仮想関数
	//***************************/

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
	/// targetPosの位置に配列を挿入する
	/// </summary>
	/// <param name="targetPos">挿入先</param>
	/// <param name="begin">挿入する配列の開始地点</param>
	/// <param name="end">挿入する配列の終了地点</param>
	/// <returns></returns>
	typename vector<Geometry>::const_iterator insert 
	(
		typename vector<Geometry>::const_iterator targetPos, 
		typename vector<Geometry>::const_iterator begin, 
		typename vector<Geometry>::const_iterator end
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
	/// 頂点数再計算用関数
	/// </summary>
	/// <returns>全頂点数</returns>
	UINT CountVertexNum ();

	/// <summary>
	/// 頂点インデックス数再計算用関数
	/// </summary>
	/// <returns>全頂点インデックス数</returns>
	UINT CountIndexNum ();

	/// <summary>
	/// 形状の配列
	/// </summary>
	vector<Geometry> m_geometries;

	/// <summary>
	/// 全頂点数
	/// </summary>
	UINT m_vertexNum;

	/// <summary>
	/// 頂点インデックス数
	/// </summary>
	UINT m_indexNum;
};

