#include <iostream>
#include "base_av_tree.hpp"

int main() {
    // Print a welcome message
    std::cout << "Hello, world!" << std::endl;
    trees::AVTree< int, int, trees::AVNode > tree;
    int zero = 0;
    int one = 1;
    int two = 2;

    tree.insert(one,one);
    tree.insert(zero,zero);
    tree.insert(two,two);


    std::cout << tree.find(one, tree.root)->height << std::endl;
    std::cout << tree.root->val << std::endl;

    // Return 0 to indicate successful execution
    return 0;
}