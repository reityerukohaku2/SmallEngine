#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include "pch.h"

using namespace DirectX;
using namespace std;
using winrt::com_ptr;
using std::shared_ptr;

/// <summary>
/// 頂点情報を持つクラス
/// </summary>
class Vertex
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Vertex ();

	/// <summary>
	/// 複数の頂点座標から頂点情報の配列を生成する
	/// </summary>
	/// <param name="positions">頂点座標群</param>
	/// <returns>頂点情報の配列</returns>
	static vector<shared_ptr<Vertex>> CreateVerticesFromXMFloat3Array (vector<shared_ptr<XMFLOAT3>> positions);
private:
	/// <summary>
	/// 頂点座標
	/// </summary>
	XMFLOAT3 m_pos;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">頂点位置</param>
	Vertex (XMFLOAT3 pos);
};
