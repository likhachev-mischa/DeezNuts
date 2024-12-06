#include "GLIndexBuffer.h"

#include <glad/glad.h>

GLIndexBuffer::~GLIndexBuffer()
{
	GLIndexBuffer::destroy();
}

bool GLIndexBuffer::isCreated()
{
	return m_isCreated;
}

void GLIndexBuffer::destroy()
{
	if (m_isCreated && !m_isAlreadyDestroyed)
	{
		glDeleteBuffers(1, &m_indexBufferId);
		m_isAlreadyDestroyed = true;
	}
}

void GLIndexBuffer::create()
{
	if (m_isCreated)
		return;

	glGenBuffers(1, &m_indexBufferId);
	m_isCreated = true;
}

void GLIndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
}

void GLIndexBuffer::release()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLIndexBuffer::allocate(void* data, uint32_t size)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
