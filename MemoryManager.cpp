//
// Created by Connor on 2/22/2019.
//
#include "MemoryManager.h"
#include <cmath>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
MemoryManager::MemoryManager(unsigned wordSize, std::function<int(int, void *)> allocator){
    //wordsize is in bytes
    size = wordSize;
    defaultAllocator = std::bind(allocator, std::placeholders::_1, std::placeholders::_2);
    memoryList = new ProcessList;
    bitmap = new BitMap;
    active = false;
}

MemoryManager:: ~MemoryManager(){
    if (active)
        delete[] memBlock;
    if (bitmap){
        if (active) {
	    bitmap->clear();
	}
        delete(bitmap);
    }
    if (memoryList)
        delete(memoryList);

}

void MemoryManager::initialize(size_t sizeInWords){
    //set new bitmap for tracking the block
    bitmap->setBitMap(sizeInWords, size);
    memBlock = new char[sizeInWords*size];
    active = true;
}

void MemoryManager::shutdown(){
    if (memBlock)
        delete[] memBlock;
    memoryList->clear();
    bitmap->clear();
    active = false;
}

void * MemoryManager::allocate(size_t sizeInBytes){
    int result = defaultAllocator((int)ceil((double)sizeInBytes / size), bitmap);
    if (result == -1) {
        return nullptr;
    }

    memoryList->addProcess((int)ceil((double)sizeInBytes / size), result);
    bitmap->addProcess((int)ceil((double)sizeInBytes / size), result);
    //return the location

    return result * size + (char *) getMemoryStart();
}

void MemoryManager::free(void *address){
    char *position = (char *) address;
    int offset = (int) (position - (char *) getMemoryStart()) / size;
    int length = memoryList->getLengthFromOffset(offset);
    memoryList->removeProcess(offset);
    bitmap->freeProcess(length,offset);

}

void MemoryManager::setAllocator(std::function<int(int, void *)> allocator){
    defaultAllocator = allocator;
}

int MemoryManager::dumpMemoryMap(char *filename){
    string memMap = bitmap->getMemoryMap();
    char* buf = new char[memMap.length()+1];
    strcpy(buf, memMap.c_str());
    size_t bytes = strlen(buf);
    remove(filename);
    int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 777);
    write(fd, buf, bytes);
    close(fd);
    delete[] buf;
    return 0;
}

void * MemoryManager::getList(){
    return bitmap->convertToList();
}

void * MemoryManager::getBitmap(){
    return bitmap->formatOutput();
}

unsigned MemoryManager::getWordSize(){
    return size;
}

void * MemoryManager::getMemoryStart(){
    char* out = memBlock;
    return out;
}

unsigned MemoryManager::getMemoryLimit(){
    return bitmap->getRange()*size;
}

int MemoryManager::holeCount() {
    return bitmap->getHoleCount();
}
