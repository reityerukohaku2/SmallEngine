#include "pch.h"
#include "VertexIndex.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="indices">���_�C���f�b�N�X</param>
VertexIndex::VertexIndex (vector<DWORD> indices) {
	m_indices = indices;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
VertexIndex::~VertexIndex (){}

/// <summary>
/// ���_�C���f�b�N�X�̃o�C�g����Ԃ�
/// </summary>
/// <returns>���_�C���f�b�N�X�̃o�C�g��</returns>
UINT VertexIndex::GetIndicesSize () 
{
	return m_indices.size () * sizeof (DWORD);
}

/// <summary>
/// �z��̖����ɗv�f��ǉ�����
/// </summary>
/// <param name="index">�ǉ�����v�f</param>
void VertexIndex::push_back (DWORD index)
{
    m_indices.push_back (index);
}

/// <summary>
/// �z��̐擪�|�C���^��Ԃ�
/// </summary>
/// <returns>�z��̐擪�|�C���^</returns>
DWORD* VertexIndex::data () {
    return m_indices.data ();
}

/// <summary>
/// �z��̏I���n�_�������C�e���[�^�[��Ԃ�
/// </summary>
/// <returns></returns>
typename vector<DWORD>::const_iterator VertexIndex::end () {
    return m_indices.end ();
}

typename vector<DWORD>::const_iterator VertexIndex::begin ()
{
    return m_indices.begin ();
}

/// <summary>
/// targetPos�̈ʒu�ɔz���}������
/// </summary>
/// <param name="targetPos">�}����</param>
/// <param name="begin">�}������z��̊J�n�n�_</param>
/// <param name="end">�}������z��̏I���n�_</param>
/// <returns></returns>
typename vector<DWORD>::const_iterator VertexIndex::insert
(
    typename vector<DWORD>::const_iterator targetPos,
    typename vector<DWORD>::const_iterator begin,
    typename vector<DWORD>::const_iterator end
) {
    return m_indices.insert (targetPos, begin, end);
}

/// <summary>
/// �z��̗v�f����Ԃ�
/// </summary>
/// <returns></returns>
size_t VertexIndex::size ()
{
    return m_indices.size ();
}

/// <summary>
/// �z��v�f��S�č폜
/// </summary>
void VertexIndex::clear ()
{
    m_indices.clear ();
}

