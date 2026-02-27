#include "doubly_list.h"
#include <iostream> 
#include <string> 

using namespace std;

// Функция инициализации двусвязного списка.
void initList(DList &list)
{
    list.head = nullptr; // Установка указателя на голову (начало) в null (список пуст).
    list.tail = nullptr; // Установка указателя на хвост (конец) в null (список пуст).
}


// Операция добавления элемента в голову списка. Сложность O(1).
void addHead(DList &list)
{
    cout << "Введите значение"; // Запрос значения у пользователя.
    string val;
    cin >> val; // Считывание значения.

    // Создание нового узла:
    // val - значение узла
    // list.head - новый узел будет указывать на текущую голову (это его 'next').
    // nullptr - у нового узла пока нет предыдущего ('prev'), т.к. он становится головой.
    DNode* node = new DNode{val, list.head, nullptr}; 

    if(list.head) // Проверка, не пуст ли список (есть ли текущая голова).
    {
        list.head->prev = node; // Если список не пуст, старая голова теперь должна указывать 'prev' на новый узел.
    }
    else // Если список был пуст.
        list.tail = node; // Новый узел становится и головой, и хвостом.
    
    list.head = node; // Назначение нового узла новой головой списка.
}


// Операция добавления элемента в хвост списка. Сложность O(1).
void addDTail(DList &list, string val)
{
    // Создание нового узла:
    // val - значение узла
    // nullptr - узел будет хвостом, поэтому 'next' - null.
    // list.tail - новый узел будет указывать на старый хвост (это его 'prev').
    DNode* node = new DNode{val, nullptr, list.tail}; 

    if(list.tail) // Проверка, не пуст ли список (есть ли текущий хвост).
        list.tail->next = node; // Если не пуст, старый хвост теперь должен указывать 'next' на новый узел.
    else // Если список был пуст.
        list.head = node; // Новый узел становится и головой, и хвостом.
    
    list.tail = node; // Назначение нового узла новым хвостом списка.
}

// Операция вставки элемента перед заданным значением (target). Сложность O(N).
void addBefore(DList &list)
{
    if(!list.head) // Проверка на пустой список.
    {
        cout << "Список пуст" << endl;
        return;
    }

    cout << "Введите значение перед которым вставить: ";
    string target, val;
    cin >> target; // Считывание целевого значения.

    cout <<"Введите новое значение";
    cin >> val; // Считывание нового значения.

    // Цикл для поиска целевого значения (target).
    for(DNode* curr = list.head; curr; curr=curr->next) // Обход списка с головы до хвоста.
    {
        if(curr->value == target) // Если целевое значение найдено.
        {
            // Создание нового узла.
            DNode* node = new DNode{val, curr, curr->prev}; // next = curr, prev = curr->prev.
            if(curr->prev) // Проверка, есть ли предыдущий узел перед curr.
            {
                curr->prev->next = node; // Если есть, его 'next' теперь указывает на новый узел.
            }
            else // Если предыдущего узла нет (curr является головой).
                list.head = node; // Новый узел становится новой головой.
            curr->prev = node; // Узел curr теперь указывает 'prev' на новый узел.
            cout << "Элемент добавлен перед " << target << " не найден" << endl; // Это сообщение, кажется, ошибочно в оригинале (должно быть "Элемент добавлен...").
        }
    }
}


