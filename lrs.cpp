#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct cost {
	int val;
	char dir;
};

std::vector<std::vector<cost>> LRS(std::string& m) {
	// std::string n = m;
	// TRICK : )  
	// didnt even need this I can just compare with itself with m and m_Size
	const int m_size = m.length();
	//const int n_size = n.length();

	std::vector<std::vector<cost>> dp(m_size + 1, std::vector<cost>(m_size + 1));
	std::string kekk; // a string for returning 

	for (int i = 0; i <= m_size; i++) {
		for (int j = 0; j <= m_size; j++) {

			if (i == 0 || j == 0) { // halt state
				dp[i][j].val = 0;
				dp[i][j].dir = 'h';
			}
			else if (m[i - 1] == m[j - 1] && i != j) {
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


void print_lcs(const std::vector<std::vector<cost>>& dp, const std::string& m, int i, int j, std::string& out) {
	if (i == 0 || j == 0) return;

	if (dp[i][j].dir == 'd') {
		print_lcs(dp, m, i - 1, j - 1, out);
		out.push_back(m[i - 1]);
	}
	else if (dp[i][j].dir == 'u') {
		print_lcs(dp, m, i - 1, j, out);
	}
	else if (dp[i][j].dir == 'l') {
		print_lcs(dp, m, i, j - 1, out);
	}
}


int main() {
	std::string m = "AABEBCDD";
	//std::string n = "AABEBCDD";
	const int m_size = m.length();
	//const int n_size = n.length();

	std::vector<std::vector<cost>> bro = LRS(m);

	std::cout << "            ";
	for (auto& c : m) {
		std::cout << c << "       ";
	}
	std::cout << std::endl << std::endl;
	int k = 0;
	for (int i = 0; i <= m_size; i++) {
		for (int j = 0; j <= m_size; j++) {
			if (i > 0 && j == 0) std::cout << m[i - 1] << "   ";
			else std::cout << "   ";
			if (i == 0 && j == 0) { std::cout << " "; }
			std::cout << bro[i][j].val << "/" << bro[i][j].dir << "  ";
		}
		std::cout << std::endl << std::endl;
	}

	std::string brobro; // passed by ref : ) lol

	print_lcs(bro, m, m_size, m_size, brobro);

	std::cout << "Output for the LRS: " << brobro << std::endl;
	std::cout << "Length of LRS : " << brobro.length() << std::endl;

}
