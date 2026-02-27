#include <iostream>  
#include <fstream>  
#include <string>    
#include <algorithm> 
#include <sstream>   
#include <limits>    
#include "arr.h"
#include "doubly_list.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"

using namespace std;


MyArr arr; 
MyList slist; 
DList dlist; 
Queue queue;
Stack stack; 
CompleteBinaryTree tree; 


// --- 1. Функции сохранения/загрузки данных ---

// (Функции saveData для всех структур остаются без изменений)

void saveData(const MyArr& arr) {
    ofstream file("array.txt");
    for(int i=0; i< arr.size; i++) file << arr.data[i] << endl;
    cout << "Массив сохранен в array.txt" << endl;
}
void loadData(MyArr& arr) {
    ifstream file("array.txt"); 
    if (!file.is_open()) return; 
    string val;
    while(file >> val) addEnd(arr,val);
}

void saveData(const MyList& list) {
    ofstream file("slist.txt");
    for(Node* curr = list.head; curr; curr = curr ->next) file << curr ->value << endl;
    cout << "Односвязный список сохранен в slist.txt" << endl;
}
void loadData(MyList& list) {
    ifstream file ("slist.txt");
    if (!file.is_open()) return;
    string val;
    while(file >> val) addTail(list,val);
}

void saveData(const DList& list) {
    ofstream file("dlist.txt");
    for(DNode* curr = list.head; curr; curr = curr->next) file << curr ->value << endl;
    cout << "Двусвязный список сохранен в dlist.txt" << endl;
}
void loadData(DList& list) {
    ifstream file("dlist.txt");
    if (!file.is_open()) return;
    string val;
    while(file >> val) addDTail(list,val);
}

void saveData(const Queue& q) {
    ofstream file("queue.txt");
    for(QNode* curr = q.front; curr; curr = curr->next) file << curr->data << endl;
    cout << "Очередь сохранена в queue.txt" << endl;
}
void loadData(Queue& q) {
    ifstream file("queue.txt");
    if (!file.is_open()) return;
    string val;
    while(file >> val) push(q,val);
}

void saveData(const Stack& stack) {
    ofstream file("stack.txt");
    for(SNode* curr = stack.top; curr; curr = curr->next) file << curr->value << endl;
    cout << "Стек сохранен в stack.txt" << endl;
}

// *** ИСПРАВЛЕННАЯ ЗАГРУЗКА СТЕКА (БЕЗ <vector>) ***
void loadData(Stack& stack) {
    ifstream file("stack.txt");
    if (!file.is_open()) return;

    string line;
    // Используем динамический массив для временного хранения (имитация vector)
    string* temp_arr = nullptr;
    int size = 0;
    int capacity = 0;
    
    // 1. Читаем все строки из файла и сохраняем их во временном массиве
    while(getline(file, line)) {
        if (line.empty()) continue;

        // Расширение массива при необходимости
        if (size == capacity) {
            int new_capacity = (capacity == 0) ? 4 : capacity * 2;
            string* new_arr = new string[new_capacity];
            for (int i = 0; i < size; ++i) {
                new_arr[i] = temp_arr[i];
            }
            delete[] temp_arr;
            temp_arr = new_arr;
            capacity = new_capacity;
        }
        
        temp_arr[size] = line;
        size++;
    }
    
    // 2. Добавляем элементы в стек в обратном порядке (LIFO)
    for(int i = size - 1; i >= 0; --i) {
        push(stack, temp_arr[i]);
    }
    
    // 3. Очищаем временный массив
    delete[] temp_arr;
}

void saveData(const CompleteBinaryTree& tree) {
    ofstream file("tree.txt");
    for(int i=0; i < tree.size; i++) file << tree.arr[i] << endl;
    cout << "Дерево сохранено в tree.txt" << endl;
}
void loadData(CompleteBinaryTree& tree) {
    ifstream file("tree.txt");
    if (!file.is_open()) return;
    string val;
    while(file >> val) insert(tree, val);
}


// --- 2. Функция Справки (HELP) ---

