//
// Created by Connor on 2/22/2019.
//

#ifndef UNTITLED_PROCESSLIST_H
#define UNTITLED_PROCESSLIST_H
struct node {
    int length;
    int wordOffset;
    struct node *next;
};
class ProcessList {
private:
    node *head;
public:
    ProcessList();
    ~ProcessList();
    void clear();
    int getLengthFromOffset(int wordOffset);
    void addProcess(size_t length, int offset);
    void removeProcess(int wordOffset);
};
#endif //UNTITLED_PROCESSLIST_H

