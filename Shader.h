#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void bind() const = 0;
	virtual void release() const = 0;

	virtual void setInt(const std::string& name, int value) = 0;
	virtual void setIntArray(const std::string& name, int* values, uint32_t count) = 0;
	virtual void setFloat(const std::string& name, float value) = 0;
	virtual void setVec2(const std::string& name, const glm::vec2& value) = 0;
	virtual void setVec3(const std::string& name, const glm::vec3& value) = 0;
	virtual void setVec4(const std::string& name, const glm::vec4& value) = 0;
	virtual void setMat3(const std::string& name, const glm::mat3& matrix) = 0;
	virtual void setMat4(const std::string& name, const glm::mat4& matrix) = 0;

protected:
	enum class HandleType
	{
		Vertex = 0,
		Fragment,
		Program
	};
};

