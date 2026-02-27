package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// --- 1. Динамический массив (Dynamic Array) ---
// Структура для динамического массива, использующая срез (slice) Go.
type DynamicArray struct {
	data []string
}

// AddEnd - добавляет элемент в конец массива.
func (arr *DynamicArray) AddEnd(val string) {
	arr.data = append(arr.data, val)
	fmt.Println("Элемент добавлен в конец.")
}

// AddAt - добавляет элемент по указанному индексу.
func (arr *DynamicArray) AddAt(idx int, val string) {
	if idx < 0 || idx > len(arr.data) {
		fmt.Println("Ошибка: Некорректный индекс.")
		return
	}
	// Расширяем срез, вставляя пустой элемент, чтобы освободить место
	arr.data = append(arr.data, "")
	// Сдвигаем элементы вправо от индекса
	copy(arr.data[idx+1:], arr.data[idx:])
	// Вставляем новый элемент
	arr.data[idx] = val
	fmt.Printf("Элемент добавлен по индексу %d.\n", idx)
}

// DelAt - удаляет элемент по указанному индексу.
func (arr *DynamicArray) DelAt(idx int) {
	if idx < 0 || idx >= len(arr.data) {
		fmt.Println("Ошибка: Некорректный индекс.")
		return
	}
	// Удаляем элемент, соединяя части среза до и после индекса
	arr.data = append(arr.data[:idx], arr.data[idx+1:]...)
	fmt.Printf("Элемент по индексу %d удален.\n", idx)
}

// GetAt - получает элемент по индексу.
func (arr *DynamicArray) GetAt(idx int) {
	if idx < 0 || idx >= len(arr.data) {
		fmt.Println("Ошибка: Некорректный индекс.")
		return
	}
	fmt.Printf("Элемент по индексу %d: \"%s\"\n", idx, arr.data[idx])
}

// ReplaceAt - заменяет элемент по индексу.
func (arr *DynamicArray) ReplaceAt(idx int, val string) {
	if idx < 0 || idx >= len(arr.data) {
		fmt.Println("Ошибка: Некорректный индекс.")
		return
	}
	arr.data[idx] = val
	fmt.Printf("Элемент по индексу %d заменен.\n", idx)
}

// Length - возвращает длину массива.
func (arr *DynamicArray) Length() int {
	return len(arr.data)
}

// Print - выводит содержимое массива.
func (arr *DynamicArray) Print() {
	if len(arr.data) == 0 {
		fmt.Println("Массив пуст.")
		return
	}
	fmt.Println("Массив:", strings.Join(arr.data, ", "))
}

// --- 2. Односвязный список (Singly Linked List) ---
// Узел односвязного списка.
type SNode struct {
	value string
	next  *SNode
}

// Структура односвязного списка.
type SinglyList struct {
	head *SNode
}

// AddHead - добавляет элемент в начало списка.
func (list *SinglyList) AddHead(val string) {
	newNode := &SNode{value: val, next: list.head}
	list.head = newNode
}

// AddTail - добавляет элемент в конец списка.
func (list *SinglyList) AddTail(val string) {
	newNode := &SNode{value: val, next: nil}
	if list.head == nil {
		list.head = newNode
		return
	}
	current := list.head
	for current.next != nil {
		current = current.next
	}
	current.next = newNode
}

// DelHead - удаляет первый элемент.
func (list *SinglyList) DelHead() {
	if list.head == nil {
		fmt.Println("Список пуст.")
		return
	}
	list.head = list.head.next
	fmt.Println("Первый элемент удален.")
}

// Print - выводит список.
func (list *SinglyList) Print() {
	if list.head == nil {
		fmt.Println("Список пуст.")
		return
	}
	fmt.Print("Список: ")
	current := list.head
	for current != nil {
		fmt.Printf("\"%s\" ", current.value)
		current = current.next
	}
	fmt.Println()
}

// --- 3. Двусвязный список (Doubly Linked List) ---
// Узел двусвязного списка.
type DNode struct {
	value string
	next  *DNode
	prev  *DNode
}

// Структура двусвязного списка.
type DoublyList struct {
	head *DNode
	tail *DNode
}

// AddHead - добавляет элемент в начало.
func (list *DoublyList) AddHead(val string) {
	newNode := &DNode{value: val, next: list.head}
	if list.head != nil {
		list.head.prev = newNode
	}
	list.head = newNode
	if list.tail == nil {
		list.tail = newNode
	}
}

// AddTail - добавляет элемент в конец.
func (list *DoublyList) AddTail(val string) {
	newNode := &DNode{value: val, prev: list.tail}
	if list.tail != nil {
		list.tail.next = newNode
	}
	list.tail = newNode
	if list.head == nil {
		list.head = newNode
	}
}

