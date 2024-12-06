#include "GLShader.h"

#include <stdexcept>

#include "File.hpp"

GLShader::GLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	std::string vsString = readShaderFile(vertexShaderPath);
	std::string fsString = readShaderFile(fragmentShaderPath);

	const char* vsSource = vsString.c_str();
	const char* fsSource = fsString.c_str();

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vertexShader, 1, &vsSource, nullptr);
	glCompileShader(m_vertexShader);

	glShaderSource(m_fragmentShader, 1, &fsSource, nullptr);
	glCompileShader(m_fragmentShader);

	m_program = glCreateProgram();

	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
}

GLShader::~GLShader()
{
	GLShader::release();
	glDeleteProgram(m_program);
}

void GLShader::bind() const
{
	if (isShaderProgramCompiled())
	{
		glUseProgram(m_program);
		return;
	}

	glLinkProgram(m_program);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);

	if (!isShaderProgramCompiled())
	{
		throw std::runtime_error("Shader program is not compiled");
	}

	glUseProgram(m_program);
}

void GLShader::release() const
{
	glUseProgram(0);
}

void GLShader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void GLShader::setIntArray(const std::string& name, int* values, uint32_t count)
{
	glUniform1iv(glGetUniformLocation(m_program, name.c_str()), static_cast<int>(count), values);
}

void GLShader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

void GLShader::setVec2(const std::string& name, const glm::vec2& value)
{
	glUniform2f(glGetUniformLocation(m_program, name.c_str()), value.x, value.y);
}

void GLShader::setVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(m_program, name.c_str()), value.x, value.y, value.z);
}

void GLShader::setVec4(const std::string& name, const glm::vec4& value)
	//m_modelShaderProgram->disableAttributeArray(2);
{
	glUniform4f(glGetUniformLocation(m_program, name.c_str()), value.x, value.y, value.z, value.w);
}

void GLShader::setMat3(const std::string& name, const glm::mat3& matrix)
{
	glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void GLShader::setMat4(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

int GLShader::attributeLocation(const std::string& attributeName) const
{
	return glGetAttribLocation(m_program, attributeName.c_str());
}

void GLShader::enableAttributeArray(const int attributeLocation) const
{
	glEnableVertexAttribArray(attributeLocation);
}

void GLShader::disableAttributeArray(const int attributeLocation) const
{
	return glDisableVertexAttribArray(attributeLocation);
}

void GLShader::setAttributeBuffer(const int attributeLocation,
                                  const int size,
                                  const GLenum& type,
                                  GLsizei stride,
                                  const void* pointer) const
{
	glVertexAttribPointer(attributeLocation, size, type, GL_FALSE, stride, pointer);
}

bool GLShader::isHandleCompiled(const GLuint handle, const HandleType& handleType) const
{
	int success;
	char infoLog[1024];
	if (handleType != HandleType::Program)
	{
		glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(handle, 1024, nullptr, infoLog);
			return false;
		}
	}
	else
	{
		glGetProgramiv(handle, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(handle, 1024, nullptr, infoLog);
			return false;
		}
	}

	return true;
}

bool GLShader::isShaderProgramCompiled() const
{
	bool isShaderCompiledSuccess = true;

	isShaderCompiledSuccess &= isHandleCompiled(m_vertexShader, HandleType::Vertex);
	isShaderCompiledSuccess &= isHandleCompiled(m_fragmentShader, HandleType::Fragment);
	isShaderCompiledSuccess &= isHandleCompiled(m_program, HandleType::Program);

	return isShaderCompiledSuccess;
}
