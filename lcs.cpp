#include <iostream>
#include <string>
using namespace std;

// Returns length of LCS for X[0..m-1], Y[0..n-1]
int lcs(string X, string Y, int m, int n)
{
    if (m == 0 || n == 0)
        return 0;
    if (X[m - 1] == Y[n - 1])
        return 1 + lcs(X, Y, m - 1, n - 1);
    else
        return max(lcs(X, Y, m, n - 1),
                   lcs(X, Y, m - 1, n));
}

int main()
{
    string S1, S2;

    cout << "Enter string S1: ";
    cin >> S1;

    cout << "Enter string S2: ";
    cin >> S2;

    int m = S1.size();
    int n = S2.size();

    cout << "Length of LCS is " << lcs(S1, S2, m, n);

    return 0;
}
