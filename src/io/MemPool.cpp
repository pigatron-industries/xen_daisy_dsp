#include "MemPool.h"
#include <DaisyDuino.h>

DSY_SDRAM_BSS char MemPool::permMem[SDRAM_PERM_SIZE];
size_t MemPool::permIndex = 0;
DSY_SDRAM_BSS char MemPool::poolMem[SDRAM_POOL_SIZE];
size_t MemPool::poolIndex = 0;

void* MemPool::allocatePerm(size_t size) {
    if (permIndex + size >= SDRAM_PERM_SIZE) {
        Serial.println("Perm memory space exceeded");
        return 0;
    }
    void* ptr = &permMem[permIndex];
    permIndex += size;
    return ptr;
}

void* MemPool::allocatePool(size_t size) {
    if (poolIndex + size >= SDRAM_POOL_SIZE) {
        Serial.println("Pool memory space exceeded");
        return 0;
    }
    void* ptr = &poolMem[poolIndex];
    poolIndex += size;
    return ptr;
}

void MemPool::resetPool() {
    poolIndex = 0;
}
