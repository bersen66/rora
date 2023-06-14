#pragma once

#include <glad/glad.h>

#include <fstream>
#include <glm/glm.hpp>


#include <string>


namespace graphics
{

std::string LoadShaderText(const std::string& path);

template<GLenum Type>
class Shader
{
public:
	Shader(const char* source)
		: descriptor_(glCreateShader(Type))
		, source_(source)
	{
		glShaderSource(descriptor_, 1, &source, NULL);
	}

	Shader(const std::string& source)
		: descriptor_(glCreateShader(Type))
		, source_(source)
	{
		const char* src = source_.c_str();
		glShaderSource(descriptor_, 1, &src, NULL);
	}

	~Shader()
	{
		glDeleteShader(descriptor_);
	}

	GLuint Descriptor() const
	{
		return descriptor_;
	}

private:
	GLuint descriptor_;
	std::string source_;
};


template<GLuint Type>
void Compile(const Shader<Type>& shader)
{
	glCompileShader(shader.Descriptor());
}


template<GLuint Type>
Shader<Type> PrepareShader(const std::string& path)
{
	Shader<Type> result(LoadShaderText(path));
	Compile<Type>(result);
	return result;
}



class ShaderProgram
{
public:
	ShaderProgram();

	template<GLuint Type>
	ShaderProgram& AttachShader(const Shader<Type>& shader)
	{
		glAttachShader(descriptor_, shader.Descriptor());
		return *this;
	}

	GLuint Descriptor();

	~ShaderProgram();
private:
	GLuint descriptor_;
};


void Link(ShaderProgram& program);

ShaderProgram PrepareProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_paths);

} // namespace graphics

