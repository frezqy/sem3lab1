#include "tree.h"
#include <iostream> 
#include <string>    

using namespace std;

// --- Реализация основных функций ---

// Инициализация структуры дерева
void init(CompleteBinaryTree& tree, int capacity)
{
    // Выделяем память под массив строк
    tree.arr = new std::string[capacity];
    // Устанавливаем начальное количество элементов в 0
    tree.size = 0;
    // Сохраняем заданную начальную вместимость
    tree.capacity = capacity;
}

// Освобождение памяти и сброс структуры
void destroy(CompleteBinaryTree& tree)
{
    // Освобождаем память, выделенную через new[]
    delete[] tree.arr;
    // Сбрасываем указатель
    tree.arr = nullptr;
    // Обнуляем размер и вместимость
    tree.size = 0;
    tree.capacity = 0;
}

// Вставка нового элемента
void insert(CompleteBinaryTree& tree, const std::string& val) {
    // Проверка, достаточно ли места в массиве
    if (tree.size == tree.capacity) {
        // Удваиваем ёмкость, если массив заполнен
        int new_capacity = (tree.capacity == 0) ? 1 : tree.capacity * 2;
        
        // Выделяем новый массив удвоенного размера
        std::string* new_arr = new std::string[new_capacity]; 

        // Копируем все старые элементы в новый массив
        for (int i = 0; i < tree.size; i++) {
            new_arr[i] = tree.arr[i];
        }

        // Удаляем старый массив
        delete[] tree.arr; 

        // Обновляем указатель и вместимость
        tree.arr = new_arr;
        tree.capacity = new_capacity;
        std::cout << "Массив перераспределен. Новая вместимость: " << tree.capacity << std::endl;
    }
    // Добавляем новый элемент в конец массива (сохраняя полноту)
    tree.arr[tree.size] = val;
    // Увеличиваем счетчик размера
    tree.size++;
    std::cout << "Элемент '" << val << "' добавлен." << std::endl;
}

// Поиск элемента по значению (линейный поиск)
int search(const CompleteBinaryTree& tree, const std::string& val)
{
    // Перебираем все элементы от начала до текущего размера
    for(int i=0; i < tree.size; i++)
    {
        // Если элемент найден, возвращаем его индекс
        if(tree.arr[i] == val)
        {
            return i;
        }
    }
    // Если элемент не найден, возвращаем -1
    return -1;
}

// *** НОВЫЙ ДРЕВОВИДНЫЙ ВЫВОД ***
void print(const CompleteBinaryTree& tree) {
    if (tree.size == 0) {
        std::cout << "Дерево пусто." << std::endl;
        return;
    }
    std::cout << "--- Визуализация дерева (по уровням) ---\n";
    
    int level = 0;              // Текущий уровень (начиная с 0 - корень)
    int nodes_at_current_level = 1; // Количество узлов на текущем уровне (1, 2, 4, 8...)
    int current_index = 0;      // Индекс первого элемента текущего уровня в массиве

    while (current_index < tree.size) {
        
        // Выводим отступ: уменьшается с ростом уровня, чтобы имитировать пирамиду
        for (int i = 0; i < (4 - level) * 3; ++i) {
            std::cout << " ";
        }
        
        // Выводим узлы текущего уровня
        int nodes_printed = 0;
        for (int i = 0; i < nodes_at_current_level && current_index < tree.size; ++i) {
            std::cout << tree.arr[current_index];
            // Добавляем пробел между узлами
            if (i < nodes_at_current_level - 1 && current_index + 1 < tree.size) {
                 std::cout << "  "; // Двойной пробел для разделения
            }
            current_index++;
            nodes_printed++;
        }
        
        std::cout << "\n"; // Переход на новую строку для следующего уровня
        level++;
        nodes_at_current_level *= 2; // Удваиваем количество узлов на следующем уровне
    }
    std::cout << "------------------------------------------\n";
}

// Проверка на полноту
bool isComplete(const CompleteBinaryTree& tree)
{
    // Так как дерево реализовано на массиве и заполняется последовательно,
    // оно всегда считается полным по определению.
    return true;
}

// --- Реализация НОВЫХ ФУНКЦИЙ ---

/**
 * @brief Вычисляет высоту полного бинарного дерева БЕЗ <cmath>.
 * @return int Высота дерева (количество уровней). Сложность O(log N).
 */
int getHeight(const CompleteBinaryTree& tree) {
    if (tree.size == 0) {
        return 0; // Пустое дерево имеет высоту 0
    }
    int h = 0;
    int temp_size = tree.size;
    // Делим размер на 2 до тех пор, пока он не станет 0. 
    // Количество итераций равно floor(log2(N)) + 1, что и есть высота.
    while (temp_size > 0) {
        temp_size /= 2;
        h++;
    }
    return h;
}

/**
 * @brief Удаляет корневой элемент (по индексу 0).
 * @note Корень заменяется последним элементом для сохранения полноты.
 */
void delRoot(CompleteBinaryTree& tree) {
    if (tree.size == 0) {
        std::cout << "Ошибка: Дерево пусто, корень удалить невозможно." << std::endl;
        return;
    }
    
    // 1. Заменяем корень (индекс 0) последним элементом (индекс size - 1)
    tree.arr[0] = tree.arr[tree.size - 1];
    
    // 2. Уменьшаем размер дерева (фактически удаляя последний элемент)
    tree.size--;
    
    std::cout << "Корень дерева успешно удален и заменен последним элементом." << std::endl;
}

/**
 * @brief Удаляет элемент по заданному значению.
 * @note Сначала ищется элемент (O(N)), затем найденный элемент заменяется последним (O(1)).
 */
void delByValue(CompleteBinaryTree& tree, const std::string& val) {
    if (tree.size == 0) {
        std::cout << "Ошибка: Дерево пусто, удалить элемент невозможно." << std::endl;
        return;
    }

    // 1. Поиск элемента (O(N))
    int index = search(tree, val);

    if (index == -1) {
        std::cout << "Ошибка: Элемент '" << val << "' не найден." << std::endl;
        return;
    }

    // Если найденный элемент - НЕ последний
    if (index != tree.size - 1) {
        // 2. Замена: заменяем найденный элемент значением последнего
        tree.arr[index] = tree.arr[tree.size - 1];
    }
    
    // 3. Уменьшаем размер дерева (удаление последнего элемента)
    tree.size--;
    
    std::cout << "Элемент '" << val << "' успешно удален." << std::endl;
}