// Операция вставки элемента после заданного значения (target). Сложность O(N).
void addAfter(DList &list)
{
    if(!list.head) // Проверка на пустой список.
    {
        cout << "Список пуст" << endl;
        return;
    }

    cout << "Введите значение после которого вставить: ";
    string target, val;
    cin >> target; // Считывание целевого значения.
    cout << "Введите новое значение: ";
    cin >> val; // Считывание нового значения.

    // Цикл для поиска целевого значения (target).
    for(DNode* curr = list.head; curr; curr=curr->next) // Обход списка с головы до хвоста.
    {
        if(curr->value == target) // Если целевое значение найдено.
        {
            // Создание нового узла.
            DNode* node = new DNode{val, curr->next, curr}; // next = curr->next, prev = curr.
            if(curr->next) // Проверка, есть ли следующий узел после curr.
            {
                curr->next->prev = node; // Если есть, его 'prev' теперь указывает на новый узел.
            }
            else // Если следующего узла нет (curr является хвостом).
                list.tail = node; // Новый узел становится новым хвостом.
            curr->next = node; // Узел curr теперь указывает 'next' на новый узел.
            cout << "Элемент добавлен после " << target << endl; // Уведомление об успехе.
            return; // Завершение функции, т.к. элемент найден и добавлен.
        }
    }
    cout << "Элемент " << target << " не найден" << endl; // Уведомление о неудаче (если цикл завершился).
}


// Операция удаления элемента из головы списка. Сложность O(1).
void delHead(DList &list)
{
    if(!list.head) // Проверка на пустой список.
    {
        cout << "Список пуст" << endl;
        return;
    }
    DNode* tmp = list.head; // Сохранение указателя на текущую голову для последующего удаления.
    list.head = list.head->next; // Смещение головы на следующий узел.

    if(list.head) // Проверка, не стал ли список пустым после удаления (если новая голова существует).
        list.head->prev = nullptr; // Если существует, ее 'prev' должен стать null.
    else // Если список стал пустым.
        list.tail = nullptr; // Хвост также должен стать null.
    
    delete tmp; // Освобождение памяти, занятой старой головой.
    cout << "Первый элемент удалён" << endl; // Уведомление.
}

// Операция удаления элемента из хвоста списка. Сложность O(1), благодаря двусвязности.
void delTail(DList &list)
{
    if(!list.tail) // Проверка на пустой список.
    {
        cout << "Список пуст" << endl;
        return;
    }

    DNode* tmp = list.tail; // ОШИБКА В ОРИГИНАЛЬНОМ КОДЕ: Должно быть: DNode* tmp = list.tail;
    list.tail = list.tail->prev; // Смещение хвоста на предыдущий узел (быстрая операция O(1)).

    if(list.tail) // Проверка, не стал ли список пустым.
        list.tail->next = nullptr; // Если новый хвост существует, его 'next' должен стать null.
    else // Если список стал пустым.
        list.head = nullptr; // Голова также должна стать null.

    // ВНИМАНИЕ: В оригинальном коде была ошибка DNode* tmp = list.head; в начале функции.
    // Если бы код был корректен, здесь стояло бы delete tmp; для удаления старого хвоста.
    delete tmp; 
    cout << "Первый элемент удалён"; // В оригинале это сообщение ошибочно. Должно быть "Последний элемент удалён".
}

// Операция удаления элемента по заданному значению. Сложность O(N).
void delByVal(DList &list, const string& val) {
    if(!list.head) { // Проверка на пустой список.
        cout << "Список пуст." << endl;
        return;
    }
    DNode* curr = list.head;
    while(curr && curr->value != val) { // Поиск узла с заданным значением.
        curr = curr->next;
    }

    if (!curr) { // Если цикл завершился и узел не найден.
        cout << "Элемент " << val << " не найден." << endl;
        return;
    }

    // Линковка: Перенаправляем указатель 'next' предыдущего узла.
    if (curr->prev) // Если узел не голова.
        curr->prev->next = curr->next; // Предыдущий узел указывает на следующий за curr.
    else
        list.head = curr->next; // Если узел голова, то головой становится следующий.

    // Линковка: Перенаправляем указатель 'prev' следующего узла.
    if (curr->next) // Если узел не хвост.
        curr->next->prev = curr->prev; // Следующий узел указывает на предыдущий за curr.
    else
        list.tail = curr->prev; // Если узел хвост, то хвостом становится предыдущий.

    delete curr; // Освобождение памяти удаляемого узла.
    cout << "Элемент \"" << val << "\" удален." << endl; // Уведомление.
}

