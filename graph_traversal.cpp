#include <iostream>
#include <vector>
#include <array>
#include <stack>
using namespace std;

/*
    Find all possible paths from one node to another node using recursion
    @param adj_matrix   Adjacency matrix of the graph
    @param start        The beginning node 
    @param end          The destination node
*/
void find_all_paths(const vector<vector<int>> &adj_matrix, int start, int end)
{
    // Create three static variables that will not reset during recursion
    //      nNodes  -   the total number of nodes
    //      path    -   used to record the path
    //      visited -   used to record which node is visited before
    static int nNodes = adj_matrix[0].size();
    static vector<int> path;
    static vector<bool> visited(nNodes);

    // Since the index in adjcent matrix is zero-based and the given graph is one-based,
    //  we have to adjust the "start" which is one-based to zero-based.
    int start_zero_base = start - 1;

    // Whenever we recuse into the function, we record the current node to "path"
    //  and mark the current node to have been visited.
    path.push_back(start);
    visited[start_zero_base] = true;

    // If "start" == "end", we reach our destination node
    if (start == end) {
        // Print out the path
        cout << "\t" << path[0];
        for (int i = 1; i < path.size(); i++)
            cout << "->" << path[i];
        cout << "\n";

        // Pop back the end node from path and mark the end node as not visited,
        //  so we have a correct visited state and path to search for other possible paths.
        path.pop_back();
        visited[start_zero_base] = false;

        // return to where the function is called
        return;
    }

    // Iterate through all the connected state to others node of the current node in the adjcent matrix
    for (int i = 0; i < nNodes; i++) {
        // Here "i" can represent as the other node.
        // if the current node connects to "i" &&
        // if "i" is not equal to the current node &&
        // if "i" is not visited before,
        //  then go into "i" node and find all path from "i" to the end node
        if (adj_matrix[start_zero_base][i] == 1 && i != start_zero_base && !visited[i]) {
            // Because "i" is zero-based, we have to pass "i+1"
            find_all_paths(adj_matrix, i + 1, end);
        }
    }

    // We have found all possible path from the current node to the end node.
    // Pop back the end node from path and mark the end node as not visited,
    //  so we have a correct visited state and path to search for other possible paths.
    path.pop_back();
    visited[start_zero_base] = false; 

    // return to where the function is called
}

int main()
{
    vector<vector<int>> adj_matrix =
        {
            {1, 1, 0, 1, 1},
            {1, 0, 0, 1, 0},
            {0, 0, 0, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 0, 1, 1, 0}
        };

    // print out all possible paths in the adjancency matrix
    int nNodes = adj_matrix[0].size();
    for (int i = 0; i < nNodes; i++) {
        cout << "--------------------------------------\n";
        cout << "All the possible paths starting from " << i + 1 <<":\n\n";
        for (int j = 0; j < nNodes; j++) {
            if (i != j) {
                cout << i + 1 << " to " << j + 1 << ":\n";
                find_all_paths(adj_matrix, i + 1, j + 1);
                cout << "\n";
            }
        }
    }

    return 0;
}