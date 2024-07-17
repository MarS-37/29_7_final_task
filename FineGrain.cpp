#include "FineGrain.h"

FineGrainList::FineGrainList(int value)
    : ptr_head(std::make_unique<Node>(value)), size_list(1), last_added_index(0), flag_last_added(true)
{
    // initializing the random number generator
    std::srand(std::time(0));
}

int FineGrainList::GetRandNum(int min, int end)
{
    // generating a random number
    return min + rand() % ((end + 1) - min);
}

void FineGrainList::CreateNode(int value, int index)
{
    // creating a new node
    auto p_new_node = std::make_unique<Node>(value);
    // locking the head of the list
    std::unique_lock<std::mutex> head_lock(head_mutex);

    if (index <= 0) {
        // inserting a new node at the beginning of the list
        p_new_node->ptr_next = std::move(ptr_head);
        ptr_head = std::move(p_new_node);
        // updating the index of the last added node
        std::lock_guard<std::mutex> last_added_lock(last_added_mutex);
        last_added_index = 0;
    }
    else {
        // finding a place to insert the new node
        Node* ptr_current = ptr_head.get();
        std::unique_lock<std::mutex> lock(ptr_current->node_mutex);

        for (size_t i = 1; i < index; ++i) {
            // moving to the next node
            Node* next_node = ptr_current->ptr_next.get();

            if (next_node) {
                // 
                std::unique_lock<std::mutex> next_lock(next_node->node_mutex);
                // 
                lock.unlock();
                // 
                ptr_current = next_node;
                // 
                lock = std::move(next_lock);
            }
        }

        // inserting the new node
        p_new_node->ptr_next = std::move(ptr_current->ptr_next);
        ptr_current->ptr_next = std::move(p_new_node);
        // updating the index of the last added node
        std::lock_guard<std::mutex> last_added_lock(last_added_mutex);
        last_added_index = index;
    }

    // updating the last added flag
    std::lock_guard<std::mutex> flag_last_added_lock(flag_last_added_mutex);

    flag_last_added = true;
    ++size_list;
}

void FineGrainList::DeleteNode(int index)
{
    // locking the last deleted node
    std::lock_guard<std::mutex> last_deleted_lock(last_deleted_mutex);

    last_deleted_index = index;

    // locking the head of the list
    std::unique_lock<std::mutex> head_lock(head_mutex);

    if (index < 0 || index >= size_list) return;

    if (index == 0) {
        // deleting the head of the list
        ptr_head = std::move(ptr_head->ptr_next);
    }
    else {
        // finding the node to delete
        Node* ptr_current = ptr_head.get();

        std::unique_lock<std::mutex> lock(ptr_current->node_mutex);

        for (size_t i = 1; i < index && ptr_current->ptr_next; ++i) {

            Node* next_node = ptr_current->ptr_next.get();

            if (next_node) {
                std::unique_lock<std::mutex> next_lock(next_node->node_mutex);
                lock.unlock();
                ptr_current = next_node;
                lock = std::move(next_lock);
            }
        }

        if (ptr_current && ptr_current->ptr_next) {
            // deleting the node
            ptr_current->ptr_next = std::move(ptr_current->ptr_next->ptr_next);
        }
    }

    // updating the last deleted flag
    std::lock_guard<std::mutex> flag_last_deleted_lock(flag_last_deleted_mutex);

    flag_last_deleted = true;
    --size_list;
}

void FineGrainList::SetNodeValue(int value, int index)
{
    // locking the head of the list
    std::unique_lock<std::mutex> head_lock(head_mutex);

    if (index < 0 || index >= size_list) return;

    // finding the node to change value
    Node* ptr_current = ptr_head.get();

    std::unique_lock<std::mutex> lock(ptr_current->node_mutex);

    for (size_t i = 0; i < index; ++i) {
        Node* next_node = ptr_current->ptr_next.get();

        if (next_node) {
            std::unique_lock<std::mutex> next_lock(next_node->node_mutex);
            lock.unlock();
            ptr_current = next_node;
            lock = std::move(next_lock);
        }
    }

    // changing the node value
    ptr_current->value = value;
}

int& FineGrainList::GetNodeValue(int index)
{
    // locking the head of the list
    std::unique_lock<std::mutex> head_lock(head_mutex);

    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }

    if (index >= size_list) {
        index = size_list - 1;
    }

    // finding the node to get value
    Node* ptr_current = ptr_head.get();

    std::unique_lock<std::mutex> lock(ptr_current->node_mutex);

    for (size_t i = 0; i < index; ++i) {
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

void FineGrainList::PrintListInfo() const
{
    // if there was an addition or deletion of a node
    if (flag_last_added || flag_last_deleted) {
        // locking the head of the list
        std::unique_lock<std::mutex> head_lock(head_mutex);

        // pointer to the current node
        Node* ptr_current = ptr_head.get();

        {
            // locking the last added flag
            std::lock_guard<std::mutex> flag_last_added_lock(flag_last_added_mutex);

            if (flag_last_added)
                std::cout << "\nIndex node added: " << last_added_index << std::endl;
        }
        {
            // locking the last deleted flag
            std::lock_guard<std::mutex> flag_last_deleted_lock(flag_last_deleted_mutex);

            if (flag_last_deleted)
                std::cout << "\nDeleting the index node: " << last_deleted_index << std::endl;
        }

        unsigned int index = 0;

        do {
            // locking the current node
            std::unique_lock<std::mutex> lock(ptr_current->node_mutex);
            {
                // locking the last added flag
                std::lock_guard<std::mutex> flag_last_added_lock(flag_last_added_mutex);

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
            }

            ++index;

            // locking the last deleted flag
            std::lock_guard<std::mutex> flag_last_deleted_lock(flag_last_deleted_mutex);

            if (flag_last_deleted && index == last_deleted_index) {
                std::cout << "\033[1;31m[" << "x" << "]\033[0m";
                flag_last_deleted = false;
                --index;
            }

        } while (ptr_current);

        std::cout << std::endl;
    }
}

int FineGrainList::GetListSize() const
{
    // locking the head of the list
    std::unique_lock<std::mutex> lock(head_mutex);
    return size_list;
}
