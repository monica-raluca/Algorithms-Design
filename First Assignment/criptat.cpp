#include <bits/stdc++.h>
#include <iomanip>

#define MOD 1000000007
using namespace std;

class Encryption {
	public:
		void solve() {
			read_input();
			print_output(get_result());
		}

	private:
		int n;
		vector<string> words;

		void read_input() {
			ifstream fin("criptat.in");
			fin >> n;
			for (int i = 0; i < n; i++) {
				string word;
				fin >> word;
				words.push_back(word);
			}
		}

		unordered_set<char> get_letters(vector<string> words) {
			unordered_set<char> letters;
			for (string word : words)
				for (char letter : word)
					letters.insert(letter);

			return letters;
		}

		void merge(vector<string> &words, vector<vector<int>> &freq,
				int letter_index, int left, int mid, int right) {
			int n1 = mid - left + 1;
			int n2 = right - mid;

			vector<string> L_words(n1);
			vector<vector<int>> L_freq(n1, vector<int>(26, 0));
			vector<string> R_words(n2);
			vector<vector<int>> R_freq(n2, vector<int>(26, 0));

			for (int i = 0; i < n1; i++) {
				L_words[i] = words[left + i];
				L_freq[i] = freq[left + i];
			}
			for (int j = 0; j < n2; j++) {
				R_words[j] = words[mid + 1 + j];
				R_freq[j] = freq[mid + 1 + j];
			}

			int i = 0, j = 0, k = left;

			while (i < n1 && j < n2) {
				double freq_L = (double)L_freq[i][letter_index] / L_words[i].size();
				double freq_R = (double)R_freq[j][letter_index] / R_words[j].size();

				if (freq_L > freq_R ||
					(freq_L == freq_R &&
					L_words[i].size() > R_words[j].size())) {
					words[k] = L_words[i];
					freq[k] = L_freq[i];
					i++;
				} else {
					words[k] = R_words[j];
					freq[k] = R_freq[j];
					j++;
				}
				k++;
			}

			while (i < n1) {
				words[k] = L_words[i];
				freq[k] = L_freq[i];
				i++;
				k++;
			}

			while (j < n2) {
				words[k] = R_words[j];
				freq[k] = R_freq[j];
				j++;
				k++;
			}
		}

		void mergeSort(vector<string> &words, vector<vector<int>> &freq,
					int letter_index, int left, int right) {
			if (left < right) {
				int mid = left + (right - left) / 2;
				mergeSort(words, freq, letter_index, left, mid);
				mergeSort(words, freq, letter_index, mid + 1, right);
				merge(words, freq, letter_index, left, mid, right);
			}
		}

		int get_result() {
			unordered_set<char> letters = get_letters(words);
			unordered_map<char, int> letter_index;

			int index = 0;
			for (char letter : letters) {
				letter_index[letter] = index++;
			}

			vector<vector<int>> freq(n);
			for (int i = 0; i < n; i++) {
				freq[i].resize(8, 0);
			}

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < words[i].size(); j++) {
					freq[i][letter_index[words[i][j]]]++;
				}
			}

			string password = "";
			int max_length = 0;

			for (char letter : letters) {
				mergeSort(words, freq, letter_index[letter], 0, words.size() - 1);

				int frequency = 0;
				password = "";
				for (int i = 0; i < words.size(); i++) {
					if (frequency + freq[i][letter_index[letter]] >=
					(password.length() + words[i].size()) / 2 + 1) {
						password.append(words[i]);
						frequency += freq[i][letter_index[letter]];
					}
				}

				if (password.length() > max_length) {
					max_length = password.length();
				}
			}

			return max_length;
		}

		void print_output(long result) {
			ofstream fout("criptat.out");
			fout << result << endl;
			fout.close();
		}
};

int main() {
	auto *task = new (nothrow) Encryption();
	if (!task) {
		cerr << "new failed: WTF are you doing? Throw your PC!\n";
		return -1;
	}
	task->solve();
	delete task;
	return 0;
}
