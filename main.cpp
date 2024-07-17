//+------------------------------------------------------------------+
//|                      29.7. Final assignment                      |
//|                                                                  |
//|              TESTED: MSVC v.143 - VS 2022 C++ 86/64              |
//|                                                                  |
//|                   https://github.com/MarS-37/29_7_final_task.git |
//|                                       markin.sergey.37@yandex.ru |
//+------------------------------------------------------------------+

#include "FineGrain.h"


void ThreadFunction(FineGrainList& list, int max_node_count, int new_value_node, int min, int max)
{
    while (list.GetListSize() < max_node_count) {
        // getting the list size
        int list_size = list.GetListSize();
        // getting a random index
        int index = list.GetRandNum(0, std::max(0, list_size - 1));
        // getting the node value
        int value = list.GetNodeValue(index);
        // changing the node value
        value += list.GetRandNum(min, max);

        if (value < 0) {
            // deleting the node
            if (list.GetListSize() > 1) {
                list.DeleteNode(index);
                list.PrintListInfo();
            }
            else {
                value = new_value_node;
            }
        }
        else {
            if (value > 10) {
                value = new_value_node;
                // creating a new node
                list.CreateNode(new_value_node, index + 1);
                list.PrintListInfo();
            }

            // setting the new node value
            list.SetNodeValue(value, index);
        }
    }
}


int main()
{
    setlocale(LC_ALL, "");

    // maximum number of nodes
    const int max_node_count = 10;
    // initial node value
    const int new_value_node = 5;
    // node change range
    const int min = -1, max = 1;
    // number of threads
    const int num_threads = 2;

    // creating the first node with index 0
    FineGrainList list(new_value_node);

    list.PrintListInfo();

    // creating threads
    std::vector<std::thread> threads;

    for (size_t i = 0; i < num_threads; ++i) {
        // adding threads to the vector
        threads.emplace_back(ThreadFunction, std::ref(list), max_node_count, new_value_node, min, max);
    }

    for (auto& t : threads) {
        // waiting for all threads to finish
        t.join();
    }

    std::cout << "\nProgram executed, maximum number of nodes reached: "
        << max_node_count << std::endl;


    return 0;
}
