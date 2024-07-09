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

	void PushBack(int data);

private:
	// pointer the first node
	Node* p_head;
};

List::List() : p_head(nullptr) {}
List::~List() {}

void List::PushBack(int data)
{
	if (p_head == nullptr) {
		// if the list is empty,
		// create a new one
		p_head = new Node(data);
	}
	else {
		Node* current = p_head;

		while (current->p_next != nullptr) {
			current = current->p_next;
		}

		// add new node to the end list
		current->p_next = new Node(data);
	}
}


int main()
{
	List list;

	list.PushBack(0);
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);
	list.PushBack(5);


	return 0;
}


