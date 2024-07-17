#pragma once
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>
#include <thread>
#include <locale>
#include <mutex>
#include <ctime>

// abstract class/
class Random
{
public:
    virtual int GetRandNum(int start, int end) = 0;
};


// the class name by task FineGrainedQueue is replaced with
// FineGrainList due to the use of "Linked-List"
class FineGrainList : public Random
{
public:
    FineGrainList(int value);
    ~FineGrainList() = default;

    // gets a random number in the range min, max
    int GetRandNum(int start, int end) override;
    // adds a new node at the given place, replacing the suggested
    // by task insertIntoMiddle(int value, int pos)
    void CreateNode(int value, int index);
    // removes a node by index
    void DeleteNode(int index);
    // sets the node value
    void SetNodeValue(int value, int index);
    // universal method returns the node value, 
    // added the ability to change the node value
    int& GetNodeValue(int index);
    // prints the "Linked-List"
    void PrintListInfo() const;
    // returns the list size
    int GetListSize() const;

private:
    struct Node
    {
        // value
        int value;
        // pointer to the next node
        std::unique_ptr<Node> ptr_next;
        //  node mutex
        std::mutex node_mutex;
        // node constructor
        Node(int val) : value(val), ptr_next(nullptr) {}
    };

    // pointer to the head of the list
    std::unique_ptr<Node> ptr_head;
    // head mutex
    mutable std::mutex head_mutex;
    int size_list;

    // auxiliary flags
    // adding nodes
    int last_added_index;
    mutable bool flag_last_added;
    // mutex for the last added node
    mutable std::mutex last_added_mutex;
    // mutex for the last added flag
    mutable std::mutex flag_last_added_mutex;
    // index deleting nodes
    int last_deleted_index;
    mutable bool flag_last_deleted;
    // mutex for the last deleted node
    mutable std::mutex last_deleted_mutex;
    // mutex for the last deleted flag
    mutable std::mutex flag_last_deleted_mutex;
};