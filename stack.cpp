#include "stack.h"
#include <iostream>
#include <string>

// Функция инициализации структуры стека. Сложность O(1).
void initStack(Stack &stack)
{
    stack.top = nullptr; // Установка указателя на вершину стека (top) в null (стек пуст).
}

// Операция добавления элемента на вершину стека (PUSH). Сложность O(1).
void push(Stack &stack, string val)
{
    // Создание нового узла SNode.
    SNode* node = new SNode; 
    node ->value= val; // Присвоение значения новому узлу.
    node->next = stack.top; // Новый узел указывает на текущую вершину (старую).
    stack.top = node; // Новый узел становится новой вершиной стека.
}

//извлекает элмент из стека и возвращает его тому, кто вызвал
// Операция извлечения элемента с вершины стека (POP). Сложность O(1).
string pop(Stack &stack)
{
    if(!stack.top) // Проверка на пустой стек.
    {
        return ""; //если стек пуст - возвращаем пустую строку
    }
    SNode* tmp = stack.top; // Сохранение указателя на текущую вершину (для удаления).
    string val = tmp->value; // Сохранение значения, которое нужно вернуть.
    stack.top = stack.top->next; // Сдвиг указателя 'top' на следующий элемент (удаление).
    delete tmp; //освобождение
    return val; // Возвращение извлеченного значения.
}

//чтение без удаления
// Операция чтения значения с вершины стека без удаления (PEEK). Сложность O(1).
string peek(const Stack& stack)
{
    if(!stack.top) // Проверка на пустой стек.
    {
        return ""; // Возвращение пустой строки.
    }
    return stack.top->value; // Возвращение значения с вершины.
}

// Функция вывода всего содержимого стека. Сложность O(N).
void readStack(const Stack &stack)
{
    if(!stack.top) // Проверка на пустой стек.
    {
        cout << "Стек пуст" << endl;
        return;
    }
    cout << "Содержимое стека" << endl;
    // Обход стека, начиная с вершины.
    for(SNode* curr = stack.top; curr; curr = curr ->next) 
    {
        cout << curr->value << endl; // Вывод значения.
    }
}

// Операция полной очистки стека и освобождения памяти. Сложность O(N).
void clearStack(Stack &stack)
{
    while(stack.top) // Пока вершина стека не null.
    {
        SNode* tmp = stack.top; // Сохранение узла для удаления.
        stack.top = stack.top ->next; // Смещение вершины на следующий узел.
        delete tmp; // Освобождение памяти.
    }
    // После цикла стек пуст, указатель stack.top уже null.
}