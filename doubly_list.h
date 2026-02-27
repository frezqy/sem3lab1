#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <iostream>
#include <string>
using namespace std;

// Структура узла двусвязного списка
struct DNode {
    string value;   // значение узла
    DNode* next;     // указатель на следующий элемент
    DNode* prev;     // указатель на предыдущий элемент
};

// Структура самого списка
struct DList {
    DNode* head;     // указатель на первый элемент
    DNode* tail;     // указатель на последний элемент
};

void initList(DList &list);
void addHead(DList &list);
void addDTail(DList &list, string val);
void addBefore(DList &list);
void addAfter(DList &list);
void delHead(DList &list);
void delTail(DList &list);
void delByVal(DList &list, const string& val);
DNode* findValue(const DList &list, const string& val);
void readForward(const DList &list);
void readBackward(const DList &list);
void clearList(DList &list);

void delAfterValue(DList &list, const string& val);
void delBeforeValue(DList &list, const string& val);

#endif
