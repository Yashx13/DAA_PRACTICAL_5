#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct cost {
	int val;
	char dir;
};

std::vector<std::vector<cost>> LCS(std::string& m, std::string& n) {
	const int m_size = m.length();
	const int n_size = n.length();

	std::vector<std::vector<cost>> dp(m_size + 1, std::vector<cost>(n_size + 1));
	std::string kekk; // a string for returning 

	for (int i = 0; i <= m_size; i++) {
		for (int j = 0; j <= n_size; j++) {

			if (i == 0 || j == 0) { // halt state
				dp[i][j].val = 0;
				dp[i][j].dir = 'h';
			}
			else if (m[i - 1] == n[j - 1]) {
				dp[i][j].val = 1 + dp[i - 1][j - 1].val;
				dp[i][j].dir = 'd';
			}
			else {
				if (dp[i - 1][j].val >= dp[i][j - 1].val) {
					dp[i][j].val = dp[i - 1][j].val;
					dp[i][j].dir = 'u';
				}
				else {
					dp[i][j].val = dp[i][j - 1].val;
					dp[i][j].dir = 'l';
				}
			}
		}
	}

	return dp;

}


void print_lcs(const std::vector<std::vector<cost>>& dp, const std::string& m, const std::string& n, int i, int j, std::string& out) {
	if (i == 0 || j == 0) return;

	if (dp[i][j].dir == 'd') {
		print_lcs(dp, m, n, i - 1, j - 1, out);
		out.push_back(m[i - 1]);
	}
	else if (dp[i][j].dir == 'u') {
		print_lcs(dp, m, n, i - 1, j, out);
	}
	else if (dp[i][j].dir == 'l') {
		print_lcs(dp, m, n, i, j - 1, out);
	}
}


int main() {
	std::string m = "AGCCCTAAGGGCTACCTAGCTT";
	std::string n = "GACAGCCTACAAGCGTTAGCTTG";
	const int m_size = m.length();
	const int n_size = n.length();

	std::vector<std::vector<cost>> bro = LCS(m, n);

	std::cout << "   ";
	for (auto& c : m) {
		std::cout << "    " << c;
	}
	std::cout << std::endl;
	for (int i = 0; i <= m_size; i++) {
		for (int j = 0; j <= n_size; j++) {
			if (j == 0) std::cout << n[i] << "  ";
			std::cout << bro[i][j].val << "/" << bro[i][j].dir << "  ";
		}
		std::cout << std::endl << std::endl;
	}

	std::string brobro; // passed by ref 

	print_lcs(bro, m, n, m_size, n_size, brobro);

	std::cout << "Output for the LCS: " << brobro << std::endl;
	std::cout << "Length of LCS : " << brobro.length() << std::endl;

}
