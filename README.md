# Итоговое задание 29.7

## Реализация метода ___insertIntoMiddle___ _(int value, int pos)_ для списка с мелкогранулярной блокировкой.

// абстрактный класс, создан для примера использования абстрактных классов
class Random
	public virtual GetRandNum(начало диапазона, конец диапазона)


// класс работы с контейнером - односвязный список
class FineGrainList : public Random
	публичные методы
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

приватные методы:
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

