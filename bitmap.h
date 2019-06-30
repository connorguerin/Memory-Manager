//
// Created by Connor on 2/22/2019.
//

#ifndef UNTITLED_BITMAP_H
#define UNTITLED_BITMAP_H


#include <iostream>
#include <assert.h>
using namespace std;

class BitMap {
public:
    BitMap();
    //~BitMap();
    void clear();
    void setBitMap(unsigned n, int size);
    bool set(int index);
    bool unset(int index);
    int get(int index);
    void printBitMap();
    int getRange();
    void addProcess(int length, int offset);
    void freeProcess(int length, int offset);
    string getMemoryMap();
    uint16_t * convertToList();
    uint8_t* formatOutput();
    int getHoleCount();
private:
    int* m_buffer;
    int m_range;
    int wordSize;
};



#endif //UNTITLED_BITMAP_H

