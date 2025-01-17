#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int main() {
    std::vector<std::vector<int>> adj_list = 
    {
        {0,1,3}, 
        {1,2}, 
        {2},
        {3}
    };

    int N = 4;
    vector<vector<int>> transitive_closure(4, vector<int>(4,0));

    std::vector<int> visited(N,0);
    for (int i = 0; i<N; ++i)
    {
        queue<int> q;
        q.push(i);
        visited[i] = 1;

        while (!q.empty())
        {
            auto element = q.front();
            q.pop();

            for (auto neighbor : adj_list[element])
            {
                if (visited[neighbor] == 1) {
                    transitive_closure[i][neighbor] = 1;
                    continue;
                }

                visited[neighbor] = 1;
                transitive_closure[i][neighbor] = 1;
                q.push(neighbor);
            }


        }
        visited.clear();
    }



    for (auto& row : transitive_closure)
    {
        for (auto& element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }


    return 1;
}