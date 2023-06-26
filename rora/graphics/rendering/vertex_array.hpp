#pragma once

#include <glad/glad.h>
#include <vector>

#include <rora/graphics/rendering/details/casts.hpp>


namespace graphics
{

class VertexArrayBuilder;
class Environment;

class VertexArray
{
public:
	friend VertexArrayBuilder;
	friend Environment;

public:
	void LoadVertexBufferData(const void* data_ptr, std::size_t size);

	void LoadIndexBufferData(const void* data_ptr, std::size_t size);

	~VertexArray();
	VertexArray(const VertexArray& other) = delete;
	VertexArray& operator=(const VertexArray& other) = delete;
	VertexArray(VertexArray&&) noexcept;

private:
	VertexArray(int size = 1);

private:
	GLuint vao_descriptor_;
	GLuint vbo_descriptor_;
	GLuint ebo_descriptor_;
	int attributes_number_;
	bool is_valid_;
};

class VertexArrayBuilder
{
public:
	VertexArray Build();

	template<typename T>
	void AddVertexAttribute(int size, bool need_normalization=false)
	{
		constexpr int gl_type = details::gl_type_of<T>();
		static_assert(gl_type, "VertexArrayBuilder::AddVertexAttribute called with invalid attribute type");

		attributes_.push_back(
			VertexAttribute{
				.gl_type=gl_type,
				.need_normalization=need_normalization,
				.size=size
			}
		);
	}

	void ResetAttributes();

private:
	struct VertexAttribute
	{
		int gl_type;
		bool need_normalization;
		int size;
	};

	int ComputeStride() const;

	void ApplyAttributeLayout(VertexArray&);
private:
	::std::vector<VertexAttribute> attributes_;
};


} // namespace graphics