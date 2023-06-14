#include <rora/graphics/rendering/shaders/shader.h>

#include <fstream>


namespace graphics
{

ShaderProgram::ShaderProgram()
	: descriptor_(glCreateProgram())
{}


GLuint ShaderProgram::Descriptor()
{
	return descriptor_;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(descriptor_);
}


void Link(ShaderProgram& program)
{
	glLinkProgram(program.Descriptor());
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

} // namespace graphics

