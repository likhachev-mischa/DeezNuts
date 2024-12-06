#include "GLVertexBuffer.h"

#include <glad/glad.h>

GLVertexBuffer::~GLVertexBuffer()
{
	GLVertexBuffer::destroy();
}

bool GLVertexBuffer::isCreated()
{
	return m_isCreated;
}

void GLVertexBuffer::destroy()
{
	if (m_isCreated && !m_isAlreadyDestroyed)
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
		m_isAlreadyDestroyed = true;
	}
}

void GLVertexBuffer::create()
{
	if (m_isCreated)
		return;

	glGenBuffers(1, &m_VBO);
	glGenVertexArrays(1, &m_VAO);

	m_isCreated = true;
}

void GLVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindVertexArray(m_VAO);
}

void GLVertexBuffer::release()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GLVertexBuffer::allocate(void* data, const uint32_t size)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
