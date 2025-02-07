#include <cstddef>
#include <iostream>
#include <vector>
#include <queue>
#include "../trees/prefix_sum_tree.hpp"
#include "../trees/utils.hpp"

using std::vector;
using std::queue;

using PfxSumTree = trees::PrefixSumTree<int, int>;
using utils::inOrderTraversal;



std::vector<int> k_sort(std::vector<int>& k_jumbled, size_t k)
{
    PfxSumTree k_tree;
    std::vector<int> toReturn;
    toReturn.reserve(k_jumbled.size());

    int dummy_val = 0;

    for (auto i : k_jumbled)
    {
        k_tree.insert(i, dummy_val, 1);
        
        if (k_tree.size == k+1)
        {
            auto min = k_tree.find_prefix_sum(1);
            toReturn.push_back(min->key);
            k_tree.delete_node(min->key);
        }
    }

    inOrderTraversal(k_tree.root, toReturn);

    return toReturn;
}

int main() {
    // K Sorted Array

    // k=2, [1,2,3,4,5,6]
    // k=3, [3,1,2,6,5,4]

    std::vector<int> k_array{3,1,2,6,5,4};
    auto op = k_sort(k_array, 2);

    for (auto i : op)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 1;
}