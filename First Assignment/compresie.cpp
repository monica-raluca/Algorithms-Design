#include <bits/stdc++.h>
#include <iomanip>

#define MOD 1000000007
using namespace std;

class Compress {
	public:
		void solve() {
			read_input();
			print_output(get_result());
		}

	private:
		int n, m;
		vector<int> a, b;

		void read_input() {
			ifstream fin("compresie.in");
			fin >> n;
			for (int i = 0; i < n; i++) {
				int x;
				fin >> x;
				a.push_back(x);
			}
			fin >> m;
			for (int i = 0; i < m; i++) {
				int x;
				fin >> x;
				b.push_back(x);
			}
			fin.close();
		}

		int get_result() {
			int result = 0, i = 1, j = 1;
			int sum_a = a[0], sum_b = b[0];

			while (i < n && j < m) {
				if (sum_a > sum_b) {
					sum_b += b[j++];
				} else if (sum_a < sum_b) {
					sum_a += a[i++];
				} else {
					result++;
					sum_a = a[i++];
					sum_b = b[j++];
				}
			}

			while (i < n)
				sum_a += a[i++];
			while (j < m)
				sum_b += b[j++];

			if (sum_a == sum_b)
				return result + 1;

			return -1;
		}

		void print_output(long result) {
			ofstream fout("compresie.out");
			fout << result << endl;
			fout.close();
		}
};

int main() {
	auto *task = new (nothrow) Compress();
	if (!task) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	task->solve();
	delete task;
	return 0;
}
