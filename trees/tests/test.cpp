#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include <cstdint>
#include <vector>
#include "base_av_tree.hpp"
#include "utils.hpp"


using BaseAvTree = trees::AVTree< int, int, trees::AVNode >;
using std::vector;

uint32_t factorial( uint32_t number ) {
    return number <= 1 ? number : factorial(number-1) * number;
}

TEST_CASE( "Tree insertion/deletion", "[correctness]" ) {
    BaseAvTree tree;
    int one = 1;
    vector<int> keys = {10, 15, 17, 12, 5, 1, 7, 18, 20, 8, -1, 3};
    for (int key : keys) {
        tree.insert(key, one);
    }

    for (int key : keys) {
        auto* node = tree.find(key, tree.root);
        assert(node->key == key);
    }

    for (int key : keys) {
        auto* node = tree.find(key, tree.root);
        assert(node->key == key);
        tree.delete_node(key);
    }
}