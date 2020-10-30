#ifndef MemPool_h
#define MemPool_h

#include <DaisyDuino.h>

#define SDRAM_POOL_SIZE (48*1024*1024)

class MemPool {

public:
    static void* allocate(size_t size);
    static void reset();
    static size_t getUsedMem() { return poolIndex; }

private:
    static char mem[SDRAM_POOL_SIZE];
    static size_t poolIndex;
};

#endif
