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

// �������������� ����� ��� ��������� �������� ���� ��
// �������, ����� ������������ ��������� ���������
void FineGrainList::AddToNodeValue(int value, int index)
{
	if (index < 0 || index >= size_list) return;

	Node* ptr_current = ptr_head;
	for (int i = 0; i < index; ++i) {
		ptr_current = ptr_current->ptr_next;
	}

	ptr_current->value += value;
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
	FineGrainList list(0);

	list.CreateNode(1, 1);
	list.CreateNode(2, 2);
	list.CreateNode(3, 3);
	list.CreateNode(4, 3);
	list.CreateNode(5, 1);

	list.PrintList();


	std::cout << "�������� ������� 2: " << list.GetNodeValue(2) << std::endl;

	list.AddToNodeValue(10, 5);

	// Use the reference returned by GetNodeValue to modify the node's value
	int& change_value = list.GetNodeValue(3);
	change_value = 123;

	std::cout << "�������� ������� 3: " << change_value << std::endl;

	list.PrintList();

	return 0;
}