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