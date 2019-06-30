//
// Created by Connor on 2/22/2019.
//
#include "AllocationAlgorithms.h"
#include "bitmap.h"
#include <cstdio>
#include <math.h>
int bestFit(int size, void *list){
    BitMap *b;
    b = (BitMap *) list;
    if (size <= 0 || size > b->getRange())
        return -1;

    int emptyCount = 0;
    int minEmpty = b->getRange();
    int minIndex = -1;
    int j = -1;

    //loops through bitmap
    for (int i = 0; i < b->getRange(); i++){
        //finds first position of hole
        if (!b->get(i) && i > j) {
            emptyCount = 0;
            j = i;
            //counts empty blocks
            while (j < b->getRange() && !b->get(j)) {
                emptyCount++;
                j++;
                if (j == b->getRange())
                    break;
            }
            //sets smallest hole if new hole is smaller than smallest current
            if (emptyCount <= minEmpty && emptyCount >= size) {
                minEmpty = emptyCount;
                minIndex = i;
            }
        }
    }

    //char test = b->get(0);
//    printf("Smallest hole is %d\n", minEmpty);
//    printf("This begins at index %d\n", minIndex);
    return minIndex;
}

int worstFit(int size, void *list) {
    BitMap *b;
    b = (BitMap *) list;
    if (size <= 0 || size > b->getRange())
        return -1;
    int emptyCount = 0;
    int maxEmpty = 0;
    int maxIndex = -1;
    int j = -1;

    for (int i = 0; i < b->getRange(); i++){
        if (!b->get(i) && i > j) {
            emptyCount = 0;
            j = i;
            while (j < b->getRange() && !b->get(j)) {
                emptyCount++;
                j++;
                if (j == b->getRange())
                    break;
            }
            if (emptyCount >= maxEmpty) {
                maxEmpty = emptyCount;
                maxIndex = i;
            }
        }
    }

//    printf("Largest hole is %d\n", emptyCount);
//    printf("This begins at index %d\n", maxIndex);
    return maxIndex;
}
