#include <iostream>
#include "base_av_tree.hpp"
#include "utils.hpp"

int main() {
    // Print a welcome message
    std::cout << "Hello, world!" << std::endl;
    trees::AVTree< int, int, trees::AVNode> tree;
    int one = 1;

    tree.insert(10,one);
    tree.insert(15,one);
    tree.insert(17,one);
    tree.insert(12,one);


    tree.insert(5,one);
    
    tree.insert(1,one);

    tree.insert(7,one);

    tree.insert(18,one);
    tree.insert(20,one);
    tree.insert(8,one);
    tree.insert(-1,one);
    tree.insert(3,one);

    std::cout << utils::wideness(tree.root).first << " " << utils::wideness(tree.root).second << std::endl;

    utils::printTree(tree.root);

    return 0;
}