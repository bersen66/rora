#include <rora/graphics/rendering/vertex_array.hpp>
#include <algorithm>

namespace graphics
{


VertexArray::VertexArray(VertexArray&& other) noexcept
	: vao_descriptor_(other.vao_descriptor_)
	, vbo_descriptor_(other.vbo_descriptor_)
	, ebo_descriptor_(other.ebo_descriptor_)
	, attributes_number_(other.attributes_number_)
	, is_valid_(true)
{
	other.is_valid_ = false;
}

VertexArray::VertexArray(int size)
	: attributes_number_(size)
	, is_valid_(true)
{
	glGenVertexArrays(size, &vao_descriptor_);
	glGenBuffers(size, &vbo_descriptor_);
	glGenBuffers(size, &ebo_descriptor_);
}

VertexArray::~VertexArray()
{
	if (!is_valid_)
	{
		glDeleteBuffers(attributes_number_, &vbo_descriptor_);
		glDeleteVertexArrays(attributes_number_, &vao_descriptor_);
		glDeleteBuffers(attributes_number_, &ebo_descriptor_);
	}
}

void VertexArray::LoadVertexBufferData(const void* data_ptr, std::size_t size)
{
	glBindVertexArray(vao_descriptor_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_descriptor_);

	glBufferData(GL_ARRAY_BUFFER, size, data_ptr, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::LoadIndexBufferData(const void* data_ptr, std::size_t size)
{
	glBindVertexArray(vao_descriptor_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_descriptor_);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data_ptr, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int VertexArrayBuilder::ComputeStride() const
{
	int result = 0;

	std::for_each(
		attributes_.begin(),
		attributes_.end(),
		[&result](const VertexAttribute& attr) {
			result += attr.size * details::gl_sizeof(attr.gl_type);
		}
	);

	return  result;
}

void VertexArrayBuilder::ApplyAttributeLayout(VertexArray& result)
{
	glBindVertexArray(result.vao_descriptor_);
	glBindBuffer(GL_ARRAY_BUFFER, result.vbo_descriptor_);
	
	int stride = ComputeStride();
	std::size_t offset = 0;
	for (int current_location_idx = 0; current_location_idx < attributes_.size(); current_location_idx++)
	{
		const VertexAttribute& attrib = attributes_[current_location_idx];
		
		glVertexAttribPointer(
			current_location_idx,
			attrib.size,
			attrib.gl_type,
			attrib.need_normalization ? GL_TRUE : GL_FALSE,
			stride,
			(const GLvoid*)offset
		);
		glEnableVertexAttribArray(current_location_idx);

		offset += attrib.size * details::gl_sizeof(attrib.gl_type);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArray VertexArrayBuilder::Build()
{

	VertexArray result;
	ApplyAttributeLayout(result);
	ResetAttributes();
	return result;
}

void VertexArrayBuilder::ResetAttributes()
{
	attributes_.clear();
}

} // namespace graphics
