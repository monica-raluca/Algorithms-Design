#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

class Servers {
	public:
		void solve() {
			read_input();
			print_output(get_result());
		}

	private:
		int n;
		vector<int> power, current;

		void read_input() {
			ifstream fin("servere.in");
			fin >> n;
			for (int i = 0; i < n; i++) {
				int p;
				fin >> p;
				power.push_back(p);
			}
			for (int i = 0; i < n; i++) {
				int c;
				fin >> c;
				current.push_back(c);
			}
			fin.close();
		}

		double individualPower(int power, int current, double value) {
			return power - abs(value - current);
		}

		double minimumPower(vector<int> power, vector<int> current, double value) {
			double minimum = INT_MAX;

			for (int i = 0; i < n; i++) {
				double temp_min = individualPower(power[i], current[i], value);

				if (temp_min < minimum) {
					minimum = temp_min;
				}
			}

			return minimum;
		}

		double get_result() {
			double left = 1;
			double right = 1e9;

			while (right - left > 1e-6) {
				double mid1 = left + (right - left) / 3;
				double mid2 = right - (right - left) / 3;

				double min_power_mid1 = minimumPower(power, current, mid1);
				double min_power_mid2 = minimumPower(power, current, mid2);

				if (min_power_mid1 < min_power_mid2)
					left = mid1;
				else
					right = mid2;
			}

			return minimumPower(power, current, left);
		}

		void print_output(double result) {
			ofstream fout("servere.out");
			fout << fixed << setprecision(1) << result;
			fout.close();
		}
};

int main() {
	auto *task = new (nothrow) Servers();
	if (!task) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	task->solve();
	delete task;
	return 0;
}
