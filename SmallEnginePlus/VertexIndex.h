#pragma once
#include "pch.h"
#include "ICollection.h"

/// <summary>
/// 頂点インデックス
/// </summary>
class VertexIndex: private vector<DWORD>
{
public:
	VertexIndex () {}
	VertexIndex (vector<DWORD> &&indicecsData);

	/// <summary>
	/// 頂点インデックスのバイト数を返す
	/// </summary>
	/// <returns>頂点インデックスのバイト数</returns>
	UINT GetIndicesSize ();


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
	using vector::reserve;
};
