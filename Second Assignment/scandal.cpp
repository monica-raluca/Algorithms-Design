#include <bits/stdc++.h>
#include <fstream>

#define MAX 200001

using namespace std;

vector<int> found(MAX, -1);
vector<int> low(MAX, -1);
vector<int> onStack(MAX, 0);
vector<int> scc(MAX, -1);
vector<int> sccNodes;

vector<bool> visited(MAX, false);

stack<int> s;

class Scandal {
	public:
		void solve() {
			readInput();
			computeTarjan();
			validate2Sat();
			getResult();
		}

	private:
		int N, M;
		vector<int> adj[MAX];
		int friends = 0;
		int currentIndex = 0;
		int sccCount = 0;

		void readInput() {
			ifstream fin("scandal.in");
			fin >> N >> M;

			for (int i = 0; i < M; i++) {
				int x, y, c;
				fin >> x >> y >> c;

				if (c == 0) {
					addImplications(x, y);
				} else if (c == 1) {
					addImplications(x, -y);
				} else if (c == 2) {
					addImplications(-x, y);
				} else if (c == 3) {
					addImplications(-x, -y);
				} else {
					cout << "Invalid input" << endl;
				}
			}

			fin.close();
		}

		void addImplications(int x, int y) {
			/*
				x | y <=> !x => y & !y => x
				x | !y <=> !x => !y & y => x
				!x | y <=> x => y & !y => !x
				!x | !y <=> x => !y & y => !x
			*/
			int u = abs(x), v = abs(y);
			int negU = (x < 0 ? u : u + N);
			int negV = (y < 0 ? v : v + N);

			adj[negU].push_back(v + (y < 0 ? N : 0));
			adj[negV].push_back(u + (x < 0 ? N : 0));
		}

		void computeTarjan() {
			function<void(int)> tarjanSCC = [&](int u) {
				found[u] = low[u] = currentIndex++;
				s.push(u);
				onStack[u] = true;

				// Explore all the adjacent nodes
				for (int v : adj[u]) {
					if (found[v] == -1) {
						tarjanSCC(v);
						low[u] = min(low[u], low[v]);
					} else if (onStack[v]) {
						low[u] = min(low[u], found[v]);
					}
				}

				// Node is root in a SCC
				if (low[u] == found[u]) {
					// Pop the nodes from that SCC from the stack
					while (true) {
						int v = s.top();
						s.pop();
						onStack[v] = false;
						scc[v] = sccCount;
						sccNodes.push_back(v);
						if (v == u) break;
					}
					sccCount++;
				}
			};

			// Run Tarjan's algorithm
			for (int i = 1; i <= 2 * N; i++) {
				if (found[i] == -1) {
					tarjanSCC(i);
				}
			}
		}

		void validate2Sat() {
			for (int i = 1; i <= N; i++) {
				/* If a variable and its negation are in the same SCC, 
				then it is impossible to find a valid combination */
				if (scc[i] == scc[i + N]) {
					cout << "Objection. No valid combinations of friends." << endl;
					return;
				} else if (scc[i] < scc[i + N]) {
					friends++;
				}
			}
		}

		void getResult() {
			ofstream fout("scandal.out");
			fout << friends << endl;

			for (int i = 1; i <= N; i++) {
				if (scc[i] < scc[i + N])
					fout << i << endl;
			}
			fout.close();
		}
};

int main() {
	auto *scandal = new (nothrow) Scandal();
    if (!scandal) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    scandal->solve();
    delete scandal;
    return 0;
}
