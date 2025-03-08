### Birladeanu Raluca-Monica 325CA - Second PA Homework

# First problem - Count

- The implementation of this problem can be found in `numarare.cpp`, and the solution is written in the class `Count`.
- In order to only consider the common paths between the two graphs, during the input reading we read the whole first graph, but then for the second one I only add the edges that are also found in the first graph as well.
- This way, we can perform a topological sort using an iterative depth first search approach.
- For the iterative DFS, we start with the initial node being unprocessed. We go through the stack until it is empty, extracting one node at a time. If the node was fully processed, we add it to our ordered vector. Otherwise, if the node is not visited, we mark it and push it back into the stack as processed and then we visit the unvisited neighbours of the current node.
- The topological order is then obtained by reversing the ordered vector obtained after the DFS.
- In order to count the paths a dynamic programming approach is used on the ordered vector that is obtained after the topological sort. The base case includes the starting node which has esentially just one path to itself. We then iterate through all the nodes, and for each node we go through all the neighbours and increment the number of paths to the neighbour by the number of paths to the current node. Modulo is used in order to avoid overflow.

Complexity: Since each node is visited once, the DFS has a complexity of O(N + M), where N is the number of nodes and M is the number of edges. After the topological sort, the path is updated and the final complexity ends up still being O(N + M).

# Second problem - Trains
- The implementation of this problem can be found in `trenuri.cpp`, and the solution is written in the class `Trains`.
- The longest path function computes the longest path from start to end using DFS and dynamic programming.
- The visited unordered map keeps track of the visited nodes, and the dp stores the length of the longest path starting from each node.
- For simplicity, an anonymous dfs function is defined, since I only needed to add one additional parameter to the function, the current node. 
- The function marks the current node as visited, and for each unvisited neighbour, calls dfs recursively. After visiting a neighbour, the longest path is updated, by either taking the current value, or the longest path from the neighbour plus one more, indicating one more neighbour that would therefore be taken into consideration - between these two, we want to take the max length of the path.
- The dfs starts from the starting node and the longest path function returns the longest path from that starting node plus one, indicating the starting city is being added.

Complexity: Since each node is visited once, the DFS has a complexity of O(N + M), where N is the number of nodes and M is the number of edges. Updating the dp map is done in constant time, which leaves the final complexity at O(N + M).


# Third problem - Paths
- The implementation of this problem can be found in `drumuri.cpp`, and the solution is written in the class `Paths`.
- For this problem, I was still not able to get the full solution, but I did tinker with it quite a bit before reaching this version of the code.
- One of the ideas I had was to add an intermediate node connecting both sources with a path of cost 0 and start the Dijkstra algorithm from that node, which would supposedly solve the problem. However, the cost was either always 0, or very far off.
- The other notable solution was a Dijkstra starting from both sources and going to the sole destination, where I would just add those two results in order to obtain the final cost.
- The solution that I settled for is quite similar, except it uses a set and a vector of parents in order to fix the problem where some edges would be counted twice.
- The minimum cost function uses an edge set in order to store unique edges.
- For simplicity, I implemented an anonymous Dijkstra function inside the minimum cost one. It uses a parent vector in order to later reconstruct the minimum path and save the corresponding edges into the set, as well as a min heap implementation.
- The algorithm starts with the distance from the start node to itself as 0, pushing it into the priority queue. It explores all adjacent edges and updates the distance and the parent if it finds a shorter path.
- The minimum cost function runs Dijkstra twice, from x to z and from y to z and then sums the costs of the unique edges, returning the total cost.

Complexity: The graph is represented using an adjacency list, having N nodes and M edges. Dijkstra's algorithm implemented with a priority queue takes O(M*logN) time, since the queue operations take O(logN) and each node is processed once. Inserting an edge into the set takes O(log E), where E is the number of edges in our set, so the max complexity for insertion is O(N\*logN). Therefore, the final complexity ends up being O((N + M)\*logN).


# Fourth problem - Scandal
- The implementation of this problem can be found in `scandal.cpp`, and the solution is written in the class `Scandal`.
- This problem was probably the most tricky at first sight, since I had a pretty complicated idea that wouldn't have worked on all cases, because there were many edge cases I would've had to handle. However, once I saw that the problem basically boils down to 2-SAT, things became much more clear. All in all, it was a pretty fun problem to solve and the realization that the SAT problem that we studied during the last semester would work was quite satisfying.
- My initial solution intended to make two different graphs, each one representing a possible party. For example, if we knew that one of the people couldn't participate, we would distribute one of the in a graph, and the second in the other graph. If we knew at least one of them had to participate, however, we would fill in both graphs with both people. Following this logic, after the input was read, I would've had two graphs to go through and more thoroughly check the conditions. However, there could've been more combinations of people or there could've been the need to constantly update the graphs as we go, which wouldn't be very efficient, and also very hard to debug on the larger tests. Hence, this is where 2-SAT comes in play.
- The trickiest part was modelling the clause after the problem, but after playing with truth tables for a bit, I got the following one:
    - (x | y) & (!x | y) & (x | !y) & (!x | !y) -> and now that I look at it, it makes perfect sense and I don't know why it took me so long to figure out.
- After figuring out the clause, we have to build the implication graph, after the following rules:
    - x | y <=> !x => y & !y => x
    - x | !y <=> !x => !y & y => x
    - !x | y <=> x => y & !y => !x
    - !x | !y <=> x => !y & y => !x
- Having gotten the logic bits out of the way and with the graph now built, things are much easier. The goal is to determine whether or not a variable X and !X are in the same strongly connected component (SCC). If it is, then we get a contradition, since both X and !X can't be satisfiable at the same time, which indicates the fact that the clause I proposed has no possible combination of values which would validate it.
- I used the Tarjan algorithm from the lab in order to find the SCC's, which is implemented for simplicity with an anonymous function. The computeTarjan function then runs this anonymous function.
- During the validation phase, if we encounter a contradiction we stop the algorithm, otherwise we keep counting the number of friends that will show to the party.
- Lastly, we show the number of friends and with another iteration we print the friends that are attending the party.

Complexity: During the input read, we read N friends and M conditions and build a graph that will contain 2*N nodes, since we must have both the friend and the negated version of the variable, and 2\*M edges, since for each condition we will be adding two edges for the implications. Tarjan's algorithm has a complexity of O(V + E), where V is 2\*N and E is 2\*M. For the validation part, we simply do a liniar traversal in O(N), and the same goes for printing the output. Overall, the complexity will be O(V + E).


