#ifndef MemPool_h
#define MemPool_h

#include <DaisyDuino.h>

#define SDRAM_TOTAL_SIZE (64*1024*1024)
#define SDRAM_PERM_SIZE (1*1024*1024)
#define SDRAM_POOL_SIZE SDRAM_TOTAL_SIZE-SDRAM_PERM_SIZE

#define SDRAM_POOL MemPool::allocatePool
#define SDRAM_PERM MemPool::allocatePerm

class MemPool {

public:
    static void* allocatePerm(size_t size);
    static void* allocatePool(size_t size);
    static void resetPool();
    static size_t getUsedMem() { return poolIndex; }

private:
    static char permMem[SDRAM_PERM_SIZE];
    static size_t permIndex;
    static char poolMem[SDRAM_POOL_SIZE];
    static size_t poolIndex;
};

#endif
