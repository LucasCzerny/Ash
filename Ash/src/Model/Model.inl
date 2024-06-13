namespace Ash
{
	template <typename IndexType>
	void Model::LoadIndices(tinygltf::Primitive& primitive, uint32_t indexStart, std::vector<uint32_t>&indices, size_t* countOut)
	{
		const tinygltf::Accessor& accessor = m_Model.accessors[primitive.indices];
		const tinygltf::BufferView& bufferView = m_Model.bufferViews[accessor.bufferView];
		const tinygltf::Buffer& buffer = m_Model.buffers[bufferView.buffer];

		if (countOut)
		{
			*countOut = accessor.count;
		}

		const IndexType* indexPointer = (const IndexType*)&buffer.data[accessor.byteOffset + bufferView.byteOffset];

		for (size_t i = 0; i < accessor.count; i++)
		{
			indices.push_back(indexStart + indexPointer[i]);
		}
	}
}