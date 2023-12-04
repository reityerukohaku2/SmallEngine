#include "pch.h"
#include "VertexCollection.h"

VertexCollection::VertexCollection (vector<Vertex> vertices) {
    m_vertices = vertices;
}

/// <summary>
/// �z��̖����ɗv�f��ǉ�����
/// </summary>
void VertexCollection::push_back (Vertex vertex)
{
    m_vertices.push_back (vertex);
}

/// <summary>
/// �z��v�f�̐擪�|�C���^��Ԃ�
/// </summary>
/// <returns>�z��̐擪�|�C���^</returns>
Vertex* VertexCollection::data ()
{
    return m_vertices.data();
}

/// <summary>
/// �z��̊J�n�n�_�������C�e���[�^�[��Ԃ�
/// </summary>
/// <returns></returns>
vector<Vertex>::const_iterator VertexCollection::begin ()
{
    return m_vertices.begin();
}

/// <summary>
/// �z��̏I���n�_�������C�e���[�^�[��Ԃ�
/// </summary>
/// <returns></returns>
vector<Vertex>::const_iterator VertexCollection::end ()
{
    return m_vertices.end ();
}

/// <summary>
/// �z��v�f��S�č폜
/// </summary>
void VertexCollection::clear () {
    m_vertices.clear ();
}

/// <summary>
/// �z��̗v�f����Ԃ�
/// </summary>
/// <returns></returns>
size_t VertexCollection::size () {
    return m_vertices.size ();
}

/// <summary>
/// �v���~�e�B�u�^�z��ɂ������_�z���Ԃ�
/// </summary>
/// <returns>�v���~�e�B�u�^�z��ɂ������_�z��</returns>
vector<XMFLOAT3> VertexCollection::GetArrayOfXMFLOAT3Position ()
{
    vector<XMFLOAT3> positions;

    for (auto vertex:m_vertices) {
        auto vectorPos = vertex.GetXMVECTORPosition();
        shared_ptr<XMFLOAT3> float3Pos = make_shared<XMFLOAT3>();
        XMStoreFloat3(float3Pos.get(), vectorPos);
        positions.push_back (*float3Pos);
    }

    return positions;
}

/// <summary>
/// targetPos�̈ʒu�ɔz���}������
/// </summary>
/// <param name="targetPos">�}����</param>
/// <param name="begin">�}������z��̊J�n�n�_</param>
/// <param name="end">�}������z��̏I���n�_</param>
/// <returns></returns>
typename vector<Vertex>::const_iterator VertexCollection::insert (
    typename vector<Vertex>::const_iterator targetPos, 
    typename vector<Vertex>::const_iterator begin, 
    typename vector<Vertex>::const_iterator end
)
{
    return m_vertices.insert (targetPos, begin, end);
}

/// <summary>
/// �z��S�̂̃o�C�g����Ԃ�
/// </summary>
/// <returns></returns>
UINT VertexCollection::GetVerticesSize ()
{
    return m_vertices.size() * sizeof(Vertex);
}
