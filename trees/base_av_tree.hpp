#pragma once
#define FMT_HEADER_ONLY 
#include <iostream>
#include <type_traits>
#include <concepts>
#include <compare>
#include "../fmt/format.h"

using std::max;
using fmt::format;

namespace trees {

template <std::totally_ordered K, typename V> 
class AVNode final
{
public:
    AVNode* left;
    AVNode* right;
    AVNode* parent;

    K key;
    V val;
    size_t height;

    AVNode(K key, V val, AVNode* parent) : 
    key(key), 
    val(val),
    parent(parent) {
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }

    std::string toString()
    {
        return format("[{},{}]", key, height); 
    }

};



// bare minimum needed to implement an avtree
template < std::totally_ordered K, typename V, template <typename, typename> class N>
class AVTree
{
public:
    static_assert(std::is_base_of<AVNode<K,V>, N<K,V>>::value, "");
    static_assert(std::is_final_v<N<K,V>> == true);

    N<K,V>* root;

    AVTree()
    {
        this->root = nullptr;
    }

    // can make this slightly faster by inserting a pointer to a node directly
    // this prevents us from copying 2 address each time we recurse down the tree
    virtual void insert(K key, V& val)
    {
        if (this->root == nullptr)
        {
            this->root = new N<K,V>(key,val,nullptr);
            return;
        }

        _insert(this->root, key, val);
    }

    const virtual N<K,V>* find(K& key, N<K,V>* root) 
    {
        if (root->key == key)
        {
            return root;
        }

        if (root->key < key && root->right != nullptr)
        {
            return find(key, root->right);
        }

        if (root->key > key && root->left != nullptr)
        {
            return find(key, root->left);
        }


        return root;
    }

    bool rebalance(N<K,V>* node)
    {
        return false;
    }

private:
    void r_r(N<K,V>* node)
    {

    }

    void l_r(N<K,V>* node)
    {

    }

    void rl_r(N<K,V>* node)
    {

    }

    void lr_r(N<K,V>* node)
    {

    }

    void _delete(N<K,V>* node)
    {
        auto* toDelete = find(node->key, this->root);
        if (toDelete->left == nullptr && toDelete->right == nullptr)
        {
            toDelete->parent->left = nullptr;
            toDelete->parent->right = nullptr;
        }

    }


    void _insert(N<K,V>* root, K key, V& val)
    {
        N<K,V>* left = root->left;
        N<K,V>* right = root->right;

        if (key < root->key)
        {
            if (left == nullptr)
            {
                root->left = new N<K,V>(key,val,nullptr);
                root->left->parent = root;
            } else{
                _insert(root->left,key,val);
            }


            size_t l_h = root->left->height;
            size_t r_h = root->right != nullptr ? root->right->height : 0;
            root->height = max(r_h, l_h) + 1;

        } else if (key > root->key)
        {
            if (right == nullptr)
            {
                root->right = new N<K,V>(key,val,nullptr);
                root->right->parent = root;
                std::cout << format("Me:{},{},{} ", (void*)root->right, root->right->toString(), (void*)root->right->parent) << std::endl;
                
            } else {
                _insert(root->right,key,val);
            }

            size_t r_h = root->right->height;
            size_t l_h = root->left != nullptr ? root->left->height : 0;
            root->height = max(r_h, l_h) + 1;

        }else {
            root->val = val;
        }
    }

};

}