// DelTail - удаляет последний элемент.
func (list *DoublyList) DelTail() {
	if list.tail == nil {
		fmt.Println("Список пуст.")
		return
	}
	if list.head == list.tail {
		list.head = nil
		list.tail = nil
	} else {
		list.tail = list.tail.prev
		list.tail.next = nil
	}
	fmt.Println("Последний элемент удален.")
}

// Print - выводит список вперед.
func (list *DoublyList) Print() {
	if list.head == nil {
		fmt.Println("Список пуст.")
		return
	}
	fmt.Print("Список (вперед): ")
	current := list.head
	for current != nil {
		fmt.Printf("\"%s\" ", current.value)
		current = current.next
	}
	fmt.Println()
}

// PrintReverse - выводит список назад.
func (list *DoublyList) PrintReverse() {
	if list.tail == nil {
		fmt.Println("Список пуст.")
		return
	}
	fmt.Print("Список (назад): ")
	current := list.tail
	for current != nil {
		fmt.Printf("\"%s\" ", current.value)
		current = current.prev
	}
	fmt.Println()
}

// --- 4. Очередь (Queue) ---
// Узел очереди.
type QNode struct {
	data string
	next *QNode
}

// Структура очереди.
type Queue struct {
	front *QNode
	rear  *QNode
}

// IsEmpty - проверка на пустоту.
func (q *Queue) IsEmpty() bool {
	return q.front == nil
}

// Push - добавление в конец очереди.
func (q *Queue) Push(val string) {
	newNode := &QNode{data: val}
	if q.rear != nil {
		q.rear.next = newNode
	}
	q.rear = newNode
	if q.front == nil {
		q.front = newNode
	}
}

// Pop - извлечение из начала очереди.
func (q *Queue) Pop() string {
	if q.IsEmpty() {
		fmt.Println("Очередь пуста.")
		return ""
	}
	data := q.front.data
	q.front = q.front.next
	if q.front == nil {
		q.rear = nil
	}
	return data
}

// Peek - просмотр первого элемента без удаления.
func (q *Queue) Peek() string {
	if q.IsEmpty() {
		fmt.Println("Очередь пуста.")
		return ""
	}
	return q.front.data
}

// Print - печать очереди.
func (q *Queue) Print() {
	if q.IsEmpty() {
		fmt.Println("Очередь пуста.")
		return
	}
	fmt.Print("Очередь (начало -> конец): ")
	current := q.front
	for current != nil {
		fmt.Printf("\"%s\" ", current.data)
		current = current.next
	}
	fmt.Println()
}

// --- 5. Стек (Stack) ---
// Узел стека.
type StackNode struct {
	value string
	next  *StackNode
}

// Структура стека.
type Stack struct {
	top *StackNode
}

// Push - добавление элемента на верхушку стека.
func (s *Stack) Push(val string) {
	newNode := &StackNode{value: val, next: s.top}
	s.top = newNode
}

// Pop - извлечение элемента с верхушки стека.
func (s *Stack) Pop() string {
	if s.top == nil {
		fmt.Println("Стек пуст.")
		return ""
	}
	val := s.top.value
	s.top = s.top.next
	return val
}

// Peek - просмотр верхнего элемента без удаления.
func (s *Stack) Peek() string {
	if s.top == nil {
		fmt.Println("Стек пуст.")
		return ""
	}
	return s.top.value
}

// Print - печать стека.
func (s *Stack) Print() {
	if s.top == nil {
		fmt.Println("Стек пуст.")
		return
	}
	fmt.Println("Содержимое стека (вершина -> низ):")
	current := s.top
	for current != nil {
		fmt.Println(current.value)
		current = current.next
	}
}

// --- 6. Полное бинарное дерево (Complete Binary Tree) ---
// Реализовано на основе массива/среза.
type CompleteBinaryTree struct {
	arr []string
}

// Insert - вставка элемента в дерево.
func (t *CompleteBinaryTree) Insert(val string) {
	t.arr = append(t.arr, val)
}

// Search - поиск элемента в дереве (возвращает индекс).
func (t *CompleteBinaryTree) Search(val string) int {
	for i, item := range t.arr {
		if item == val {
			return i
		}
	}
	return -1 // Элемент не найден
}

// Print - печать дерева (простой вывод элементов массива).
func (t *CompleteBinaryTree) Print() {
	if len(t.arr) == 0 {
		fmt.Println("Дерево пустое.")
		return
	}
	fmt.Println("Дерево:", strings.Join(t.arr, " "))
}

