#include "pch.h"
#include "VertexIndexCollection.h"

VertexIndexCollection::VertexIndexCollection (vector<VertexIndex> indices) {
    m_indices = indices;
}

/// <summary>
/// �z��̖����ɗv�f��ǉ�����
/// </summary>
void VertexIndexCollection::push_back (VertexIndex vertex)
{
    m_indices.push_back (vertex);
}

/// <summary>
/// �z��v�f�̐擪�|�C���^��Ԃ�
/// </summary>
/// <returns>�z��̐擪�|�C���^</returns>
VertexIndex* VertexIndexCollection::data ()
{
    return m_indices.data ();
}

/// <summary>
/// �z��̊J�n�n�_�������C�e���[�^�[��Ԃ�
/// </summary>
/// <returns></returns>
vector<VertexIndex>::const_iterator VertexIndexCollection::begin ()
{
    return m_indices.begin ();
}

/// <summary>
/// �z��̏I���n�_�������C�e���[�^�[��Ԃ�
/// </summary>
/// <returns></returns>
vector<VertexIndex>::const_iterator VertexIndexCollection::end ()
{
    return m_indices.end ();
}

/// <summary>
/// �z��v�f��S�č폜
/// </summary>
void VertexIndexCollection::clear () {
    m_indices.clear ();
}

/// <summary>
/// �z��̗v�f����Ԃ�
/// </summary>
/// <returns></returns>
size_t VertexIndexCollection::size () {
    return m_indices.size ();
}

/// <summary>
/// targetPos�̈ʒu�ɔz���}������
/// </summary>
/// <param name="targetPos">�}����</param>
/// <param name="begin">�}������z��̊J�n�n�_</param>
/// <param name="end">�}������z��̏I���n�_</param>
/// <returns></returns>
typename vector<VertexIndex>::const_iterator VertexIndexCollection::insert (
    typename vector<VertexIndex>::const_iterator targetPos,
    typename vector<VertexIndex>::const_iterator begin,
    typename vector<VertexIndex>::const_iterator end
)
{
    return m_indices.insert (targetPos, begin, end);
}
