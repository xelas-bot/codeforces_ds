#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include <cstdint>
#include <random>
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

TEST_CASE( "PfxSumTree load test", "[correctness]" ) {
    PfxSumTree tree;
    int one = 1;
    vector<int> keys;
    keys.reserve(100000);

    // Generate 100000 random unique keys
    for (int i = 0; i < 100000; i++) {
        keys.push_back(i - 50000); // Generate keys from -50000 to 49999
    }

    // Shuffle the keys randomly
    auto rng = std::default_random_engine{};
    std::shuffle(keys.begin(), keys.end(), rng);

    // Insert all keys
    for (int key : keys) {
        auto node = tree.insert(key, one, 1);
        REQUIRE(node->key == key);
    }

    REQUIRE(tree.size == 100000);

    // Check in-order traversal matches sorted keys
    std::vector<int> inOrder;
    utils::inOrderTraversal(tree.root, inOrder);

    std::sort(keys.begin(), keys.end());
    REQUIRE(inOrder == keys);

    // Verify we can find all keys
    for (int key : keys) {
        auto* node = tree.find(key, tree.root);
        REQUIRE(node->key == key);
    }

    // Delete all nodes and verify size decreases
    for (int key : keys) {
        tree.delete_node(key);
    }

    REQUIRE(tree.root == nullptr);
    REQUIRE(tree.size == 0);

}

TEST_CASE( "PrefixSumTree insertion/deletion", "[correctness]" ) {
    PfxSumTree tree;
    int one = 1;
    vector<int> keys = {10, 15, 17, 12, 5, 1, 7, 18, 20, 8, -1, 3};
    for (int key : keys) {
        auto node = tree.insert(key, one,1);
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
        tree.delete_node(key);
    }
}