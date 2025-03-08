#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

class Offer {
	public:
		void solve() {
			read_input();
			print_output(get_result());
		}

	private:
		int n, k;
		vector<double> prices;

		void read_input() {
			ifstream fin("oferta.in");
			fin >> n >> k;
			prices.push_back(-1.0);
			for (int i = 1; i <= n; i++) {
				double x;
				fin >> x;
				prices.push_back(x);
			}
			fin.close();
		}

		double get_result() {
			if (n == 1) {
				if (k <= n) {
					return prices[1];
				} else {
					return -1;
				}
			}

			vector<vector<double>> dp(n + 1, vector<double>(k + 1, -1.0));

			dp[0][0] = 0;
			dp[1][0] = prices[1];
			dp[2][0] = prices[1] + prices[2] - min(prices[1], prices[2]) / 2.0;
			dp[2][1] = prices[1] + prices[2];

			for (int i = 3; i <= n; i++) {
				vector<double> halfPrice;
				vector<double> freePrice;
				vector<double> fullPrice;

				double half = min(prices[i - 1], prices[i]) / 2.0;
				double free = min(min(prices[i - 2], prices[i - 1]), prices[i]);

				for (int j = 0; j <= k; j++) {
					if (dp[i - 2][j] != -1.0)
						halfPrice.push_back(dp[i - 2][j] + prices[i - 1] + prices[i] -
									half);
					if (dp[i - 3][j] != -1.0)
						freePrice.push_back(dp[i - 3][j] + prices[i - 2] + prices[i - 1] +
									prices[i] - free);
					if (dp[i - 1][j] != -1.0)
						fullPrice.push_back(dp[i - 1][j] + prices[i]);
				}

				vector<double> partialPrices(halfPrice.size() + freePrice.size());
				merge(halfPrice.begin(), halfPrice.end(),
					  freePrice.begin(), freePrice.end(), partialPrices.begin());

				vector<double> sortedPrices(partialPrices.size() + fullPrice.size());
				merge(partialPrices.begin(), partialPrices.end(),
					fullPrice.begin(), fullPrice.end(), sortedPrices.begin());
				sortedPrices.erase(unique(sortedPrices.begin(), sortedPrices.end()),
									sortedPrices.end());

				int elems = k;
				for (int l = 0; l < sortedPrices.size(); l++) {
					if (elems == 0)
						break;
					dp[i][l] = sortedPrices[l];
					elems--;
				}
			}

			return dp[n][k - 1];
		}

		void print_output(double result) {
			ofstream fout("oferta.out");
			fout << fixed << setprecision(1) << result;
			fout.close();
		}
};

int main() {
	auto *task = new (nothrow) Offer();
	if (!task) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	task->solve();
	delete task;
	return 0;
}
