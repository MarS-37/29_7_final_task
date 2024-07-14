#include <iostream>
#include <memory>
#include <random>
#include <ctime>


class Random {
public:
    virtual int GetRandNum(int start, int end) = 0;
};


class FineGrainList : public Random {
public:
    FineGrainList(int value);
    ~FineGrainList();

    int GetRandNum(int start, int end) override;
    void CreateNode(int value, int index);
    void DeleteNode(int index);
    void SetNodeValue(int value, int index);
    int& GetNodeValue(int index);
    void PrintList();
    int GetListSize();

private:
    struct Node {
        int value;
        std::unique_ptr<Node> ptr_next;

        Node(int val) : value(val), ptr_next(nullptr) {}
    };

    std::unique_ptr<Node> ptr_head;
    int size_list;

    // индекс последнего добавленного узла
    int last_added_index;
    // флаг для подсветки последнего добавленного узла
    bool flag_last_added;

    std::mt19937 rng;
};

FineGrainList::FineGrainList(int value)
    : ptr_head(std::make_unique<Node>(value)), size_list(1), rng(std::random_device{}()),
    last_added_index(-1), flag_last_added(false) {}

FineGrainList::~FineGrainList() = default;

int FineGrainList::GetRandNum(int start, int end) {
    std::uniform_int_distribution<int> dist(start, end);
    return dist(rng);
}

void FineGrainList::CreateNode(int value, int index) {
    auto new_node = std::make_unique<Node>(value);

    if (index <= 0) {
        new_node->ptr_next = std::move(ptr_head);
        ptr_head = std::move(new_node);
        last_added_index = 0;
    }
    else if (index >= size_list) {
        Node* ptr_current = ptr_head.get();
        while (ptr_current->ptr_next) {
            ptr_current = ptr_current->ptr_next.get();
        }
        ptr_current->ptr_next = std::move(new_node);
        last_added_index = size_list;
    }
    else {
        Node* ptr_current = ptr_head.get();
        for (int i = 1; i < index; ++i) {
            ptr_current = ptr_current->ptr_next.get();
        }
        new_node->ptr_next = std::move(ptr_current->ptr_next);
        ptr_current->ptr_next = std::move(new_node);
        last_added_index = index;
    }

    flag_last_added = true;
    ++size_list;
}

void FineGrainList::DeleteNode(int index) {
    if (index < 0 || index >= size_list) return;

    if (index == 0) {
        ptr_head = std::move(ptr_head->ptr_next);
    }
    else {
        Node* ptr_current = ptr_head.get();
        for (int i = 1; i < index && ptr_current->ptr_next; ++i) {
            ptr_current = ptr_current->ptr_next.get();
        }
        if (ptr_current && ptr_current->ptr_next) {
            ptr_current->ptr_next = std::move(ptr_current->ptr_next->ptr_next);
        }
    }

    flag_last_added = false;
    --size_list;
}

void FineGrainList::SetNodeValue(int value, int index) {
    if (index < 0 || index >= size_list) return;

    Node* ptr_current = ptr_head.get();
    for (int i = 0; i < index; ++i) {
        ptr_current = ptr_current->ptr_next.get();
    }

    ptr_current->value = value;
}

int& FineGrainList::GetNodeValue(int index) {
    if (index < 0 || index >= size_list) {
        throw std::out_of_range("Index out of range");
    }

    Node* ptr_current = ptr_head.get();
    for (int i = 0; i < index; ++i) {
        ptr_current = ptr_current->ptr_next.get();
    }

    return ptr_current->value;
}

void FineGrainList::PrintList() {
    Node* ptr_current = ptr_head.get();
    int index = 0;

    while (ptr_current) {
        if (flag_last_added && index == last_added_index && ptr_current->value == 5) {
            std::cout << "\033[1;32m[" << ptr_current->value << "]\033[0m";
        }
        else {
            std::cout << '[' << ptr_current->value << "]";
        }
        ptr_current = ptr_current->ptr_next.get();
        ++index;
    }

    std::cout << std::endl;
}

int FineGrainList::GetListSize() {
    return size_list;
}


int main() {
    setlocale(LC_ALL, "");
    FineGrainList list(5);
    std::cout << "\nСоздан узел индекс: 0" << std::endl;
    list.PrintList();

    int min{ -1 }, max{ 1 };

    while (list.GetListSize() < 20) {
        int index = list.GetRandNum(0, list.GetListSize() - 1);
        int value = list.GetNodeValue(index);
        value += list.GetRandNum(min, max);

        if (value < 0) {
            if (list.GetListSize() > 1) {
                list.DeleteNode(index);
                std::cout << "\nУдален узел индекс: " << index << std::endl;
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
                std::cout << "\nДобавлен узел индекс: " << index + 1 << std::endl;
                list.PrintList();
            }

            list.SetNodeValue(value, index);
        }
    }

    return 0;
}