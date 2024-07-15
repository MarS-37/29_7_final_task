#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <locale>
#include <algorithm>


// абстрактный класс
class Random
{
public:
    virtual int GetRandNum(int start, int end) = 0;
};


// название класса по заданию FineGrainedQueue заменено на 
// FineGrainList, из-за использования "Linked-List"
class FineGrainList : public Random
{
public:
    FineGrainList(int value);
    ~FineGrainList() = default;

    // получает случацное число в диапазоне start, end
    int GetRandNum(int start, int end) override;
    // добавляет новый узел в заданное место, замена предложенной
    // по заданию insertIntoMiddle(int value, int pos)
    void CreateNode(int value, int index);
    // удаляет узел по индексу
    void DeleteNode(int index);
    //  устанавливает значение узла
    void SetNodeValue(int value, int index);
    // универсальный метод возвращает значение узла, 
    // добавлена возможность изменения значения узла
    int& GetNodeValue(int index);
    // выводит список "Linked-List"
    void PrintList() const;
    // возвращает размер списка
    int GetListSize() const;

private:
    struct Node
    {
        // значение
        int value;
        // 
        std::unique_ptr<Node> ptr_next;
        std::mutex node_mutex;

        Node(int val) : value(val), ptr_next(nullptr) {}
    };

    std::unique_ptr<Node> ptr_head;
    mutable std::mutex head_mutex;
    int size_list;

    // вспомогательные флаги
    // добавление узлов
    int last_added_index;
    mutable bool flag_last_added;
    // удаление узлов
    int last_deleted_index;
    mutable bool flag_last_deleted;
};

FineGrainList::FineGrainList(int value)
    : ptr_head(std::make_unique<Node>(value)), size_list(1), last_added_index(0), flag_last_added(true)
{
    std::srand(std::time(0));
}

int FineGrainList::GetRandNum(int start, int end)
{
    return start + rand() % ((end + 1) - start);
}

void FineGrainList::CreateNode(int value, int index)
{
    auto p_new_node = std::make_unique<Node>(value);

    std::unique_lock<std::mutex> head_lock(head_mutex);
    if (index <= 0) {
        p_new_node->ptr_next = std::move(ptr_head);
        ptr_head = std::move(p_new_node);
        last_added_index = 0;
    }
    else {
        Node* ptr_current = ptr_head.get();
        std::unique_lock<std::mutex> lock(ptr_current->node_mutex);
        for (int i = 1; i < index; ++i) {
            Node* next_node = ptr_current->ptr_next.get();
            if (next_node) {
                std::unique_lock<std::mutex> next_lock(next_node->node_mutex);
                lock.unlock();
                ptr_current = next_node;
                lock = std::move(next_lock);
            }
        }

        p_new_node->ptr_next = std::move(ptr_current->ptr_next);
        ptr_current->ptr_next = std::move(p_new_node);
        last_added_index = index;
    }

    std::cout << "\nДобавлен узел индекс: " << index << std::endl;

    flag_last_added = true;
    // flag_last_deleted = false;
    ++size_list;
}

void FineGrainList::DeleteNode(int index)
{
    last_deleted_index = index;

    std::unique_lock<std::mutex> head_lock(head_mutex);
    if (index < 0 || index >= size_list) return;

    if (index == 0) {
        ptr_head = std::move(ptr_head->ptr_next);
    }
    else {
        Node* ptr_current = ptr_head.get();
        std::unique_lock<std::mutex> lock(ptr_current->node_mutex);

        for (int i = 1; i < index && ptr_current->ptr_next; ++i) {
            Node* next_node = ptr_current->ptr_next.get();

            if (next_node) {
                std::unique_lock<std::mutex> next_lock(next_node->node_mutex);
                lock.unlock();
                ptr_current = next_node;
                lock = std::move(next_lock);
            }
        }

        if (ptr_current && ptr_current->ptr_next) {
            ptr_current->ptr_next = std::move(ptr_current->ptr_next->ptr_next);
        }
    }

    std::cout << "\nУдаляем узел индекс: " << index << std::endl;

    // flag_last_added = false;
    flag_last_deleted = true;
    --size_list;
}

