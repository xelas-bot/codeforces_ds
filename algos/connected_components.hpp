#include <set>
#include <unordered_set>
#include <vector>

using std::unordered_set;
using std::vector;


// Slow way to get connected components
// we dont use the fact that for numerical (int,uint etc) types we dont 
// need to use a hashmap for visited
// template <typename T> 
// vector<unordered_set<T>> get_connected_components_slow(vector<vector<T>> adj_list) 
// {

//     vector<unordered_set<T>> toReturn;
//     unordered_set<T> visited;
// }