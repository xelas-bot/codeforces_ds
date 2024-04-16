#pragma once
#include <iostream>
#include <type_traits>
#include <concepts>
#include <compare>

template <std::totally_ordered K, class V> 
class AVNode final
{
public:
    AVNode* left;
    AVNode* right;
    AVNode* parent;

    K key;
    V val;
    int height;

    AVNode(K key, V val) : 
    key(key), 
    val(val) {
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
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

    virtual N<K,V>* insert(K& key, V& val)
    {
        if (this->root == nullptr)
        {
            this->root = new N(key,val);
            return this->root;
        }
        
        return;
    }

    const virtual N<K,V>* find(K& key, N<K,V>* root) 
    {
        if (root->key == key)
        {
            return root;
        }

        if (root->key > key && root->right != nullptr)
        {
            return find(key, root->right);
        }

        if (root->key < key && root->left != nullptr)
        {
            return find(key, root->left);
        }


        return root;
    }

    bool rebalance(N<K,V>* node)
    {
        return node.isred;
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

};