// IsComplete - по определению, эта реализация всегда является полным деревом.
func (t *CompleteBinaryTree) IsComplete() bool {
	return true
}

// --- Глобальные переменные для структур данных ---
var (
	arr    = &DynamicArray{}
	slist  = &SinglyList{}
	dlist  = &DoublyList{}
	queue  = &Queue{}
	stack  = &Stack{}
	tree   = &CompleteBinaryTree{}
	reader = bufio.NewReader(os.Stdin)
)

// --- Функции для сохранения/загрузки данных ---

// saveData - универсальная функция для сохранения данных в файл.
func saveData(filename string, data []string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка при создании файла:", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	for _, line := range data {
		fmt.Fprintln(writer, line)
	}
	writer.Flush()
	fmt.Printf("Данные сохранены в %s\n", filename)
}

// loadData - универсальная функция для загрузки данных из файла.
func loadData(filename string) []string {
	file, err := os.Open(filename)
	if err != nil {
		// Файл может не существовать при первом запуске, это не ошибка.
		return nil
	}
	defer file.Close()

	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	return lines
}

// --- Функции меню ---

func readString(prompt string) string {
	fmt.Print(prompt)
	input, _ := reader.ReadString('\n')
	return strings.TrimSpace(input)
}

func readInt(prompt string) int {
	fmt.Print(prompt)
	input, _ := reader.ReadString('\n')
	val, err := strconv.Atoi(strings.TrimSpace(input))
	if err != nil {
		return -1 // Возвращаем -1 в случае ошибки
	}
	return val
}

func arrayMenu() {
	for {
		fmt.Println("\n=== МЕНЮ: МАССИВ ===")
		fmt.Println("1. Добавить в конец")
		fmt.Println("2. Добавить по индексу")
		fmt.Println("3. Удалить по индексу")
		fmt.Println("4. Получить по индексу")
		fmt.Println("5. Заменить по индексу")
		fmt.Println("6. Узнать длину")
		fmt.Println("7. Показать массив")
		fmt.Println("0. Назад")
		choice := readInt("> ")

		switch choice {
		case 1:
			val := readString("Строка для добавления: ")
			arr.AddEnd(val)
		case 2:
			idx := readInt("Индекс: ")
			val := readString("Строка: ")
			arr.AddAt(idx, val)
		case 3:
			idx := readInt("Индекс: ")
			arr.DelAt(idx)
		case 4:
			idx := readInt("Индекс: ")
			arr.GetAt(idx)
		case 5:
			idx := readInt("Индекс: ")
			val := readString("Новая строка: ")
			arr.ReplaceAt(idx, val)
		case 6:
			fmt.Printf("Длина массива: %d\n", arr.Length())
		case 7:
			arr.Print()
		case 0:
			saveData("array.txt", arr.data)
			return
		default:
			fmt.Println("Неверный выбор!")
		}
	}
}

func singlyListMenu() {
	for {
		fmt.Println("\n=== МЕНЮ: ОДНОСВЯЗНЫЙ СПИСОК ===")
		fmt.Println("1. Добавить в начало")
		fmt.Println("2. Добавить в конец")
		fmt.Println("3. Удалить первый элемент")
		fmt.Println("4. Показать список")
		fmt.Println("0. Назад")
		choice := readInt("> ")

		switch choice {
		case 1:
			val := readString("Строка: ")
			slist.AddHead(val)
		case 2:
			val := readString("Строка: ")
			slist.AddTail(val)
		case 3:
			slist.DelHead()
		case 4:
			slist.Print()
		case 0:
			// Логика сохранения односвязного списка
			var data []string
			current := slist.head
			for current != nil {
				data = append(data, current.value)
				current = current.next
			}
			saveData("slist.txt", data)
			return
		default:
			fmt.Println("Неверный выбор!")
		}
	}
}

func doublyListMenu() {
	for {
		fmt.Println("\n=== МЕНЮ: ДВУСВЯЗНЫЙ СПИСОК ===")
		fmt.Println("1. Добавить в начало")
		fmt.Println("2. Добавить в конец")
		fmt.Println("3. Удалить последний элемент")
		fmt.Println("4. Показать список (вперед)")
		fmt.Println("5. Показать список (назад)")
		fmt.Println("0. Назад")
		choice := readInt("> ")

		switch choice {
		case 1:
			val := readString("Строка: ")
			dlist.AddHead(val)
		case 2:
			val := readString("Строка: ")
			dlist.AddTail(val)
		case 3:
			dlist.DelTail()
		case 4:
			dlist.Print()
		case 5:
			dlist.PrintReverse()
		case 0:
			// Логика сохранения двусвязного списка
			var data []string
			current := dlist.head
			for current != nil {
				data = append(data, current.value)
				current = current.next
			}
			saveData("dlist.txt", data)
			return
		default:
			fmt.Println("Неверный выбор!")
		}
	}
}

