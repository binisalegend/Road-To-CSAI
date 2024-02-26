#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void printOptimalParenthesis(vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        cout << ")";
    }
}

void matrixChainOrder(vector<int>& p, int n) {
    // int n = p.size() - 1;
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    cout << m[1][n] << endl;
    if (n == 1) {
        cout << "(A1)" << endl;
        return;
    }
    printOptimalParenthesis(s, 1, n);
    cout << endl;
}

int main() {
    int N;
    cin >> N;
    vector<int> p(N + 1);
    for (int i = 0; i <= N; i++) {
        cin >> p[i];
    }
    matrixChainOrder(p, N);
    return 0;
}
