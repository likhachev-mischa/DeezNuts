#pragma once

#include <cstdint>

class Buffer
{
public:
	virtual ~Buffer() = default;

	virtual bool isCreated() = 0;

	virtual void destroy() = 0;

	virtual void create() = 0;

	virtual void bind() = 0;
	virtual void release() = 0;

	virtual void allocate(void* data, uint32_t size) = 0;
};

