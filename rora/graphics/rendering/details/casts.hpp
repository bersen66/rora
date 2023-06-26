#pragma once


#include <glad/glad.h>
#include <type_traits>

namespace graphics::details
{

template<typename T>
constexpr int gl_type_of()
{
	if constexpr (std::is_same_v<T, int>)
	{
		return GL_INT;
	} 
	else if constexpr (std::is_same_v<T, float>)
	{
		return GL_FLOAT;
	}
	else if constexpr (std::is_same_v<T, double>)
	{
		return GL_DOUBLE;
	}
	else if constexpr (std::is_same_v<T, bool>)
	{
		return GL_BOOL;
	}

	return 0;
}

constexpr std::size_t gl_sizeof(int type)
{
	if (type == GL_INT)
	{
		return sizeof(int);
	}
	else if (type == GL_FLOAT)
	{
		return sizeof(float);
	}
	else if  (type == GL_DOUBLE)
	{
		return sizeof(double);
	}
	else if (type == GL_BOOL)
	{
		return sizeof(bool);
	}
	return 0;
}

} // namespace graphics::details