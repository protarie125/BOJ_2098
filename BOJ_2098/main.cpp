#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using ul = unsigned long long;

constexpr auto INF = numeric_limits<ll>::max() / 2;

int N;
vvl W;
vvl dp;
ul fitNum;

ll solve(ul p, ul visit) {
	// ����� ��
	if (visit == fitNum) {
		if (0 == W[p][0]) { // ó������ ���ư��� ���� ������
			return INF;
		}

		return W[p][0];
	}

	// DP ����
	if (0 < dp[p][visit]) {
		return dp[p][visit];
	}

	// dp construct
	dp[p][visit] = INF;
	for (auto i = 0; i < N; ++i) {
		if (0 == W[p][i]) { // �� `p -> i`�� ������
			continue;
		}

		const auto vpos = (1ULL << i);
		if (vpos == (visit & vpos)) { // �̹� �湮�ߴٸ�
			continue;
		}

		dp[p][visit] = min(dp[p][visit], W[p][i] + solve(i, visit | vpos));
	}

	return dp[p][visit];
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> N;
	W = vvl(N, vl(N));
	for (auto&& rows : W) {
		for (auto&& x : rows) {
			cin >> x;
		}
	}

	dp = vvl(N, vl(1ULL << N, -1));
	fitNum = (1ULL << N) - 1;

	cout << solve(0ULL, 1ULL);

	return 0;
}