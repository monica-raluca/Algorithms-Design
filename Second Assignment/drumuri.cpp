#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <set>

#define NMAX 100002

using namespace std;

class Paths {
	public:
		void solve() {
			readInput();
			printOutput(findMinCost());
		}

	private:
		long long N, M;
		vector<pair<long long, long long>> adj[NMAX];
		long long x, y, z;

		void readInput() {
			ifstream fin("drumuri.in");
			fin >> N >> M;

			for (long long i = 0; i < M; i++) {
				long long x, y, w;
				fin >> x >> y >> w;
				adj[x].push_back({y, w});
			}

			fin >> x >> y >> z;
			fin.close();
		}

		long long findMinCost() {
			// Set that stores unique edges
			set<pair<long long, long long>> edgeSet;

			auto dijkstra = [&](long long start, long long end) {
				vector<long long> dist(N + 1, LLONG_MAX);

				// Parent vector used to keep track of the path
				vector<long long> parent(N + 1, -1);
				dist[start] = 0;
				priority_queue<pair<long long, long long>,
						vector<pair<long long, long long>>,
						greater<pair<long long, long long>>> pq;
				pq.push({0, start});

				while (!pq.empty()) {
					long long u = pq.top().second;
					pq.pop();

					// Explore all the adjacent edges
					for (auto& edge : adj[u]) {
						long long v = edge.first;
						long long weight = edge.second;

						// If a shorter path is found, update the distance and the parent
						if (dist[u] + weight < dist[v]) {
							dist[v] = dist[u] + weight;
							parent[v] = u;
							pq.push({dist[v], v});
						}
					}
				}

				// Reconstruct the path from start to end and add the edges to the set
				for (long long v = end; v != start; v = parent[v]) {
					if (parent[v] != -1) {
						edgeSet.insert({parent[v], v});
					}
				}
			};

			// Run Dijkstra's algorithm from x to z and from y to z
			dijkstra(x, z);
			dijkstra(y, z);

			// Sum up the costs of the unique edges
			long long totalCost = 0;
			for (const auto& edge : edgeSet) {
				long long u = edge.first;
				long long v = edge.second;
				for (const auto& adjEdge : adj[u]) {
					if (adjEdge.first == v) {
						totalCost += adjEdge.second;
						break;
					}
				}
			}

			return totalCost;
		}

		void printOutput(long long minCost) {
			ofstream fout("drumuri.out");
			fout << minCost << endl;
			fout.close();
		}
};

int main() {
	auto *paths = new (nothrow) Paths();
	if (!paths) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	paths->solve();
	delete paths;
	return 0;
}