func queueMenu() {
	for {
		fmt.Println("\n=== МЕНЮ: ОЧЕРЕДЬ ===")
		fmt.Println("1. Добавить в очередь (push)")
		fmt.Println("2. Извлечь из очереди (pop)")
		fmt.Println("3. Прочитать первый элемент (peek)")
		fmt.Println("4. Показать очередь")
		fmt.Println("0. Назад")
		choice := readInt("> ")

		switch choice {
		case 1:
			val := readString("Строка: ")
			queue.Push(val)
		case 2:
			fmt.Println("Извлечен элемент:", queue.Pop())
		case 3:
			fmt.Println("Первый элемент:", queue.Peek())
		case 4:
			queue.Print()
		case 0:
			var data []string
			current := queue.front
			for current != nil {
				data = append(data, current.data)
				current = current.next
			}
			saveData("queue.txt", data)
			return
		default:
			fmt.Println("Неверный выбор!")
		}
	}
}

func stackMenu() {
	for {
		fmt.Println("\n=== МЕНЮ: СТЕК ===")
		fmt.Println("1. Добавить в стек (push)")
		fmt.Println("2. Извлечь из стека (pop)")
		fmt.Println("3. Прочитать верхний элемент (peek)")
		fmt.Println("4. Показать стек")
		fmt.Println("0. Назад")
		choice := readInt("> ")

		switch choice {
		case 1:
			val := readString("Строка: ")
			stack.Push(val)
		case 2:
			fmt.Println("Извлечен элемент:", stack.Pop())
		case 3:
			fmt.Println("Верхний элемент:", stack.Peek())
		case 4:
			stack.Print()
		case 0:
			var data []string
			current := stack.top
			for current != nil {
				data = append(data, current.value)
				current = current.next
			}
			saveData("stack.txt", data)
			return
		default:
			fmt.Println("Неверный выбор!")
		}
	}
}

func treeMenu() {
	for {
		fmt.Println("\n=== МЕНЮ: ДЕРЕВО ===")
		fmt.Println("1. Вставить в дерево")
		fmt.Println("2. Найти в дереве по значению")
		fmt.Println("3. Проверить, является ли дерево полным")
		fmt.Println("4. Показать дерево")
		fmt.Println("0. Назад")
		choice := readInt("> ")
		switch choice {
		case 1:
			val := readString("Строка: ")
			tree.Insert(val)
		case 2:
			val := readString("Строка для поиска: ")
			idx := tree.Search(val)
			if idx != -1 {
				fmt.Printf("Элемент найден по индексу %d\n", idx)
			} else {
				fmt.Println("Элемент не найден.")
			}
		case 3:
			if tree.IsComplete() {
				fmt.Println("Это полное бинарное дерево.")
			}
		case 4:
			tree.Print()
		case 0:
			saveData("tree.txt", tree.arr)
			return
		default:
			fmt.Println("Неверный выбор!")
		}
	}
}

// --- Основная функция программы ---
func main() {
	// Загрузка данных из файлов
	arr.data = loadData("array.txt")
	for _, val := range loadData("slist.txt") {
		slist.AddTail(val)
	}
	for _, val := range loadData("dlist.txt") {
		dlist.AddTail(val)
	}
	for _, val := range loadData("queue.txt") {
		queue.Push(val)
	}
	// Для стека загружаем в обратном порядке, чтобы сохранить структуру
	stackData := loadData("stack.txt")
	for i := len(stackData) - 1; i >= 0; i-- {
		stack.Push(stackData[i])
	}
	tree.arr = loadData("tree.txt")
	fmt.Println("Данные из файлов загружены.")

	// Главное меню
	for {
		fmt.Println("\n=== ГЛАВНОЕ МЕНЮ ===")
		fmt.Println("1. Массив")
		fmt.Println("2. Односвязный список")
		fmt.Println("3. Двусвязный список")
		fmt.Println("4. Стек")
		fmt.Println("5. Очередь")
		fmt.Println("6. Полное бинарное дерево")
		fmt.Println("0. Выход")
		choice := readInt("Выберите структуру данных: ")

		switch choice {
		case 1:
			arrayMenu()
		case 2:
			singlyListMenu()
		case 3:
			doublyListMenu()
		case 4:
			stackMenu()
		case 5:
			queueMenu()
		case 6:
			treeMenu()
		case 0:
			fmt.Println("Завершение работы.")
			return
		default:
			fmt.Println("Неверный выбор!")
		}
	}
}