void showHelp(const string& structure) {
    cout << "\n=== СПРАВКА по командам для " << structure << " ===" << endl;

    if (structure == "массив") {
        cout << "* ADD_END <значение> - Добавить в конец. (O(N))\n";
        cout << "* ADD_AT <индекс> <значение> - Вставить по индексу. (O(N))\n";
        cout << "* DEL_AT <индекс> - Удалить по индексу. (O(N))\n";
        cout << "* GET_AT <индекс> - Получить по индексу. (O(1))\n";
        cout << "* REP <индекс> <значение> - Заменить по индексу. (O(1))\n";
        cout << "* LEN - Получить размер. (O(1))\n";
        cout << "* READ - Вывести все элементы. (O(N))\n";
    } else if (structure == "односвязный список") {
        cout << "* ADD_HEAD - Добавить в голову (запросит значение). (O(1))\n";
        cout << "* ADD_TAIL <значение> - Добавить в хвост. (O(N))\n";
        cout << "* ADD_BEFORE - Добавить перед значением (запросит параметры). (O(N))\n";
        cout << "* ADD_AFTER - Добавить после значения (запросит параметры). (O(N))\n";
        cout << "* DEL_HEAD - Удалить голову. (O(1))\n";
        cout << "* DEL_TAIL - Удалить хвост. (O(N))\n";
        cout << "* DEL_VAL <значение> - Удалить по значению. (O(N))\n";
        cout << "* FIND <значение> - Найти элемент. (O(N))\n";
        cout << "* READ_F - Вывести список с головы. (O(N))\n";
        cout << "* READ_B - Вывести список с хвоста (рекурсивно). (O(N))\n";
    } else if (structure == "двусвязный список") {
        cout << "* ADD_HEAD - Добавить в голову (запросит значение). (O(1))\n";
        cout << "* ADD_TAIL <значение> - Добавить в хвост. (O(1))\n";
        cout << "* ADD_BEFORE - Добавить перед значением (запросит параметры). (O(N))\n";
        cout << "* ADD_AFTER - Добавить после значения (запросит параметры). (O(N))\n";
        cout << "* DEL_HEAD - Удалить голову. (O(1))\n";
        cout << "* DEL_TAIL - Удалить хвост. (O(1))\n";
        cout << "* DEL_VAL <значение> - Удалить по значению. (O(N))\n";
        cout << "* READ_F - Вывести список с головы. (O(N))\n";
        cout << "* READ_B - Вывести список с хвоста. (O(N))\n";
    } else if (structure == "стек") {
        cout << "* PUSH <значение> - Добавить на вершину. (O(1))\n";
        cout << "* POP - Извлечь с вершины. (O(1))\n";
        cout << "* PEEK - Просмотреть вершину. (O(1))\n";
        cout << "* READ - Вывести содержимое. (O(N))\n";
    } else if (structure == "очередь") {
        cout << "* PUSH <значение> - Добавить в хвост. (O(1))\n";
        cout << "* POP - Извлечь из начала. (O(1))\n";
        cout << "* PEEK - Просмотреть начало. (O(1))\n";
        cout << "* READ - Вывести содержимое. (O(N))\n";
    } else if (structure == "дерево") {
        cout << "* INSERT <значение> - Вставить элемент. (O(1) в ср./O(N) в худшем)\n";
        cout << "* SEARCH <значение> - Найти элемент. (O(N) - линейный поиск)\n";
        cout << "* DEL_BY_VAL <значение> - Удалить по значению. (O(N))\n";
        cout << "* DEL_ROOT - Удалить корень. (O(1))\n";
        cout << "* GET_HEIGHT - Получить высоту. (O(log N))\n";
        cout << "* PRINT - Вывести элементы (древовидно). (O(N))\n";
        cout << "* IS_COMPLETE - Проверить полноту. (O(1) - заглушка)\n";
    }

    cout << "* EXIT - Вернуться в предыдущее меню.\n";
    cout << "* HELP - Показать эту справку.\n";
}


// --- 3. Функции меню (Обработчики текстовых команд) ---

