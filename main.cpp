#include <iostream>


class List
{
public:
	List();
	~List();

	void PushBack(int data);
	void PushFront(int data);
	void Insert(int pos, int data);
	int  GetSize() const { return list_size; }
	void Delete(int index);
	void ClearList();
	void PrintList();

private:
	struct Node
	{
		Node* p_next;
		int data;

		Node(int data = int(), Node* p_next = nullptr) : data(data), p_next(p_next) {}
	};

	// pointer the first node
	Node* p_head;
	int list_size;
};

List::List() : p_head(nullptr), list_size(0) {}
List::~List() 
{
	ClearList();
}

// down the list
void List::PushBack(int data)
{
	if (p_head == nullptr) {
		// if the list is empty,
		// create a new one
		p_head = new Node(data);
	}
	else {
		Node* p_current = p_head;

		while (p_current->p_next != nullptr) {
			p_current = p_current->p_next;
		}

		// add new node to the end list
		p_current->p_next = new Node(data);
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
		Node* p_current = p_head;
		
		for (int i = 0; i < pos - 1; ++i) {
			p_current = p_current->p_next;
		}

		p_current->p_next = new Node(data, p_current->p_next);
		++list_size;
	}
}

// delete element by index
void List::Delete(int index)
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
			Node* p_current = p_head;

			for (int i = 0; i < index - 1; ++i) {
				p_current = p_current->p_next;
			}

			p_delete = p_current->p_next;
			p_current->p_next = p_delete->p_next;
		}

		delete p_delete;
		--list_size;
}

// sheet cleaning
void List::ClearList()
{
	while (p_head != nullptr) {
		Node* temp = p_head;
		p_head = p_head->p_next;
		delete temp;
	}

	list_size = 0;
}

// print list
void List::PrintList()
{	
	// заглушка дл€ красоты вывода. 
	if (p_head != nullptr) std::cout << "\nnode data:\n";

	Node* p_current = p_head;

	while (p_current != nullptr) {
		std::cout << "(" << p_current->data << ") [" << p_current->p_next << "]\n";
		p_current = p_current->p_next;
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

	list.PrintList();

	list.PushFront(6);
	list.PushFront(7);
	list.PushFront(8);
	list.PushFront(9);
	list.PushFront(10);
	list.PushFront(11);

	list.PrintList();

	list.Insert(0, 12);
	list.Insert(2, 13);
	list.Insert(4, 14);
	list.Insert(5, 15);
	list.Insert(7, 16);
	list.Insert(10, 17);

	std::cout << "In container holds " << list.GetSize() << " items\n";

	list.PrintList();

	list.Delete(0);
	list.Delete(3);
	list.Delete(7);
	list.Delete(9);
	list.Delete(10);
	list.Delete(11);

	std::cout << "After remove nodes " << list.GetSize() << " items\n";

	list.PrintList();

	list.ClearList();

	std::cout << "After cleaning list " << list.GetSize() << " items\n";

	list.PrintList();



	return 0;
}

/*
* –≈«”Ћ№“ј“:
node data:
(0) [0000019172C71ED0]
(1) [0000019172C71CF0]
(2) [0000019172C71160]
(3) [0000019172C71D40]
(4) [0000019172C71B60]
(5) [0000000000000000]

node data:
(11) [0000019172C712F0]
(10) [0000019172C712A0]
(9) [0000019172C71E30]
(8) [0000019172C71F20]
(7) [0000019172C71DE0]
(6) [0000019172C71B10]
(0) [0000019172C71ED0]
(1) [0000019172C71CF0]
(2) [0000019172C71160]
(3) [0000019172C71D40]
(4) [0000019172C71B60]
(5) [0000000000000000]
In container holds 18 items

node data:
(12) [0000019172C71E80]
(11) [0000019172C713E0]
(13) [0000019172C712F0]
(10) [0000019172C71430]
(14) [0000019172C717A0]
(15) [0000019172C712A0]
(9) [0000019172C71F70]
(16) [0000019172C71E30]
(8) [0000019172C71F20]
(7) [0000019172C71480]
(17) [0000019172C71DE0]
(6) [0000019172C71B10]
(0) [0000019172C71ED0]
(1) [0000019172C71CF0]
(2) [0000019172C71160]
(3) [0000019172C71D40]
(4) [0000019172C71B60]
(5) [0000000000000000]
After remove nodes 12 items

node data:
(11) [0000019172C713E0]
(13) [0000019172C712F0]
(10) [0000019172C717A0]
(15) [0000019172C712A0]
(9) [0000019172C71F70]
(16) [0000019172C71E30]
(8) [0000019172C71480]
(17) [0000019172C71DE0]
(6) [0000019172C71ED0]
(1) [0000019172C71160]
(3) [0000019172C71B60]
(5) [0000000000000000]
After cleaning list 0 items
*/