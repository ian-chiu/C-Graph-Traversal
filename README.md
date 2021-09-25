# CppGraphTraversal - 計算機概論期中專題報告
1. The main idea of how to develop your codes? <br>
I create a recursive function called find_all_paths used to find all possible paths of a graph from one node to another node. This function has two static arrays that will not be reset when we call the recursive function. One is used to record whether a node is visited and the other is used to record the path. Whenever we recuse into the function, we add the current node to the path and mark the current node as visited. We can loop through the list of the adjacency matrix of the current node to find all possible paths from the current node to the destination node. If the current node connects to a node and that node is not visited before, we can get into that node using the same recursive function. This process will continue until we find our destination node. If we find our destination node, we can print out our path. Then, we return to where the function is called and continue to search other possible paths. Moreover, there are times we need to adjust our path and visited array. When we find our destination node or iterate through all the connection node of the current node, we have to pop back the path and mark the current node back as not visited. By doing this, we have a correct visited state and path to search for other possible paths. Please refer to the comment section of the code snippet below or “graph_traversal.cpp” to see a more detailed explanation

* Code snippet of the function “find_all_path”:

``` cpp
/*
Find all possible paths from one node to another node using recursion
@param adj_matrix Adjacency matrix of the graph
@param start The beginning node
@param end The destination node
*/
void find_all_paths(const vector<vector<int>> &adj_matrix, int start, int end)
{
  // Create three static variables that will not reset during recursion
  // nNodes - the total number of nodes
  // path - used to record the path
  // visited - used to record which node is visited before
  static int nNodes = adj_matrix[0].size();
  static vector<int> path;
  static vector<bool> visited(nNodes);
  // Since the index in adjcent matrix is zero-based and the given graph is one-based,
  // we have to adjust the "start" which is one-based to zero-based.
  int start_zero_base = start - 1;
  // Whenever we recuse into the function, we record the current node to "path"
  // and mark the current node to have been visited.
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
    // so we have a correct visited state and path to search for other possible paths.
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
    // then go into "i" node and find all path from "i" to the end node
    if (adj_matrix[start_zero_base][i] == 1 && i != start_zero_base && !visited[i]) {
      // Because "i" is zero-based, we have to pass "i+1"
      find_all_paths(adj_matrix, i + 1, end);
    }
  }
  // We have found all possible path from the current node to the end node.
  // Pop back the end node from path and mark the end node as not visited,
  // so we have a correct visited state and path to search for other possible paths.
  path.pop_back();
  visited[start_zero_base] = false;
  // return to where the function is called
}

```

2. The adjacency matrix of the given graph
![](https://i.imgur.com/UrUuPD8.png)

3. All the possible traversal paths from all the points. <br>
From the output of “graph_traversal.cpp”:
```
--------------------------------------
All the possible paths starting from 1:
1 to 2:
  1->2
  1->4->2
  1->5->3->4->2
  1->5->4->2
1 to 3:
  1->2->4->3
  1->2->4->5->3
  1->4->3
  1->4->5->3
  1->5->3
  1->5->4->3
1 to 4:
  1->2->4
  1->4
  1->5->3->4
  1->5->4
1 to 5:
  1->2->4->3->5
  1->2->4->5
  1->4->3->5
  1->4->5
  1->5
--------------------------------------
All the possible paths starting from 2:
2 to 1:
  2->1
  2->4->1
  2->4->3->5->1
  2->4->5->1
2 to 3:
  2->1->4->3
  2->1->4->5->3
  2->1->5->3
  2->1->5->4->3
  2->4->1->5->3
  2->4->3
  2->4->5->3
2 to 4:
  2->1->4
  2->1->5->3->4
  2->1->5->4
  2->4
2 to 5:
  2->1->4->3->5
  2->1->4->5
  2->1->5
  2->4->1->5
  2->4->3->5
  2->4->5
--------------------------------------
All the possible paths starting from 3:
3 to 1:
  3->4->2->1
  3->4->5->1
  3->5->1
  3->5->4->1
  3->5->4->2->1
3 to 2:
  3->4->1->2
  3->4->2
  3->4->5->1->2
  3->5->1->2
  3->5->1->4->2
  3->5->4->1->2
  3->5->4->2
3 to 4:
  3->4
  3->5->1->2->4
  3->5->1->4
  3->5->4
3 to 5:
  3->4->1->5
  3->4->2->1->5
  3->4->5
  3->5
--------------------------------------
All the possible paths starting from 4:
4 to 1:
  4->1
  4->2->1
  4->3->5->1
  4->5->1
4 to 2:
  4->1->2
  4->2
  4->3->5->1->2
  4->5->1->2
4 to 3:
  4->1->5->3
  4->2->1->5->3
  4->3
  4->5->3
  4 to 5:
  4->1->5
  4->2->1->5
  4->3->5
  4->5
--------------------------------------
All the possible paths starting from 5:
5 to 1:
  5->1
  5->3->4->1
  5->3->4->2->1
  5->4->1
  5->4->2->1
5 to 2:
  5->1->2
  5->1->4->2
  5->3->4->1->2
  5->3->4->2
  5->4->1->2
  5->4->2
5 to 3:
  5->1->2->4->3
  5->1->4->3
  5->3
  5->4->3
5 to 4:
  5->1->2->4
  5->1->4
  5->3->4
  5->4
```
