//
// Created by Connor on 2/22/2019.
//
#include <cstdlib>
#include <cstdio>
#include <string>
#include "ProcessList.h"
ProcessList::ProcessList() {
    head= nullptr;
}

ProcessList::~ProcessList() {
    node* current = head;
    while (current != nullptr) {
        node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
void ProcessList::clear(){
     node* current = head;
    while (current != nullptr) {
        node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
void ProcessList::addProcess(size_t length, int offset) {
    node *temp = new node;
    temp->length = length;
    temp->wordOffset = offset;
    temp->next = nullptr;
    if (head) {
        node *iter = head;
        while (iter->next != nullptr)
            iter=iter->next;
        iter->next = temp;
    }
    else {
        head = temp;
    }

}
int ProcessList::getLengthFromOffset(int wordOffset) {
    node *temp = head;
    while (temp) {
        if (temp->wordOffset == wordOffset) {
            return temp->length;
        }
        temp = temp->next;
    }
    return -1;
}

void ProcessList::removeProcess(int wordOffset) {
    node *temp = head;
    node *prev = head;

    if (temp != nullptr && temp->wordOffset == wordOffset) {
        head = temp->next;
        delete(temp);
        return;
    }

    while (temp != nullptr && temp->wordOffset != wordOffset) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) return;

    prev->next = temp->next;

    delete(temp);
}