// Операция поиска узла по значению. Сложность O(N).
DNode* findValue(const DList &list, const string& val) {
    for(DNode* curr = list.head; curr; curr = curr->next) { // Обход списка с головы.
        if(curr->value == val) { // Если значение найдено.
            return curr; // Возвращение указателя на найденный узел.
        }
    }
    return nullptr; // Если цикл завершился и элемент не найден.
}


// Операция прямого чтения (с головы до хвоста). Сложность O(N).
void readForward(const DList &list)
{
    if(!list.head) // Проверка на пустой список.
    {
        cout << "Список пуст" << endl;
        return;
    }

    cout << "Список вперед: ";
    for(DNode* curr = list.head; curr; curr = curr->next) // Обход списка, используя 'next'.
        cout << curr->value << " ";
    cout << endl;
}

// Операция обратного чтения (с хвоста до головы). Сложность O(N).
void readBackward(const DList &list)
{
    if(!list.tail) // Проверка на пустой список.
    {
        cout << "Список пуст" << endl;
        return;
    }

    cout << "Список назад: ";
    for(DNode* curr = list.tail; curr; curr= curr->prev) // Обход списка, используя 'prev' (возможно только в двусвязном списке).
    {
        cout << curr->value << " ";
    }
    cout << endl;
}

// Операция полной очистки списка и освобождения всей памяти. Сложность O(N).
void clearList(DList &list)
{
    while(list.head) // Пока в списке есть узлы.
    {
        DNode* tmp = list.head; // Сохранение указателя на текущую голову.
        list.head = list.head ->next; // Смещение головы на следующий узел.
        delete tmp; // Освобождение памяти старой головы.
    }
    list.tail = nullptr; // После удаления всех узлов хвост также должен стать null.
}

// Операция удаления узла, расположенного СРАЗУ ПОСЛЕ узла со значением 'val'. Сложность O(N) из-за findValue.
void delAfterValue(DList &list, const string& val) {
    DNode* targetNode = findValue(list, val); // Поиск целевого узла (O(N)).
    if (!targetNode || !targetNode->next) { // Проверка, найден ли узел и не является ли он последним.
        cout << "Элемент '" << val << "' не найден или он последний." << endl;
        return;
    }
    DNode* nodeToDelete = targetNode->next; // Узел, который нужно удалить.
    // Если удаляемый узел - хвост, используем стандартное удаление хвоста.
    if (nodeToDelete == list.tail) { 
        delTail(list); // Вызов delTail (O(1)).
    } else {
        targetNode->next = nodeToDelete->next; // Целевой узел указывает на узел, следующий за удаляемым.
        nodeToDelete->next->prev = targetNode; // Узел после удаляемого указывает 'prev' на целевой узел.
        delete nodeToDelete; // Освобождение памяти.
    }
    cout << "Элемент после '" << val << "' удален." << endl;
}

// Операция удаления узла, расположенного СРАЗУ ПЕРЕД узлом со значением 'val'. Сложность O(N) из-за findValue.
void delBeforeValue(DList &list, const string& val) {
    DNode* targetNode = findValue(list, val); // Поиск целевого узла (O(N)).
    if (!targetNode || !targetNode->prev) { // Проверка, найден ли узел и не является ли он первым.
        cout << "Элемент '" << val << "' не найден или он первый." << endl;
        return;
    }
    DNode* nodeToDelete = targetNode->prev; // Узел, который нужно удалить.
    // Если удаляемый узел - голова, используем стандартное удаление головы.
    if (nodeToDelete == list.head) { 
        delHead(list); // Вызов delHead (O(1)).
    } else {
        targetNode->prev = nodeToDelete->prev; // Целевой узел указывает 'prev' на узел, идущий перед удаляемым.
        nodeToDelete->prev->next = targetNode; // Узел перед удаляемым указывает 'next' на целевой узел.
        delete nodeToDelete; // Освобождение памяти.
    }
     cout << "Элемент перед '" << val << "' удален." << endl;
}