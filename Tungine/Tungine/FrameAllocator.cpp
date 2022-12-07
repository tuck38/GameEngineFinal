#include "FrameAllocator.h"
#include "Transform.h"

FrameAllocator::FrameAllocator(int size):
	buffer(new char[size])
{
	base = buffer;
	stackSize = size;
}

void FrameAllocator::clear()
{
	base = buffer;
}