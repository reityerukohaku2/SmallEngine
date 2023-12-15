#pragma once
#include "pch.h"
#include "Geometry.h"
#include "VertexIndex.h"

/// <summary>
/// Geometryの配列
/// </summary>
class GeometryCollection : private vector<Geometry>
{
public:

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
	vector<Vertex> GetVertices ();

	/// <summary>
	/// 頂点のバイト数を返す
	/// </summary>
	/// <returns></returns>
	UINT GetVerticesSize ();

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
	// vectorクラスの関数		
	//***************************/

	using vector::push_back;
	using vector::data;
	using vector::begin;
	using vector::end;
	using vector::insert;
	using vector::size;
	using vector::clear;

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
	/// 全頂点数
	/// </summary>
	UINT m_vertexNum;

	/// <summary>
	/// 頂点インデックス数
	/// </summary>
	UINT m_indexNum;
};

