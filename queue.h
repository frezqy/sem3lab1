#ifndef QUEUE_H
#define QUEUE_H
#include <string>
#include <iostream>
// Структура для одного элемента (узла) очереди
struct QNode {
    std::string data;       // Данные узла (в нашем случае, целое число)
    QNode* next;     // Указатель на следующий узел в очереди
};

// Структура самой очереди
struct Queue {
    QNode* front;    // Указатель на начало (голову) очереди
    QNode* rear;     // Указатель на конец (хвост) очереди
};

// Прототипы функций для работы с очередью
void init(Queue& q);         // Инициализация (создание) пустой очереди
void push(Queue& q,std::string val); // Добавление элемента в конец очереди
std::string pop(Queue &q);           // Удаление элемента из начала очереди
std::string peek(const Queue& q);    // Чтение элемента из начала без удаления
bool isEmpty(const Queue& q); // Проверка, пуста ли очередь
void clear(Queue& q);        // Очистка очереди (удаление всех элементов)
void print(const Queue& q);

#endif // QUEUE_H


