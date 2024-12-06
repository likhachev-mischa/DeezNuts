#include "GLModel.h"

GLModel::GLModel(std::vector<glm::vec3> vertices, std::vector<int> indices) :
	m_vertices(std::move(vertices)),
	m_indices(std::move(indices))
{
	initialize();
}

GLModel::~GLModel()
{
	if (m_indexBuffer.isCreated())
		m_indexBuffer.destroy();

	if (m_vertexBuffer.isCreated())
		m_vertexBuffer.destroy();
}

void GLModel::draw()
{
	m_modelShaderProgram->bind();

	m_vertexBuffer.bind();

	int positionLocation = m_modelShaderProgram->attributeLocation("in_position");
	m_modelShaderProgram->enableAttributeArray(positionLocation);
	m_modelShaderProgram->setAttributeBuffer(positionLocation,
	                                         3,
	                                         GL_FLOAT,
	                                         sizeof(glm::vec3),
	                                         nullptr);

	m_indexBuffer.bind();

	m_modelShaderProgram->setMat4("model", modelMatrix);
	m_modelShaderProgram->setMat4("view", viewMatrix);
	m_modelShaderProgram->setMat4("projection", projectionMatrix);

	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	m_indexBuffer.release();

	m_modelShaderProgram->disableAttributeArray(positionLocation);

	m_vertexBuffer.release();

	m_modelShaderProgram->release();
}

void GLModel::initialize()
{
	m_vertexBuffer.create();
	m_vertexBuffer.bind();
	m_vertexBuffer.allocate(m_vertices.data(), m_vertices.size() * sizeof(glm::vec3));
	m_vertexBuffer.release();

	m_indexBuffer.create();
	m_indexBuffer.bind();
	m_indexBuffer.allocate(m_indices.data(), m_indices.size() * sizeof(int));
	m_indexBuffer.release();

	m_modelShaderProgram = new GLShader("./Shaders/vert.vert", "./Shaders/frag.frag");
}
