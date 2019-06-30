//
// Created by Connor on 2/22/2019.
//

#include "bitmap.h"
#include <string>
#include <iomanip>
#include <math.h>
#include <bitset>
BitMap::BitMap()
{
    //m_buffer = (unsigned char*) malloc((n+7)/8);
    //assert(m_buffer);

}

//BitMap::~BitMap()
//{
//    if (m_buffer) {
//        delete[] m_buffer;
//    }
//}

bool BitMap::set(int index)
{
    if (index < 0 || index >= m_range) {
        return false;
    }
    m_buffer[index] = 1;
    return true;
}

bool BitMap::unset(int index)
{
    if (index < 0 || index >= m_range) {
        return false;
    }
    m_buffer[index] = 0;
    return true;
}

int BitMap::get(int index)
{
    if (index < 0 || index >= m_range) {
        return false;
    }

    //return (m_buffer[index/8] & (0x01 << (index%8))) ? 0x01 : 0x00;
    return m_buffer[index];
}

void BitMap::printBitMap()
{
    for (int ii = 0; ii < m_range; ii++) {
        std::cout<<"'"<<m_buffer[ii]<<"'";
    }
    std::cout<<endl;
}

int BitMap::getRange() {
    return m_range;
}

void BitMap::addProcess(int length, int offset) {
    for (int i = offset; i < offset + length; i++ ){
        set(i);
    }
    //printBitMap();
}

void BitMap::clear() {
    if (m_buffer)
        delete[] m_buffer;
}

void BitMap::freeProcess(int length, int offset) {
    for (int i = offset; i < offset + length; i++)
        unset(i);
    //printBitMap();
}

string BitMap::getMemoryMap() {
    string retStr;
    int start = 0;
    int length = 0;
    int j = 0;
    while (start + j < m_range) {
        if (!get(start)) {
            j = 0;
            length = 0;
            while (!get(start + j) && (start + j < m_range)) {
                length++;
                j++;
            }
            retStr += (string)"[" + to_string(start) + ", " + to_string(length) + "] - ";
            start += j;
            j = 0;
        }
        else
            start++;
    }
    //need to erase the extra bracket and dash
    return retStr.substr(0, retStr.size()-3);
}

uint16_t *BitMap::convertToList() {
    int holes = 0;
    int start = 0;
    while (start < m_range) {
        if (!get(start)){
            holes++;
            while (!get(start) && start < m_range)
                start++;
        }
        else
            start++;
    }
    uint16_t * retArray = new uint16_t[2* holes + 1];
    retArray[0] = sizeof(uint16_t)*holes*2;

    start = 0;
    int length = 0;
    int j = 0;
    int arrayIndex = 1;
    while (start + j < m_range) {
        if (!get(start)) {
            j = 0;
            length = 0;
            while (!get(start + j) && (start + j < m_range)) {
                length++;
                j++;
            }
            retArray[arrayIndex] = (uint16_t)start;
            retArray[arrayIndex + 1] = (uint16_t)length;
            start += j;
            j = 0;
            arrayIndex += 2;
        }
        else
            start++;
    }
    return retArray;
}

uint8_t *BitMap::formatOutput() {

    uint16_t length = (uint16_t) ceil((double) m_range / 8);
    //cout << length << "\n";
    uint8_t *retArray = new uint8_t[(int) ceil((double) m_range / 8)+2];
    for (int j = 0; j < (int) ceil((double) m_range / 8) + 2; j++) {
        retArray[j] = 0;
    }

    length = static_cast<uint16_t>((length << 8) | ((length >> 8) & 0x00ff));
    retArray[0] = length >> 8;
    retArray[1] = length & 0x0FF;

    uint8_t orBits = 0;
    for (int i = 0; i < m_range; i++) {

        if (get(i)) {
            orBits += (uint8_t) pow(2, i % 8);
        }
        if (((i + 1) % 8 == 0 && i != 0) || i == m_range - 1) {
            retArray[(i+1) / 8 + 1] = retArray[(i+1) / 8 + 1]^orBits;
            orBits = 0;
        }
    }

    return retArray;
}

void BitMap::setBitMap(unsigned n, int size) {
    m_buffer = new int[n];
    for (int ii = 0; ii < n; ii++) {
        m_buffer[ii] = 0x00;
    }
    m_range = n;
    wordSize = size;
}

int BitMap::getHoleCount() {
    int count = 0;
    for (int i = 0; i < m_range; i++) {
	if (m_buffer[i] == 0)
	    count++;
    }
	return count;

}
