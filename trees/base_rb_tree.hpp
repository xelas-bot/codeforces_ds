#pragma once
#include <iostream>


template <class K, class V> 
class RBNode
{
public:
    RBNode* left;
    RBNode* right;
    K key;
    V val;
    bool isred;

    RBNode(K key, V val, bool is_red) : 
    key(key), 
    val(val), 
    isred(is_red) {}

    bool is_red()
    {
        return this->isred;
    }
};



// bare minimum needed to implement an rbtree
template < typename K, typename V, template <typename, typename> class N>
class RBTree
{
public:
    static_assert(std::is_base_of<RBNode<K,V>, N<K,V>>::value, "");
    N<K,V>* root;

    RBTree(N<K,V>* root) : root(root)
    {
        this->root->isred = true;
    }

    virtual void insert(N<K,V>* node, int (*func)(N<K,V>*, N<K,V>*) )
    {
        std::cout << node->is_red() << std::endl; 
        return;
    }

    virtual void find(N<K,V>* node, int (*func)(N<K,V>*, N<K,V>*))
    {
        std::cout << node->is_red() << std::endl; 
        return;
    }

};











