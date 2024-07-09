#include <iostream>


struct Node
{
	Node* p_next;
	int data;

	Node(int data = int(), Node* p_next = nullptr) : data(data), p_next(p_next) {}
};


class List
{
public:
	List();
	~List();

private:
	// pointer the first node
	Node* ptr_head;
};

List::List() : ptr_head(nullptr) {}
List::~List() {}

int main()
{

}


