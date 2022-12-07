#pragma once

class FrameAllocator
{
private:

    char* base;
    char* buffer;

    int stackSize;

public:
    FrameAllocator(int size);

    ~FrameAllocator()
    {
        delete base;
    }

    template <typename T>
    T* alloc()
    {
        size_t sizeToAllocate = sizeof(T);
        T* allocationPoint = (T*)base;

        if (sizeToAllocate + base > buffer + stackSize)
        {
            return nullptr;
        }

        base += sizeToAllocate;
        return allocationPoint;
    }

    template <typename T>
    T* alloc(size_t size)
    {
        size_t sizeToAllocate = sizeof(T) * size;
        T* allocationPoint = (T*)base;

        if (sizeToAllocate + base > buffer + stackSize)
        {
            return nullptr;
        }

        base += sizeToAllocate;
        return allocationPoint;
    }

    void clear();
};