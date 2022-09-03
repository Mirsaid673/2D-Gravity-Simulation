#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

Shader Shader::default_shader;

std::string get_file_contents(const char *filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw(errno);
}

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
	load(vertexFile, fragmentFile);
}

void Shader::load(const char *vertexFile, const char *fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char *vertexSource = vertexCode.c_str();
	const char *fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const
{
	glUseProgram(ID);
}

void Shader::destroy() const
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char *type) const
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n"
					  << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n"
					  << infoLog << std::endl;
		}
	}
}

template <>
void Shader::setScalar<int>(const char *name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

template <>
void Shader::setScalar<unsigned int>(const char *name, unsigned int value) const
{
	glUniform1ui(glGetUniformLocation(ID, name), value);
}

template <>
void Shader::setScalar<float>(const char *name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

template <>
void Shader::setScalar<double>(const char *name, double value) const
{
	glUniform1d(glGetUniformLocation(ID, name), value);
}

void Shader::setVec2(const char *name, float value1, float value2) const
{
	glUniform2f(glGetUniformLocation(ID, name), value1, value2);
}
void Shader::setVec2(const char *name, float *values) const
{
	glUniform2fv(glGetUniformLocation(ID, name), 1, values);
}
void Shader::setVec2(const char *name, const glm::vec2 &v) const
{
	glUniform2fv(glGetUniformLocation(ID, name), 1, &v.x);
}

void Shader::setVec3(const char *name, float value1, float value2, float value3) const
{
	glUniform3f(glGetUniformLocation(ID, name), value1, value2, value3);
}
void Shader::setVec3(const char *name, float *values) const
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, values);
}
void Shader::setVec3(const char *name, const glm::vec3 &v) const
{
	glUniform3fv(glGetUniformLocation(ID, name), 1, &v.x);
}

void Shader::setMat2(const char *name, float *m) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, m);
}

void Shader::setMat2(const char *name, const glm::mat2 &m) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setMat2x3(const char *name, float *m) const
{
	glUniformMatrix2x3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, m);
}

void Shader::setMat2x3(const char *name, const glm::mat2x3 &m) const
{
	glUniformMatrix2x3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setMat3x2(const char *name, float *m) const
{
	glUniformMatrix3x2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, m);
}

void Shader::setMat3x2(const char *name, const glm::mat3x2 &m) const
{
	glUniformMatrix3x2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setMat3(const char *name, float *m) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, m);
}

void Shader::setMat3(const char *name, const glm::mat3 &m) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setMat4(const char *name, float *m) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, m);
}

void Shader::setMat4(const char *name, const glm::mat4 &m) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setCamera(const Camera2D &c) const
{
	setMat3x2("v", c.transform.getMatrix());
	setMat4("p", c.getProjection());
}