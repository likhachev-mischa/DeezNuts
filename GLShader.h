#pragma once

#include <glad/glad.h>

#include "Shader.h"

class GLShader : public Shader
{
public:
	GLShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~GLShader() override;

	void bind() const override;
	void release() const override;

	void setInt(const std::string& name, int value) override;
	void setIntArray(const std::string& name, int* values, uint32_t count) override;
	void setFloat(const std::string& name, float value) override;
	void setVec2(const std::string& name, const glm::vec2& value) override;
	void setVec3(const std::string& name, const glm::vec3& value) override;
	void setVec4(const std::string& name, const glm::vec4& value) override;
	void setMat3(const std::string& name, const glm::mat3& matrix) override;
	void setMat4(const std::string& name, const glm::mat4& matrix) override;

	int attributeLocation(const std::string& attributeName) const;
	void enableAttributeArray(const int attributeLocation) const;
	void disableAttributeArray(const int attributeLocation) const;
	void setAttributeBuffer(const int attributeLocation,
	                        const int size,
	                        const GLenum& type,
	                        GLsizei stride,
	                        const void* pointer) const;

private:
	GLuint m_vertexShader;
	GLuint m_fragmentShader;

	GLuint m_program;

	bool isHandleCompiled(const GLuint handle, const HandleType& handleType) const;

	bool isShaderProgramCompiled() const;
};
