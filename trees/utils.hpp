#pragma once
#include <iostream>
#include <utility>
#include <algorithm>
#include "base_av_tree.hpp"

using namespace trees;
using std::pair;
using std::max;
using std::string;


namespace utils
{

template <std::totally_ordered K, typename V>
pair<size_t,size_t> wideness(AVNode<K,V>* root)
{
    if (root->right == nullptr && root->left == nullptr)
    {
        return pair<size_t,size_t>{0,0};
    }

    size_t right_wideness = 0;
    size_t left_wideness =0;
    size_t inside_right_wideness = 0;
    size_t inside_left_wideness =0;

    size_t ret_left_wideness = 0;
    size_t ret_right_wideness = 0;

    if (root->left != nullptr)
    {
        auto ovr_wideness = wideness(root->left);
        inside_left_wideness = ovr_wideness.second;
        left_wideness = ovr_wideness.first;
        ret_left_wideness = max((size_t)2, 2 * inside_left_wideness);
    }

    if (root->right != nullptr)
    {
        auto ovr_wideness = wideness(root->right);
        inside_right_wideness = ovr_wideness.first;
        right_wideness = ovr_wideness.second;
        ret_right_wideness = max((size_t)2, 2 * inside_right_wideness);
    }


    return pair<size_t,size_t>{ret_left_wideness + left_wideness, ret_right_wideness + right_wideness};

}

template <std::totally_ordered T>
T maxPair(std::pair<T,T> p)
{
    return std::max(p.first, p.second);
}

template <std::totally_ordered K, typename V> void inOrderTraversal(AVNode<K,V>* root) 
{
    if (root == nullptr)
    {
        return;
    }

    inOrderTraversal(root->left);
    std::cout << root->toString() << std::endl;
    inOrderTraversal(root->right);
}

namespace {
template <std::totally_ordered K, typename V>
void _printTree(std::vector<std::vector<string>>& board, size_t x, size_t y, AVNode<K,V>* root)
{       
        if (root == nullptr)
        {
            return;
        }


        auto node = root->toString();
        size_t start = x - (node.length()/2);

        for (size_t i =0; i<node.length(); ++i)
        {
            board[y][start + i] = node[i];
        }

        auto wd = wideness(root);
        size_t toDrawRight = wd.second;
        size_t toDrawLeft = wd.first;

        if (root->left != nullptr)
        {
            for (size_t i = 1; i<=toDrawLeft; ++i) {
                board[y+i][x-i] = "/";
            }
        }

        if (root->right != nullptr)
        {
            for (size_t i = 1; i<=toDrawRight; ++i) {
                board[y+i][x+i] = "\\";
            }
        }

        _printTree(board, x-toDrawLeft - 1 , y+toDrawLeft + 1, root->left);
        _printTree(board, x+toDrawRight+1, y+toDrawRight + 1, root->right);

}
}

template <std::totally_ordered K, typename V>  void printTree(AVNode<K,V>* root) 
{
    size_t wdn = maxPair(wideness(root));

    std::cout << wdn << std::endl;

    std::vector<std::vector<string>> board(wdn*root->height, std::vector<string>(wdn*root->height * 1.5, " "));

    auto print2DVector = [](const std::vector<std::vector<string>>& vec) {
        for (const auto& row : vec) {
            for (auto& val : row) {
                std::cout << val;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };
    _printTree(board, board[0].size() / 2, 0, root);
    print2DVector(board);
}

}