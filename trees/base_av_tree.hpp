#pragma once
#include <cassert>
#define FMT_HEADER_ONLY 
#include <iostream>
#include <type_traits>
#include <concepts>
#include <compare>
#include <format.h>

using std::max;
using fmt::format;

namespace trees {

template<typename T>
class BaseNode{
public:
  T* parent;
  T* left;
  T* right;
};

template <std::totally_ordered K, typename V, typename NodeType>
class BaseAVLNode : public BaseNode<NodeType>{

public:
    K key;
    V val;
    size_t height;

    BaseAVLNode(K key, V val, NodeType* parent) : 
    key(key), 
    val(val)
    {
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
        this->parent = parent;
    }

    std::string toString()
    {
        return format("[{},{}]", key, height); 
    }
};


template <std::totally_ordered K, typename V> 
class AVNode final : public BaseAVLNode<K,V,AVNode<K,V>>{
public:
  AVNode(K key, V val, AVNode<K,V>* parent) : BaseAVLNode<K,V,AVNode<K,V>>(key, val, parent){};
};


template<typename K, typename V, template<typename, typename> class N>
concept AVLNodeType = std::is_base_of_v<BaseAVLNode<K,V,N<K,V>>, N<K,V>>
                     && std::is_final_v<N<K,V>>;

                     
template < std::totally_ordered K, typename V, template <typename, typename> class N>
requires AVLNodeType<K,V,N>
class AVTree
{
public:

    N<K,V>* root;
    size_t size;

    AVTree()
    {
        this->root = nullptr;
        this->size = 0;
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
        this->size++;
    }

    // Returns 
    virtual N<K,V>* find(K& key, N<K,V>* root) 
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


        return nullptr;
    }

    void delete_node(K key)
    {
        auto* node = find(key, this->root);
        auto* toAdjust = _delete(node);
        this->size--;
        _variant_adjustments(toAdjust);
    }

    N<K,V>* find_rebalance_node(N<K,V>* node)
    {
        int diff = get_height_diff(node);

        std::cout << format("[{},{}]", node->key, diff) << std::endl;

        if (abs(diff) <= 1)
        {
            return nullptr;
        }

        int right_diff = get_height_diff(node->right);
        int left_diff = get_height_diff(node->left);

        if (abs(right_diff) > 1)
        {
            return find_rebalance_node(node->right);
        }

        if (abs(left_diff) > 1)
        {
            return find_rebalance_node(node->left);
        }

        return node;
    }

private:

    inline int get_height_diff(N<K,V>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        auto* left = node->left;
        auto* right = node->right;

        int l_h = left != nullptr ? left->height : 0;
        int r_h = right != nullptr ? right->height : 0;

        return r_h - l_h;
    }

    void rebalance(N<K,V>* node)
    {
        auto* rebalance_node = find_rebalance_node(node);
        if (rebalance_node == nullptr)
        {
            return;
        }

        int curr_diff = get_height_diff(rebalance_node);
        int left_diff = get_height_diff(rebalance_node->left);
        int right_diff = get_height_diff(rebalance_node->right);

        int left_height = rebalance_node->left != nullptr ? rebalance_node->left->height : 0;
        int right_height = rebalance_node->right != nullptr ? rebalance_node->right->height : 0;

        if (curr_diff == 2)
        {
            assert(right_diff == 1 || right_diff == -1);

            if (right_diff == 1) {
                r_r(rebalance_node);
            } else {
                l_l(rebalance_node->right);
                r_r(rebalance_node);
            }
        } else if (curr_diff == -2)
        {
            assert(left_diff == 1 || left_diff == -1);
            if (left_diff == 1) {
                r_r(rebalance_node->left);
                l_l(rebalance_node);
            } else {
                l_l(rebalance_node);
            }
        }

    }

    void r_r(N<K,V>* node)
    {
        auto* right = node->right;
        auto* parent = node->parent;

        if (parent->right == node)
        {
            parent->right = right;
        } else {
            parent->left = right;
        }

        auto* right_left = right->left;
        node->right = right_left;
        right_left->parent = node;

        node->parent = right;
        right->left = node;
    }

    void l_l(N<K,V>* node)
    {
        auto* left = node->left;
        auto* parent = node->parent;

        if (parent->right == node)
        {
            parent->right = left;
        } else {
            parent->left = left;
        }

        auto* left_right = left->right;
        node->left = left_right;
        left_right->parent = node;

        node->parent = left;
        left->right = node;
    }

    N<K,V>* arg_max(N<K,V>* node)
    {
        if (node->right == nullptr)
        {
            return node;
        }

        return arg_max(node->right);
    }

    // Starts from node, and goes up the tree, updating heights
    // TODO can probably move this to the node class itself
    void _variant_adjustments(N<K,V>* node)
    {
        if (node == nullptr)
        {
            return;
        }

        auto l_h = node->left != nullptr ? node->left->height : 0;
        auto r_h = node->right != nullptr ? node->right->height : 0;
        node->height = max(l_h, r_h) + 1;

        if (node->parent != nullptr)
        {
            _variant_adjustments(node->parent);
        }
    }

    N<K,V>* _delete(N<K,V>* root)
    {
        auto* parent = root->parent;
        auto* left = root->left;
        auto* right = root->right;
        N<K,V>* stub = nullptr;
        N<K,V>* newRoot = root;

        if (root->left == nullptr && root->right == nullptr)
        {
            if (parent) {
                if (parent->left == root) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            }
            stub = parent;
            newRoot = stub;
            delete root;
        }

        // Single child node
        if (left == nullptr && right != nullptr)
        {
            stub = right;
            stub->parent = parent;
            if (parent) {
                if (parent->left == root){
                    parent->left = stub;
                } else {
                    parent->right = stub;
                }
            }
            newRoot = stub;
            delete root;
        }

        if (right == nullptr && left != nullptr)
        {
            stub = left;
            stub->parent = parent;
            if (parent) {
                if (parent->left == root){
                    parent->left = stub;
                } else {
                    parent->right = stub;
                }
            }
            newRoot = stub;
            delete root;
        }


        if (right != nullptr && left != nullptr)
        {
            stub = arg_max(left);
            *root = *stub;
            root->parent = parent;
            root->left = left;
            root->right = right;
            stub = _delete(stub);
        }

        if (parent == nullptr)
        {
            this->root = newRoot;
        }

        return stub;
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











