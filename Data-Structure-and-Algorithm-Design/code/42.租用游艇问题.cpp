#include <iostream>
#include <vector>

using namespace std;

int calculateMinRent(vector<vector<int>>& m, int N) 
{
	for(int i = N; i >= 1; i--)
    {
		for(int j = i + 1; j <= N; j++)
        {
			for(int k = i + 1; k < j; k++)
            {
				int temp = m[i][k] + m[k][j];
				
				if(temp < m[i][j])
                {
					m[i][j] = temp;
				}	
			} 
		} 	
	} 
    return m[1][N];
}

int main() {
    int N;
    cin >> N;

    vector<vector<int>> m(N, vector<int>(N, 0));
    for(int i = 1; i <= N; i++)
    {
		for(int j = i + 1; j <= N; j++)
        {
			cin >> m[i][j];
		}
	}
	
	cout << calculateMinRent(m, N) << endl;
    return 0;
}
