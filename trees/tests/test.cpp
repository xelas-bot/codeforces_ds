#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include <cstdint>
#include <random>
#include <vector>
#include "base_av_tree.hpp"
#include "prefix_sum_tree.hpp"
#include <nanobench.h>
#include "utils.hpp"
#include <atomic>


using BaseAvTree = trees::AVTree<int, int, trees::AVNode>;
using PfxSumTree = trees::PrefixSumTree<int, int>;
using std::vector;


ankerl::nanobench::Bench get_bench()
{
    auto bench = ankerl::nanobench::Bench()
    .timeUnit(std::chrono::milliseconds(1), "ms")
    .minEpochIterations(15)
    .warmup(2)
    .performanceCounters(false);

    return bench;
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

    for (size_t i = 0; i < inOrder.size(); i++) {
        auto* node = tree.find_prefix_sum(i + 1);
        REQUIRE(node->key == inOrder[i]);
    }

    auto* node = tree.find_prefix_sum(70);
    REQUIRE(node == NULL);

    node = tree.find_prefix_sum(7);
    REQUIRE(node->key == 10);


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

TEST_CASE( "avtree_benchmark", "[benchmark]" ) {
    BaseAvTree tree;
    int one = 1;
    vector<int> keys;
    size_t N = 10000;
    keys.reserve(N);

    for (size_t i = 0; i < N; i++) {
        keys.push_back(i - (N/2));
    }

    auto rng = std::default_random_engine{};
    std::shuffle(keys.begin(), keys.end(), rng);

    for (int key : keys) {
        auto node = tree.insert(key, one);
        REQUIRE(node->key == key);
    }

    auto bench = get_bench();

    REQUIRE(tree.size == N);

    bench.run("baseline", [&] {
        for (size_t i = 0; i < N; i++) {
            int num = i - (N/2);
            auto val = std::find(keys.begin(), keys.end(), num);
            assert(val != keys.end());
        }
    });

    bench.run("avtree", [&] {
        for (size_t i = 0; i < N; i++) {
            int num = i - (N/2);
            auto found = tree.find(num, tree.root);
            assert(num == found->key);
        }
    });

    auto res = bench.results();

    auto baseline_res = res[0].median(ankerl::nanobench::Result::Measure::elapsed);
    auto avtree_res = res[1].median(ankerl::nanobench::Result::Measure::elapsed);

    REQUIRE(baseline_res > 150 * avtree_res);
}


TEST_CASE( "avtree_complexity", "[benchmark]" ) {

    auto bench = get_bench();
    BaseAvTree tree;
    ankerl::nanobench::Rng rng;
    int one = 1;

    // Running the benchmark multiple times, with different number of elements
    for (auto setSize :
         {1000U, 1500U, 2000U, 2500U, 3500U, 5000U, 10000U, 15000U, 20000U, 25000U}) {
        
            while (tree.size < setSize - 10) {
                tree.insert(rng(), one);
            }
            // Run the benchmark, provide setSize as the scaling variable.
            bench.complexityN(tree.size).run("avtree_insert", [&] {
                while (tree.size < setSize) {
                    tree.insert(rng(), one);
                }
            });
    }

    auto res = bench.complexityBigO();
    std::cout << res[0].name() << std::endl;
    assert(res[0].name() == "O(log(n))" || res[0].name() == "O(1)");

}