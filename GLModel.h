#pragma once

#pragma once

#include <vector>

#include "GLIndexBuffer.h"
#include "GLVertexBuffer.h"
#include "GLShader.h"

class GLModel
{
public:
	GLModel() = default;
	GLModel(std::vector<glm::vec3> vertices, std::vector<int> indices);
	~GLModel();

	void draw();

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);

private:
	void initialize();

	GLShader* m_modelShaderProgram = nullptr;

	std::vector<glm::vec3> m_vertices;
	std::vector<int> m_indices;

	GLIndexBuffer m_indexBuffer;
	GLVertexBuffer m_vertexBuffer;
};
