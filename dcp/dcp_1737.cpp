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

/*
Given an array of integers in which two elements appear exactly once and all other elements appear exactly twice, find the two elements that appear only once.

For example, given the array [2, 4, 6, 8, 10, 2, 6, 10], return 4 and 8. The order does not matter.
Can you do this in linear time and constant space?
*/


// approach 1: develop custom hashing function? Preprocessing runs in O(n^2) but once function is
// built, its a mathematical function
/*
Our function h(x) should have the following properties:
For every x1,x2 pair in our input array, h(x1) mod N != h(x2) mod N, if h(x) = ax + b then
ax1 + b mod N != ax2 + b mod N, ax1 - ax2 mod N != 0 mod N -> a(x1 - x2) mod N != 0 mod N

approach 2:
pick prime P such that P > max(N)
---- Both approaches impossible -- See https://en.wikipedia.org/wiki/Perfect_hash_function#Construction
--- lowest bound in space for perfect hash is o(n)
*/


std::pair<int, int> find_two_unique_numbers(std::vector<int>& elements)
{
    return std::make_pair(0, 0);
}

int main() {

    return 1;
}