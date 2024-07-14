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