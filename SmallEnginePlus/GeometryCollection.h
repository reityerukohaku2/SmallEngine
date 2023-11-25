#pragma once
#include "pch.h"
#include "Geometry.h"

class GeometryCollection:public vector<Geometry>
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
};

