#include "pch.h"
#include "GeometryCollection.h"


UINT GeometryCollection::GetVertexNum ()
{
    UINT vertexNum = 0;
    for (auto geometry: *this) {
        vertexNum += geometry.GetVertexNum ();
    }

    return vertexNum;
}

UINT GeometryCollection::GetGeometriesSize ()
{
    return this->GetVertexNum () * sizeof(Vertex);
}

/// <summary>
/// ‘S‚Ä‚Ì’¸“_î•ñ‚ğæ“¾‚·‚é
/// </summary>
vector<Vertex> GeometryCollection::GetVertices ()
{
    vector<Vertex> allVertices;
    for (auto geometry : *this) {
        auto vertices = geometry.GetVertices ();
        copy (vertices.begin (), vertices.end (), back_inserter (allVertices));
    }

    return allVertices;
}

