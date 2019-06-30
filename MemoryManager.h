//
// Created by Connor on 2/22/2019.
//
#ifndef UNTITLED_MEMORYMANAGER_H
#define UNTITLED_MEMORYMANAGER_H
#include <functional>
#include "bitmap.h"
#include "ProcessList.h"
#include "AllocationAlgorithms.h"
class MemoryManager {
private:
    unsigned size;
    std::function<int(int, void *)> defaultAllocator;
    BitMap *bitmap;
    ProcessList *memoryList;
    char* memBlock;
    bool active;
public:
    MemoryManager(unsigned wordSize, std::function<int(int, void *)> allocator);
    ~MemoryManager();
    void initialize(size_t sizeInWords);
    void shutdown();
    void *allocate(size_t sizeInBytes);
    void free(void *address);
    void setAllocator(std::function<int(int, void *)> allocator);
    int dumpMemoryMap(char *filename);
    void *getList();
    void *getBitmap();
    unsigned getWordSize();
    void *getMemoryStart();
    unsigned getMemoryLimit();
    int holeCount();
};

#endif


