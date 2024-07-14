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
	void GetNodeValue(int& value, int index);
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