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
	void PushFront(int data);
	void Insert(int pos, int data);
	int GetSize() const { return list_size; }
	void DelNode(int index);
	void ClearList();

private:
	// pointer the first node
	Node* p_head;
	int list_size;
};

List::List() : p_head(nullptr), list_size(0) {}
List::~List() {}

// down the list
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

	++list_size;
}

// top of the list
void List::PushFront(int data)
{
	// create a node and tie
	// it to the current head
	p_head = new Node(data, p_head);
	++list_size;
}

// in the specified position
void List::Insert(int pos, int data)
{
	if (pos < 0 || pos > list_size)
		throw std::out_of_range("Index out of range");

	if (pos == 0) {
		PushFront(data);
	}
	else {
		Node* current = p_head;
		
		for (int i = 0; i < pos - 1; ++i) {
			current = current->p_next;
		}

		current->p_next = new Node(data, current->p_next);
		++list_size;
	}
}

// delete element by index
void List::DelNode(int index)
{
	if (index < 0 || index >= list_size)
		throw std::out_of_range("index out of range");

		Node* p_delete = nullptr;

		if (index == 0) {
			// delete first node
			p_delete = p_head;
			p_head = p_head->p_next;
		}
		else {
			Node* current = p_head;

			for (int i = 0; i < index; ++i) {
				current = current->p_next;
			}

			p_delete = current->p_next;
			current->p_next = p_delete->p_next;
		}

		delete p_delete;
		--list_size;
}

// sheet cleaning
void List::ClearList()
{
	p_head = nullptr;
	list_size = 0;
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

	list.PushFront(6);
	list.PushFront(7);
	list.PushFront(8);
	list.PushFront(9);
	list.PushFront(10);
	list.PushFront(11);

	list.Insert(0, 12);
	list.Insert(2, 13);
	list.Insert(4, 14);
	list.Insert(5, 15);
	list.Insert(7, 16);
	list.Insert(10, 17);

	std::cout << "In container holds " << list.GetSize() << " items\n";

	list.DelNode(0);
	list.DelNode(3);
	list.DelNode(7);
	list.DelNode(9);
	list.DelNode(10);
	list.DelNode(11);

	std::cout << "After remove nodes " << list.GetSize() << " items\n";

	list.ClearList();

	std::cout << "After cleaning list " << list.GetSize() << " items\n";


	return 0;
}


