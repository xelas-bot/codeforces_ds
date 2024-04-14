#include <iostream>
#include "base_rb_tree.hpp"

int main() {
    // Print a welcome message
    std::cout << "Hello, world!" << std::endl;

    RBNode<int,int> myNode(0,0,true);

    RBTree<int,int,RBNode> myTree(&myNode);

    myTree.insert(&myNode);
    myTree.find(&myNode);


    // Return 0 to indicate successful execution
    return 0;
}