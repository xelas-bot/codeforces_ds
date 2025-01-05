#include <base_av_tree.hpp>


namespace trees {

template <std::totally_ordered K, typename V> 
class PrefixNode final : public BaseAVLNode<K,V,PrefixNode<K,V>>{
public:
    PrefixNode(K key, V val, PrefixNode<K,V>* parent) : BaseAVLNode<K,V,PrefixNode<K,V>>(key, val, parent)
    {
        this->weight = -1;
        this->prefix_sum = -1;
    };

    std::string toString() const override {
        return format("[{},{},{}]", this->key, this->weight, this->prefix_sum); 
    }

    void adjust_properties() override {
        BaseAVLNode<K,V,PrefixNode<K,V>>::adjust_properties();

        auto left_prefix = this->left != nullptr ? this->left->prefix_sum : 0;
        auto right_prefix = this->right != nullptr ? this->right->prefix_sum : 0;
        this->prefix_sum = left_prefix + this->weight + right_prefix;
    }

  int weight;
  int prefix_sum;
};

template <std::totally_ordered K, typename V>
requires AVLNodeType<K,V,PrefixNode>
class PrefixSumTree : public AVTree<K,V,PrefixNode>
{
public:
    PrefixSumTree() : AVTree<K,V,PrefixNode>() {}


    // Finds the first key that has at least sum units in front of it
    const PrefixNode<K,V>* find_prefix_sum(int sum) const {
        return find_prefix_sum_helper(this->root, sum);
    }

    PrefixNode<K,V>* insert(K key, V& val, int weight) {
        if (this->root == nullptr)
        {
            this->root = new PrefixNode<K,V>(key,val,nullptr);
            this->root->weight = weight;
            this->root->prefix_sum = weight;
            this->size++;
            return this->root;
        }
        auto* toAdjust = this->_insert(this->root, key, val);
        toAdjust->weight = weight;
        toAdjust->prefix_sum = weight;
        this->size++;
        this->_variant_adjustments(toAdjust);
        // TODO unneccesary logn lookup in rebalance (logn to find rebalance node)
        this->rebalance(this->root);
        return toAdjust;
    }


private:
    const PrefixNode<K,V>* find_prefix_sum_helper(const PrefixNode<K,V>* node, int sum) const {
        if (node == nullptr) return nullptr;

        int left_weight = (node->left != nullptr ? node->left->prefix_sum : 0) + node->weight;

        if (left_weight == sum) {
            return node;
        }

        if (left_weight > sum) {
            return find_prefix_sum_helper(node->left, sum);
        }

        return find_prefix_sum_helper(node->right, sum - left_weight);
    }


};

}