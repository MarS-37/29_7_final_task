#include <iostream>

// абстрактный класс
class Random
{
public:
	// виртуальная функция
	virtual int GetRandNum(int start, int end) = 0;
};

// FineGrainQueue
class FineGrainList : public Random
{
public:
	// конструктор, инициализирует первый узел
	FineGrainList(int value);
	// деструктор, освобождаем память
	~FineGrainList();

	// виртуальная функция
	int  GetRandNum(int start, int end) override;
	// метод создание узла
	void CreateNode(int value, int index);
	// метод удаления узла
	void DeleteNode(int index);
	// метод для изменения значения узла по индексу
	void SetNodeValue(int value, int index);
	// метод для получения значения узла по индексу
	int& GetNodeValue(int index);
	// метод для прибавления значения к узлу по индексу
	void AddToNodeValue(int value, int index);
	// печать листа
	void PrintList();
	// метод возвращает размер списка
	int  GetListSize();

private:
	struct Node
	{
		// данные узла
		int value;
		// указатель на следующий узел
		Node* ptr_next;
	};

	// указатель на начало листа
	Node* ptr_head;
	// размер контейнера
	int size_list;
};

// конструктор, инициализирует первый узел
FineGrainList::FineGrainList(int value)
	: ptr_head(new Node{ value, nullptr }), size_list(1)
{
	// инициализация rand()
	std::srand(std::time(0));
}

// деструктор, освобождаем память
FineGrainList::~FineGrainList()
{
	// получаем указатель начала листа
	Node* ptr_current = ptr_head;

	// поэлементный обход листа
	while (ptr_current != nullptr) {
		// сохраняем текущий указатель
		Node* temp = ptr_current;
		// получаем указатель следующего элемента
		ptr_current = ptr_current->ptr_next;
		// освобождаем память предыдущего элемента
		delete temp;
	}
}

// реализация виртуальной функции случауное число
int FineGrainList::GetRandNum(int start, int end)
{
	return start + rand() % ((end + 1) - start);
}

// реализация метода создания нода
void FineGrainList::CreateNode(int value, int index)
{
	Node* new_node = new Node{ value, nullptr };

	// если индекс меньше или равен 0
	if (index <= 0) {
		new_node->ptr_next = ptr_head;
		ptr_head = new_node;
	}
	// если индекс больше размера контейнера
	else if (index >= size_list) {
		Node* ptr_current = ptr_head;

		while (ptr_current->ptr_next != nullptr) {
			ptr_current = ptr_current->ptr_next;
		}

		ptr_current->ptr_next = new_node;
	}
	// индекс в диапазоне контейнера
	else {
		Node* ptr_current = ptr_head;

		for (int i = 1; i < index; ++i) {
			ptr_current = ptr_current->ptr_next;
		}

		new_node->ptr_next = ptr_current->ptr_next;
		ptr_current->ptr_next = new_node;
	}

	++size_list;
}

// реализация метода удаления узла
void FineGrainList::DeleteNode(int index)
{
	if (index < 0 || ptr_head == nullptr) return;

	Node* ptr_to_delete = nullptr;

	if (index == 0) {
		ptr_to_delete = ptr_head;
		ptr_head = ptr_head->ptr_next;
	}
	else {
		Node* ptr_current = ptr_head;
		for (int i = 1; i < index && ptr_current->ptr_next->ptr_next != nullptr; ++i) {
			ptr_current = ptr_current->ptr_next;
		}
		ptr_to_delete = ptr_current->ptr_next;
		ptr_current->ptr_next = ptr_to_delete->ptr_next;
	}

	delete ptr_to_delete;
	--size_list;
}

// метод для изменения значения узла по индексу
void FineGrainList::SetNodeValue(int value, int index)
{
	if (index < 0 || index >= size_list) return;

	Node* ptr_current = ptr_head;
	for (int i = 0; i < index; ++i) {
		ptr_current = ptr_current->ptr_next;
	}

	ptr_current->value = value;
}

// метод для получения значения узла по индексу
// с возможностью изменения значения
int& FineGrainList::GetNodeValue(int index)
{
	if (index < 0 || index >= size_list)
		throw std::out_of_range("Index out of range");

	Node* ptr_current = ptr_head;
	for (int i = 0; i < index; ++i) {
		ptr_current = ptr_current->ptr_next;
	}

	return ptr_current->value;
}

// альтернативный метод для изменения значения узла по
// индексу, метод соответстует алгоритму программы
void FineGrainList::AddToNodeValue(int value, int index)
{
	if (index < 0 || index >= size_list) return;

	Node* ptr_current = ptr_head;
	for (int i = 0; i < index; ++i) {
		ptr_current = ptr_current->ptr_next;
	}

	ptr_current->value += value;
}

// печать контейнера List
void FineGrainList::PrintList()
{
	Node* ptr_current = ptr_head;

	while (ptr_current != nullptr) {
		std::cout << '[' << ptr_current->value << "]";
		ptr_current = ptr_current->ptr_next;
	}

	std::cout << std::endl;
}

// метод возвращает размер списка
int FineGrainList::GetListSize()
{
	return size_list;
}

int main()
{
	setlocale(LC_ALL, "");
	FineGrainList list(0);

	list.CreateNode(1, 1);
	list.CreateNode(2, 2);
	list.CreateNode(3, 3);
	list.CreateNode(4, 3);
	list.CreateNode(5, 1);

	list.PrintList();


	std::cout << "Значение индекса 2: " << list.GetNodeValue(2) << std::endl;

	list.AddToNodeValue(10, 5);

	// Use the reference returned by GetNodeValue to modify the node's value
	int& change_value = list.GetNodeValue(3);
	change_value = 123;

	std::cout << "Значение индекса 3: " << change_value << std::endl;

	list.PrintList();

	return 0;
}