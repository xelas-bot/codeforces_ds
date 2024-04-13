### Trees

## Red-Black Tree Proof/Algorithm 
![Example](sketch/rbtree.drawio.svg)
*No way to color this tree following the rbtree rules, (try to allocate black nodes its impossible)*

Rules imposed on rb-tree:
let bh(x: node) -> # of black nodes on a path starting at x and ending at a leaf.
1. For every node, bh(x) is the same for every node->leaf path
2. Red nodes cannot touch other red nodes

Thus, looking at the diagram its pretty easy to see that if the height(x) is h, there must be at least h/2 black nodes. Furthermore, if the bh(x) is the same for
every path, the max height from a node is bh(x) * 2, every other "height" must have the same bh(x) but minimum h/2 nodes. Thus in the worst case one leg of the tree might be height h/2 and the other one h.


## Treap proof/algorithm