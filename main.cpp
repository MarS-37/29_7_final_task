#include <iostream>

// ����������� �����
class Random
{
public:
	// ����������� �������
	virtual int GetRandNum(int start, int end) = 0;
};

// FineGrainQueue
class FineGrainList : public Random
{
public:
	// �����������, �������������� ������ ����
	FineGrainList(int value);
	// ����������, ����������� ������
	~FineGrainList();

	// ����������� �������
	int  GetRandNum(int start, int end) override;
	// ����� �������� ����
	void CreateNode(int value, int index);
	// ����� �������� ����
	void DeleteNode(int index);
	// ����� ��� ��������� �������� ���� �� �������
	void SetNodeValue(int value, int index);
	// ����� ��� ��������� �������� ���� �� �������
	int& GetNodeValue(int index);
	// ����� ��� ����������� �������� � ���� �� �������
	void AddToNodeValue(int value, int index);
	// ������ �����
	void PrintList();
	// ����� ���������� ������ ������
	int  GetListSize();

private:
	struct Node
	{
		// ������ ����
		int value;
		// ��������� �� ��������� ����
		Node* ptr_next;
	};

	// ��������� �� ������ �����
	Node* ptr_head;
	// ������ ����������
	int size_list;
};

// �����������, �������������� ������ ����
FineGrainList::FineGrainList(int value)
	: ptr_head(new Node{ value, nullptr }), size_list(1)
{
	// ������������� rand()
	std::srand(std::time(0));
}

// ����������, ����������� ������
FineGrainList::~FineGrainList()
{
	// �������� ��������� ������ �����
	Node* ptr_current = ptr_head;

	// ������������ ����� �����
	while (ptr_current != nullptr) {
		// ��������� ������� ���������
		Node* temp = ptr_current;
		// �������� ��������� ���������� ��������
		ptr_current = ptr_current->ptr_next;
		// ����������� ������ ����������� ��������
		delete temp;
	}
}

// ���������� ����������� ������� ��������� �����
int FineGrainList::GetRandNum(int start, int end)
{
	return start + rand() % ((end + 1) - start);
}

// ���������� ������ �������� ����
void FineGrainList::CreateNode(int value, int index)
{
	Node* new_node = new Node{ value, nullptr };

	// ���� ������ ������ ��� ����� 0
	if (index <= 0) {
		new_node->ptr_next = ptr_head;
		ptr_head = new_node;
	}
	// ���� ������ ������ ������� ����������
	else if (index >= size_list) {
		Node* ptr_current = ptr_head;

		while (ptr_current->ptr_next != nullptr) {
			ptr_current = ptr_current->ptr_next;
		}

		ptr_current->ptr_next = new_node;
	}
	// ������ � ��������� ����������
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

// ���������� ������ �������� ����
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

// ����� ��� ��������� �������� ���� �� �������
void FineGrainList::SetNodeValue(int value, int index)
{
	if (index < 0 || index >= size_list) return;

	Node* ptr_current = ptr_head;
	for (int i = 0; i < index; ++i) {
		ptr_current = ptr_current->ptr_next;
	}

	ptr_current->value = value;
}

// ����� ��� ��������� �������� ���� �� �������
// � ������������ ��������� ��������
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

// ������ ���������� List
void FineGrainList::PrintList()
{
	Node* ptr_current = ptr_head;

	while (ptr_current != nullptr) {
		std::cout << '[' << ptr_current->value << "]";
		ptr_current = ptr_current->ptr_next;
	}

	std::cout << std::endl;
}

// ����� ���������� ������ ������
int FineGrainList::GetListSize()
{
	return size_list;
}

int main()
{
	setlocale(LC_ALL, "");
	FineGrainList list(5);
	std::cout << "\n������ ���� ������: 0" << std::endl;
	list.PrintList();

	// ������� � �������� ���������
	int min{ -1 }, max{ 1 };

	while (list.GetListSize() < 20) {
		// �������� ����� �� 0 �� ������� ����� - 1
		int index = list.GetRandNum(0, list.GetListSize() - 1);

		// �������� �������� ����
		int value = list.GetNodeValue(index);

		// ��������� ����� ��������
		value += list.GetRandNum(min, max);

		// ���� �������� ���� ������ 10...
		if (value < 0) {
			if (list.GetListSize() > 1) {
				list.DeleteNode(index);
				std::cout << "\n������ ���� ������: " << index << std::endl;
				list.PrintList();
			}
			else {
				value = 5;
			}			
		}
		else {
			if (value > 10) {
				value = 5;

				list.CreateNode(5, index + 1);
				std::cout << "\n�������� ���� ������: " << index << std::endl;
				list.PrintList();
			}

			list.SetNodeValue(value, index);			
		}
	}


	return 0;
}