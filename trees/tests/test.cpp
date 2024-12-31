#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include <cstdint>
#include <vector>
#include "base_av_tree.hpp"
#include "prefix_sum_tree.hpp"
#include "utils.hpp"


using BaseAvTree = trees::AVTree<int, int, trees::AVNode>;
using PfxSumTree = trees::PrefixSumTree<int, int>;
using std::vector;
    
uint32_t factorial( uint32_t number ) {
    return number <= 1 ? number : factorial(number-1) * number;
}

TEST_CASE( "AVTree insertion/deletion", "[correctness]" ) {
    BaseAvTree tree;
    int one = 1;
    vector<int> keys = {10, 15, 17, 12, 5, 1, 7, 18, 20, 8, -1, 3};
    for (int key : keys) {
        auto node = tree.insert(key, one);
        std::cout << format("Inserting {}", (void*)tree.root) << std::endl;
        REQUIRE(node->key == key);
    }

    std::vector<int> inOrder;
    utils::inOrderTraversal(tree.root, inOrder);

    std::sort(keys.begin(), keys.end());
    REQUIRE(inOrder == keys);

    for (int key : keys) {
        auto* node = tree.find(key, tree.root);
        REQUIRE(node->key == key);
    }

    for (int key : keys) {
        auto* node = tree.find(key, tree.root);
        REQUIRE(node->key == key);
        if (tree.size > 3) {
            utils::printTree(tree.root);
        }
        tree.delete_node(key);
    }
}

TEST_CASE( "PrefixSumTree insertion/deletion", "[correctness]" ) {
    PfxSumTree tree;
    int one = 1;
    vector<int> keys = {10, 15, 17, 12, 5, 1, 7, 18, 20, 8, -1, 3};
    for (int key : keys) {
        auto node = tree.insert(key, one,1);
        std::cout << format("Inserting {}", (void*)tree.root) << std::endl;
        REQUIRE(node->key == key);
    }

    std::vector<int> inOrder;
    utils::inOrderTraversal(tree.root, inOrder);

    std::sort(keys.begin(), keys.end());
    REQUIRE(inOrder == keys);

    for (int key : keys) {
        auto* node = tree.find(key, tree.root);
        REQUIRE(node->key == key);
    }

    for (int key : keys) {
        auto* node = tree.find(key, tree.root);
        REQUIRE(node->key == key);
        if (tree.size > 3) {
            utils::printTree(tree.root);
        }
        tree.delete_node(key);
    }
}