#include "MemPool.h"
#include <DaisyDuino.h>

DSY_SDRAM_BSS char MemPool::mem[SDRAM_POOL_SIZE];
size_t MemPool::poolIndex = 0;

void* MemPool::allocate(size_t size) {
    if (poolIndex + size >= SDRAM_POOL_SIZE) {
            return 0;
    }
    void* ptr = &mem[poolIndex];
    poolIndex += size;
    return ptr;
}

void MemPool::reset() {
    poolIndex = 0;
}
