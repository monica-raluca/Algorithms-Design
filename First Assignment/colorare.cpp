#include <bits/stdc++.h>
#include <iomanip>

#define MOD 1000000007
using namespace std;

class Color {
	public:
		void solve() {
			print_output(get_result());
		}

	private:
		int n;

		long power(long x, long p) {
			long result = 1;

			if (p == 0)
				return 1;
			if (p == 1)
				return x;
			while (p) {
				if (p % 2 == 1)
					result = (result * x) % MOD;
				p /= 2;
				x = (x * x) % MOD;
			}

			return result;
		}

		long get_result() {
			ifstream fin("colorare.in");
			fin >> n;
			int x;
			long result = 0;
			char y;
			/*
				V -> H/V * 2
				H -> H * 3
				H -> V * 1
				initial H = 6
				initial V = 3
			*/
			fin >> x;
			fin >> y;
			if (y == 'H')
				result = (6 * power(3, x - 1)) % MOD;
			else
				result = (3 * power(2, x - 1)) % MOD;

			for (int i = 0; i < n - 1; i++) {
				int x1;
				fin >> x1;
				char y1;
				fin >> y1;
				if (y == 'H') {
					if (y1 == 'H')
						result = (result * 3 * power(3, x1 - 1)) % MOD;
					else
						result = (result * 1 * power(2, x1 - 1)) % MOD;
				} else {
					if (y1 == 'H')
						result = (result * 2 * power(3, x1 - 1)) % MOD;
					else
						result = (result * 2 * power(2, x1 - 1)) % MOD;
				}
				x = x1;
				y = y1;
			}
			fin.close();
			return result % MOD;
		}

		void print_output(long result) {
			ofstream fout("colorare.out");
			fout << result % MOD << endl;
			fout.close();
		}
};

int main() {
	auto *task = new (nothrow) Color();
	if (!task) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	task->solve();
	delete task;
	return 0;
}
