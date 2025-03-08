#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

using namespace std;

class Trains {
	public:
		void solve() {
			readInput();
			printOutput();
		}

	private:
		string start, end;
		int M;
		unordered_map<string, vector<string>> graph;

		void readInput() {
			ifstream fin("trenuri.in");
			fin >> start >> end >> M;

			for (int i = 0; i < M; i++) {
				string x, y;
				fin >> x >> y;
				graph[x].push_back(y);
			}

			fin.close();
		}

		/* Computes the longest path from start to end using DFS
		and dynamic programming. */
		int longestPath(unordered_map<string, vector<string>>& graph,
						string start, string end) {
			unordered_map<string, int> dp;

			// Keeps track of visited nodes
			unordered_map<string, bool> visited;

			for (const auto& pair : graph) {
				visited[pair.first] = false;
			}

			function<void(string)> dfs = [&](string node) {
				// Mark the current node as visited
				visited[node] = true;

				for (const string& neighbor : graph[node]) {
					// If the neighbor is not visited, visit it
					if (!visited[neighbor])
						dfs(neighbor);

					// Update the longest path from the current node
					dp[node] = max(dp[node], dp[neighbor] + 1);
				}
			};

			dfs(start);

			// Add 1 to include the starting node
			return dp[start] + 1;
		}

		void printOutput() {
			ofstream fout("trenuri.out");
			fout << longestPath(graph, start, end) << endl;
			fout.close();
		}
};

int main() {
	auto *trains = new (nothrow) Trains();
	if (!trains) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}

	trains->solve();
	delete trains;

	return 0;
}
