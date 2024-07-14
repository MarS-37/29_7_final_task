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
	void GetNodeValue(int& value, int index);
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