void arrayMenu() {
    string command, val_str;
    int idx;
    cout << "\n=== РАБОТА С МАССИВОМ ===\n";
    showHelp("массив");

    while (true) {
        cout << "\nМАССИВ >> ";
        cin >> command;
        transform(command.begin(), command.end(), command.begin(), ::toupper); 

        if (command == "EXIT") {
            saveData(arr); 
            break;
        } else if (command == "HELP") {
            showHelp("массив");
        } else if (command == "ADD_END") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            addEnd(arr, val_str);
        } else if (command == "ADD_AT") {
            if (!(cin >> idx >> val_str)) { cout << "Ошибка ввода <индекс> <значение>.\n"; continue; }
            addAt(arr, idx, val_str);
        } else if (command == "DEL_AT") {
            if (!(cin >> idx)) { cout << "Ошибка ввода <индекс>.\n"; continue; }
            delAt(arr, idx);
        } else if (command == "GET_AT") {
            if (!(cin >> idx)) { cout << "Ошибка ввода <индекс>.\n"; continue; }
            getAt(arr, idx);
        } else if (command == "REP") {
            if (!(cin >> idx >> val_str)) { cout << "Ошибка ввода <индекс> <значение>.\n"; continue; }
            repArr(arr, idx, val_str);
        } else if (command == "LEN") {
            cout << "Размер массива: " << lenArr(arr) << endl;
        } else if (command == "READ") {
            readArray(arr);
        } else {
            cout << "Неизвестная команда. Введите HELP для списка команд.\n";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void singlyListMenu() {
    string command, val_str;
    cout << "\n=== РАБОТА С ОДНОСВЯЗНЫМ СПИСКОМ ===\n";
    showHelp("односвязный список");

    while (true) {
        cout << "\nSLIST >> ";
        cin >> command;
        transform(command.begin(), command.end(), command.begin(), ::toupper);

        if (command == "EXIT") {
            saveData(slist);
            break;
        } else if (command == "HELP") {
            showHelp("односвязный список");
        } else if (command == "ADD_HEAD") {
            addHead(slist);
        } else if (command == "ADD_TAIL") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            addTail(slist, val_str);
        } else if (command == "ADD_BEFORE") {
            addBefore(slist);
        } else if (command == "ADD_AFTER") {
            addAfter(slist);
        } else if (command == "DEL_HEAD") {
            delHead(slist);
        } else if (command == "DEL_TAIL") {
            delTail(slist);
        } else if (command == "DEL_VAL") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            delByValue(slist, val_str);
        } else if (command == "FIND") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            findValue(slist, val_str);
        } else if (command == "READ_F") {
            readForward(slist);
        } else if (command == "READ_B") {
            readBack(slist);
        } else {
            cout << "Неизвестная команда. Введите HELP для списка команд.\n";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void doublyListMenu() {
    string command, val_str;
    cout << "\n=== РАБОТА С ДВУСВЯЗНЫМ СПИСКОМ ===\n";
    showHelp("двусвязный список");

    while (true) {
        cout << "\nDLIST >> ";
        cin >> command;
        transform(command.begin(), command.end(), command.begin(), ::toupper);

        if (command == "EXIT") {
            saveData(dlist);
            break;
        } else if (command == "HELP") {
            showHelp("двусвязный список");
        } else if (command == "ADD_HEAD") {
            addHead(dlist);
        } else if (command == "ADD_TAIL") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            addDTail(dlist, val_str);
        } else if (command == "ADD_BEFORE") {
            addBefore(dlist);
        } else if (command == "ADD_AFTER") {
            addAfter(dlist);
        } else if (command == "DEL_HEAD") {
            delHead(dlist);
        } else if (command == "DEL_TAIL") {
            delTail(dlist);
        } else if (command == "DEL_VAL") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            delByVal(dlist, val_str);
        } else if (command == "READ_F") {
            readForward(dlist);
        } else if (command == "READ_B") {
            readBackward(dlist);
        } else {
            cout << "Неизвестная команда. Введите HELP для списка команд.\n";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void stackMenu() {
    string command, val_str;
    cout << "\n=== РАБОТА СО СТЕКОМ (LIFO) ===\n";
    showHelp("стек");

    while (true) {
        cout << "\nSTACK >> ";
        cin >> command;
        transform(command.begin(), command.end(), command.begin(), ::toupper);

        if (command == "EXIT") {
            saveData(stack);
            break;
        } else if (command == "HELP") {
            showHelp("стек");
        } else if (command == "PUSH") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            push(stack, val_str);
        } else if (command == "POP") {
            val_str = pop(stack);
            if (!val_str.empty()) cout << "Извлечено: " << val_str << endl;
            else cout << "Стек пуст." << endl;
        } else if (command == "PEEK") {
            val_str = peek(stack);
            if (!val_str.empty()) cout << "Вершина: " << val_str << endl;
            else cout << "Стек пуст." << endl;
        } else if (command == "READ") {
            readStack(stack);
        } else {
            cout << "Неизвестная команда. Введите HELP для списка команд.\n";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void queueMenu() {
    string command, val_str;
    cout << "\n=== РАБОТА С ОЧЕРЕДЬЮ (FIFO) ===\n";
    showHelp("очередь");

    while (true) {
        cout << "\nQUEUE >> ";
        cin >> command;
        transform(command.begin(), command.end(), command.begin(), ::toupper);

        if (command == "EXIT") {
            saveData(queue);
            break;
        } else if (command == "HELP") {
            showHelp("очередь");
        } else if (command == "PUSH") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            push(queue, val_str);
        } else if (command == "POP") {
            val_str = pop(queue);
            if (!val_str.empty()) cout << "Извлечено: " << val_str << endl;
            else cout << "Очередь пуста." << endl;
        } else if (command == "PEEK") {
            val_str = peek(queue);
            if (!val_str.empty()) cout << "Начало: " << val_str << endl;
            else cout << "Очередь пуста." << endl;
        } else if (command == "READ") {
            print(queue);
        } else {
            cout << "Неизвестная команда. Введите HELP для списка команд.\n";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void treeMenu() {
    string command, val_str;
    cout << "\n=== РАБОТА С ДЕРЕВОМ ===\n";
    showHelp("дерево");

    while (true) {
        cout << "\nTREE >> ";
        cin >> command;
        transform(command.begin(), command.end(), command.begin(), ::toupper);

        if (command == "EXIT") {
            saveData(tree);
            break;
        } else if (command == "HELP") {
            showHelp("дерево");
        } else if (command == "INSERT") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            insert(tree, val_str);
        } else if (command == "SEARCH") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            int idx = search(tree, val_str);
            if (idx != -1) cout << "Элемент найден по индексу (массива): " << idx << endl;
            else cout << "Элемент не найден." << endl;
        } else if (command == "PRINT") {
            print(tree);
        // --- НОВЫЕ КОМАНДЫ ---
        } else if (command == "DEL_BY_VAL") {
            if (!(cin >> val_str)) { cout << "Ошибка ввода <значение>.\n"; continue; }
            delByValue(tree, val_str);
        } else if (command == "DEL_ROOT") {
            delRoot(tree);
        } else if (command == "GET_HEIGHT") {
            cout << "Высота дерева: " << getHeight(tree) << endl;
        } else if (command == "IS_COMPLETE") {
            if (isComplete(tree)) cout << "Дерево является полным." << endl;
            else cout << "Дерево НЕ является полным." << endl;
        } else {
            cout << "Неизвестная команда. Введите HELP для списка команд.\n";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// --- 4. Главная функция программы (main) ---
int main()
{
    // Установка локали для корректной работы с кириллицей в консоли
    setlocale(LC_ALL, "Russian");
    
    // 1. Инициализация структур данных
    initArray(arr); 
    initList(slist);
    initList(dlist);
    init(queue);
    initStack(stack);
    init(tree, 8); // Инициализация дерева с начальной вместимостью 8

    // 2. Загрузка данных из файлов
    loadData(arr);
    loadData(slist);
    loadData(dlist);
    loadData(queue);
    loadData(stack); // Использует новый метод без vector
    loadData(tree);
    cout << "Данные из файлов загружены." << endl;
    cout << "Для выбора структуры введите ее название (ARRAY, SLIST, DLIST, STACK, QUEUE, TREE) или HELP." << endl;

    string mainCommand;
    // 3. Основной цикл главного меню
    while (true) {
        cout << "\nГЛАВНОЕ МЕНЮ >> ";
        if (!(cin >> mainCommand)) {
             mainCommand = "EXIT";
        }

        // Приведение команды к верхнему регистру
        transform(mainCommand.begin(), mainCommand.end(), mainCommand.begin(), ::toupper); 

        if (mainCommand == "EXIT" || mainCommand == "0") {
            cout << "Очистка памяти и выход..." << endl;
            goto cleanup;
        } else if (mainCommand == "HELP") {
            cout << "\n=== ГЛАВНОЕ МЕНЮ: КОМАНДЫ ===\n"
                 << "* ARRAY - Работа с динамическим массивом.\n"
                 << "* SLIST - Работа с односвязным списком.\n"
                 << "* DLIST - Работа с двусвязным списком.\n"
                 << "* STACK - Работа со стеком.\n"
                 << "* QUEUE - Работа с очередью.\n"
                 << "* TREE - Работа с полным бинарным деревом.\n"
                 << "* EXIT - Завершение программы.\n";
        } else if (mainCommand == "ARRAY") {
            arrayMenu();
        } else if (mainCommand == "SLIST") {
            singlyListMenu();
        } else if (mainCommand == "DLIST") {
            doublyListMenu();
        } else if (mainCommand == "STACK") {
            stackMenu();
        } else if (mainCommand == "QUEUE") {
            queueMenu();
        } else if (mainCommand == "TREE") {
            treeMenu();
        } else {
            cout << "Неизвестная команда. Введите HELP для списка структур.\n";
        }
        // Очистка буфера cin
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

// 4. Секция очистки памяти (Cleanup)
cleanup:
    // Вызов функций освобождения памяти для предотвращения утечек
    freeArr(arr);
    freeList(slist);
    clearList(dlist);
    clear(queue);
    clearStack(stack);
    destroy(tree);

    return 0; // Успешное завершение программы
}