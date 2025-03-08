#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

#define MOD 1000000007

using namespace std;

class Count {
	public:
		void solve() {
			readInput();
			countPaths();
			printOutput();
		}

	private:
		int n, m;
		vector<vector<int>> graph1, graph2;
		vector<long long> paths;

		void readInput() {
			ifstream fin("numarare.in");
			fin >> n >> m;

			graph1.resize(n + 1);
			graph2.resize(n + 1);
			paths.resize(n + 1, 0);

			for (int i = 0; i < m; i++) {
				int x, y;
				fin >> x >> y;
				graph1[x].push_back(y);
			}

			/* Adds in graph2 only the edges that are also found in graph1, 
			in order to only consider the common paths between the two graphs. */
			for (int i = 0; i < m; i++) {
				int x, y;
				fin >> x >> y;
				for (int j = 0; j < graph1[x].size(); j++)
					if (graph1[x][j] == y)
						graph2[x].push_back(y);
			}

			fin.close();
		}

		void dfs(int node, vector<bool> &visited, vector<int> &ordered) {
			stack<pair<int, bool>> stack;
			stack.push({node, false});

			while (!stack.empty()) {
				// Get the current node and its processed status
				auto [current, processed] = stack.top();
				stack.pop();

				// If the node was already processed, add it to the ordered list
				if (processed) {
					ordered.push_back(current);
					continue;
				}

				if (visited[current])
					continue;

				// Mark the current node as visited
				visited[current] = true;

				// Push the current node back to the stack, but mark it as processed
				stack.push({current, true});

				// Visit the neighbors of the current node
				for (int neighbor : graph2[current]) {
					if (!visited[neighbor]) {
						stack.push({neighbor, false});
					}
				}
			}
		}

		// Topological sort using DFS
		void topoSort(vector<int>& ordered) {
			vector<bool> visited(n + 1, false);

			for (int i = 1; i <= n; i++) {
				if (!visited[i])
					dfs(i, visited, ordered);
			}

			// Reverse the ordered list to get the topological order
			reverse(ordered.begin(), ordered.end());
		}

		void countPaths() {
			vector<int> ordered;
			topoSort(ordered);

			// The starting node has only one path to itself
			paths[1] = 1;

			// For each node in the ordered list, update the number of paths
			for (auto node : ordered) {
				for (auto neighbor : graph2[node]) {
					paths[neighbor] += paths[node];
					paths[neighbor] %= MOD;
				}
			}
		}

		void printOutput() {
			ofstream fout("numarare.out");
			fout << paths[n] << "\n";
			fout.close();
		}
};

int main() {
	auto *count = new (nothrow) Count();
	if (!count) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	count->solve();
	delete count;
	return 0;
}
