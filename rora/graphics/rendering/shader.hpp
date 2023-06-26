#pragma once

#include <glad/glad.h>

#include <fstream>
#include <glm/glm.hpp>


#include <string>
#include <map>


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

template<GLenum ShaderType>
std::string GetInfoMessage(const Shader<ShaderType>& shader)
{
	GLint message_len = 0;
	glGetShaderiv(shader.Descriptor(), GL_INFO_LOG_LENGTH, &message_len);
	std::string result;
	result.reserve(message_len);
	glGetShaderInfoLog(shader.Descriptor(), message_len, &message_len, result.data());
	return result;
}




template<GLuint Type>
void Compile(const Shader<Type>& shader)
{
	int compilation_status = 0;
	glCompileShader(shader.Descriptor());
	glGetShaderiv(shader.Descriptor(), GL_COMPILE_STATUS, &compilation_status);
	if (compilation_status == GL_FALSE)
	{
		throw std::runtime_error( GetInfoMessage(shader));
	}
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


	void SetUniform(const GLchar* name, const glm::vec2& v);
	void SetUniform(const GLchar* name, const glm::vec3& v);
	void SetUniform(const GLchar* name, const glm::vec4& v);

private:
	GLint UniformLocation(const GLchar* uniform_name);
private:
	GLuint descriptor_;
	std::map<std::string, GLint> uniforms_;
};


void Link(ShaderProgram& program);

ShaderProgram PrepareProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_paths);

std::string GetInfoMessage(ShaderProgram& program);
} // namespace graphics

