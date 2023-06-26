#include <rora/graphics/rendering/shader.hpp>

#include <fstream>


namespace graphics
{

ShaderProgram::ShaderProgram()
	: descriptor_(glCreateProgram())
{}


GLuint ShaderProgram::Descriptor() const
{
	return descriptor_;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(descriptor_);
}

GLint ShaderProgram::UniformLocation(const GLchar* uniform_name)
{
	std::map<std::string, GLint>::iterator uniform_it = uniforms_.find(uniform_name);
	if (uniform_it == uniforms_.end())
	{
		uniforms_[uniform_name] = glGetUniformLocation(descriptor_, uniform_name);
	}
	return uniforms_[uniform_name];
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec2& v)
{
	GLint location = UniformLocation(name);
	glUniform2f(location, v.x, v.y);
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec3& v)
{
	GLint location = UniformLocation(name);
	glUniform3f(location, v.x, v.y, v.z);
}

void ShaderProgram::SetUniform(const GLchar* name, const glm::vec4& v)
{
	GLint location = UniformLocation(name);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}


void Link(ShaderProgram& program)
{
	int link_status = 0;
	glLinkProgram(program.Descriptor());
	glGetProgramiv(program.Descriptor(), GL_LINK_STATUS, &link_status);
	if (link_status == GL_FALSE)
	{
		throw std::runtime_error(GetInfoMessage(program));
	}
}

std::string LoadShaderText(const std::string& path)
{
	std::ifstream in{ path };
	return { std::istreambuf_iterator<char>{ in }, std::istreambuf_iterator<char>{} };
}

ShaderProgram PrepareProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_paths)
{
	ShaderProgram result;
	auto vss = PrepareShader<GL_VERTEX_SHADER>(vertex_shader_path);
	auto fss = PrepareShader<GL_FRAGMENT_SHADER>(fragment_shader_paths);
	result.AttachShader(vss)
		  .AttachShader(fss);
	Link(result);
	return result;
}

std::string GetInfoMessage(ShaderProgram& program)
{
	GLint message_len = 0;
	glGetProgramiv(program.Descriptor(), GL_INFO_LOG_LENGTH, &message_len);
	std::string result;
	result.reserve(message_len);
	glGetProgramInfoLog(program.Descriptor(), message_len, &message_len, result.data());
	return result;
	
}

} // namespace graphics

