#include <string> // Включение библиотеки для работы со строками

// Структура для представления полного бинарного дерева, реализованного на массиве
struct CompleteBinaryTree {
    std::string* arr; // Указатель на динамический массив, где хранятся элементы дерева
    int size;         // Текущее количество элементов в дереве (узлов)
    int capacity;     // Максимальное количество элементов, которое может вместить текущий массив
};

// --- Объявления основных функций АТД "Дерево" ---

// Инициализация структуры дерева: выделяет начальную память
void init(CompleteBinaryTree& tree, int capacity);

// Освобождение памяти, выделенной для массива дерева
void destroy(CompleteBinaryTree& tree);

// Вставка нового элемента в дерево (в конец массива для сохранения полноты)
void insert(CompleteBinaryTree& tree, const std::string& val);

// Поиск элемента по значению (линейный поиск по массиву)
int search(const CompleteBinaryTree& tree, const std::string& val);

// Вывод содержимого дерева (в древовидной структуре)
void print(const CompleteBinaryTree& tree);

// Проверка, является ли дерево полным (всегда true при данной реализации)
bool isComplete(const CompleteBinaryTree& tree);

// --- Функции, требуемые по заданию ---

// Удаление элемента по заданному значению
void delByValue(CompleteBinaryTree& tree, const std::string& val);

// Удаление корневого элемента
void delRoot(CompleteBinaryTree& tree);

// Получение высоты дерева (количество уровней), без <cmath>
int getHeight(const CompleteBinaryTree& tree);