void FineGrainList::SetNodeValue(int value, int index)
{
    std::unique_lock<std::mutex> head_lock(head_mutex);
    if (index < 0 || index >= size_list) return;

    Node* ptr_current = ptr_head.get();
    std::unique_lock<std::mutex> lock(ptr_current->node_mutex);
    for (int i = 0; i < index; ++i) {
        Node* next_node = ptr_current->ptr_next.get();
        if (next_node) {
            std::unique_lock<std::mutex> next_lock(next_node->node_mutex);
            lock.unlock();
            ptr_current = next_node;
            lock = std::move(next_lock);
        }
    }

    ptr_current->value = value;
}

int& FineGrainList::GetNodeValue(int index)
{
    std::unique_lock<std::mutex> head_lock(head_mutex);
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }
    if (index >= size_list) {
        index = size_list - 1;
    }

    Node* ptr_current = ptr_head.get();
    std::unique_lock<std::mutex> lock(ptr_current->node_mutex);
    for (int i = 0; i < index; ++i) {
        Node* next_node = ptr_current->ptr_next.get();
        if (next_node) {
            std::unique_lock<std::mutex> next_lock(next_node->node_mutex);
            lock.unlock();
            ptr_current = next_node;
            lock = std::move(next_lock);
        }
    }

    return ptr_current->value;
}

void FineGrainList::PrintList() const
{
    std::unique_lock<std::mutex> head_lock(head_mutex);
    Node* ptr_current = ptr_head.get();
    int index = 0;

    do {
        std::unique_lock<std::mutex> lock(ptr_current->node_mutex);
        if (flag_last_added && index == last_added_index && ptr_current->value == 5) {
            std::cout << "\033[1;32m[" << ptr_current->value << "]\033[0m";
            ptr_current = ptr_current->ptr_next.get();
            flag_last_added = false;
        }
        else if (flag_last_deleted && index == last_deleted_index) {
            std::cout << "\033[1;31m[" << "x" << "]\033[0m";
            flag_last_deleted = false;
            --index;
        }
        else {
            std::cout << '[' << ptr_current->value << "]";
            ptr_current = ptr_current->ptr_next.get();
        }

        ++index;

        if (flag_last_deleted && index == last_deleted_index) {
            std::cout << "\033[1;31m[" << "x" << "]\033[0m";
            flag_last_deleted = false;
            --index;
        }
                
    } while (ptr_current);

    std::cout << std::endl;
}

int FineGrainList::GetListSize() const
{
    std::unique_lock<std::mutex> lock(head_mutex);
    return size_list;
}

void ThreadFunction(FineGrainList& list, int max_node_count, int new_value_node, int min, int max)
{
    while (list.GetListSize() < max_node_count) {
        int list_size = list.GetListSize();
        int index = list.GetRandNum(0, std::max(0, list_size - 1));
        int value = list.GetNodeValue(index);
        value += list.GetRandNum(min, max);

        if (value < 0) {
            if (list.GetListSize() > 1) {
                list.DeleteNode(index);

                list.PrintList();
            }
            else {
                value = new_value_node;
            }
        }
        else {
            if (value > 10) {
                value = new_value_node;
                list.CreateNode(new_value_node, index + 1);

                list.PrintList();
            }

            list.SetNodeValue(value, index);
        }
    }
}


int main()
{
    setlocale(LC_ALL, "");

    // максимальное количество узлов
    const int max_node_count = 10;
    // начальное значение узлов
    const int new_value_node = 5;
    // диапазон изменения узлов
    const int min = -1, max = 1;
    // количество потоков
    const int num_threads = 4;

    FineGrainList list(new_value_node);

    // создание первого узла с индексом 0
    std::cout << "\nСоздан узел индекс: 0" << std::endl;
    list.PrintList();

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(ThreadFunction, std::ref(list), max_node_count, new_value_node, min, max);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "\nПрограмма выполнена, достигнуто максимальное количество узлов: "
        << max_node_count << std::endl;


    // std::system("pause");

    return 0;
}